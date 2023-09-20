/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 19:19:16by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	add_intersection(t_intersection *new_elem,
						t_intersection_list **list)
{
	t_intersection_list	*nl;
	int					i;

	i = -1;
	nl = intersection_list_make((*list)->size + 1);
	while (++i < (*list)->size)
		nl->list[i] = (*list)->list[i];
	nl->list[i] = new_elem;
	if ((*list)->list)
		free((*list)->list);
	free(*list);
	*list = nl;
}

t_intersection_list	*intersect_world(t_ray *r, t_world *w, t_tmp_m *m_tmp)
{
	int					i;
	int					j;
	int					size;

	w->unsorted = malloc(sizeof(t_intersection_list *) * w->shape_counter);
	i = w->shape_counter;
	size = 0;
	while (--i >= 0)
	{
		w->unsorted[i] = intersect_shape(w->shapes[i], r, m_tmp);
		size += w->unsorted[i]->size;
	}
	w->merged = intersection_list_make(size);
	size = -1;
	i = -1;
	while (++i < w->shape_counter)
	{
		j = -1;
		while (++j < w->unsorted[i]->size)
			w->merged->list[++size] = w->unsorted[i]->list[j];
		free(w->unsorted[i]->list);
		free(w->unsorted[i]);
	}
	free(w->unsorted);
	return (w->merged);
}

void	precomp(t_computations	*comps, t_intersection *i, t_ray *r, t_tmp_m *m_tmp)
{
	t_tuple	tmp;

	comps->t = i->t;
	comps->shape = i->shape;
	ray_position(&comps->point, r, i->t);
	tuple_negate(&comps->eyev, &r->dir);
	shape_normal_at(&comps->normv, i->shape, &comps->point, m_tmp);

	if (tuple_dot_product(&comps->normv, &comps->eyev) < 0)
	{
		comps->inside = 1;
		tuple_negate(&comps->normv, &comps->normv);
	}
	else
		comps->inside = 0;
	tuple_scalar_multiply(&tmp, &comps->normv, 0.0001);
	tuple_add(&comps->overpoint, &comps->point, &tmp);
}

void	shade_hit(t_world *w, t_computations *cs, t_light *current, t_tmp_m *m_tmp)
{
	make_l_p(&m_tmp->pack, current, cs);
	lightning(&m_tmp->tmp_color, &m_tmp->pack,
			in_shadow(w, &cs->overpoint, current, m_tmp));
}

void	color_at(t_world *w, t_ray *r, t_tmp_m *m_tmp)
{
	t_intersection_list	*l;
	t_intersection		*i;
	t_computations		c;
	//t_tuple				tmp_color1;
	t_tuple				tmp_color2;
	int					j;

	j = -1;
	l = intersect_world(r, w, m_tmp);
	i = hit(l);
	if (!i)
		tuple_color(&m_tmp->color, 0, 0, 0);
	else
	{
		precomp(&c, i, r, m_tmp);
		shade_hit(w, &c, &w->ambienace, m_tmp);
		tuple_copy(&tmp_color2, &m_tmp->tmp_color);
		//free(c.shape);
			/* DEBUG */
			printf("\n");
			printf("\t\tcolor :");
			print_tuple(&m_tmp->tmp_color);
			/* ***** */

		while (++j < w->lights_counter)
		{
			precomp(&c, i, r, m_tmp);

			shade_hit(w, &c, w->lights[j], m_tmp);
			//tuple_copy(&tmp_color2, &m_tmp->color);
			tuple_add(&m_tmp->color, &m_tmp->tmp_color, &tmp_color2);

			/* DEBUG */
			//printf("\n");
			//printf("\t\tcolor :");
			//print_tuple(&m_tmp->color);
			/* ***** */

			//free(c.shape);
		}
	}
	free(i);
}
