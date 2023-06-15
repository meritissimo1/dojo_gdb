// TO SOLVE:
//
// Ctrl-D -> Has a Segfault

#include "libft/includes/get_next_line.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"

int outra_pegadinha(int i)
{
	ft_print("entre aqui");
	return(i);
}

int	pegadinha(int i)
{
	ft_print("pegadinha garai");
	return (0);
}

void	*rand_string(int i)
{
	char *string;

	string = ft_strdup("la ele");
	return string;
}

int	main( void )
{
	char 	*input;
	void	*result;
	
	result = rand_string(pegadinha(42));
	ft_printf("$> ");
	input = get_next_line(0);
	while (ft_strncmp(input, result, ft_strlen(result)))
	{
		ft_print("Fail");
		ft_printf("$> ");
		input = get_next_line(0);
	}
	ft_print("Boua!");
}
