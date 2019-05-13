#include "libft.h"
#include "line_editing.h"

int		compare_entry(char *s, char *n)
{
	int i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	if (!s)
		return (1);
	while (s && is_white_spaces(s[i]))
		i++;
	len = ft_strlen(s - i + 1);
	while (len-- && s && n[j] && s[i] == n[j])
	{
		j++;
		i++;
	}
	return (s[i] - n[j]);
}

int		compare_entry2(char *s, char *n)
{
	int i;
	int k;

	k = 0;
	i = 0;
	if (!s || !n)
		return (1);
	if (s[0] != '.' && (n[0] == '.' || (n[0] == '.' && n[1] == '.')))
		return (0);
	while (s[k] && is_white_spaces(s[k]))
		k++;
	while (s[k] && n[i] && is_same_char(s[k], n[i]))
	{
		k++;
		i++;
	}
	if (!s[k])
		return (1);
	return (0);
}
