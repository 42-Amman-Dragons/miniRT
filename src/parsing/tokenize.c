/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:12 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/01 15:22:12 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	count_words(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_space(s[i]))
			i++;
	}
	return (count);
}

int	word_len(char *s)
{
	int	len;

	len = 0;
	while (s[len] && !is_space(s[len]))
		len++;
	return (len);
}

char	**split_ws(char *line)
{
	char	**tokens;
	int		i;
	int		w;

	tokens = malloc(sizeof(char *) * (count_words(line) + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	w = 0;
	while (line[i])
	{
		while (line[i] && is_space(line[i]))
			i++;
		if (!line[i])
			break ;
		tokens[w] = ft_substr(line, i, word_len(line + i));
		if (!tokens[w++])
			return (free_tokens(tokens), NULL);
		i += word_len(line + i);
	}
	tokens[w] = NULL;
	return (tokens);
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
