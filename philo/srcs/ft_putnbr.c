/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:28:37 by simon             #+#    #+#             */
/*   Updated: 2024/09/22 20:37:34 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putnbr(int nbr)
{
	int	i;

	i = 0;
	if (nbr == -2147483648)
		return (write(1, "-2147483648", 12));
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
		i++;
	}
	while (nbr > 0)
	{
		
	}
		
		
		
	
}

int main(void)
{
	ft_putnbr(0);
	write(1, "\n", 1);
	ft_putnbr(1);
	write(1, "\n", 1);
	ft_putnbr(21);
	write(1, "\n", 1);
	ft_putnbr(-1);
	write(1, "\n", 1);
	ft_putnbr(-42);
	write(1, "\n", 1);
	ft_putnbr(-2147483647);
	write(1, "\n", 1);
	ft_putnbr(2147483648);
	write(1, "\n", 1);
	ft_putnbr(-98452);
	write(1, "\n", 1);
	ft_putnbr(265989);
	return (0);
}