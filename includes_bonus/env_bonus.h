/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_BONUS_H
#  define ENV_BONUS_H

#  include "types_bonus.h"

/* Environment Creation and Management */
t_env	*create_env(char **envp);
t_env	*create_env_node(char *key, char *value);

/* Environment Operations */
char	*get_env_value(char *key, t_env *env);
void	set_env_value(char *key, char *value, t_env **env);
void	unset_env_value(char *key, t_env **env);
int		update_existing_env(t_env *current, char *value);

/* Environment Cleanup */
void	free_env(t_env *env);

#endif
