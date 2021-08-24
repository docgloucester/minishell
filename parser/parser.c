/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:11:31 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/24 14:05:43 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   include "parser.h"

int main(int argc, char **argv)
{
    (void)argc;
	(void)argv;
	char	*line;
	line = "";
	while (line)
	{
		line = readline("prompt$ ");
		if (line)
		{
			add_history(line);
			//printf("%s\n%ld\n", line, fchar_nesc(line, '$', 4));
			printf("[%s]\n%d\n", line, count_all_segments(line));
		}
	}
	return (0);
}