/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:37:42 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/13 21:05:27 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int		exit_integrity(char *src)
{
	int		i;

	i = -1;
	while (src[++i])
		if (src[i] != ' ')
			break ;
	i--;
	while (src[++i])
		if (src[i] < '0' || src[i] > '9')
			break ;
	i--;
	while (src[++i])
		if (src[i] != ' ')
			return (0);
	return (1);
}

int		exit_error(t_minishell *m, char *src)
{
	write(2, "bash: exit: ", 12);
	write(2, src, ft_strlen(src));
	write(2, ": numeric argument required\n", 28);
	exec_killer(m->ed);
	exit(-1);
}

char	atoi_exit(char *src)
{
	int		i;
	int		neg;
	long	ret;

	i = -1;
	ret = 0;
	neg = 0;
	if (!ft_strncmp(src, "-9223372036854775808", 0))
		return (0);
	if (src[0] == '-')
		i = 0;
	if (src[0] == '-')
		neg = 1;
	while (src[++i])
		if (src[i] != ' ')
			ret = ret * 10 + (src[i] - '0');
	if (neg)
		ret *= -1;
	return ((char)ret);
}

int	builtin_exit(void *minishell, char **str)
{
	t_minishell		*m;
	char			ret;

	ret = 0;
	m = minishell;
	write(2, "exit\n", 5);
	if (str && str[0] && str[1])
	{
		write(2, "bash: exit: too many arguments\n", 31);
		return (1);
	}
	varenv_kill(&m->ve);
	if (!str)
	{
		exec_killer(m->ed);
		exit(EXIT_SUCCESS);
	}
	if (!exit_integrity(str[0]))
		exit_error(m, str[0]);
	ret = atoi_exit(str[0]);
	exec_killer(m->ed);
	exit(ret);
	return (0);
}
