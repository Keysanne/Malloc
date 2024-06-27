/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:56:29 by tbatteux          #+#    #+#             */
/*   Updated: 2023/04/18 11:17:44 by tbatteux         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		j;
	char	*final;

	final = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!final)
		return (NULL);
	j = -1;
	while (s1[++j])
		final[j] = s1[j];
	j = -1;
	while (s2[++j])
		final[ft_strlen(s1) + j] = s2[j];
	final[ft_strlen(s1) + j] = 0;
	return (final);
}