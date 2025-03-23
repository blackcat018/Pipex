/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:28:04 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/19 14:13:42 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **strs)
{
	char	**temp;

	if (strs == NULL)
		return ;
	temp = strs;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(strs);
}

char	*parce(char *word)
{
	char	**temp;
	char	*outcome;
	char	*new_outcome;
	int		i;

	if (contains_quotes(word))
	{
		i = 0;
		temp = ft_split(word, '\'');
		if (!temp)
			return (NULL);
		outcome = NULL;
		new_outcome = NULL;
		while (temp[i])
		{
			new_outcome = ft_strjoin(outcome, temp[i]);
			free(outcome);
			if (!new_outcome)
				return (free_split(temp), NULL);
			outcome = new_outcome;
			i++;
		}
		return (free_split(temp), free(word), outcome);
	}
	return (word);
}

static char	*returning(char *word)
{
	char	*parced;

	if (!word)
		return (NULL);
	parced = parce(word);
	if (!parced)
		return (NULL);
	return (parced);
}

char	*is_script(char *str, int *i)
{
	int		start;
	char	*word;

	if (str[*i] == '\'')
	{
		(*i)++;
		start = *i;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		word = ft_substr(str, start, *i - start);
		if (str[*i])
			(*i)++;
	}
	else
	{
		start = *i;
		while (str[*i] && str[*i] != ' ')
			(*i)++;
		word = ft_substr(str, start, *i - start);
	}
	return (returning(word));
}

char	**handle_command(char *str, char *envp)
{
	char	**args;

	int (i), (j);
	if (!str || is_space(str))
		return (ft_putstr_fd("Error: empty command\n", 2), NULL);
	args = malloc(sizeof(char *) * 40);
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	str = cmd_is_path(str, envp);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		args[j] = is_script(str, &i);
		if (!args[j])
			return (free_split(args), NULL);
		j++;
	}
	return ((args[j] = NULL), (args));
}
