#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>
#include <time.h>


int	pegadinha()
{
	printf("pegadinha garai\n");
	return (0);
}

char	*rand_string(int i)
{
	char *string;

	string = strdup("la ele");
	return string;
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	current;

	current = 0;
	while ((s1[current] || s2[current]) && current < n)
	{
		if (s1[current] != s2[current])
			return ((unsigned char)s1[current] - (unsigned char)s2[current]);
		current++;
	}
	return (0);
}

int	main( void )
{
	char 	*input;

	input = readline("minihell - $> ");
	while (ft_strncmp(input, rand_string(pegadinha()), strlen(rand_string(0))))
	{
		printf("Fail\n");
		input = readline("$> ");
	}
	printf("Boua!\n");

}
