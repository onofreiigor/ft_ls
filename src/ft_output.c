/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <okosiako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:21:45 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/12 14:45:12 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
** takes a root of the list and prints all elements in long format
*/

void	ft_print_long(t_curr *root, int *param, char color)
{
	while (root)
	{
		ft_pr_type(root);
		ft_printf("%s", ((root->lx <= 0 && !root->acl) ? " " : ""));
		ft_printf("%s", ((root->lx > 0) ? "@" : ""));
		ft_printf("%s", ((root->acl && !root->lx) ? "+" : ""));
		ft_printf("%*d", W_LINKS, root->info.st_nlink);
		ft_printf(" %-*s ", W_USER, root->pw_name);
		ft_printf(" %-*s ", W_GROUP, root->gr_name);
		if (S_ISBLK(root->info.st_mode) || S_ISCHR(root->info.st_mode))
			ft_printf("%*d, %*d", W_MAJOR, major(root->info.st_rdev),
									W_MINOR, minor(root->info.st_rdev));
		else
			ft_printf("%*lld", W_SIZE, root->info.st_size);
		ft_printf(" %.7s", (ctime(&root->info.st_mtime) + 4));
		if (IS_HALF(root->info.st_mtime) || root->info.st_mtime - time(0) > 0)
			ft_printf(" %.4s ", (ctime(&root->info.st_mtime) + 20));
		else
			ft_printf("%.5s ", (ctime(&root->info.st_mtime) + 11));
		color == 'G' ? ft_lprint_color(root, 0) : ft_printf("%s", root->name);
		ft_printf("%s\n", (S_ISLNK(root->info.st_mode)) ? root->link_path : "");
		root = root->next;
	}
}

/*
** for usuall output
*/

void	ft_print_x(t_curr *root, int *param, char color)
{
	struct winsize	ws;
	int				column;

	ioctl(0, TIOCGWINSZ, &ws);
	while (root)
	{
		column = ws.ws_col / (W_NAME + 1);
		while (root && column--)
		{
			color == 'G' ? ft_lprint_color(root, W_NAME + 1) :
								ft_printf("%-*s", W_NAME + 1, root->name);
			root = root->next;
		}
		ft_printf("\n");
	}
}

void	ft_print_n(t_curr *root, int *param, char color)
{
	struct winsize	ws;
	int				count;
	int				step;
	int				n;

	ioctl(0, TIOCGWINSZ, &ws);
	step = ft_list_count(root) / (ws.ws_col / (W_NAME + 1)) + 1;
	count = 0;
	while (count < step)
	{
		n = count++;
		while (ft_get_elem(root, n))
		{
			color == 'G' ? ft_lprint_color(ft_get_elem(root, n), W_NAME + 1) :
					ft_printf("%-*s", W_NAME + 1, ft_get_elem(root, n)->name);
			n += step;
		}
		ft_printf("\n");
	}
}

void	ft_lprint(t_curr *root, int *param, char *options)
{
	if (root)
	{
		if (O_FORMAT == C_FORMAT)
			while (root)
			{
				O_COLORS == 'G' ? ft_lprint_color(root, ft_strlen(root->name)) :
										ft_printf("%s", root->name);
				ft_printf("\n");
				root = root->next;
			}
		else if (O_FORMAT == L_FORMAT)
			ft_print_long(root, param, O_COLORS);
		else if (O_FORMAT == X_FORMAT)
			ft_print_x(root, param, O_COLORS);
		else
			ft_print_n(root, param, O_COLORS);
	}
}
