#include "miniRT.h"

int	read_float_1(double *n, char *str)
{
	int	kol;

	kol = 0;
	*n = 0;
	while (ft_isdigit(*str))
	{
		*n = *n * 10 + *str - '0';
		kol += 1;
		str++;
	}
	return (kol);
}

int	read_float_2(double *n, char *str)
{
	int	kol;

	kol = 0;
	*n = 0.0;
	if (ft_isdigit(*str))
	{
		kol = read_float_2(n, str + 1);
		*n = (*n + *str - '0') * 0.1;
		kol += 1;
	}
	return (kol);
}

char	*read_float_3(char *str, int *minus)
{
	if (*str == '-')
	{
		*minus = -1;
		str++;
	}
	return (str);
}

int	read_float(double *n, char *str)
{
	int		minus;
	int		kol;
	int		kol1;
	double	tale;

	minus = 1;
	str = read_float_3(str, &minus);
	kol = read_float_1(n, str);
	str = str + kol;
	if (*str == '.')
	{
		kol1 = read_float_2(&tale, ++str);
		if (kol1 == 0)
			return (0);
		kol = kol + kol1 + 1;
		*n = *n + tale;
	}
	if (kol > 21)
		return (0);
	if (kol > 0 && minus == -1)
		kol++;
	*n = *n * minus;
	return (kol);
}
