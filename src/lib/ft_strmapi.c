/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:11:41 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/30 11:42:24 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Applies the function 'f' to each character of the string 's'
** to create a new string.
**
** s:	The string to modify.
** f:	The function to apply.
**
** Returns:
** The new string created by applying 'f' to each character of 's',
** or NULL if the allocation fails.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*smapi;

	if (!s || !f)
		return (NULL);
	smapi = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!smapi)
		return (NULL);
	i = 0;
	while (s[i])
	{
		smapi[i] = f(i, s[i]);
		i++;
	}
	smapi[i] = '\0';
	return (smapi);
}
