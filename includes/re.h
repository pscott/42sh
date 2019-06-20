
#define MAX_REGEXP_OBJECTS      30    /* Max number of regex symbols in expression. */
#define MAX_CHAR_CLASS_LEN      40    /* Max length of character-class buffer in.   */


enum { UNUSED, DOT, BEGIN, END, QUESTIONMARK, STAR, PLUS, CHAR, CHAR_CLASS, INV_CHAR_CLASS, DIGIT, NOT_DIGIT, ALPHA, NOT_ALPHA, WHITESPACE, NOT_WHITESPACE, /* BRANCH */ };

typedef struct regex_t
{
	unsigned char  type;   /* CHAR, STAR, etc.                      */
	union
	{
		unsigned char  ch;   /*      the character itself             */
		unsigned char* ccl;  /*  OR  a pointer to characters in class */
	};
} regex_t;

/* Typedef'd pointer to get abstract datatype. */
typedef struct regex_t* re_t;


/* Compile regex string pattern to a regex_t-array. */
re_t re_compile(const char* pattern);


/* Find matches of the compiled pattern inside text. */
int  re_matchp(re_t pattern, const char* text);


/* Find matches of the txt pattern inside text (will compile automatically first). */
int  re_match(const char* pattern, const char* text);


