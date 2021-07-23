/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minierrors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:41:14 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 15:30:13 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIERRORS_H
# define MINIERRORS_H
# include "utils.h"

typedef enum e_error
{
	ERR_MULTILINE,
	ERR_MEM,
	ERR_INVALID_FILE_OR_PATH,
	ERR_CMD_NOT_FOUND,
	ERR_HOME_NOT_SET,
	ERR_WRONG_TOKEN
}			t_error;

int			miniperror(t_error err);
#endif