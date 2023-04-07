#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
# include <readline/history.h>


#define SPACE 0
#define APPEND 1
#define HEREDOC 2
#define RIGHTRED 3
#define LEFTRED 4
#define DOLLAR 5
#define PIPE 6
#define S_QUOTE 7
#define D_QUOTE 8
#define WORD 9
#define AFDOLLAR 10
#define NLINE 11

typedef struct line
{
    char        *value;
    int         type;
    struct line *next;
    struct line *prev;
}t_token_list;

typedef struct redirections
{
    int					type;
    char				*file;
    int fd;
	struct redirections *next;
}t_redirections;

typedef enum sep
{
    e_pipe,
    e_nline,
} t_sep;
///
typedef struct cmd_line
{
    char            **str;
    t_redirections  *redirections;
    t_sep			separator;
    struct cmd_line *next;
}t_cmd_line;
///
typedef	struct env_list
{
	char			*name;
	char			*value;
	struct env_list	*next;
}t_env_list;


typedef struct tools
{
    int there_is_dollar;
    int s_quote;
    int d_quote;
    int no_expand;
    int dollar_in;
}t_tools;

// Tokenizer Utils
t_token_list    *tokenizer(char *line, t_tools *tools);
char			*is_redirections(t_token_list **tokens, char *line, t_tools *tools);
char			*is_wspace(t_token_list **tokens, char *line);
char			*is_dollar_pipe(t_token_list **tokens, char *line);
char			*is_word(t_token_list **tokens, char *line);
char			*is_squote(t_token_list **tokens, char *line, t_tools *tools);
char			*is_dquote(t_token_list **tokens, char *line, t_tools *tools);
char			*afdollar(t_token_list **tokens, char *line);
char			*is_space(t_token_list **tokens, char *line);
char			*ft_dquotes(t_token_list **tokens, char *line, t_tools *tools);
char	*no_expand(t_token_list **tokens, char	*line, t_tools *tools);
void	open_quote_error(t_token_list **tokens);


// Expander
void	expand(t_token_list **tokens, t_env_list **env);
t_env_list	*add_var(char *name, char *value);
void	fill_env_list(t_env_list **env_list, t_env_list *new);
void	env_vars_list(t_env_list **env_list, char **env);

// Syntax
int	syntax(t_token_list *tokens);

// Parser
void			*parser(t_cmd_line **cmd_line, t_token_list *tokens);
t_redirections	*init_redirection(int type, char *file);
void			fill_redirections_list(t_redirections **redirections, t_redirections *new);
void			separator(t_cmd_line *cmd, t_token_list *token);
t_cmd_line		*init_cmdline(char **str, t_redirections *redirections, t_token_list *token);
void			fill_cmd_line(t_cmd_line **cmdline, t_cmd_line *new);
int				to_alloc_count(t_token_list **tokens);



void	free_2d(char **str);
int	ft_isalnum(int c);
int is_open_quote(char *line, char quote);
int     ft_strcmp(char *s1, char *s2);
int	ft_strncmp(const char *str1, const char *str2, size_t n);
int     ft_strlen(char *str);
int		count(char *line);
int		inside_quotes(char *line, int i);
int     all_spaces(char *line, int i);
int     inside_quotes(char *line, int i);
char    *handle_quotes(t_token_list **tokens, char *line);
char    *check_redirections(char *line);
char    *check_pipe(char *line);
char    *skip_wspaces(char *line);
char *remove_additional_spaces(char *line);
char	*ft_strchr(char *str, int c);
void	ft_lstclear(t_token_list	**lst);
void    addback(t_token_list **tokens, char *value, int type);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void    free_node(t_token_list **tokens);
t_token_list *new_token(char *value, int type);
char	*ft_itoa(int n);
char	*ft_strdup(char *src);
char	*ft_strndup(char *src, int len);
//excution
typedef struct  t_export
{
    char *var;
    char *value;
    struct t_export *next;
    
}t_export;

void    excution(t_cmd_line *cmd_line, char *env[],t_env_list **env_list, t_export **data);
void    handle_echo(t_cmd_line *head);
void    do_cd(char *path);
void    do_pwd();
char	**ft_split(char const *s, char c);
void    do_pipes(t_cmd_line *data, int len,char *env[]);
void    ft_putstr(char *s);
void	excuter(char **commands, char *env[]);
t_export    *data;
t_env_list  *env_list;


#endif