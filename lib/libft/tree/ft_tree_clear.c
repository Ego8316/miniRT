/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:34:20 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/16 16:28:25 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_clear(t_tree *tree, void (*del)(void *));

/**
 * @brief Recursively frees a binary tree, applying `del` to content.
 */
void	ft_tree_clear(t_tree *node, void (*del)(void *))
{
	if (node->left)
		ft_tree_clear(node->left, del);
	if (node->right)
		ft_tree_clear(node->right, del);
	del(node->content);
	free(node);
	return ;
}
