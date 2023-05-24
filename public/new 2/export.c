/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:20:21 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/04 16:05:19 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// while true ; sleep 1; do leaks minishell; done
#include "minishell.h"

void	custom_edit_env(t_env_list	**env_list, char *name, char *value)
{
	t_env_list	*lst;
	int			no_created;

	no_created = 0;
	lst = (*env_list);
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			no_created = 1;
			free(lst->value);
			lst->value = ft_strdup_export("");
			lst->flag = 1;
			return ;
		}
		lst = lst->next;
	}
	if (!no_created)
		addback_env2(env_list, addnew_env(name, value));
}

void	custom_edit_value(char *name, char *value, t_export **data,
	t_env_list **env_list)
{
	t_export	*head;

	head = (*data);
	while (head)
	{
		if (ft_strcmp(head->var, name) == 0)
		{
			free(head->value);
			head->value = ft_strndup2("", 1);
			head->flag = 1;
			break ;
		}
		head = head->next;
	}
	custom_edit_env(env_list, name, value);
}

void	free_rows(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	while(i > -1)
		free(str[i--]);
}

void	if_equal_only(char *str, char **name_value, t_export **export,
	t_env_list **env_list)
{
	if(eqaul_last_only(str) && check_if_exist(name_value[0], *export))
		custom_edit_value(name_value[0],name_value[1],export,env_list);
	else if (check_if_exist(name_value[0], *export))
	{
		free_rows(name_value);
		return ;
	}
	else if (eqaul_last_only(str))
	{
		addback_env(env_list, addnew_env(name_value[0], "\0"));
		addback_export(export, addnew_export(name_value[0], "eq"));
	}
	else
	{
		addback_export(export, addnew_export(name_value[0], name_value[1]));
	}
	free_rows(name_value);
}

void	add_var_in_list(t_export **export, t_env_list **env_list, char *str)
{
	char	**name_value;
	int		i;

	i = 0;
	name_value = malloc(sizeof(char *) * 3);
	name_value[0] = get_name(str);
	name_value[1] = get_value(str);
	name_value[2] = NULL;
	if (check_if_equal_is(str) && eqaul_last_only(str) == 0)
	{
		if (check_if_exist(name_value[0], *export))
		{
			if (check_append(str))
			{
				append_string(name_value[0], name_value[1], export, env_list);
				free_2d(name_value);
				return ;
			}
			edit_value(name_value[0], name_value[1], export, env_list);
			free_2d(name_value);
			return ;
		}
		addback_export(export, addnew_export(name_value[0], name_value[1]));
		addback_env2(env_list, addnew_env(name_value[0], name_value[1]));
		free_2d(name_value);
	}
	else
	{
		if_equal_only(str, name_value, export, env_list);
		free(name_value);
	}
}

void	print_export(t_export *head)
{
	while (head)
	{
		if(head->flag == 1)
		{
			printf("declare -x %s=\"\"\n", head->var);
		}
		else if (*(head->value) == '\0')
		{
				printf("declare -x %s\n", head->var);
		}
		else
			printf("declare -x %s=\"%s\"\n", head->var, head->value);
		head = head->next;
	}
}

void	edit_env(t_env_list	**env_list, char *name, char *value)
{
	t_env_list	*lst;
	int			no_created;

	no_created = 0;
	lst = (*env_list);
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			no_created = 1;
			free(lst->value);
			lst->value = ft_strdup_export(value);
			lst->flag = 0;
			return ;
		}
		lst = lst->next;
	}
	if (!no_created)
		addback_env(env_list, addnew_env(name, value));
}

void	do_export(char *str[], t_export **export,
t_env_list **env_list, int flag)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	j = 0;
	g_var.exit_state = 0;
	if (str[1] == NULL)
		print_export(*export);
	while (str[i])
	{
		if (correct_name(get_name(str[i])) && !ft_isdigit(str[i][0]))
		{
			add_var_in_list(export, env_list, str[i]);
		}
		else
			error_od_export(str[i]);
		i++;
	}
	sort(export);
	if (flag)
		exit(g_var.exit_state);
}
