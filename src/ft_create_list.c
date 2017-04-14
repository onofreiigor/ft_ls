/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <okosiako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 17:02:05 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/12 14:46:54 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
** add a new element to library struct t_list
*/

void		ft_ladd_2(t_list **root, t_list *new)
{
	t_list	*temp;

	if (!*root || ft_strcmp((char *)new->content, (char *)(*root)->content) < 0)
	{
		new->next = *root;
		*root = new;
	}
	else
	{
		temp = *root;
		while (temp->next && ft_strcmp((char *)new->content,
			(char *)temp->next->content) > 0)
			temp = temp->next;
		new->next = temp->next;
		temp->next = new;
	}
}

/*
** function for deleting t_list
*/

void		ft_str_list(t_list **t)
{
	t_list *copy;

	if (*t)
	{
		while ((*t))
		{
			ft_memdel((void **)&((*t)->content));
			copy = *t;
			*t = (*t)->next;
			ft_memdel((void **)&copy);
		}
	}
}

/*
** function for counting the nodes of list
*/

int			ft_list_count(t_curr *list)
{
	int	res;

	res = 0;
	if (list)
		while (list)
		{
			res++;
			list = list->next;
		}
	return (res);
}

/*
** functions for getting an n element
*/

t_curr		*ft_get_elem(t_curr *list, int n)
{
	if (list)
	{
		while (list && n--)
			list = list->next;
		if (list)
			return (list);
		else
			return (0);
	}
	return (0);
}
