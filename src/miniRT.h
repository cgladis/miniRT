/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:32:44 by cgladis           #+#    #+#             */
/*   Updated: 2021/05/03 17:31:48 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>

# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/src/libft.h"
# include <limits.h>
# include <fcntl.h>
# include <stdarg.h>
# include <pthread.h>

# define DEFAULT_COLOR 0xFFFFFF
# define BACKGROUND_COLOR 0x000000
# define DEFAULT_X 600
# define DEFAULT_Y 600
# define DEFAULT_FOV 70
# define MODE 0
# define NUM_PTHREAD 6

# define BMP_H_SIZE 14
# define BMP_I_SIZE 40

typedef union u_color
{
	unsigned int	color;
	struct s_rgb
	{
		unsigned int	b : 8;
		unsigned int	g : 8;
		unsigned int	r : 8;
	}	t_rgb;
}	t_color;

typedef struct s_matrix
{
	double	sin_x;
	double	cos_x;
	double	sin_y;
	double	cos_y;
	double	sin_z;
	double	cos_z;
}	t_matrix;

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	z;
}	t_coordinates;

typedef struct s_t_minmax
{
	double	t_min;
	double	t_max;
}	t_t_minmax;

typedef struct s_canva
{
	int		x;
	int		y;
	double	ambient;
	t_color	color;
	t_color	obj_color;
	t_color	background_color;
}	t_canva;

typedef struct s_obj
{
	int				number;
	int				identifier;
	t_coordinates	xyz;
	t_coordinates	xyz2;
	t_coordinates	xyz3;
	t_color			rgb;
	t_coordinates	vector_3d;
	double			size1;
	double			size2;
	int				shine;
}	t_obj;

typedef struct s_closest_obj
{
	double	closest_t;
	t_obj	*obj;
}	t_closest_obj;

typedef struct s_vars
{
	void	*mlx;
	void	*img;
	void	*win;
	void	*debug_win;
	void	*color_box;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		bmp;
	int		need_free;
	int		need_free_win;
	int		potok;
	t_canva	canva;
	t_list	*obj;
	t_obj	*current_camera;
	t_obj	*current_obj;
	int		mode;
	int		read_a;
	int		read_r;
	int		no_camera;
	char	**arg;
}	t_vars;

typedef struct s_param_obj
{
	t_coordinates	coordinates;
	t_coordinates	coordinates1;
	t_coordinates	coordinates2;
	t_coordinates	vector_3d;
	double			size1;
	double			size2;
	t_color			color;
}	t_param_obj;

typedef struct s_xy
{
	int	x;
	int	y;
}	t_xy;

typedef struct s_trace_obj
{
	t_obj			*obj;
	t_closest_obj	shaddow_obj;
	t_coordinates	l;
	t_coordinates	r;
	t_coordinates	v;
	double			n_dot_l;
	double			r_dot_v;
}	t_trace_obj;

typedef struct s_ray_tracing
{
	int				k;
	int				debuger_trace;
	t_vars			*vars;
	int				x;
	int				y;
	t_coordinates	ray;
	t_coordinates	camera;
	t_coordinates	camera_vector;
	t_closest_obj	closest_obj;
	t_coordinates	p;
	t_coordinates	normal;
	t_list			*lights;
}	t_ray_tracing;

t_list			*new_camera(t_list *list_obj, t_param_obj camera, t_vars *vars);

t_list			*new_sphere(t_list *list_obj, t_param_obj sphere, t_vars *vars);

t_list			*new_plane(t_list *list_obj, t_param_obj plane, t_vars *vars);

t_list			*new_light(t_list *list_obj, t_param_obj light, t_vars *vars);

void			my_mlx_pixel_put(t_vars *data, int x, int y, int color);

t_coordinates	coordinates(double x, double y, double z);

t_coordinates	minus_vector(t_coordinates vector1, t_coordinates vector2);

double			calc_length_to_canva(double FOV, int length_x);

t_coordinates	norm_vector(t_coordinates vector);

t_coordinates	coordinates_point(t_coordinates camera,
					t_coordinates norm_vector, double t);

t_color			get_color(double t, t_coordinates vector_point,
					 t_obj *obj, t_ray_tracing *data);

double			scalar_product(t_coordinates v1, t_coordinates v2);

t_coordinates	vector_na_chislo(t_coordinates vector, double t);

t_coordinates	light_plane(t_vars *vars, t_obj *obj, t_coordinates p);

double			vector_length(t_coordinates vector);

double			intersect_ray_sphere(t_coordinates camera,
					t_coordinates vector_point, t_obj *obj);

double			intersect_ray_plane(t_coordinates camera,
					t_coordinates vector_point, t_obj *obj);

t_coordinates	multi_vector(t_coordinates v1, t_coordinates v2);

t_coordinates	norm_vector_obj(int x, int y, t_vars *vars);

t_matrix		get_matrix(t_coordinates vector);

t_coordinates	rotate_vector(t_coordinates vector, t_matrix matrix);

t_coordinates	rotate_vector_v1(t_coordinates vector, t_vars *vars);

t_color			multi_color(t_color color, t_color light_color, double n);

t_color			plus_color(t_color color, t_color light_color, double n);

int				get_nomber_obj(t_list *list_obj);

void			print_obj(t_vars *vars);

t_obj			*last_obj(t_list *list_obj);

int				get_number_obj(t_list *list_obj, t_vars *vars);

void			export(t_vars *vars, char *file_mame);

char			*delete_n(char *str);

char			*delete_str(char *str, char *c);

int				import(t_vars *vars, char *file_name);

void			view_scene(t_vars *vars);

void			free_vars(t_vars *vars);

void			remove_content(void *obj);

void			debug(t_vars *vars);

void			refresh_debug_win(t_vars *vars);

t_closest_obj	closest_intersection(t_coordinates camera, t_coordinates ray,
					t_ray_tracing *data, t_t_minmax t_minmax);

char			*get_name_obj(int identifier, char *str);

void			open_color_box(t_vars *vars);

int				edit_functions(int keycode, t_vars *vars);

t_list			*new_square(t_list *list_obj, t_param_obj square, t_vars *vars);

t_list			*new_triangle(t_list *list_obj, t_param_obj triangle,
					t_vars *vars);

t_list			*new_cylinder(t_list *list_obj, t_param_obj cylinder,
					t_vars *vars);

t_coordinates	sum_vector(t_coordinates vector1, t_coordinates vector2);

double			intersect_ray_square(t_coordinates camera,
					t_coordinates vector_point, t_obj *obj);

double			intersect_ray_triangle(t_coordinates camera,
					t_coordinates vector_point, t_obj *obj);

double			intersect_ray_cylinder(t_coordinates camera,
					t_coordinates vector_point, t_obj *obj);

t_color			umn_color(t_color color, double n);

t_color			new_color(int r, int g, int b);

t_color			add_color(t_color color1, t_color color2);

t_color			gradient(t_color color1, t_color color2);

t_coordinates	light_plane(t_vars *vars, t_obj *obj, t_coordinates p);

t_coordinates	light_triangle(t_vars *vars, t_obj *obj, t_coordinates p);

t_coordinates	light_square(t_vars *vars, t_obj *obj, t_coordinates p);

t_coordinates	light_cylinder(t_vars *vars, t_obj *obj, t_coordinates p);

void			remove_obj(int number, t_vars *vars);

void			draw_obj(t_vars *vars);

int				bmp_header(t_vars *vars, char *filename);

void			error_and_exit(const char *str, t_vars *vars);

void			draw_obj_light(t_vars *vars);

void			clear_vars(t_vars *vars);

void			trace_ray(int i, int j, t_ray_tracing *data);

t_color			compute_lighting(t_ray_tracing *data, t_obj *obj);

int				read_camera(char *str, t_vars *vars);

int				read_cylinder(char *str, t_vars *vars);

int				read_light(char *str, t_vars *vars);

int				read_sphere(char *str, t_vars *vars);

int				read_plane(char *str, t_vars *vars);

int				read_triangle(char *str, t_vars *vars);

int				read_coordinates(t_coordinates *coordinates, char *str);

int				read_color(t_color *color, char *str);

int				read_ambient(char *str, t_vars *vars);

int				check_resolution(t_vars *vars, int x, int y);

int				read_resolution(char *str, t_vars *vars);

int				read_int_rev(int *n, char *str);

int				read_int(int *n, char *str);

int				read_float_1(double *n, char *str);

int				read_float_2(double *n, char *str);

int				read_float(double *n, char *str);

int				define_obj(char *str);

void			write_float(int fd, double num, int precision);

void			write_int(int fd, int num);

void			write_coordinates(int fd, t_coordinates coordinates);

void			write_color(int fd, t_color color);

void			write_ambient(int fd, double n, t_color color);

void			write_resolution(int fd, int x, int y);

void			write_sphere(int fd, t_obj *obj);

void			write_camera(int fd, t_obj *obj);

void			write_light(int fd, t_obj *obj);

void			write_plane(int fd, t_obj *obj);

void			write_squere(int fd, t_obj *obj);

void			write_cylinder(int fd, t_obj *obj);

void			write_triangle(int fd, t_obj *obj);

char			*rt_get_coordinates(t_coordinates coordinates);

char			*rt_get_int(int num);

char			*rt_get_float(double num, int precision);

char			*rt_get_color(t_color color);

int				clamp(int data, int min, int max);

int				close_w(t_vars *vars);

void			add_sphere_mode(t_vars *vars, int keycode, t_xy xy, int mouse);

void			add_square_mode(t_vars *vars, int keycode, t_xy xy, int mouse);

void			add_triangle_mode(t_vars *vars, int keycode, t_xy xy,
					int mouse);

void			add_cylinder_mode(t_vars *vars, int keycode, t_xy xy,
					int mouse);

void			add_plane_mode(t_vars *vars, int keycode, t_xy xy, int mouse);

void			add_light_mode(t_vars *vars, int keycode, t_xy xy, int mouse);

void			edit_mode(int keycode, int x, int y, t_vars *vars);

int				loop_hook(t_vars *vars);

int				mouse_press_hook(int key_code, t_xy xy, t_vars *vars,
					int press_key);

int				push_mouse_key(int keycode, int x, int y, t_vars *vars);

int				release_mouse_key(int keycode, int x, int y, t_vars *vars);

void			create_sphere(t_vars *vars, int x, int y);

void			create_square(t_vars *vars, int x, int y);

void			create_triangle(t_vars *vars, int x, int y);

void			create_cylinder(t_vars *vars, int x, int y);

void			create_camera(t_vars *vars);

void			create_plane(t_vars *vars, int x, int y);

void			create_light(t_vars *vars, int x, int y);

void			move_camera_standart(t_vars *vars, int keycode, int x, int y);

void			move_camera(t_vars *vars, int x, int y, int keycode);

void			move_obj(t_vars *vars, int keycode, int x, int y);

void			next_camera(t_vars *vars);

t_color			read_color_hex(char *str);

char			is_simbol(int keycode);

int				read_param(char *arg, const char *param);

void			edit_scene(t_vars *vars);

void			save_bmp(t_vars *vars);

char			*rt_to_bmp(char *str);

char			*add_rt(char *str);

char			*add_bmp(char *str);

void			clear_ray_tracing_data(t_ray_tracing *data);

double			get_t(t_obj *obj, t_coordinates ray,
					t_coordinates camera);

int				read_square(char *str, t_vars *vars);

#endif
