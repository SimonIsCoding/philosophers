/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:57:08 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/06 16:05:25 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		a;
	int		i;
	int		sign;

	i = 0;
	a = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-' && sign == 1)
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
		a = a * 10 + (str[i++] - 48);
	return (a * sign);
}

char	*ft_strdup(const char *str)
{
	char	*dst;
	size_t	i;

	i = -1;
	dst = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (str[++i] != '\0')
		dst[i] = str[i];
	dst[i] = '\0';
	return (dst);
}

static size_t	ft_ctr(long num)
{
	size_t	ctr;

	ctr = 0;
	while (num < 0)
	{
		num *= -1;
		ctr++;
	}
	while (num > 0)
	{
		num /= 10;
		ctr++;
	}
	return (ctr);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	tmp;
	size_t	len;

	tmp = n;
	len = ft_ctr(tmp);
	if (n == 0)
		return (ft_strdup("0"));
	str = malloc((len + 1) * (sizeof(char)));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (tmp < 0)
	{
		tmp *= -1;
		str[0] = '-';
	}
	while (tmp > 0)
	{
		str[len--] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (str);
}