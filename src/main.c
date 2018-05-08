/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 01:06:30 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/08 19:54:29 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

size_t		ls_strlen_printing(char *name)
{
	size_t		i;

	i = 0;
	while (*name)
	{
		if ((*name | 0x7F) != 0x7F)
		{
			name += sizeof(wchar_t);
			i += 2;
		}
		else
		{
			++name;
			++i;
		}
	}
	return (i);
}

size_t		count_files(const char *path)
{
	DIR				*dir;
	struct dirent	*dp;
	size_t			count;

	dir = opendir(path);
	count = 0;
	if (dir == NULL)
		return (0);
	while ((dp = readdir(dir)) != NULL)
	{
		if (!(!g_params['a'] && dp->d_name[0] == '.'))
			++count;
	}
	closedir(dir);
	return (count);
}

void		reset_max_length(void)
{
	g_max_length.links = 0;
	g_max_length.login = 0;
	g_max_length.group = 0;
	g_max_length.size = 0;
	g_max_length.name = 0;
}

void		fill_max_length(t_stat_name *file)
{
	int	temp;

	if (g_params['l'])
	{
		if ((temp = ft_nbr_size(file->stat.st_nlink)) > g_max_length.links)
			g_max_length.links = temp;
		if ((temp = ft_strlen(getpwuid(file->stat.st_uid)->pw_name))
				> g_max_length.login)
			g_max_length.login = temp;
		if ((temp = ft_strlen(getgrgid(file->stat.st_gid)->gr_name))
				> g_max_length.group)
			g_max_length.group = temp;
		if (S_ISBLK(file->stat.st_mode) || S_ISCHR(file->stat.st_mode))
			(g_max_length.size < 8) ? g_max_length.size = 8 : 0;
		else if ((temp = ft_nbr_size(file->stat.st_size)) > g_max_length.size)
			g_max_length.size = temp;
	}
	if ((temp = ft_strlen(file->name)) > g_max_length.name)
		g_max_length.name = temp;
}

char		check_stat(char *name, t_stat_name ***files, size_t last)
{
	size_t i;

	if (lstat(name, &((*files)[last]->stat)) != -1 ||
		(!g_params['l'] && !g_params['R']) || stat(name, &((*files)[last]->stat)) != -1)
		return (0);
	i = 0;
	while (i < last)
	{
		free((*files)[i]->pathname);
		free((*files)[i]->name);
		free((*files)[i]);
		++i;
	}
	free((*files)[i]->pathname);
	free((*files)[i]);
	free((*files));
	return (-1);
}

char		fill_stats(t_stat_name ***files, const char *path, size_t *total)
{
	DIR				*dir;
	struct dirent	*dp;
	size_t			count;
	char			*tempdir;

	count = 0;
	SMARTCHECK(dir = opendir(path));
	while ((dp = readdir(dir)) != NULL)
	{
		if (!g_params['a'] && dp->d_name[0] == '.')
			continue ;
		EXITZERO((*files)[count] = (t_stat_name *)malloc(sizeof(t_stat_name)));
		tempdir = ls_strjoin_path(path, dp->d_name);
		(*files)[count]->pathname = tempdir;
		if (check_stat(tempdir, files, count) == -1)
		{
			closedir(dir);
			return (-1);
		}
		(*files)[count]->isdir = ((!IS_CURPREV(dp->d_name) &&
					S_ISDIR((*files)[count]->stat.st_mode))) ? 1 : 0;
		(*files)[count]->name = strdup(dp->d_name);
		fill_max_length((*files)[count]);
		*total += (*files)[count]->stat.st_blocks;
		++count;
	}
	closedir(dir);
	return (0);
}

void		sort_stats(t_stat_name **files, size_t amfiles)
{
	if (g_params['f'])
		return ;
	if (g_params['t'])
	{
		if (g_params['u'])
			quicksort_atime(files, 0, amfiles - 1, g_params['r']);
		else
			quicksort_time(files, 0, amfiles - 1, g_params['r']);
	}
	else
		quicksort_name(files, 0, amfiles - 1, g_params['r']);
	return ;
}

void		print_acl(t_stat_name *file)
{
	acl_t		acl;
	acl_entry_t	entry;

	if ((listxattr(file->pathname, 0, 0, XATTR_NOFOLLOW)) > 0)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "@");
	else if ((acl = acl_get_link_np(file->pathname, ACL_TYPE_EXTENDED)))
	{
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "+");
		free(acl);
	}
	else
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " ");
}

void		print_chmod_exec(t_stat_name *file, int order, size_t bit)
{
	mode_t	mode;

	mode = file->stat.st_mode;
	if (order == 2 || order == 1)
	{
		if (mode & bit)
			mode & (0x200 << order) ? ft_snprintf(g_buff.line, g_buff.cur, "s")
				: ft_snprintf(g_buff.line, g_buff.cur, "x");
		else
			mode & (0x200 << order) ? ft_snprintf(g_buff.line, g_buff.cur, "S")
				: ft_snprintf(g_buff.line, g_buff.cur, "-");
	}
	else
	{
		if (mode & bit)
			mode & 0x200 ? ft_snprintf(g_buff.line, g_buff.cur, "t")
				: ft_snprintf(g_buff.line, g_buff.cur, "x");
		else
			mode & 0x200 ? ft_snprintf(g_buff.line, g_buff.cur, "T")
				: ft_snprintf(g_buff.line, g_buff.cur, "-");
	}
}

void		print_chmod_access(t_stat_name *file)
{
	mode_t	mode;
	int		i;
	size_t	j;
	size_t	temp;

	mode = file->stat.st_mode;
	i = 8;
	while (i >= 0)
	{
		temp = 1;
		temp <<= i;
		if (!(i % 3))
			print_chmod_exec(file, i / 3, temp);
		else if (mode & temp)
		{
			if ((i % 3) == 1)
				g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "w");
			else if ((i % 3) == 2)
				g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "r");
		}
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "-");
		--i;
	}
}

void			print_chmod(t_stat_name *file)
{
	if (S_ISLNK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "l");
	else if (S_ISDIR(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "d");
	else if (S_ISCHR(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "c");
	else if (S_ISBLK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "b");
	else if (S_ISSOCK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "s");
	else if (S_ISFIFO(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "p");
	else
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "-");
	print_chmod_access(file);
	print_acl(file);
}

void		print_color_name(t_stat_name *file)
{
	if (!g_params['G'])
	{
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s", file->name);
		return ;
	}
	if (S_ISDIR(file->stat.st_mode))
	{
		if (file->stat.st_mode & 02 && file->stat.st_mode & 01000)
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_BLACK ANSI_COLOR_BGREEN);
		else if (file->stat.st_mode & 02 && !(file->stat.st_mode & 01000))
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_BLACK ANSI_COLOR_BYELLOWN);
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_BLUE);
	}
	else if (S_ISLNK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_MAGENTA);
	else if (S_ISSOCK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_GREENN);
	else if (S_ISFIFO(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_YELLOWN);
	else if (S_ISBLK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_BLUE ANSI_COLOR_BCYAN);
	else if (S_ISCHR(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_BLUE ANSI_COLOR_BYELLOWN);
	else if (access(file->pathname, X_OK) != -1)
	{
		if (file->stat.st_mode & 04000)
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_BLACK ANSI_COLOR_BRED);
		else if (file->stat.st_mode & 02000)
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_BLACK ANSI_COLOR_BCYAN);
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_RED);
	}
	else
	{
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s", file->name);
		return ;
	}
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s"ANSI_COLOR_RESET, file->name);
}

void		print_date_name(t_stat_name *file)
{
	time_t	timefile;
	char	*timefilestr;
	time_t	diffmodify;

	timefile = g_params['u'] ? file->stat.st_atimespec.tv_sec : file->stat.st_mtimespec.tv_sec;
	timefilestr = ctime(&timefile);
	diffmodify = time(0);
	diffmodify = diffmodify > timefile ?
		diffmodify - timefile : timefile - diffmodify;
	if (diffmodify > 1.557e+7)
	{
		timefilestr[11] = 0;
		timefilestr[24] = 0;
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s %s %s",
				timefilestr + 4, timefilestr + 20, file->name);
		return ;
	}
	timefilestr[16] = 0;
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s ", timefilestr + 4);
	print_color_name(file);
}

void		print_link(t_stat_name *file)
{
	char	*pathfile;
	size_t	lim;
	ssize_t	ret;

	if (!S_ISLNK(file->stat.st_mode))
	{
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
		return ;
	}
	lim = 2;
	EXITZERO(pathfile = malloc(sizeof(char) * lim));
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " -> ");
	while ((ret = readlink(file->pathname, pathfile, lim - 1)) == lim - 1)
	{
		free(pathfile);
		lim *= 2;
		EXITZERO(pathfile = malloc(sizeof(char) * lim));
	}
	pathfile[ret] = 0;
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, pathfile);
	free(pathfile);
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
}

void		print_minmaj(t_stat_name *file)
{
	int32_t	minor;
	int32_t	major;

	minor = MINOR(file->stat.st_rdev);
	major = MAJOR(file->stat.st_rdev);
	if (minor > 255 || minor < 0)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur,
				" %3d, 0x%08x ", major, minor);
	else
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur,
				" %3d, %3d ", major, minor);
}

void		handle_width_tty(t_stat_name **files, size_t amfiles,
		size_t *columns, size_t *rows)
{
	struct winsize	ws;
	size_t			sum_name;
	size_t			tabmax;

	*rows = 1;
	*columns = amfiles;
	if (ioctl(0, TIOCGWINSZ, &ws) != 0)
		return ;
	tabmax = 8 * ((g_max_length.name / 8) + 1);
	sum_name = amfiles * tabmax;
	if (!ws.ws_col || !sum_name)
		return ;
	while (ceil((double)amfiles / *rows) * tabmax > ws.ws_col)
	{
		++(*rows);
		if (!*rows)
		{
			*rows = 0;
			*columns = 0;
			return ;
		}
	}
	*columns = ceil((double)amfiles / *rows);
}

void		print_smooth_stats(t_stat_name **files, size_t num, char *first,
		int *lastnamesize)
{
	int				j;
	int				temp;
	int				tabmax;

	if (!*first)
	{
		print_color_name(files[num]);
		*first = 1;
		*lastnamesize = ls_strlen_printing(files[num]->name);
	}
	else
	{
		j = 0;
		tabmax = 8 * ((g_max_length.name / 8) + 1);
		temp = ceil((tabmax - *lastnamesize) / (double)8);
		if (!temp)
			temp = 1;
		while (j < temp)
		{
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\t");
			++j;
		}
		print_color_name(files[num]);
		*lastnamesize = ls_strlen_printing(files[num]->name);
	}
}

void		print_l_stats(t_stat_name **files, size_t amfiles)
{
	size_t	i;

	i = 0;
	while (i < amfiles)
	{
		print_chmod(files[i]);
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " %*d ",
				g_max_length.links, files[i]->stat.st_nlink);
		if (!g_params['g'])
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%-*s  ",
					g_max_length.login, getpwuid(files[i]->stat.st_uid)->pw_name);
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%-*s ",
				g_max_length.group, getgrgid(files[i]->stat.st_gid)->gr_name);
		if (S_ISCHR(files[i]->stat.st_mode) || S_ISBLK(files[i]->stat.st_mode))
			print_minmaj(files[i]);
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " %*d ",
				g_max_length.size, files[i]->stat.st_size); 
		print_date_name(files[i]);
		print_link(files[i]);
		++i;
	}
}

void		print_stats(t_stat_name **files, size_t amfiles)
{
	char	first;
	int		lastnamesize;
	t_iter	iter;
	t_tty_params	ttyparams;

	lastnamesize = 0;
	iter.j = 0;
	if (g_params['1'])
	{
		while (iter.j < amfiles)
		{
			print_color_name(files[iter.j]);
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
			++(iter.j);
		}
		return ;
	}
	handle_width_tty(files, amfiles, &ttyparams.columns, &ttyparams.rows);
	while (iter.j < ttyparams.rows)
	{
		first = 0;
		iter.i = 0;
		while (iter.i < ttyparams.columns)
		{
			if (iter.i * ttyparams.rows + iter.j >= amfiles)
				break;
			print_smooth_stats(files, iter.i * ttyparams.rows + iter.j, &first,
					&lastnamesize);
			++(iter.i);
		}
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
		++(iter.j);
	}
}

void		free_stats(t_stat_name **files, size_t amfiles)
{
	size_t i;

	i = 0;
	while (i < amfiles)
	{
		free(files[i]->name);
		free(files[i]->pathname);
		free(files[i]);
		++i;
	}
	free(files);
}

char		check_dir(const char *path)
{
	DIR			*dir;

	dir = opendir(path);
	if (!dir)
	{
//		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur,
//				"%s: %s: %s\n", g_nameapp, path, strerror(errno));
		write(1, g_buff.line, g_buff.cur);
		fprintf(stderr, "%s: %s: %s\n", g_nameapp, ft_strrchr(path, '/') + 1, strerror(errno));
		g_buff.cur = 0;
		return (0);
	}
	closedir(dir);
	return (1);
}

int			main(int argc, char **argv)
{
	int		posafterparams;

	EXITZERO(g_buff.line = malloc(PRINTF_BUFF_SIZE));
	g_buff.cur = 0;
	g_nameapp = argv[0];
	posafterparams = fill_params(argc, argv);
	print_files(argc, argv, posafterparams);
	write(1, g_buff.line, g_buff.cur);
	free(g_buff.line);
	system("leaks ft_ls");
}
