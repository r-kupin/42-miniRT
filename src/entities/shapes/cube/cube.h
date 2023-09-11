/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/11 16:26:31 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "../../../../heads_global/minirt.h"

typedef struct cube
{
	t_tuple		*center;
	double		side;
	t_tuple		*color;
	t_tuple		*norm;
	//t_matrix	*trans;
	t_matrix	trans;
}	t_cube;

t_cube	*cube_cube(void);
void	cube_free(t_cube *c);
t_tuple	*cube_normal_at(t_tuple *p);

#endif
