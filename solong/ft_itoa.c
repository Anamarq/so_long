/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:07:40 by anamarqu          #+#    #+#             */
/*   Updated: 2022/09/20 14:07:43 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "so_long.h"

typedef struct s_data
{
	char	*str;
	int		sign;
	int		len;
}	t_data;

static int	ft_count_char(int n)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	ft_convert(char *str, int *len, int n)
{
	while (n > 0)
	{
		str[*len] = n % 10 + '0';
		n /= 10;
		*len = *len - 1;
	}
}

static void	*ft_clear(char *str)
{
	free(str);
	return (NULL);
}

char	*ft_itoa(int n)
{
	t_data	d;

	d.sign = 1;
	d.len = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		d.sign = -1;
		n *= -1;
		if (n == INT32_MIN)
			return (ft_strdup("-2147483648"));
	}
	d.len = ft_count_char(n);
	if (d.sign == -1)
		d.len++;
	d.str = (char *) malloc((d.len + 1) * sizeof(char));
	if (!d.str)
		return (ft_clear(d.str));
	d.str[d.len--] = '\0';
	ft_convert(d.str, &d.len, n);
	if (d.sign == -1)
		d.str[d.len] = '-';
	return (d.str);
}
// int main()
// {
// 	printf("%s\n", ft_itoa(INT32_MIN));
// }