/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:34:58 by tbatteux          #+#    #+#             */
/*   Updated: 2023/04/18 11:54:59 by tbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static int	ft_strlen(const char* str)
{
	int i;
	for(i = 0; str[i]; i++)
		;
	return i;
}

int	is_charset(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
		if (charset[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	while (s1[i] && is_charset(s1[i], set) == 1)
		i++;
	j = ft_strlen(s1);
	while (j > i && is_charset(s1[j - 1], set) == 1)
		j--;
	k = ft_strlen(s1) - j;
	str = malloc((ft_strlen(s1) - k - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	k = 0;
	while (i < j)
		str[k++] = s1[i++];
	str[k] = 0;
	return (str);
}