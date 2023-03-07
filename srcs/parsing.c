/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:33:40 by fboulang          #+#    #+#             */
/*   Updated: 2023/02/16 10:33:41 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

/* Fonctions de parsing provisioires;
cmd_parsesq = parse quand on sait que c'est des single quotes.
cmd_parsedq = parse quand on sait que c'est des double quotes.
cmd_parse = figure out c'est quoi la ligne actually. */

char	**cmd_parsesq(char *cmd)
{
	char	*buff[3];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i] == ' ')
		i++;
	j = i;
	while (cmd[i] != ' ')
		i++;
	buff[0] = ft_substr(cmd, j, i);
	while (cmd[i] == ' ')
		i++;
	j = i;
	while (cmd[i] != ' ')
		i++;
	buff[1] = ft_substr(cmd, j, i);
	while (cmd[i] == ' ')
		i++;
	j = i;
	i = ft_strlen(cmd);
	while (cmd[i] != 39)
		i--;
	buff[2] = ft_substr(cmd, j, i);
	buff[3] = NULL;
	return (buff);
}

char	**cmd_parse(char *cmd)
{
	//possible struct;
	char	**temp;
	int		cmdtype;
}

/* Ce que je dois parse; dans quelle ordre faire le parsing.
1. On découpe la ligne de commande en double tableau.
2. On vérifie si ce qui a l'intérieur de ce que nous avons découpée est une commande.
2.a. Si oui, on passe on point 3.
2.b. Si non, on envoie un message d'erreur.
3. On vérifie que les arguments sont valides.
3.a. Si oui, on passe au point 4.
3.b. Si non, on envoie un message d'erreur.
4. Si nécessaire, on remplace $var par les variables d'environements.
5. On éxécute la commande.*/

/* Pour découper la ligne de commande en double tableau.
1. Compter le nombre de 'mots' dans la ligne de commande.
1.a. Un mot est ici définie comme un ensemble de caractères délimité soit par un ou deux espaces.
1.b. Un ensemble de mots peut aussi être délimité entre deux quotes.
1.c. "Hello"World n'est qu'un seul mot.
2. Assigner au tableau de la mémoire égale au nombre de mots + 1.
3. Remplacer dans la ligne de commande les $var par la variable d'environnement correspondante.
4. S'il y a des quotes fermées, regarder à l'intérieur des quotes et faire les opérations appropriées.
4.a. Single quotes : ne rien faire du tout, laissé tout comme telle moins les quotes.
4.b. Double quotes : remplacer $var par la variable d'environement correspondante, ne rien faire d'autre.
5. Enlever les quotes.
6. Utiliser la commande substr pour découper la commande avec les bonnes proportions plutôt que split.
7. Retourner le nouveau tableau.*/

/* Pour vérifier que ce que nous avons découpé est une commande : 
1. ft_strjoin cmd[0] et '/'.
2. On check si le path complet existe.
2.a. Si oui, c'est une commande. On arrête ici et on continue le parsing.
2.b. Si non, ce n'est pas une commande. On marque une erreur.*/

/* Pour vérifier que les arguments sont valides :
1. */


char	*get_env_var(char *var, char **env)
{
	int		i;
	char	*s;

	s = make_env_var(var);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
			return (convert_env_var(s, env, i));
		else
			i++;
	}
	free (s);
	s = ft_calloc (1, sizeof(char));
	return (s);
}

char	*make_env_var(char *var)
{
	int		i;
	int		j;
	char	*s;

	i = 1;
	j = 0;
	s = ft_calloc(ft_strlen(var), sizeof(char));
	while (var[i] != '\0')
	{
		s[j] = var[i];
		i++;
		j++;
	}
	s[j] = '=';
	return (s);
}

char	*convert_env_var(char *var, char **env, int index)
{
	int		i;
	int		j;
	char	*s;
	char	*temp;

	s = ft_calloc(ft_strlen(env[index]) -  ft_strlen(var) + 1, sizeof(char));
	i = 0;
	j = 0;
	temp = env[index];
	while (temp[i] != '=')
		i++;
	while (temp[i++] != '\0')
	{
		s[j] = temp[i];
		j++;
	}
	free (var);
	return (s);
}

char	*put_env_var(char *var, char *arg, int varlen)
{
	int		i;
	int		j;
	int		k;
	char	*buff;

	buff = ft_calloc(ft_strlen(arg) + ft_strlen(var) - varlen, sizeof(char));
	i = 0;
	j = -1;
	k = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '$')
		{
			i = advance_index(arg, i);
			while (var[j++] != '\0')
			{
				buff[k] = var[j];
				k++;
			}
		}
		buff[k] = arg[i];
		k++;
		i++;
	}
	return (buff);
}

int	advance_index(char *arg, int i)
{
	while (arg[i] != ' ' && arg[i] != '"' && arg[i] != 39 && arg[i] != '\0')
		i++;
	return (i);
}
