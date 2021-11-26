/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 09:40:44 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/25 13:38:40 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static	long	over_num(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

static	int	is_step(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') || \
			(str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int		sign;
	int		i;
	long	res;
	long	int_div;
	long	int_mod;

	res = 0;
	sign = 1;
	int_div = INT_MAX / 10;
	int_mod = INT_MAX % 10;
	i = 0;
	i = is_step(str);
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while ((str[i] != '\0') && (str[i] >= '0') && (str[i] <= '9'))
	{
		if (res > int_div || (res == int_div && str[i] - '0' > int_mod))
			return (over_num(sign));
		res = res * 10 + str[i++] - '0';
	}
	return (res * sign);
}
