#include "miniRT.h"

t_list	*new_camera(t_list *list_obj, t_param_obj camera, t_vars *vars)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->number = get_number_obj(list_obj, vars);
	obj->identifier = 0;
	obj->xyz = camera.coordinates;
	obj->vector_3d = norm_vector(camera.vector_3d);
	obj->size1 = camera.size1;
	obj->size2 = calc_length_to_canva(camera.size1, vars->canva.x);
	vars->no_camera = 0;
	return (ft_lstnew(obj));
}

t_list	*new_plane(t_list *list_obj, t_param_obj plane, t_vars *vars)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->number = get_number_obj(list_obj, vars);
	obj->identifier = 2;
	obj->xyz = plane.coordinates;
	obj->vector_3d = norm_vector(plane.vector_3d);
	obj->rgb = plane.color;
	return (ft_lstnew(obj));
}

t_list	*new_light(t_list *list_obj, t_param_obj light, t_vars *vars)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->number = get_number_obj(list_obj, vars);
	obj->identifier = 9;
	obj->xyz = light.coordinates;
	obj->size1 = light.size1;
	obj->rgb = light.color;
	return (ft_lstnew(obj));
}

t_list	*new_sphere(t_list *list_obj, t_param_obj sphere, t_vars *vars)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->number = get_number_obj(list_obj, vars);
	obj->identifier = 1;
	obj->xyz = sphere.coordinates;
	obj->rgb = sphere.color;
	obj->size1 = sphere.size1;
	return (ft_lstnew(obj));
}

t_list	*new_triangle(t_list *list_obj, t_param_obj triangle, t_vars *vars)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->number = get_number_obj(list_obj, vars);
	obj->identifier = 3;
	obj->xyz = triangle.coordinates;
	obj->xyz2 = triangle.coordinates1;
	obj->xyz3 = triangle.coordinates2;
	obj->rgb = triangle.color;
	return (ft_lstnew(obj));
}
