// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_lstnew.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/12/20 16:44:54 by hprudhom          #+#    #+#             */
// /*   Updated: 2020/12/20 17:26:44 by hprudhom         ###   ########lyon.fr   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "libft.h"

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*elmt;

// 	elmt = ((t_list *)malloc(sizeof(*elmt)));
// 	if (!elmt)
// 		return (NULL);
// 	elmt->content = content;
// 	elmt->next = NULL;
// 	return (elmt);
// }
