/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:29:43 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/30 11:39:50 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Tests whether the given character is a printable ASCII character.
** A printable ASCII character is any character between 32 and 126,
** inclusive.
**
** c:	The character to be checked.
**
** Returns:
** Non-zero value if the character is a printable ASCII character,
** 0 otherwise.
*/

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
