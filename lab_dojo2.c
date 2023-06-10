#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <time.h>


char* rand_string() {
    static const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int size = rand() % 10 + 10;  
    char* string = (char*)malloc((size + 1) * sizeof(char));
    int i;

    for (i = 0; i < size; i++) {
        int index = rand() % (sizeof(chars) - 1); 
        string[i] = chars[index];  
    }

    string[size] = '\0';  

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
	while (ft_strncmp(input, rand_string(), strlen(rand_string())))
	{
		printf("Fail\n");
		input = readline("$> ");
	}
	printf("Boua!\n");

}
