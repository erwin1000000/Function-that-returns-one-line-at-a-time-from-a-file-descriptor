/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabyaa <yabyaa@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:33:28 by yabyaa            #+#    #+#             */
/*   Updated: 2025/11/18 13:41:00 by yabyaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*ft_distribution_1(char **rest)
{
	char	*hold;
	char	*line;
	char	**cut;

	cut = ft_cut_str(*rest, 0, 0);
	if (!cut)
	{
		super_free(rest, NULL, NULL, NULL);
		return (NULL);
	}
	line = cut[0];
	hold = *rest;
	*rest = cut[1];
	super_free(NULL, NULL, hold, cut);
	return (line);
}

static char	*ft_distribution_2(char **rest, char **buff, char **line)
{
	char	*hold;
	char	**cut;

	cut = ft_cut_str(*buff, 0, 0);
	if (!cut)
	{
		super_free(NULL, *line, *buff, NULL);
		return (NULL);
	}
	hold = *line;
	*line = ft_join_str(*line, cut[0], 0, 0);
	*rest = cut[1];
	super_free(buff, hold, cut[0], cut);
	return (*line);
}

static char	*ft_error(int r, char **line, char **buff)
{
	if (r == -1)
	{
		super_free(NULL, *line, *buff, NULL);
		return (NULL);
	}
	if (line[0][0] == '\0')
	{
		super_free(NULL, *line, *buff, NULL);
		return (NULL);
	}
	free(*buff);
	return (*line);
}

static char	*ft_build(int fd, char **rest, char **line, char **buff)
{
	char	*hold;
	int		i;

	while (1)
	{
		i = read(fd, *buff, BUFFER_SIZE);
		if (i == 0 || i == -1)
			return (ft_error(i, line, buff));
		else
		{	
			buff[0][i] = '\0';
			i = 0;
			while (buff[0][i] && buff[0][i++] != '\n')
			{
			}
			if (buff[0][i - 1] == '\n')
				return (ft_distribution_2(rest, buff, line));
			else
			{
				hold = *line;
				*line = ft_join_str(*line, *buff, 0, 0);
				free(hold);
			}
		}
	}	
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*buff;
	int			i;

	if (rest)
	{
		i = 0;
		while (rest[i] && rest[i++] != '\n')
		{
		}
		if (rest[i - 1] == '\n')
			return (ft_distribution_1(&rest));
		line = ft_join_str(rest, "", 0, 0);
		super_free(&rest, NULL, NULL, NULL);
	}
	else
		line = ft_join_str("", "", 0, 0);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff || !line)
	{
		super_free(NULL, buff, line, NULL);
		return (NULL);
	}
	return (ft_build(fd, &rest, &line, &buff));
}
