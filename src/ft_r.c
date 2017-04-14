/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:45:11 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/03 14:45:13 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
** recursive function
*/

void		ft_recurse(t_curr *t, int *param, char *options)
{
	DIR		*recurs_dir;
	t_curr	*temp;
	int		*recurs_param;

	if (O_FORMAT == L_FORMAT)
		ft_printf("total %d\n", W_BLOCKS);
	ft_lprint(t, param, options);
	while (t)
	{
		if (ft_strcmp(t->name, ".") != 0 && ft_strcmp(t->name, "..") != 0)
			if ((recurs_dir = opendir(t->path)))
			{
				recurs_param = ft_memalloc(sizeof(int) * 8);
				temp = NULL;
				ft_make_list(&temp, t->path, recurs_param, options);
				ft_printf("\n%s:\n", t->path);
				if (temp)
					ft_recurse(temp, recurs_param, options);
				ft_str_del(&temp);
				ft_memdel((void **)&recurs_param);
				closedir(recurs_dir);
			}
		t = t->next;
	}
}
