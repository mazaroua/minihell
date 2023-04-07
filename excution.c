#include "minishell.h"
t_export	*addnew(char *var, char *value)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	new->var = var;
	new->value = value;
	new->next = NULL;
	return (new);
}
void	addback_export(t_export **a, t_export *new)
{
  t_export  *head;
	if((*a) == NULL)
	{
		(*a) = new;
	}
	else
	{
		head = (*a);
		new->next = NULL;
		head = (*a);
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

t_env_list	*addnew2(char *var, char *value)
{
	t_env_list	*new;

	new = malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->name = var;
	new->value = value;
	new->next = NULL;
	return (new);
}
void	addback_env(t_env_list **a, t_env_list *new)
{
  t_env_list  *head;

	new->next = NULL;
	head = (*a);
	if(head == NULL)
	{
		 (*a) = new;
	}
	else
	{ 
		head = (*a);
		while (head->next)
			head = head->next;
		head->next = new;
	}
}
void    do_env(char *env[])
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i]);
		ft_putstr("\n");
		i++;
	}
}

void    do_pwd(void)
{
   char cwd[2000];

   if (getcwd(cwd, sizeof(cwd)) != NULL)
	   ft_putstr(cwd);
   else
	   perror("getcwd() error");
	ft_putstr("\n");
}

int check_if_equal_is(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1])
		{
			return (1);
		}
		i++;
	}
	return (0);
}
int check_if_in_env(char *name,char *value, t_export *env)
{
	t_export *head;

	head = env;
	while (head)
	{
		if (ft_strcmp(head->var,name) == 0)
		{
			return (1);
		}
		head = head->next;
	}
	return (0);
}
char *get_name(char *s)
{
	int i;
	char *p;

	i = 0;
	if(s[0] == '=')
		return (NULL);
	while (s[i] && s[i] != '=')
	{
		if(s[i] == '+' && s[i + 1] == '=')
			break;
		i++;
	}
	p = malloc(i + 1);
	i = 0;
	while (s[i] && s[i]  != '=')
	{
		p[i] = s[i];
		if(s[i] == '+' && s[i + 1] == '=')
			break;
		i++;
	}
	p[i] = '\0';
	return (p);
}
char *get_value(char *s)
{
	int i;
	int j;
	int f;
	char *p;

	i = 0;
	f = 0;
	while (s[i] != '=')
		i++;
	i++;
	j = i;
	while (s[i++])
		f++;
	p = malloc(f + 1);
	i = 0;
	while (s[j])
		p[i++] = s[j++];
	p[i] = '\0';
	return (p);
}
void	edit_value(char *name, char *value, t_export **data)
{
	t_export *head;

	head = (*data);
	while (head)
	{
		if (ft_strcmp(head->var,name) == 0)
		{
			head->value = NULL;
			head->value = value;
			return ;
		}
		head = head->next;
	}
}
int	check_append(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if(s[i] == '+' && s[i + 1] == '=')
		{
			return 1;
		}
		i++;
	}
	return (0);
}
void	append_string(char *name, char *value,t_export **data)
{
	int	i;
	t_export *head;

	head = (*data);
	while (head)
	{
		if (ft_strcmp(head->var, name) == 0)
		{
			head->value = ft_strjoin(head->value,value);
			return;
		}
		head = head->next;
	}
}
void    add_var_in_list(t_export **data,t_env_list **env_list, char *str)
{
	char    **var = malloc(sizeof(char *) * 3);
	t_env_list *variable;
	t_export *variable1;

	if (check_if_equal_is(str))
	{
		var[0] = get_name(str);
		var[1] = get_value(str);
		if(check_if_in_env(var[0],var[1],*data)) 
		{
				if(check_append(str))
				{
					append_string(var[0],var[1],data);
					return;
				}
				// stop here.. for modifying
				edit_value(var[0], var[1],data);
				return ;
		}
		variable1 = addnew(var[0],var[1]);
		addback_export(data,variable1);
		variable = addnew2(var[0],var[1]);
		addback_env(env_list,variable);
	}
	else
	{
		var[0] = get_name(str);
		variable1 = addnew(var[0],"");
		addback_export(data,variable1);
	}
}
int correct_name(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if(ft_isalnum(s[i]) == 0) // check correct name 
		{
			if(s[i] == '+' && s[i + 1] == '\0' && i != 0) // for append in last 
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}
void	error_od_export(char *s)
{
	printf("error : %s not identifier\n",s);
}
void    do_export(char *str[], char *env[],t_export **data, t_env_list **env_list)
{
	int i;
	int j;
	char *temp;

	i = 1;
	j = 0;
	if (str[1] == NULL)
	{
		t_export *head = (*data);
		while (head)
		{
			if(head->value == "")
				printf("%s \n",head->var);
			else
				 printf("declare -x %s=\"%s\"\n",head->var,head->value);
			head = head->next;
		}
	}
	while (str[i])
	{
		if(correct_name(get_name(str[i])))
			  add_var_in_list(data,env_list, str[i]);
		else
			error_od_export(str[i]);
		i++;
	}
}
int	check_name_is_exist(char *s, t_export *export)
{
	t_export	*head;

	head = export;
	while (head)
	{
		if(ft_strcmp(head->var,s) == 0)
			return (1);
		head = head->next;
	}
	return(0);
}

void removeNode(t_export **export, char *str)
{
	t_export	*head;
	t_export	*temp;

	head = (*export);
	if(head == NULL)
		return;
	if(head != NULL && ft_strcmp(head->var,str) == 0)
	{
		temp = (*export);
		(*export) = (*export)->next;
		free(temp);
		return ;
	}
	while (head != NULL && head->next != NULL)
	{
		if (ft_strcmp(head->next->var,str) == 0)
		{
			temp = head->next;
			head->next = temp->next;
			free(temp);
		}
		else
			head = head->next;
	}
}
void removeNode2(t_env_list **env, char *str)
{
	t_env_list	*head;
	t_env_list	*temp;

	head = (*env);
	if(head == NULL)
		return;
	if(head != NULL && ft_strcmp(head->name,str) == 0)
	{
		temp = (*env);
		(*env) = (*env)->next;
		free(temp);
		return ;
	}
	while (head != NULL && head->next != NULL)
	{
		if (ft_strcmp(head->next->name,str) == 0)
		{
			temp = head->next;
			head->next = temp->next;
			free(temp);
		}
		else
			head = head->next;
	}
}

void    do_unset(char *str[], char *env[],t_export **data, t_env_list **env_list)
{
	int	i;

	if (str[1] == NULL)
		return ;
	i = 1;
	while (str[i])
	{
		if(check_name_is_exist(str[i],(*data)))
		{
			removeNode(data,str[i]);
			removeNode2(env_list,str[i]);
		}
		else
			error_od_export(str[i]);
		i++;
	}

}
void    excution(t_cmd_line *cmd_line, char *env[],t_env_list **env_list , t_export **data)
{
	if (cmd_line->str[0] == NULL)
		return ;
	else if (ft_strcmp(cmd_line->str[0],"echo") == 0)
		handle_echo(cmd_line);
	else if (ft_strcmp(cmd_line->str[0],"cd") == 0)
		do_cd(cmd_line->str[1]);
	else if (ft_strcmp(cmd_line->str[0],"env") == 0)
	{
		t_env_list *head = (*env_list);
		while (head)
		{
			printf("%s=\"%s\"\n",head->name,head->value);
			head = head->next;
		}
	}
	else if (ft_strcmp(cmd_line->str[0],"pwd") == 0)
		do_pwd();
	else if (ft_strcmp(cmd_line->str[0],"export") == 0)
		do_export(cmd_line->str,env,data,env_list);
	else if (ft_strcmp(cmd_line->str[0],"unset") == 0)
		do_unset(cmd_line->str,env,data,env_list);
	else
	{
		if (size_of_list(cmd_line) == 1)
			excute_one_cmd(cmd_line,env);
		else if(size_of_list(cmd_line) > 1)
		{
			do_pipes(cmd_line, size_of_list(cmd_line),env);
			wait(NULL);
		}
			
	}
}