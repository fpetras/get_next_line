/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 08:34:24 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/19 04:03:55 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** revised GNL with no memory leaks and a
** provisional fix to enable proper reading from stdin,
** only works with BUFF_SIZE 1
** 😌
*/

static char	*remaining_lines(char *file)
{
	size_t i;

	i = 0;
	while (file[i] != '\0')
	{
		if (file[i] == '\n')
		{
			i++;
			return (&file[i]);
		}
		i++;
	}
	return (&file[i]);
}

static void	next_line(char *file, char **line)
{
	size_t	i;
	char	*next_line;

	i = ft_strcspn(file, "\n");
	next_line = ft_strnew(i);
	ft_memcpy(next_line, file, i);
	next_line[i] = '\0';
	line[0] = next_line;
}

static int	end_of_line(char *file, char **line)
{
	next_line(file, line);
	file = remaining_lines(file);
	return (1);
}

static int	get_next_line2(int ret, char *file, char **line)
{
	if (ret == -1)
		return (-1);
	if (file[0] == '\0')
	{
		free(file);
		return (0);
	}
	next_line(file, line);
	file = remaining_lines(file);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int				ret;
	char			*tmp;
	char			buf[BUFF_SIZE + 1];
	static char		*file[MAX_FD];

	if (fd < 0 || fd > MAX_FD || !line)
		return (-1);
	if (file[fd])
		free(file[fd]);
	file[fd] = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (ft_strequ(buf, "\n"))
			return (end_of_line(file[fd], line));
		tmp = file[fd];
		file[fd] = ft_strjoin(tmp, buf);
		free(tmp);
	}
	return (get_next_line2(ret, file[fd], line));
}
