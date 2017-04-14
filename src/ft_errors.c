/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:24:51 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/05 15:24:54 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
** mistakes:
** 0 - wrong usage
** 2 - no such file or directory
*/

void	ft_errors(const char *name, char c, int mistake)
{
	if (mistake)
	{
		errno = mistake;
		ft_printf("ft_ls: %s: ", name);
		perror(0);
	}
	else
	{
		ft_printf("./ft_ls: illegal option -- %c\n", c);
		ft_printf("usage: ./ft_ls [-1AGRSaflrt] [file ...]\n");
		exit(EXIT_FAILURE);
	}
}
