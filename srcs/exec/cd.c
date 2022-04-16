#include "../../include/minishell.h"

/*
   change path of pwd in env for absolute path
   */

char	**change_pwd_absolute(char *path, char **my_env)
{
	int		i;
	int		pwd_index;
	char	**temp;
	char	*new_pwd;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (tab_2d_len(my_env) + 1));
	if (!temp)
		return (NULL);
	pwd_index = my_env_index_elem(my_env, "PWD");
	new_pwd = ft_strjoin("PWD=", path);
	while (my_env[i])
	{
		if (i == pwd_index)
			temp[i] = ft_strdup(new_pwd);
		else
			temp[i] = ft_strdup(my_env[i]);
		i++;
	}
	temp[i] = NULL;
	free_tab_2d(my_env);
	free(new_pwd);
	return (temp);
}

/*
   change path of pwd in env for relativ path
   */

char	**change_pwd_relativ(char *path, char **my_env)
{
	char	**temp;
	char	**temp2;
	char	*pwd;
	int		i;

	i = 0;
	pwd = my_getenv(my_env, "PWD");
	temp = ft_split(path, '/');
	temp2 = ft_split(pwd, '/');
	while (temp[i])
	{
		if (strcmp(temp[i], "..") == 0)
			temp2 = supp_last_elem_tab2d(temp2);
		else if (strcmp(temp[i], ".") != 0)
			temp2 = append_tab_2d(temp2, temp[i]);
		i++;
	}
	my_env = change_pwd(temp2, my_env);
	my_env = change_oldpwd(pwd, my_env);
	free_tab_2d(temp);
	free_tab_2d(temp2);
	free(pwd);
	return (my_env);
}

/*
   change env (oldpwd and pwd) depending on if it's absolute or relativ path
   */

char	**change_my_env(char **cmd, char **my_env)
{
	char	*pwd;

	pwd = my_getenv(my_env, "PWD");
	if (!cmd[1])
	{
		my_env = change_pwd_home(my_env);
		my_env = change_oldpwd(pwd, my_env);
	}
	else if (cmd[1][0] == '/')
	{
		my_env = change_pwd_absolute(cmd[1], my_env);
		my_env = change_oldpwd(pwd, my_env);
	}
	else
		my_env = change_pwd_relativ(cmd[1], my_env);
	if (pwd)
		free(pwd);
	return (my_env);
}

/*
   if can't change directory (chdir return -1), exit statut = 1
   else change env (pwd, oldpwd), exit statut = 0
   */

int	change_dir(char **cmd, t_mem *mem)
{
	char	*home;

	home = my_getenv(mem->my_env, "HOME");
	if (!cmd[1])
	{
		if (chdir(home) == -1)
		{
			write(1, strerror(errno), ft_strlen(strerror(errno)));
			write(1, "\n", 1);
			free(home);
			return (0);
		}
	}
	else if (chdir(cmd[1]) == -1)
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
		free(home);
		return (0);
	}
	free(home);
	return (1);
}

void	ft_cd(char **cmd, t_mem *mem)
{	
	if (change_dir(cmd, mem))
	{
		mem->my_env = change_my_env(cmd, mem->my_env);
		mem->exit_statue = 0;
	}
	else
		mem->exit_statue = 1;
}
