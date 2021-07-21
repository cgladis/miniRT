#include "miniRT.h"

int	get_number_obj(t_list *list_obj, t_vars *vars)
{
	int	i;

	i = 0;
	while (list_obj)
	{
		i++;
		list_obj = list_obj->next;
	}
	vars->need_free = 1;
	return (i);
}

t_obj	*last_obj(t_list *list_obj)
{
	t_obj	*obj;

	obj = ft_lstlast(list_obj)->content;
	return (obj);
}

char	*get_name_obj(int identifier, char *str)
{
	*str = '\0';
	if (identifier == 0)
		ft_strlcpy(str, "Camera", 7);
	if (identifier == 1)
		ft_strlcpy(str, "Sphere", 7);
	if (identifier == 2)
		ft_strlcpy(str, "Plane", 6);
	if (identifier == 3)
		ft_strlcpy(str, "Triangle", 9);
	if (identifier == 4)
		ft_strlcpy(str, "Square", 7);
	if (identifier == 5)
		ft_strlcpy(str, "Cylinder", 9);
	if (identifier == 9)
		ft_strlcpy(str, "Light", 6);
	return (str);
}
