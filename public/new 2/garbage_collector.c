/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:17:26 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/11 16:25:57 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_allocated	*garbage_node(void	*alloc)
{
	t_allocated	*allocated;

	allocated = malloc(sizeof(t_allocated));
	allocated->allocated = alloc;
	allocated->next = NULL;
	return (allocated);
}

void	garbage_collector(void *alloc)
{
	t_allocated	*curr;

	curr = g_var.allocated;
	if (!g_var.allocated)
		g_var.allocated = garbage_node(alloc);
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = garbage_node(alloc);
	}
}

void	*ft_malloc(int size, int count)
{
	void	*alloc;

	alloc = malloc(size * count);
	if (!alloc)
		exit(1);
	garbage_collector(alloc);
	return (alloc);
}