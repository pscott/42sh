int main(void)
{
	char *s;

	char *s2;
	s = strdup("ls");
	s2 = strdup("lsapp");
	printf("%d", strcmp(s, s2));
	return (0);
}
