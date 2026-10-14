/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabyaa <yabyaa@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:32:32 by yabyaa            #+#    #+#             */
/*   Updated: 2025/11/15 14:38:09 by yabyaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_join_str(char const *s1, char const *s2, int i, int j)
{
	char	*p;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[i++])
	{
	}
	while (s2[j])
	{
		++j;
	}
	p = (char *)malloc((i - 1) + j + 1);
	if (!p)
		return (NULL);
	while (j >= 0)
	{
		p[j + (i - 1)] = s2[j];
		--j;
	}
	while (((i - 1) - 1) >= 0)
	{
		p[(i - 1) - 1] = s1[(i - 1) - 1];
		--i;
	}
	return (p);
}

char	**fill(char *buffer, char **hold, int j, int k)
{
	int	i;

	i = j + 1;
	while (buffer[j++])
	{
	}
	if (((j - 1) - i) == 0)
		hold[1] = NULL;
	else
	{
		hold[1] = malloc(((j - 1) - i) + 1);
		if (!(hold[1]))
		{
			free(hold[0]);
			free(hold);
			return (NULL);
		}
		while (i <= (j - 1))
		{
			hold[1][k++] = buffer[i++];
		}
	}
	hold[2] = NULL;
	return (hold);
}

char	**ft_cut_str(char *buffer, int i, int j)
{
	char	**hold;

	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i++] != '\n')
	{
	}
	hold = malloc(sizeof(char *) * 3);
	if (!hold)
		return (NULL);
	hold[0] = malloc(i + 1);
	if (!(hold[0]))
	{
		free(hold);
		return (NULL);
	}
	j = (i - 1);
	i = 0;
	while (i <= j)
	{
		hold[0][i] = buffer[i];
		++i;
	}
	hold[0][i] = '\0';
	return (fill(buffer, hold, j, 0));
}

void	super_free(char **a, char *b, char *c, char **d)
{
	if (a)
	{
		free(*a);
		*a = NULL;
	}
	free(b);
	free(c);
	free(d);
}
