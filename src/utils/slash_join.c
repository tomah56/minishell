/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:16:43 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/07 17:16:45 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*slash_join(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = (char *) malloc((len1 + len2 + 1 + 1) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	joined[len2 + len1 + 1] = '\0';
	while (len2-- > 0)
		joined[len2 + len1 + 1] = s2[len2];
	joined[len2 + len1 + 1] = '/';
	while (len1-- > 0)
		joined[len1] = s1[len1];
	return (joined);
}
