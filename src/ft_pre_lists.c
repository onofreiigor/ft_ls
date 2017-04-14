/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:08:36 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/10 13:08:39 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
** makes list with names of directories, files and errors
*/

void	ft_dir_list(t_list **dir, t_list **error, t_list **file, const char *av)
{
	DIR			*curr_dir;
	struct stat	check;

	if (!(curr_dir = opendir(av)))
	{
		if (stat(av, &check))
			ft_ladd_2(error, ft_lstnew((void *)av, ft_strlen(av) + 1));
		else
			ft_ladd_2(file, ft_lstnew((void *)av, ft_strlen(av) + 1));
	}
	else
	{
		ft_ladd_2(dir, ft_lstnew((void *)av, ft_strlen(av) + 1));
		closedir(curr_dir);
	}
}

/*
** works with list of directories
*/

void	ft_work_dir_list(t_list **dir, char *options, int files)
{
	t_curr	*t;
	t_list	*address;
	int		*param;

	address = *dir;
	while (*dir)
	{
		t = NULL;
		param = ft_memalloc(sizeof(int) * 8);
		ft_make_list(&t, (char *)(*dir)->content, param, options);
		files ? ft_printf("\n") : 0;
		if (ft_lstlen(address) > 1 || files)
			ft_printf("%s:\n", (char *)(*dir)->content);
		if (O_FORMAT == L_FORMAT && O_RECURS == '0')
			ft_printf("total %d\n", W_BLOCKS);
		O_RECURS == RECURS ?
				ft_recurse(t, param, options) : ft_lprint(t, param, options);
		ft_str_del(&t);
		ft_memdel((void **)&param);
		*dir = (*dir)->next;
		(*dir) && !files ? ft_printf("\n") : 0;
	}
	ft_str_list(&address);
}

/*
** works with lists of files
*/

void	ft_work_fl_list(t_list **files, char *options)
{
	t_curr	*t;
	t_list	*address;
	int		*param;

	address = *files;
	t = NULL;
	param = ft_memalloc(sizeof(int) * 8);
	while (*files)
	{
		ft_make_list(&t, (char *)(*files)->content, param, options);
		*files = (*files)->next;
	}
	ft_lprint(t, param, options);
	ft_memdel((void **)&param);
	ft_str_del(&t);
	ft_str_list(&address);
}

/*
** works with list of errors
*/

void	ft_work_er_list(t_list **error)
{
	t_list			*address;

	address = *error;
	while (*error)
	{
		ft_errors((char *)(*error)->content, 0, 2);
		*error = (*error)->next;
	}
	ft_str_list(&address);
}
