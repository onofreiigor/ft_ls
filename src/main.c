/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <okosiako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:18:53 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/12 15:31:24 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
** reads av parametrs
** makes options array
** makes lists for errors, files and directories
*/

int		main(int ac, char **av)
{
	t_list	*lists[3];
	char	*options;
	int		av_ind;
	int		fl_er;

	av_ind = 3;
	while (av_ind - 1 >= 0)
		lists[--av_ind] = NULL;
	options = ft_strnew(6);
	ft_memset(options, '0', sizeof(char) * 6);
	while (++av_ind < ac && av[av_ind][0] == '-' && (av[av_ind][1]))
		ft_options(av[av_ind], options);
	if (av_ind == ac)
		ft_ladd_2(&DIR_LIST, ft_lstnew(".", ft_strlen(".") + 1));
	else
		while (av_ind++ < ac)
			ft_dir_list(&DIR_LIST, &ERROR_LIST, &FILE_LIST, av[av_ind - 1]);
	fl_er = (ERROR_LIST || FILE_LIST) ? 1 : 0;
	ft_work_er_list(&ERROR_LIST);
	ft_work_fl_list(&FILE_LIST, options);
	ft_work_dir_list(&DIR_LIST, options, fl_er);
	ft_strdel(&options);
	return (0);
}
