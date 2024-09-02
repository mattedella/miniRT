/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:12:29 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/29 16:50:28 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_mem(char **s, int i)
{
	while (i >= 0)
	{
		free (s[i]);
		i--;
	}
	free (s);
}

static int	count_word(char *s, int c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			w++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (w);
}

static void	f_strcpy(char *w, char *s, char c, int j)
{
	int	i;

	i = 0;
	while (s[j] == c && s[j] != '\0')
		j++;
	while (s[j + i] != c && s[j + i] != '\0')
	{
		w[i] = s[j + i];
		i++;
	}
	w[i] = '\0';
}

static char	*alloc_str(char *s, char c, int *j)
{
	char	*w;
	int		i;
	int		k;

	i = *j;
	k = 0;
	w = NULL;
	while (s[*j] != '\0')
	{
		if (s[*j] != c)
		{
			while (s[*j] != c && s[*j] != '\0')
			{
				*j = *j + 1;
				k++;
			}
			w = (char *)malloc(sizeof(char) *(k + 1));
			if (w == NULL)
				return (0);
			break ;
		}
		*j = *j + 1;
	}
	f_strcpy(w, s, c, i);
	return (w);
}

char	**ft_split(char const *s, char c)
{
	char	**st;
	int		i;
	int		j;
	int		w;

	i = 0;
	j = 0;
	if (s == NULL)
		return (0);
	w = count_word((char *) s, c);
	st = (char **)malloc(sizeof(char *) * (w + 1));
	if (st == NULL)
		return (0);
	while (i < w)
	{
		st[i] = alloc_str((char *) s, c, &j);
		if (!st[i])
		{
			free_mem (st, i);
			return (NULL);
		}
		i++;
	}
	st[i] = NULL;
	return (st);
}
