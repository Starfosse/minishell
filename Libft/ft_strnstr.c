/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:23:05 by abouleau          #+#    #+#             */
/*   Updated: 2021/11/29 14:28:19 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (!little[0])
		return ((char *)big);
	while (big[i])
	{
		n = 0;
		while (big[i + n] == little[n] && (i + n) < len)
		{
			if (!big[i + n] && !little[n])
				return ((char *)&big[i]);
			n++;
		}
		if (!little[n])
			return ((char *)big + i);
		i++;
	}
	return (0);
}
