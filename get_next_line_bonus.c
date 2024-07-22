/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabiad <elabiad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:53:32 by elabiad           #+#    #+#             */
/*   Updated: 2024/07/22 17:55:40 by elabiad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
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
			return (NULL);
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
	int		f;

	line = malloc(sizeof(char) * (ft_strlen(stash) + 2));
	if (line == NULL)
		return (NULL);
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
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;
	int			bytes_read;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	stash = filling_stash(fd, buffer, bytes_read, stash);
	free(buffer);
	if (stash == NULL || *stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = filling_line(stash, &stash);
	return (line);
}

 int main(int argc, char **argv) {
     int fd;
     char *line;

     if (argc != 2)
         return (1);
     fd = open(argv[1], O_RDONLY);
     if (fd == -1)
         return (1);
     while ((line = get_next_line(fd)) != NULL) {
         printf("%s", line);
         free(line);
     }
     close(fd);
 	printf("\n");
     return (0);
 }