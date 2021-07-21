#include "miniRT.h"

char	is_simbol(int keycode)
{
	int		key_code[38];
	int		i;
	char	key;

	ft_memcpy(key_code, (int [38]){29, 18, 19, 20, 21, 23, 22, 26, 28, 25,
		0, 11, 8, 2, 14, 3, 5, 4, 34, 38, 40, 37, 46, 45, 31, 35, 12,
		15, 1, 17, 32, 9, 13, 7, 16, 6, 36, 49}, 38 * 4);
	key = 0;
	i = 0;
	while (i < 38)
	{
		if (key_code[i] == keycode)
		{
			if (i < 10)
				key = (i + '0');
			else if (i >= 10 && i < 36)
				key = i - 10 + 'a';
			else if (i == 36)
				key = '\n';
			else if (i == 37)
				key = ' ';
		}
		i++;
	}
	return (key);
}

t_color	read_color_hex(char *str)
{
	t_color	color;
	int		i;

	color.color = 0;
	i = 0;
	while (i < 6)
	{
		color.color *= 16;
		if (*str >= '0' && *str < '9')
			color.color = color.color + *str - '0';
		if (*str >= 'A' && *str <= 'F')
			color.color = color.color + *str + 10 - 'A';
		if (*str >= 'a' && *str <= 'f')
			color.color = color.color + *str + 10 - 'a';
		i++;
		str++;
	}
	printf("color = %x\n", color.color);
	return (color);
}

char	*add_rt(char *str)
{
	int	n;

	delete_n(str);
	n = ft_strlen(str);
	*(str + n) = '.';
	*(str + n + 1) = 'r';
	*(str + n + 2) = 't';
	*(str + n + 3) = '\0';
	return (str);
}

char	*add_bmp(char *str)
{
	int	n;

	delete_n(str);
	n = ft_strlen(str);
	*(str + n) = '.';
	*(str + n + 1) = 'b';
	*(str + n + 2) = 'm';
	*(str + n + 3) = 'p';
	*(str + n + 4) = '\0';
	return (str);
}

char	*rt_to_bmp(char *str)
{
	*(str + ft_strlen(str) - 3) = '\0';
	add_bmp(str);
	return (str);
}
