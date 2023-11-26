/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:35:57 by anamarqu          #+#    #+#             */
/*   Updated: 2022/11/06 15:35:58 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

///STRLEN
size_t	ft_strlen(const char *str)
{
	int	cont;

	cont = 0;
	while (str[cont] != '\0')
	{
		++ cont;
	}
	return (cont);
}

//STRDUP
char	*ft_strdup(const char *string)
{
	char	*copy;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(string);
	copy = (char *) malloc((size + 1) * sizeof(char));
	if (!copy)
	{
		free(copy);
		return (NULL);
	}
	if (string != NULL)
	{
		while (string[i] != '\0')
		{
			copy[i] = string[i];
			++i;
		}
		copy[i] = '\0';
		return (copy);
	}
	return (NULL);
}

//substr
char	*ft_substr(char const *s, unsigned int start,
size_t len)
{
	char			*sub;
	size_t			i;

	i = 0;
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	sub = (char *) malloc((len + 1) * sizeof(char));
	if (sub)
	{
		while (i < len && s[i + start] != '\0')
		{
			sub[i] = s[i + start];
			++i;
		}
		sub[i] = '\0';
		return (sub);
	}
	free(sub);
	return (NULL);
}

//ft_ind
int	ft_ind(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
	{
		if (str[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

//STRJOIN
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if ((s1 != NULL) && (s2 != NULL) && (res))
	{
		while (s1[i] != '\0')
		{
			res[i] = s1[i];
			++i;
		}
		while (*s2 != '\0')
		{
			res[i] = *s2;
			++s2;
			++i;
		}
		res[i] = '\0';
		return (res);
	}
	free(res);
	return (NULL);
}
