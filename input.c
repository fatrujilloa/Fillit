/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 11:07:38 by ftrujill          #+#    #+#             */
/*   Updated: 2018/12/22 15:45:04 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			print_error(void)
{
	write(1, "error\n", 6);
	return (0);
}

int			print_usage(void)
{
	write(1, "Usage: fillit fichier_cible\n", 28);
	return (0);
}

void		print_tetris(char ***tetris)
{
	int i;
	int j;

	i = 0;
	while (tetris[i])
	{
		j = 0;
		while (tetris[i][j])
		{
			ft_putstr(tetris[i][j]);
			ft_putchar('\n');
			j++;
		}
		i++;
		if (tetris[i])
			ft_putchar('\n');
	}
}

int			free_tetris(char ***tetris, int i, int j)
{
	int k;
	int l;

	k = 0;
	while (k <= i && tetris[k])
	{
		l = 0;
		while (l < (k == i ? j : 4))
			free((tetris[k])[l++]);
		free (tetris[k++]);
	}
	free(tetris);
	return (0);
}

int			input_to_tetris(int fd, char ***tetris)
{
	int 	i;
	int		j;
	ssize_t	rd;
	char	buff[5];

	i = 0;
	while (i != -1)
	{
		if (!(tetris[i] = (char**)malloc(5 * sizeof(char*))))
			return (-1);
		j = 0;
        while (j < 4)
		{
			if ((rd = read(fd, buff, 5)) != 5 || buff[4] != '\n')
				return(free_tetris(tetris, i ,j));
		buff[4] = 0;
		if (!(tetris[i][j++] = ft_strdup(buff)))
			return (-1);
		}
		tetris[i++][j] = 0;
		if (!(rd = read(fd, buff, 1)))
		{
			tetris[i] = 0;
			return (1);
		}
		if (buff[0] != '\n')
			return (free_tetris(tetris, i ,j));
	}
	return (1);
}

int			main(int argc, char **argv)
{
	int		fd;
	char	***tetris;

	if (argc != 2)
		return (print_usage());
	if ((fd = open(argv[1], O_RDONLY)) == -1 
		|| !(tetris = (char***)malloc(26 * sizeof(char **)))
		|| input_to_tetris(fd, tetris) != 1)
		return (print_error());
	write(1, "Stocked\n", 8);
	print_tetris(tetris);
	free_tetris(tetris, 26, 4);
	return(0);
}
