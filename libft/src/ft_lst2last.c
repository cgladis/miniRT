#include "libft.h"

t_list2	*ft_lst2last(t_list2 *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
