/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dif_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <okosiako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:51:53 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/12 14:38:48 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
** creates string with flags
*/

void			ft_options(char *str, char *options)
{
	size_t		ind;

	ind = 0;
	while (++ind && str[ind] && ft_strchr(OPTIONS, str[ind]))
		if (ft_strchr("l1x", str[ind]))
			O_FORMAT = str[ind];
		else if (ft_strchr("tSf", str[ind]))
		{
			O_SORT = str[ind];
			if (O_SORT == N_SORT)
			{
				O_FILES = 'a';
				O_REVERS = 'r';
			}
		}
		else if (str[ind] == R_SORT)
			O_REVERS = str[ind];
		else if (str[ind] == DOT || (str[ind] == A_FORMAT && O_FILES != 'a'))
			O_FILES = str[ind];
		else if (str[ind] == RECURS)
			O_RECURS = str[ind];
		else if (str[ind] == COLORS)
			O_COLORS = str[ind];
	ind != ft_strlen(str) ? ft_errors(0, str[ind], 0) : 0;
}

/*
** counting a width of size column
*/

static void		ft_size(t_curr *temp, int *param)
{
	int	size;
	int	temp_integer;
	int	temp_size;

	size = 2;
	temp_integer = temp->info.st_size;
	COUNTER(temp_integer, 10, size);
	if (S_ISBLK(temp->info.st_mode) || S_ISCHR(temp->info.st_mode))
	{
		size = 2;
		temp_integer = minor(temp->info.st_rdev);
		COUNTER(temp_integer, 10, size);
		W_MINOR = size > W_MINOR ? size : W_MINOR;
		temp_integer = major(temp->info.st_rdev);
		size = 2;
		COUNTER(temp_integer, 10, size);
		W_MAJOR = size > W_MAJOR ? size : W_MAJOR;
		temp_size = W_MAJOR + W_MINOR;
	}
	else if (W_MAJOR && W_MINOR)
		temp_size = size + W_MAJOR + W_MINOR + 3;
	else
		temp_size = size;
	W_SIZE = temp_size > W_SIZE ? temp_size : W_SIZE;
}

/*
** param contains size of columns
** W_LINKS - size for links
** W_USER - size for user
** W_GROUP - size for group
** W_SIZE - size for size
** W_BLOCKS - sum of blocks
** W_MAJOR - for major parametr
** W_MINOR - for minor parametr
** t - for create a list
** curr_dir - DIR stream
** dir - name of dirrectory
*/

void			ft_make_param(t_curr *temp, int *param)
{
	int	size;
	int	temp_integer;

	temp_integer = temp->info.st_nlink;
	size = 2;
	COUNTER(temp_integer, 10, size);
	W_LINKS = size > W_LINKS ? size : W_LINKS;
	W_USER = ft_strlen(temp->pw_name) > (size_t)W_USER ?
			ft_strlen(temp->pw_name) : W_USER;
	W_GROUP = ft_strlen(temp->gr_name) > (size_t)W_GROUP ?
			ft_strlen(temp->gr_name) : W_GROUP;
	ft_size(temp, param);
	W_BLOCKS += temp->info.st_blocks;
	W_NAME = ft_strlen(temp->name) > (size_t)W_NAME ?
			ft_strlen(temp->name) : W_NAME;
}
