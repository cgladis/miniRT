#include "libft.h"

char	*ft_add_str(char *str1, char *str2)
{
	while (*str1)
		str1++;
	while (*str2)
	{
		*str1 = *str2;
		str1++;
		str2++;
	}
	*str1 = '\0';
	return (str1);
}
