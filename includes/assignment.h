/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:58:12 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/23 17:50:50 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSIGNMENT_H
# define ASSIGNMENT_H

# include "types.h"

int	is_assignment(char *str);
int	process_assignment(char *assignment, t_shell *shell);
int	process_all_assignments(char **args, t_shell *shell);

#endif