#include <strings.h>
#include <stdio.h>

int	main(void)
{
	strlen(NULL);
	printf("SEGV");
}
