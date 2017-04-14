/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:21:45 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/02 14:21:49 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
** print the permissions
*/

void	ft_pr_mode(t_curr *root)
{
	ft_printf("%c", (S_ISRUSR(root->info.st_mode) ? 'r' : '-'));
	ft_printf("%c", (S_ISWUSR(root->info.st_mode) ? 'w' : '-'));
	if (S_ISSUSR(root->info.st_mode))
		ft_printf("%c", (S_ISXUSR(root->info.st_mode) ? 'S' : 's'));
	else
		ft_printf("%c", (S_ISXUSR(root->info.st_mode) ? 'x' : '-'));
	ft_printf("%c", (S_ISRGRP(root->info.st_mode) ? 'r' : '-'));
	ft_printf("%c", (S_ISWGRP(root->info.st_mode) ? 'w' : '-'));
	if (S_ISSGRP(root->info.st_mode))
		ft_printf("%c", (S_ISXGRP(root->info.st_mode) ? 's' : 'S'));
	else
		ft_printf("%c", (S_ISXGRP(root->info.st_mode) ? 'x' : '-'));
	ft_printf("%c", (S_ISROTH(root->info.st_mode) ? 'r' : '-'));
	ft_printf("%c", (S_ISWOTH(root->info.st_mode) ? 'w' : '-'));
	if (S_ISTOTH(root->info.st_mode))
		ft_printf("%c", (S_ISXOTH(root->info.st_mode) ? 't' : 'T'));
	else
		ft_printf("%c", (S_ISXOTH(root->info.st_mode) ? 'x' : '-'));
}

/*
** print types of files or directories
*/

void	ft_pr_type(t_curr *root)
{
	ft_printf("%s", (S_ISLNK(root->info.st_mode) ? "l" : ""));
	ft_printf("%s", (S_ISDIR(root->info.st_mode) ? "d" : ""));
	ft_printf("%s", (S_ISBLK(root->info.st_mode) ? "b" : ""));
	ft_printf("%s", (S_ISCHR(root->info.st_mode) ? "c" : ""));
	ft_printf("%s", (S_ISFIFO(root->info.st_mode) ? "p" : ""));
	ft_printf("%s", (S_ISREG(root->info.st_mode) ? "-" : ""));
	ft_printf("%s", (S_ISSOCK(root->info.st_mode) ? "s" : ""));
	ft_pr_mode(root);
}

/*
** print for -G
*/

void	ft_lprint_color(t_curr *root, int width)
{
	if (S_ISDIR(root->info.st_mode))
		ft_printf("%s%-s", BLUE, root->name);
	else if (S_ISLNK(root->info.st_mode))
		ft_printf("%s%-s", MAG, root->name);
	else if (S_ISSOCK(root->info.st_mode))
		ft_printf("%s%-s", MAG, root->name);
	else if (S_ISCHR(root->info.st_mode))
		ft_printf("%s%-s", BL_YEL, root->name);
	else if (S_ISBLK(root->info.st_mode))
		ft_printf("%s%-s", BL_CYN, root->name);
	else if (S_ISXUSR(root->info.st_mode))
		ft_printf("%s%-s", RED, root->name);
	else
		ft_printf("%-s", root->name);
	ft_printf("%s%*s", NORM, width - ft_strlen(root->name), "");
}
