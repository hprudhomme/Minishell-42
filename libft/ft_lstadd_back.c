// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/12/20 16:56:48 by hprudhom          #+#    #+#             */
// /*   Updated: 2020/12/20 17:24:42 by hprudhom         ###   ########lyon.fr   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "libft.h"

// void	ft_lstadd_back(t_list **alst, t_list *new)
// {
// 	t_list	*last_elem;

// 	if (!*alst)
// 	{
// 		*alst = new;
// 		return ;
// 	}
// 	last_elem = ft_lstlast(*alst);
// 	last_elem->next = new;
// }
