/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:28:04 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/19 14:28:51 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (!str[i]);
}

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
			outcome = new_outcome;
			if (!outcome)
				return (free_split(temp), NULL);
			i++;
		}
		return (free_split(temp), free(word), outcome);
	}
	return (word);
}

char	*is_script(char *str, int *i)
{
	int		start;
	char	*word;
	char	*parced;

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
	if (!word)
		return (NULL);
	parced = parce(word);
	return (parced);
}

char	**handle_command(char *str, char *envp)
{
	char	**args;
	int		i;
	int		j;

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
	args[j] = NULL;
	return (args);
}
