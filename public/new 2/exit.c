/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:06:30 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/10 18:23:22 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
long long	ft_atoi_exit(const char *str)
{
	int			i;
	long long	result;
	long long	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	check_if_number(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-' || s[0] == '+')
		i++;
	if(ft_strlen(s) > 20)
		return (0);
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] == '\0')
		return (1);
	putes("pss\n");
	if(ft_atoi_exit(s) >= 9223372036854775808 || ft_atoi_exit(s) < -9223372036854775809)
		return (0); 
	return (0);
	// int	i;

	// i = 0;
	// if ((av[0] == '-' || av[0] == '+') && av[1] != '\0')
	// 	i++;
	// while (av[i] && ft_isdigit(av[i]))
	// 	i++;
	// if (av[i] != '\0' && ft_isdigit(av[i]) == 0)
	// 	return (0);
	// if(ft_atoi_exit(av) >= 9223372036854775808)
	// 	return (0);
	// return (1);
}

void	do_exit(char *s[], int flag) // pss env and exp
{
	if (s[1] == NULL)
	{
		if (flag)
			ft_putstr_fd("exit\n", 2);
		exit(g_var.exit_state);
	}
	if (s[1] && !s[2])
	{
		if (check_if_number(s[1]))
		{
			ft_putstr_fd("exit\n", 1);
			exit(atoi(s[1]));
		}
		else
		{
			g_var.exit_state = 255;
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(s[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(g_var.exit_state);
		}
	}
	if (s[2])
	{
		if (check_if_number(s[1]))
		{
			ft_putstr("exit\n");
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		}
		else if (!check_if_number(s[1]))
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(s[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_var.exit_state = 255;
			exit(g_var.exit_state);
		}
		g_var.exit_state = 1;
		if (!flag)
			exit(g_var.exit_state);
	}
}
