/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:29:26 by mazaroua          #+#    #+#             */
/*   Updated: 2023/03/27 02:52:49 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_alloc_count(t_token_list **tokens)
{
	t_token_list	*tokens_;
	int				i;

	tokens_ = *tokens;
	i = 0;
	while (tokens_ && tokens_->type != PIPE)
	{
		if (tokens_->type == RIGHTRED || tokens_->type == LEFTRED
			|| tokens_->type == APPEND || tokens_->type == HEREDOC)
		{
			tokens_ = tokens_->next;
			if (tokens_->type == SPACE)
				tokens_ = tokens_->next;
			if (tokens_->type == WORD)
				tokens_ = tokens_->next;
				
		}
		if (tokens_ && tokens_->type == SPACE)
			tokens_ = tokens_->next;
		if (tokens_ && tokens_->type == WORD)
		{
			tokens_ = tokens_->next;
			i++;
		}
	}
	return (i);
}

t_redirections	*init_redirection(int type, char *file)
{
	t_redirections	*redirection_node;

	redirection_node = malloc(sizeof(t_redirections));
	redirection_node->type = type;
	redirection_node->file = file;
	redirection_node->next = NULL;
	return (redirection_node);
}

void	fill_redirections_list(t_redirections **redirections, t_redirections *new)
{
	t_redirections	*curr;

	curr = *redirections;
	if (!*redirections)
		*redirections = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

t_cmd_line	*init_cmdline(char **str, t_redirections *redirections)
{
	t_cmd_line	*cmd;

	cmd = malloc(sizeof(t_cmd_line));
	cmd->str = str;
	cmd->redirections = redirections;
	cmd->next = NULL;
	return (cmd);
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > -1)
		free(str[i--]);
	free(str);
}

void	fill_cmd_line(t_cmd_line **cmdline, t_cmd_line *new)
{
	t_cmd_line	*curr;

	curr = *cmdline;
	if (!*cmdline)
		*cmdline = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	
}

t_cmd_line *parser(t_token_list *tokens)
{
    t_cmd_line		*cmd_line;
    char			**str;
	t_redirections	*redirections;
	int				i;
	
	cmd_line = NULL;
	redirections = NULL;
	while (tokens)
	{
		i = 0;
		str = malloc(to_alloc_count(&tokens) + 1);
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == WORD)
			{
				if ((tokens->next && tokens->next->type == WORD))
				{
					str[i] = ft_strjoin(tokens->value, tokens->next->value);
					i++;
					tokens = tokens->next->next;
				}
				else
				{
					str[i] = tokens->value;
					i++;
					tokens = tokens->next;
				}
			}
			else if (tokens && (tokens->type == RIGHTRED || tokens->type == LEFTRED
				|| tokens->type == APPEND || tokens->type == HEREDOC))
			{
				if (tokens->next->type == WORD)
				{
					fill_redirections_list(&redirections, init_redirection(tokens->type, tokens->next->value));
					tokens = tokens->next->next;
				}
				else
				{
					fill_redirections_list(&redirections, init_redirection(tokens->type, tokens->next->next->value));
					tokens = tokens->next->next->next;
				}
			}
			else if (tokens && tokens->type == SPACE)
				tokens = tokens->next;	
		}
		if (!tokens)
		{
			str[i] = NULL;
			//fill_cmd_line(&cmd_line, init_cmdline(str, redirections));
			int j = 0;
			while (str[j])
				printf("%s\n", str[j++]);
		}
	
	}
	return (NULL);
}