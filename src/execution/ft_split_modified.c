/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_modified.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:35:27 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/11 10:59:21 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_array(char **array, size_t index)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (i < index)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**mallocword(char const *s, char c, char **array, size_t siz_array)
{
	size_t	index_array;
	size_t	i;
	size_t	index_word;

	index_array = 0;
	i = 0;
	while (s[i] && index_array < siz_array)
	{
		index_word = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			index_word++;
			i++;
		}
		array[index_array] = malloc((index_word + 2) * sizeof(char));
		if (!array[index_array])
		{
			free_array(array, index_array);
			return (NULL);
		}
		index_array++;
	}
	return (array);
}

static char	**fill_array(char **array, char const *s, size_t siz_array, char c)
{
	size_t	i;
	size_t	index_array;
	size_t	index_word;

	index_array = 0;
	i = 0;
	index_word = 0;
	while (s[i] && index_array < siz_array)
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			array[index_array][index_word] = s[i];
			index_word++;
			i++;
		}
		array[index_array][index_word] = '/';
		array[index_array][index_word + 1] = '\0';
		index_array++;
		index_word = 0;
	}
	array[index_array] = 0;
	return (array);
}

char	**ft_split_modified(char const *s, char c, t_minishell *data)
{
	size_t	i;
	char	**array;
	size_t	siz_array;

	if (!s)
		return (0);
	i = 0;
	siz_array = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			siz_array++;
		i++;
	}
	array = malloc((siz_array + 1) * sizeof(char *));
	if (!array)
		free_all_struct(data, 1, MALLOC_ERROR);
	array = mallocword(s, c, array, siz_array);
	if (!array)
		free_all_struct(data, 1, MALLOC_ERROR);
	array = fill_array(array, s, siz_array, c);
	return (array);
}
