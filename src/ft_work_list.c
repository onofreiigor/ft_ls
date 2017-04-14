/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <okosiako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:02:03 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/12 17:29:47 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
** everything for working with lists
*/

void		ft_make_list(t_curr **res, char *path, int *param, char *options)
{
	DIR				*curr_dir;
	struct dirent	*temp_dir;
	t_curr			*temp;

	if ((curr_dir = opendir(path)))
	{
		while ((temp_dir = readdir(curr_dir)))
		{
			if (temp_dir->d_name[0] == '.' && O_FILES == '0')
				continue;
			else if (O_FILES == A_FORMAT && (!ft_strcmp(temp_dir->d_name, ".")
			|| !ft_strcmp(temp_dir->d_name, "..")))
				continue;
			temp = ft_lcreate(temp_dir->d_name, path);
			ft_make_param(temp, param);
			ft_ladd(res, temp, options);
		}
		closedir(curr_dir);
	}
	else
	{
		temp = ft_lcreate(path, ".");
		ft_make_param(temp, param);
		ft_ladd(res, temp, options);
	}
}

/*
** create a new element
** takes a name of file or directory
*/

t_curr		*ft_lcreate(char *name, char *path)
{
	t_curr			*new;
	acl_entry_t		dummy;
	char			*temp_shit;

	new = ft_memalloc(sizeof(t_curr));
	new->name = ft_strdup(name);
	new->path = ft_strjoin_n(path, "/", new->name);
	lstat(new->path, &(new->info));
	new->pw_name = ft_strdup(getpwuid(new->info.st_uid)->pw_name);
	new->gr_name = ft_strdup(getgrgid(new->info.st_gid)->gr_name);
	new->lx = listxattr(new->path, 0, 0, XATTR_NOFOLLOW);
	temp_shit = ft_strnew(sizeof(char) * 1024);
	(S_ISLNK(new->info.st_mode)) ? readlink(new->path, temp_shit, 1024) : 0;
	new->link_path = ft_strjoin(" -> ", temp_shit);
	ft_strdel(&temp_shit);
	new->acl = acl_get_link_np(new->path, ACL_TYPE_EXTENDED);
	if (new->acl && acl_get_entry(new->acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(new->acl);
		new->acl = NULL;	
	}
	return (new);
}

/*
** function for compering
*/

static	int	cmp(t_curr *a, t_curr *b, char kind)
{
	if (kind == T_SORT)
	{
		if (a->info.st_mtime == b->info.st_mtime)
		{
			if (a->info.st_mtimespec.tv_nsec == b->info.st_mtimespec.tv_nsec)
				kind = 0;
			else
				return (a->info.st_mtimespec.tv_nsec >
					b->info.st_mtimespec.tv_nsec ? 1 : 0);
		}
		else
			return (a->info.st_mtime > b->info.st_mtime ? 1 : 0);
	}
	else if (kind == S_SORT)
	{
		if (a->info.st_size != b->info.st_size)
			return (a->info.st_size > b->info.st_size ? 1 : 0);
		kind = 0;
	}
	if (kind == '0')
		return (ft_strcmp(a->name, b->name) < 0 ? 1 : 0);
	return (1);
}

/*
** add a new element to list in sort order
*/

void		ft_ladd(t_curr **root, t_curr *new, char *options)
{
	t_curr *temp;

	if (!new)
		return ;
	if (!*root || (O_REVERS != '0' ?
		!cmp(new, (*root), O_SORT) : cmp(new, (*root), O_SORT)))
	{
		new->next = *root;
		*root = new;
	}
	else
	{
		temp = *root;
		while (temp->next && (O_REVERS != '0' && O_SORT != N_SORT ?
			!cmp(temp->next, new, O_SORT) : cmp(temp->next, new, O_SORT)))
			temp = temp->next;
		new->next = temp->next;
		temp->next = new;
	}
}

/*
** delete a struct t_curr
*/

void		ft_str_del(t_curr **t)
{
	t_curr *copy;

	if (*t)
	{
		while (*t)
		{
			copy = *t;
			ft_memdel((void **)&(copy->name));
			ft_memdel((void **)&(copy->path));
			ft_memdel((void **)&(copy->link_path));
			ft_memdel((void **)&(copy->pw_name));
			ft_memdel((void **)&(copy->gr_name));
			*t = (*t)->next;
			ft_memdel((void **)&copy);
		}
	}
}
