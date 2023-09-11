/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/11 13:15:59 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H
# include "../../../heads_global/minirt.h"

/*
typedef struct shape
{
	char		type;
	t_matrl		*matrl;
	t_matrix	*trans;
	void		*shape;
}	t_shape;
*/
typedef struct shape
{
	char		type;
	t_matrl		*matrl;
	t_matrix	trans;
	void		*shape;
}	t_shape;

t_shape	*make_shape(char type, void *shape_itself);
void	*set_transform(t_shape *sh, t_matrix *trans);
t_tuple	*shape_normal_at(t_shape *sh, t_tuple *p);
void	free_shape(t_shape *s);

#endif