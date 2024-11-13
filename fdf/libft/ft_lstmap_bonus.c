/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:02:48 by inajah            #+#    #+#             */
/*   Updated: 2024/11/05 14:02:52 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*_ft_lstclear(t_list **lst, void (*del)(void*))
{
	ft_lstclear(lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void*))
{
	t_list	*new_elem;
	t_list	*new_list;
	void	*content;

	if (!f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = (*f)(lst->content);
		if (!content)
			return (_ft_lstclear(&new_list, del));
		new_elem = ft_lstnew(content);
		if (!new_elem)
		{
			(*del)(content);
			content = NULL;
			return (_ft_lstclear(&new_list, del));
		}
		ft_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}
