/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minierrors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:46:50 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 14:54:36 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minierrors.h"

/*
*	This functin prints to the stderr file descriptor a message
*	depending on the error passed as argument, always returns -1.
*/
int	miniperror(t_error err)
{
	if (err == ERR_MULTILINE)
		ft_putstr_fd(2, "Multinline not supported\n");
	else if (err == ERR_MEM)
		ft_putstr_fd(2, "Memory error\n");
	else if (err == ERR_INVALID_FILE_OR_PATH)
		ft_putstr_fd(2, "Invalid file or path\n");
	else if (err == ERR_CMD_NOT_FOUND)
		ft_putstr_fd(2, "Command not found\n");
	else if (err == ERR_HOME_NOT_SET)
		ft_putstr_fd(2, "HOME not set\n");
	else if (err == ERR_WRONG_TOKEN)
		ft_putstr_fd(2, "Wrong token\n");
	return (-1);
}
