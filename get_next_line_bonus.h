/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabyaa <yabyaa@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:09:03 by yabyaa            #+#    #+#             */
/*   Updated: 2025/11/18 13:46:02 by yabyaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
void	chr_str(int *i, char **rest);
char	*ft_join_str(char const *s1, char const *s2, int i, int j);
char	**ft_cut_str(char *buffer, int i, int j);
void	super_free(char **a, char *b, char *c, char **d);
#endif
