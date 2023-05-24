/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:28:43 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:44 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	insert(t_export **sorted, t_export *new_node)
// {
// 	t_export	*current;

// 	if (*sorted == NULL || strcmp((*sorted)->var, new_node->var) > 0)
// 	{
// 		new_node->next = *sorted;
// 		*sorted = new_node;
// 	}
// 	else
// 	{
// 		current = *sorted;
// 		while (current->next != NULL
// 			&& ft_strcmp(current->next->var, new_node->var) < 0)
// 			current = current->next;
// 		new_node->next = current->next;
// 		current->next = new_node;
// 	}
// }

// void	sort(t_export **head)
// {
// 	t_export	*sorted;
// 	t_export	*current;
// 	t_export	*temp;

// 	sorted = NULL;
// 	current = *head;
// 	while (current != NULL)
// 	{
// 		temp = current->next;
// 		insert(&sorted, current);
// 		current = temp;
// 	}
// 	*head = sorted;
// }

void swap(t_export* a, t_export* b)
{
    char* temp_var = a->var;
    char* temp_value = a->value;
    int temp_flag = a->flag;
    a->var = b->var;
    a->value = b->value;
    a->flag = b->flag;
    b->var = temp_var;
    b->value = temp_value;
    b->flag = temp_flag;
}

void sort(t_export** head)
{
    t_export* current;
    t_export* previous;
    int flag_swapped = 1;

    if (!*head)
        return ;
    while (flag_swapped) 
	{
        flag_swapped = 0;
        current = *head;

        while (current->next != NULL) 
		{
            if (strcmp(current->var, current->next->var) > 0)
			{
                swap(current, current->next);
                flag_swapped = 1;
            }
            previous = current;
            current = current->next;
        }
    }
}