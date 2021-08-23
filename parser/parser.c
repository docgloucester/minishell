/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:11:31 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/23 16:02:12 by nouchata         ###   ########.fr       */
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
			//printf("%s\n%ld\n", line, find_char_not_escaped(line, '$', 4));
			printf("[%s]\n%d\n", line, remove_spaces(&line, 0));
		}
	}
	return (0);
}