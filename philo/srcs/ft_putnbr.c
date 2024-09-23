/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:28:37 by simon             #+#    #+#             */
/*   Updated: 2024/09/23 15:14:10 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 12);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		nb = nb % 10;
	}
	if (nb < 10)
		ft_putchar(nb + 48);
}

// void	ft_putnbr(int nbr)
// {
// 	char	c;
// 	int		nbr_cpy;

// 	if (nbr == -2147483648)
// 	{
// 		write(1, "-2147483648", 12);
// 		return ;
// 	}
// 	nbr_cpy = nbr;
// 	if (nbr < 0)
// 	{
// 		write(1, "-", 1);
// 		nbr *= -1;
// 		nbr_cpy *= -1;
// 	}
// 	while (nbr > 9)
// 	{
// 		nbr /= 10;
// 	}
// 	c = nbr + 48;
// 	write(1, &c, 1);
// 	if (nbr_cpy/10 > 1)
// 		ft_putnbr(nbr_cpy / 10);
// 	else
// 		write(1, &c, 1);
// }

/*int main(void)
{
	ft_putnbr(0);
	write(1, "\n", 1);
	ft_putnbr(1);
	write(1, "\n", 1);
	ft_putnbr(10);
	write(1, "\n", 1);
	ft_putnbr(21);
	write(1, "\n", 1);
	ft_putnbr(-1);
	write(1, "\n", 1);
	ft_putnbr(-42);
	write(1, "\n", 1);
	ft_putnbr(-2147483648);
	write(1, "\n", 1);
	ft_putnbr(2147483647);
	write(1, "\n", 1);
	ft_putnbr(-98452);
	write(1, "\n", 1);
	ft_putnbr(265989);
	return (0);
}*/