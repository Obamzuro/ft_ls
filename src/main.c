/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 01:06:30 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 23:06:31 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		fill_params(t_params_corr *params)
{
	size_t	i;
i = 0;
	while (i < AM_PARAMS)
	{
//		params[i].name = i;
		params[i].ascii = PARAMS[i];
		params[i].exist = 0;
		++i;
	}
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
		++count;
	closedir(dir);
	return (count);
}

void		reset_max_length(void)
{
	g_max_length.links = 1;
	g_max_length.login = 1;
	g_max_length.group = 1;
	g_max_length.size = 1;
}

void		fill_max_length(t_stat_name *file)
{
	int	temp;

	temp = ft_nbr_size(file->stat.st_nlink);
	if (temp > g_max_length.links)
		g_max_length.links = temp;
	temp = ft_strlen(getpwuid(file->stat.st_uid)->pw_name);
	if (temp > g_max_length.login)
		g_max_length.login = temp;
	temp = ft_strlen(getgrgid(file->stat.st_gid)->gr_name);
	if (temp > g_max_length.group)
		g_max_length.group = temp;
	if (file->stat.st_mode & S_IFBLK)
	{
		if (8 > g_max_length.size)
			g_max_length.size = 8;
	}
	else
	{
		temp = ft_nbr_size(file->stat.st_size);
		if (temp > g_max_length.size)
			g_max_length.size = temp;
	}
}

void		fill_stats(t_stat_name **files, const char *path, size_t *total)
{
	DIR				*dir;
	struct dirent	*dp;
	size_t			count;
	char			*tempdir;

	count = 0;
	dir = opendir(path);
	if (dir == NULL)
		return ;
	while ((dp = readdir(dir)) != NULL)
	{
		files[count] = (t_stat_name *)malloc(sizeof(t_stat_name));
		files[count]->isdir = 0;
		tempdir = ls_strjoin_path(path, dp->d_name);
		files[count]->pathname = tempdir;
		if (lstat(tempdir, &(files[count]->stat)) == -1)
			stat(tempdir, &(files[count]->stat));
		if (!IS_CURPREV(dp->d_name) && S_ISDIR(files[count]->stat.st_mode))
			files[count]->isdir = 1;
		files[count]->name = strdup(dp->d_name);
		fill_max_length(files[count]);
		*total += files[count]->stat.st_blocks;
		++count;
	}
	closedir(dir);
}

void		sort_stats(t_stat_name **files, size_t amfiles)
{
	quicksort_name(files, 0, amfiles - 1);
	return ;
}

void		print_acl(t_stat_name *file)
{
	acl_t acl;
	acl_entry_t entry;

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
			mode & (0x200 << order) ? ft_snprintf(g_buff.line, g_buff.cur, "s") : ft_snprintf(g_buff.line, g_buff.cur, "x");
		else
			mode & (0x200 << order) ? ft_snprintf(g_buff.line, g_buff.cur, "S") : ft_snprintf(g_buff.line, g_buff.cur, "-");
	}
	else
	{
		if (mode & bit)
			mode & 0x200 ? ft_snprintf(g_buff.line, g_buff.cur, "t") : ft_snprintf(g_buff.line, g_buff.cur, "x");
		else
			mode & 0x200 ? ft_snprintf(g_buff.line, g_buff.cur, "T") : ft_snprintf(g_buff.line, g_buff.cur, "-");
	}
}

void		print_chmod(t_stat_name *file)
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

int			ret_chmod_isdir(t_stat_name *file)
{
	int mode;

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
	mode = 0;
	print_chmod(file);
	print_acl(file);
	return (mode);
}

void		print_date(t_stat_name *file)
{
	time_t	timefile;
	char	*timefilestr;
	time_t	diffmodify;

	timefile = file->stat.st_mtimespec.tv_sec;
	timefilestr = ctime(&timefile);
	diffmodify = time(0);
	diffmodify = diffmodify > timefile ? diffmodify - timefile : timefile - diffmodify;
	if (diffmodify > 1.557e+7)
	{
		timefilestr[11] = 0;
		timefilestr[24] = 0;
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s %s %s", timefilestr + 4, timefilestr + 20, file->name);
		return ;
	}
	timefilestr[16] = 0;
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s %s", timefilestr + 4, file->name);
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
	pathfile = malloc(sizeof(char) * lim);
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " -> ");
	while ((ret = readlink(file->pathname, pathfile, lim - 1)) == lim - 1)
	{
		free(pathfile);
		lim *= 2;
		pathfile = malloc(sizeof(char) * lim);
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
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " %3d, 0x%08x ", major, minor);
	else
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " %3d, %3d ", major, minor);
}

void		print_stats(t_stat_name **files, size_t amfiles)
{
	size_t	i;
	size_t	dircount;
	int		mode;
	char	*date;

	i = 0;
	dircount = 0;
	while (i < amfiles)
	{
		mode = ret_chmod_isdir(files[i]);
		if (S_ISCHR(files[i]->stat.st_mode) || S_ISBLK(files[i]->stat.st_mode))
		{
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " %*d %-*s  %-*s ", g_max_length.links, files[i]->stat.st_nlink, 
				g_max_length.login, getpwuid(files[i]->stat.st_uid)->pw_name, 
				g_max_length.group, getgrgid(files[i]->stat.st_gid)->gr_name);
			print_minmaj(files[i]);
		}
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " %*d %-*s  %-*s  %*d ", g_max_length.links, files[i]->stat.st_nlink,
				g_max_length.login, getpwuid(files[i]->stat.st_uid)->pw_name,
				g_max_length.group, getgrgid(files[i]->stat.st_gid)->gr_name,
				g_max_length.size, files[i]->stat.st_size); print_date(files[i]);
		print_link(files[i]);
		++i;
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

char		check_access(const char *path, char isrecursion)
{
	if (access(path, R_OK) == -1)
	{
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "./ls: %s: %s\n", path, strerror(errno));
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		return (0);
	}
	return (1);
}

char		check_dir(const char *path)
{
	DIR *dir;

	dir = opendir(path);
	if (!dir)
	{
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "./ls: %s: %s\n", path, strerror(errno));
		return (0);
	}
	closedir(dir);
	return (1);
}

void		print_dir(const char *path, char isrecursion)
{
	t_stat_name		**files;
	size_t			amfiles;
	size_t			i;
	size_t			total;

	if (isrecursion)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n%s:\n", path);
	if (!check_dir(path) || !check_access(path, isrecursion))
		return ;
	total = 0;
	reset_max_length();
	amfiles = count_files(path);
	files = (t_stat_name **)malloc(sizeof(t_stat_name *) * amfiles);
	fill_stats(files, path, &total);
	sort_stats(files, amfiles);
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "total %zu\n", total);
	print_stats(files, amfiles);
	i = 0;
	while (i < amfiles)
	{
		if (files[i]->isdir)
			print_dir(files[i]->pathname, 1);
		++i;
	}
	free_stats(files, amfiles);
}

int			main(int argc, char **argv)
{
	t_params_corr	params[AM_PARAMS];

	g_buff.line = malloc(PRINTF_BUFF_SIZE);
	g_buff.cur = 0;
	fill_params(params);
	print_dir(argv[1], 0);
	write(1, g_buff.line, g_buff.cur);
	free(g_buff.line);
//	system("leaks ls");
}
