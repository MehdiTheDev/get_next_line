/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nex_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabiad <elabiad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:53:32 by elabiad           #+#    #+#             */
/*   Updated: 2024/07/16 13:48:45 by elabiad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*filling(int fd)
{
	char	*buffer;
	static char	*stash;
	
	stash = malloc(sizeof(char) * BUFFER_SIZE);
	if (!stash)
		return;
	read(fd, buffer, BUFFER_SIZE);
	
}

char	*get_next_line(int fd)
{
	char	*buffer;
	int	bytes_read;
	
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	
	return(buffer);
}

int	main()
{
	int		fd;
	//char	*line;
	
	fd = open("text.txt", O_RDONLY);
	//while (1)
	//{
	//	line = get_next_line(fd);
	//	if (line == NULL)
	//		break;
	//	printf("%s\n", line);
	//	free(line);
	//}
	printf("%s\n", get_next_line(fd));
	return (0);
}