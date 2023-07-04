#include <stdio.h>


size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while(*s++)
		++i;//i++一样的
	return (i);//"hello" i = 5
}

int main()
{
	char s[] = "hello\n ha";
	char b[10];
	int i = 0;
	while (s[i] != '\n')
	{
		b[i] = s[i];
		printf("%c + %d\n", b[i], i);
		i++;
	}
	return 0;
}
