/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:50:59 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/25 13:40:08 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	ph_isdigit(char *arg)
{
	int	i;

	i = 0;
	//printf("aaaa\n");
	while (arg[i] != '\0')
	{
		if ((arg[i] >= '0') && (arg[i] <= '9'))
			i++;
		else
			return (false);
	}
	return (true);
}

bool	check_digit(int argc, char **argv)
{
	int	i;

	i = 1;
	while(i < argc)
	{
		if (ph_isdigit(argv[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

bool	check_argument(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "error: bad arguments\n", 21);
		return (false);
	}
	if (check_digit(argc, argv) == false)
	{
		write(2, "error: bad arguments\n", 21);
		return (false);
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 \
	|| ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
		return (false);
	if (argv[5] != NULL)
		if (ft_atoi(argv[5]) < 1)
			return (false);
	return (true);
}
