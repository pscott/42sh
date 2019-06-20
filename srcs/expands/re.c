#include "re.h"
#include <stdio.h>
#include "cmd_parsing.h"


/* Private function declarations: */
static int matchpattern(regex_t* pattern, const char* text);
static int matchcharclass(char c, const char* str);
static int matchstar(regex_t p, regex_t* pattern, const char* text);
static int matchplus(regex_t p, regex_t* pattern, const char* text);
static int matchone(regex_t p, char c);
static int matchdigit(char c);
static int matchalpha(char c);
static int matchwhitespace(char c);
static int matchmetachar(char c, const char* str);
static int matchrange(char c, const char* str);
static int ismetachar(char c);


int re_match(const char* pattern, const char* text)
{
  return re_matchp(re_compile(pattern), text);
}

int	find_matchs(t_st_dir *st_dir, t_st_glob *st_glob, char *str)
{
	int	ret;
	ft_dprintf(2, "%s , %s", st_dir->to_find, st_dir->current->d_name);
	ret = re_match(st_dir->to_find, st_dir->current->d_name);
	ft_dprintf(2, " %d\n", ret);
	return (ret);
}

int re_matchp(re_t pattern, const char* text)
{
	int		idx;
  if (pattern != 0)
  {
    {
     	idx = -1;
      do
      {
        idx += 1;
        
        if (matchpattern(pattern, text))
        {
          if (text[0] == '\0')
            return (-1);
        
          return (idx);
        }
      }
      while (*text++ != '\0');
    }
  }
  return (-1);
}

re_t re_compile(const char* pattern)
{
  static regex_t re_compiled[MAX_REGEXP_OBJECTS];
  static unsigned char ccl_buf[MAX_CHAR_CLASS_LEN];
  int	ccl_bufidx;

  char	c;
  int	i;
  int	j;
  int	buf_begin;

  i = 0;
  j = 0;
  ccl_bufidx = 1;
  while (pattern[i] != '\0' && (j + 1 < MAX_REGEXP_OBJECTS))
  {
    c = pattern[i];
	if (c == '*')
		re_compiled[j].type = STAR;
	else if (c == '?')
		re_compiled[j].type = QUESTIONMARK;
	else if (c == '[')
      {
        buf_begin = ccl_bufidx;
        re_compiled[j].type = CHAR_CLASS;
        while ((pattern[++i] != ']') && (pattern[i] != '\0'))
        {
          if (ccl_bufidx >= MAX_CHAR_CLASS_LEN)
          {
              //ft_dprintf(2, "Your regex search is too long!\n");
              return (0);
          }
          ccl_buf[ccl_bufidx++] = pattern[i];
        }
        if (ccl_bufidx >= MAX_CHAR_CLASS_LEN)
        {
            //ft_dprintf(2, "Your regex search is too long!\n");
            return (0);
        }
        ccl_buf[ccl_bufidx++] = 0;
        re_compiled[j].ccl = &ccl_buf[buf_begin];
      } 
	else
      {
        re_compiled[j].type = CHAR;
        re_compiled[j].ch = c;
      } 
    i += 1;
    j += 1;
  }
  re_compiled[j].type = UNUSED;
  return (re_t) re_compiled;
}

void re_print(regex_t* pattern)
{
  const char* types[] = { "UNUSED", "DOT", "BEGIN", "END", "QUESTIONMARK", "STAR", "PLUS", "CHAR", "CHAR_CLASS", "INV_CHAR_CLASS", "DIGIT", "NOT_DIGIT", "ALPHA", "NOT_ALPHA", "WHITESPACE", "NOT_WHITESPACE", "BRANCH" };

  int i;
  for (i = 0; i < MAX_REGEXP_OBJECTS; ++i)
  {
    if (pattern[i].type == UNUSED)
    {
      break;
    }

    printf("type: %s", types[pattern[i].type]);
    if (pattern[i].type == CHAR_CLASS)
    {
      printf(" [");
      int j;
      char c;
      for (j = 0; j < MAX_CHAR_CLASS_LEN; ++j)
      {
        c = pattern[i].ccl[j];
        if ((c == '\0') || (c == ']'))
        {
          break;
        }
        printf("%c", c);
      }
      printf("]");
    }
    else if (pattern[i].type == CHAR)
    {
      printf(" '%c'", pattern[i].ch);
    }
    printf("\n");
  }
}


static int matchrange(char c, const char* str)
{
  return ((c != '-') && (str[0] != '\0') && (str[0] != '-') &&
         (str[1] == '-') && (str[1] != '\0') &&
         (str[2] != '\0') && ((c >= str[0]) && (c <= str[2])));
}


static int matchcharclass(char c, const char* str)
{
  do
  {
    if (matchrange(c, str))
      return (1);
    else if (c == str[0])
    {
      if (c == '-')
        return ((str[-1] == '\0') || (str[1] == '\0'));
      else
        return (1);
    }
  }
  while (*str++ != '\0');
  return (0);
}

static int matchone(regex_t p, char c)
{
	if (p.type == CHAR_CLASS)
		return (matchcharclass(c, (const char*)p.ccl));
	else
		return (p.ch == c);
}

static int matchstar(regex_t p, regex_t* pattern, const char* text)
{
  do
  {
    if (matchpattern(pattern, text))
      return (1);
  }
  while ((text[0] != '\0') && matchone(p, *text++));
  return (0);
}

static int matchplus(regex_t p, regex_t* pattern, const char* text)
{
  while ((text[0] != '\0') && matchone(p, *text++))
  {
    if (matchpattern(pattern, text))
      return (1);
  }
  return (0);
}

static int matchquestion(regex_t p, regex_t* pattern, const char* text)
{
  if (p.type == UNUSED)
    return (1);
  if (matchpattern(pattern, text))
      return (1);
  if (*text && matchone(p, *text++))
    return (matchpattern(pattern, text));
  return 0;
}


static int matchpattern(regex_t* pattern, const char* text)
{
  do
  {
    if ((pattern[0].type == UNUSED) || (pattern[1].type == QUESTIONMARK))
    {
      return (matchquestion(pattern[0], &pattern[2], text));
    }
    else if (pattern[1].type == STAR)
    {
      return (matchstar(pattern[0], &pattern[2], text));
    }
  }
  while ((text[0] != '\0') && matchone(*pattern++, *text++));
  return (0);
}
