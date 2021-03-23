/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:25:28 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 14:09:05 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

t_flags	pr_create_flags(void)
{
	t_flags		flags;

	flags.f_size = 0;
	flags.l_align = 0;
	flags.z_fill = 0;
	flags.is_prec = 0;
	flags.prec = 0;
	return (flags);
}

int	pr_get_prec(t_flags *flags, const char *str, va_list ap)
{
	int			i;
	int			stck;

	i = 1;
	flags->is_prec = 1;
	if (str[i] == '*')
	{
		stck = va_arg(ap, int);
		if (stck < 0)
			flags->is_prec = 0;
		else
			flags->prec = stck;
		i += 1;
	}
	else
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			flags->prec = flags->prec * 10 + str[i] - 48;
			i++;
		}
	}
	return (i - 1);
}

void	pr_get_field_supp(t_flags *flags, va_list ap)
{
	int			stck;

	stck = va_arg(ap, int);
	if (stck < 0)
	{
		flags->l_align = 1;
		flags->f_size = stck * -1;
	}
	else
		flags->f_size = stck;
}

int	pr_get_field(t_flags *flags, const char *str, va_list ap)
{
	int			i;

	i = 0;
	if (str[i] == '*')
		pr_get_field_supp(flags, ap);
	else
	{
		while (str[i])
		{
			if (str[i] >= '0' && str[i] <= '9')
				flags->f_size = flags->f_size * 10 + str[i] - 48;
			else
				break ;
			i += 1;
		}
	}
	return (i - 1);
}

t_flags	pr_get_flags(const char *str, va_list ap)
{
	t_flags		flags;
	int			i;
	int			ret;

	i = 0;
	flags = pr_create_flags();
	while (str[i])
	{
		ret = 0;
		if (str[i] != '-' && str[i] != '*' && str[i] != '.' && \
		 str[i] != '0' && !(str[i] >= '1' && str[i] <= '9'))
			break ;
		if (str[i] == '0')
			flags.z_fill = 1;
		if (str[i] == '-')
			flags.l_align = 1;
		if (str[i] == '*')
			pr_get_field(&flags, &str[i], ap);
		if (!flags.is_prec && str[i] == '.')
			ret = pr_get_prec(&flags, &str[i], ap);
		if (!flags.f_size && str[i] >= '1' && str[i] <= '9')
			ret = pr_get_field(&flags, &str[i], ap);
		i = i + 1 + ret;
	}
	return (flags);
}
