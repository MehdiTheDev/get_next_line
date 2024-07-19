/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nex_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:53:32 by elabiad           #+#    #+#             */
/*   Updated: 2024/07/20 00:29:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return(result);
}

static char	*filling_stash(int fd, char *buffer, int bytes_read, char *stash)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i == 1 && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return NULL;
		}
		buffer[bytes_read] = '\0';
		if (stash == NULL)
			stash = ft_strdup("");
		stash = ft_strjoin_free(stash, buffer);
		while (stash[j])
		{
			if (stash[j] == '\0' || stash[j] == '\n')
				i = 0;
			j++;
		}
	}
	return (stash);
}

char	*filling_line(char *stash, char **new_stash)
{
	char	*line;
	int	f;
	
	line = malloc(sizeof(char) * (ft_strlen(stash) + 1));
	if (line == NULL)
		return NULL;
	f = 0;
	while (stash[f] != '\n' && stash[f] != '\0')
	{
		line[f] = stash[f];
		f++;
	}
	line[f] = stash[f];
	line[f + 1] = '\0';
	if (stash[f] == '\n')
		f++;
	*new_stash = ft_strdup(stash + f);
	free(stash);
	return(line);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;
	static char	*stash;
	int	bytes_read;
	
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return NULL;
	bytes_read = 1;
	stash = filling_stash(fd, buffer, bytes_read, stash);
	if (stash == NULL)
		return NULL;
	line = filling_line(stash, &stash);	
	free(buffer);
	return(line);
}

int	main()
{
	int		fd;
	
	fd = open("text.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%c", '\n');
	return (0);
}