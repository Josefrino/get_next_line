/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josvieir <josvieir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:48:43 by josvieir          #+#    #+#             */
/*   Updated: 2024/02/17 18:49:11 by josvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(temp), temp = NULL, NULL);
	if (has_new_line(temp))
		return (extract_line(&temp));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = 0;
		temp = ft_strjoin(temp, buffer);
		if (has_new_line(temp))
			break ;
	}
	if (buffer)
		free(buffer);
	buffer = NULL;
	return (extract_line(&temp));
}

/*int main(void)
{
	int fd = open("fd", O_RDONLY);
	char	*str;
	int		i = 0;

	while (i < 10)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		i++;
	}
	return (0);
}*/