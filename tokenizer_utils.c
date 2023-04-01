/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:44:42 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/01 01:23:44 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *is_redirections(t_token_list **tokens, char *line)
{
    if (*line == '>')
    {	
        if (*(line + 1) == '>')
        {
            addback(tokens, ">>", APPEND);
            return (line + 2);
        }
        addback(tokens, ">", RIGHTRED);
    }
    else if (*line == '<')
    {
        if (*(line + 1) == '<')
        {
            addback(tokens, "<<", HEREDOC);
            return (line + 2);
        }
        addback(tokens, "<", LEFTRED);
    }
	return (line + 1);
}

char    *is_wspace(t_token_list **tokens, char *line)
{
    int i;
    i = 0;
    while (ft_strchr(" \t\v\f\r", line[i]) && line[i])
        i++;
    addback(tokens, " ", SPACE);
    return (line + i);
}

char    *is_dollar_pipe(t_token_list **tokens, char *line)
{
    if(*line == '$')
    {
		if (*(line + 1) == '$')
		{
			addback(tokens, ft_itoa(getpid()), WORD);
        	return (line + 2);
		}
        addback(tokens,"$", DOLLAR);
		line += 1;
		line = afdollar(tokens, line, NULL);
        return (line);
    }
    else if(*line == '|')
    {
        addback(tokens,"|", PIPE);
        return (line + 1);
    }
	return (0);
}

char    *is_word(t_token_list **tokens, char *line)
{
    int		i;
    char    *word;

    i = 0;
    while (!ft_strchr(" \t\v\f\r><|\'\"", line[i]))
        i++;
	word = malloc(i + 1);
	i = 0;
	while (!ft_strchr(" \t\v\f\r><|\'\"", line[i]))
	{
		
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	addback(tokens, word, WORD);
	return (line + i);
}

int is_open_quote(char *line, char quote)
{
    int i;
    int x;

    i = 0 ;
    x = 0;
    while(line[i])
    {
        if(line[i] == quote)
            x++;
        i++;
    }
    return (x % 2);
}

int to_alloc(char *line)
{
    int i;
    int j;
    int count;
    int flag;
    char quote;

    i = 0;
    j = 0;
    count = is_open_quote(line, '\'');
    flag = 0;
    while (line[i] && count == 0)
    {
		if((line[i] == 39 || line[i] == 34) && flag == 0)
        {
            quote = line[i];
            flag = 1;
            i++;
        }
        if(line[i] != quote && flag  == 1)
        {
            i++;
            j++;
        }
        if(line[i] == quote && flag == 1)
		{
			i++;
            break;
		}
        if (line[i] == '$')
            break ;
    }
	return (j);
}

char    *is_squote(t_token_list **tokens, char *line, int *open, t_tools *tools)
{
    int i;
    int j;
    int count;
    int flag;
    char    *word;

    i = 0;
    j = 0;
    count = is_open_quote(line, '\'');
    flag = 0;
	word = malloc(to_alloc(line) + 1);
	if (tools->after_variable == 1)
	{
		count = 0;
		line = is_dquote(tokens, line, open, tools);
		tools->after_variable = 0;
		return (line);
	}
	if (count == 0)
	{
		while (line[i])
		{
			if(line[i] == 39 && flag == 0)
			{
				flag = 1;
				i++;
			}
			if(line[i] != 39 && flag  == 1)
			{
				word[j] = line[i];
				i++;
				j++;
			}
			if(line[i] == 39 && flag == 1)
			{
				i++;	
				break;
			}
		}
		word[j]= '\0';
		addback(tokens, word, WORD);
	}
	else
	{
		write(1, "Open quote\n", ft_strlen("Open quote\n"));
		ft_lstclear(tokens);
		*open = 1;
	}
	return (line + i);
}

char	*is_dquote(t_token_list **tokens, char *line, int *open, t_tools *tools)
{
	int i;
    int j;
    int count;
    int flag;
    char    *word;

    i = 0;
    j = 0;
    count = is_open_quote(line, '\"');
    flag = 0;
	word = malloc(to_alloc(line) + 1);
	if (tools->after_variable == 1)
	{
		count = 0;
		tools->after_variable = 0;
	}
	if (count == 0)
	{
		while (line[i])
		{
            if (line[i] == '$')
                break;
			else if (line[i] == 34 && flag == 0)
			{
				i++;
				flag = 1;
			}
			else if (line[i] == 32 && flag == 0)
				break ;
			else if(line[i] != 34)
			{
				word[j] = line[i];
				i++;
				j++;	
			}
			else if (line[i] == 34)
			{
				flag = 0;
				i++;
			}
		}
        if (j > 0)
        {
            word[j]= '\0';
            addback(tokens, word, WORD);
        }
	}
	else
	{
		write(1, "Open quote\n", ft_strlen("Open quote\n"));
		ft_lstclear(tokens);
		*open = 1;
	}
	return (line + i);
}

char	*afdollar(t_token_list **tokens, char *line, t_tools *tools)
{
	int	i;
	int j;
	char *afdollar;

	i = 0;
	j = 0;
	if (tools)
		line = is_dollar_pipe(tokens, line);
	while (line[i])
	{
		if ((line[i] != 34) && (ft_isalnum(line[i]) || line[i] == '_'))
			i++;
		else
			break;
	}
	afdollar = malloc(i + 1);
	while (j < i)
	{
		afdollar[j] = line[j];
		j++;
	}
	afdollar[j] = '\0';
	addback(tokens, afdollar, AFDOLLAR);
	if (tools)
		tools->after_variable = 1;
	return (line + i);
}