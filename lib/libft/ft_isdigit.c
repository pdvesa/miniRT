/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:52:37 by jcayot            #+#    #+#             */
/*   Updated: 2023/10/27 10:38:56 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Check if a character is a digit.
 *
 * This function checks if the given character is a digit by comparing it
 * against the ASCII values of '0' and '9'.
 *
 * @param c The character to check.
 * @return Returns 1 if the character is a digit, and 0 otherwise.
 */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
