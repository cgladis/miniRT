#include "libft.h"

char	*ft_cont_str(char *str1, char *str2)
{
	char	*result;

	result = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (result);
}
