/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunmigu <brunmigu@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:04:10 by brunmigu          #+#    #+#             */
/*   Updated: 2025/05/04 13:08:32 by brunmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_new_line(list);
	next_str = malloc(str_len);
	if (!next_str)
		return (NULL);
	return (next_str);
}

void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	list = NULL;
	/* Se o fd for < 0
		|| o read retorna um valor <0 se nao conseguir ler (é um cotrole se o read consegue abrir o file)*/
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0))
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
}
