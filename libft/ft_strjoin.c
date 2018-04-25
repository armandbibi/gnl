/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 20:37:27 by abiestro          #+#    #+#             */
/*   Updated: 2018/04/24 18:58:15 by abiestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*dest;
	char	*d;
	
	if (!s1)
		return (ft_strdup(s2));
	if(!s2)
		return (ft_strdup(s2));
	i = ft_strlen(s1) + ft_strlen(s2);
	if ((dest = malloc(sizeof(char) * i) + 1) == 0)
		return (NULL);
	d = dest;
	while (*s1)
		*d++ = *s1++;
	while (*s2)
		*d++ = *s2++;
	*d = '\0';
	return (dest);
}
