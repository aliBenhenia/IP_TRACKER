/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:43 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/13 11:36:15 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_global g_var;

void	free_all()
{
	t_allocated	*next;

	while (g_var.allocated)
	{
		next = g_var.allocated->next;
		free(g_var.allocated->allocated);
		free(g_var.allocated);
		g_var.allocated = next;
	}
}

void	body(char *line, t_export **export_list, t_env_list **env_list)
{
	t_token_list	*tokens;
	t_cmd_line		*cmd_line;
	t_tools			tools;

	cmd_line = NULL;
	tokens = NULL;
	tokens = tokenizer(line, tokens, &tools);
	if (tokens && syntax(tokens))
	{
		expand(&tokens, env_list);
		parser(&cmd_line, tokens);
		execution(&cmd_line, env_list, export_list);
	}
	// free_all();
		//////////////////////////////////////////////
		// int j = 0;
		// while (cmd_line && cmd_line->str[j])
		// 	printf("|%s|\n", cmd_line->str[j++]);
		// if (cmd_line->redirections)
		// {
		// 	while (cmd_line->redirections)
		// 	{
		// 		printf("%d %s\n", cmd_line->redirections->type, cmd_line->redirections->file);
		// 		cmd_line->redirections = cmd_line->redirections->next;
		// 	}
		// }
		// puts("--------");
		// if (cmd_line)
		// 	printf("%d\n", cmd_line->separator);
		// puts("--------");
		// if (cmd_line && cmd_line->next)
		// {
		// 	int j = 0;
		// 	while (cmd_line->next->str[j])
		// 	printf("%s\n", cmd_line->next->str[j++]);
		// 	if (cmd_line->next->redirections)
		// 		printf("%d %s\n", cmd_line->next->redirections->type, cmd_line->next->redirections->file);

		// }
		///////////////////////////////////////////////

	// while (tokens)
	// {
	// 	printf("|%s| ", tokens->value);
	// 	printf("|%d|\n", tokens->type);
	// 	tokens = tokens->next;
	// }
}

char    *prompt()
{
    char	*line;

	line = readline("\x1B[36m""minishell$ ""\001\e[0m\002");
	if (!line)
	{
		ft_putstr("exit\n");
		exit(0);
	}
	add_history(line);
	line = remove_additional_spaces(line);
    return (line);
}

int	found_shlvl(t_env_list **envlist)
{
	t_env_list	*env;

	env = *envlist;
	while (env)
	{
		if (!ft_strcmp("SHLVL", env->name))
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_shlvl(t_env_list **envlist, t_export **export)
{
	t_env_list	*env;

	env = *envlist;
	if (!found_shlvl(envlist))
	{
		do_export(ft_split("export SHLVL=1", ' '), export, envlist, 0);
		return ;
	}
	while (env)
	{
		if (!ft_strcmp("SHLVL", env->name))
		{
			free(env->value);
			env->value = ft_itoa(ft_atoi(env->value) + 1);
		}
		env = env->next;
	}
}

void	ctrlc(int sig)
{
	(void)sig;
	int	flag;

	flag = 0;
	g_var.exit_state = 1;
	if (g_var.heredoc == 1)
	{
		close(0);
		g_var.heredoc = -1;
		g_var.i = 1;
		return ;
	}
	if (waitpid(-1, 0, WNOHANG) == 0)
		flag = 1;
	else
		flag = 0;
	if (flag == 1)
		return ;
	if (g_var.heredoc != -1 && g_var.i == 1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main(int ac, char **av, char **env)
{
    char			*line;
	t_export    	*export_list;
	t_env_list		*env_list;
	(void)ac;
	(void)av;

	export_list = NULL;
	env_list = NULL;
	g_var.allocated = NULL;
	init_env(&export_list, &env_list, env);
	ft_shlvl(&env_list, &export_list);
    while (1)
    {
		g_var.heredoc = 0;
		signal(SIGINT, &ctrlc);
		signal(SIGQUIT, SIG_IGN);
		line = prompt();
		if (line)
			body(line, &export_list, &env_list);
    }
}