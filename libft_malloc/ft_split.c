/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:56:24 by tbatteux          #+#    #+#             */
/*   Updated: 2023/04/18 13:48:35 by tbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

int	gd_malloc(const char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			j++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (j + 1);
}

char	*mot(int *i, const char *str, char c)
{
	char	*mot;
	int		j;
	int		x;

	x = 0;
	j = 0;
	while (str[*i] == c)
		(*i)++;
	while (str[*i + j] != c && str[*i + j])
		j++;
	mot = malloc (j + 1 * sizeof(char));
	if (!mot)
		return (NULL);
	while (x < j)
	{
		mot[x++] = str[*i];
		(*i)++;
	}
	mot[j] = 0;
	return (mot);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	tab = malloc (gd_malloc(s, c) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < gd_malloc(s, c) - 1)
		tab[j++] = mot(&i, s, c);
	tab[j] = 0;
	return (tab);
}