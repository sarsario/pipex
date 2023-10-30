/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:49:04 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/30 11:40:52 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Sets the first 'len' bytes of the memory area pointed to by 'b' to the value
** of unsigned char 'c'.
**
** b:   A pointer to the memory area to be set.
** c:   The value to be set. This is passed as an int, but it is converted to an
**      unsigned char before being written to memory.
** len: The number of bytes to be set to the value.
**
** Returns:
** A pointer to the memory area 'b'.
*/

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}
