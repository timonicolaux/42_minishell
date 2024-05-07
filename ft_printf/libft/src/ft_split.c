/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:12:11 by tnicolau          #+#    #+#             */
/*   Updated: 2024/02/07 08:06:26 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freeall(char **array, int j)
{
	int	i;

	i = 0;
	if (j == -1)
	{
		array = malloc(sizeof(char *) * 1);
		if (!array)
			return (NULL);
		array[0] = NULL;
		return (array);
	}
	while (i < j)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static int	array_size(char *s, char c)
{
	int	i;
	int	count;
	int	length;

	i = 0;
	count = 0;
	length = ft_strlen(s);
	while (s[i])
	{
		if (s[i] != c && i == 0)
			count++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	if (count == length)
		return (0);
	if (count == 0)
		count++;
	return (count);
}

static int	calc_size(char *s, int start, char c, int mark)
{
	int	count;

	count = 0;
	if (mark == 1)
	{
		while (s[start] == c && s[start])
			start++;
		while (s[start] != c && s[start])
		{
			count++;
			start++;
		}
	}
	else
	{
		while (s[start] != c && s[start])
			start++;
		while (s[start] == c && s[start])
		{
			count++;
			start++;
		}
	}
	return (count);
}

static char	*fill_word(char *individual_str, char *s, char c, int start)
{
	int	j;
	int	wlength;
	int	slength;

	j = 0;
	wlength = calc_size(s, start, c, 1);
	slength = calc_size(s, start, c, 0);
	individual_str = malloc(sizeof(char) * (wlength + 1));
	if (!individual_str)
		return (NULL);
	while (s[start] == c && start < (start + wlength + slength))
		start++;
	while (s[start] && s[start] != c)
	{
		individual_str[j] = s[start];
		j++;
		start++;
	}
	individual_str[j] = '\0';
	return (individual_str);
}

char	**ft_split(char *s, char c)
{
	int		j;
	int		index;
	char	**array;

	array = NULL;
	j = 0;
	index = 0;
	if (s == 0)
		return (NULL);
	if (calc_size(s, index, c, 0) == ft_strlen(s))
		return (ft_freeall(array, -1));
	array = malloc(sizeof(char *) * (array_size(s, c) + 1));
	if (!array)
		return (NULL);
	while (j < array_size(s, c))
	{
		array[j] = fill_word(array[j], s, c, index);
		if (array[j] == NULL)
			return (ft_freeall(array, j));
		index = index + calc_size(s, index, c, 1) + calc_size(s, index, c, 0);
		j++;
	}
	array[j] = NULL;
	return (array);
}
