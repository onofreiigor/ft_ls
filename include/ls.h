/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <okosiako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 16:48:15 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/12 14:38:14 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>
# include <time.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include "../printf/include/include.h"
# include "assert.h"

# define OPTIONS	"1AGRSaflrtx"
# define R_SORT		'r'
# define T_SORT		't'
# define S_SORT		'S'
# define N_SORT		'f'
# define RECURS		'R'
# define DOT		'a'
# define L_FORMAT	'l'
# define C_FORMAT	'1'
# define A_FORMAT	'A'
# define X_FORMAT	'x'
# define COLORS		'G'

# define BLUE	"\e[3;34m"
# define RED	"\e[0;31m"
# define MAG	"\e[0;35m"
# define GR		"\e[0;32m"
# define BR		"\e[0;33m"
# define BL_YEL	"\e[0;34;43m"
# define BL_CYN	"\e[0;34;46m"
# define NORM	"\e[0m"

/*
** defines for permissions "wrxwrxwrx"
*/

# define S_ISRUSR(m) (m & S_IRUSR)
# define S_ISWUSR(m) (m & S_IWUSR)
# define S_ISXUSR(m) (m & S_IXUSR)
# define S_ISRGRP(m) (m & S_IRGRP)
# define S_ISWGRP(m) (m & S_IWGRP)
# define S_ISXGRP(m) (m & S_IXGRP)
# define S_ISROTH(m) (m & S_IROTH)
# define S_ISWOTH(m) (m & S_IWOTH)
# define S_ISXOTH(m) (m & S_IXOTH)

# define S_ISSUSR(m) (m & S_ISUID)
# define S_ISSGRP(m) (m & S_ISGID)
# define S_ISTOTH(m) (m & S_ISTXT)

/*
** width block for * in ft_printf
*/

# define W_LINKS	param[0]
# define W_USER		param[1]
# define W_GROUP	param[2]
# define W_SIZE		param[3]
# define W_BLOCKS	param[4]
# define W_MINOR	param[5]
# define W_MAJOR 	param[6]
# define W_NAME		param[7]

/*
** lists for names
*/

# define DIR_LIST	lists[0]
# define ERROR_LIST	lists[1]
# define FILE_LIST	lists[2]

/*
** list for options
*/

# define O_FORMAT	options[0]
# define O_SORT		options[1]
# define O_FILES	options[2]
# define O_RECURS	options[3]
# define O_COLORS	options[4]
# define O_REVERS	options[5]

/*
** for time printing
*/

# define SECONDS 15769999.9998992
# define IS_HALF(c_t) ((time(0) - c_t) > SECONDS)

typedef struct		s_curr
{
	char			*name;
	char			*path;
	char			*link_path;
	struct stat		info;
	char			*pw_name;
	char			*gr_name;
	ssize_t			lx;
	acl_t			acl;
	struct s_curr	*next;
}					t_curr;

/*
** different useful functions
*/

void				ft_options(char *str, char *options);
void				ft_make_param(t_curr *temp, int *param);

/*
** creates arrays with names of files, errors and directories
*/

void				ft_dir_list(t_list **dir, t_list **error, t_list **file,
							const char *av);

/*
** working with arrays of names
*/

void				ft_work_dir_list(t_list **dir, char *options, int files);
void				ft_work_fl_list(t_list **error, char *options);
void				ft_work_er_list(t_list **error);

/*
** errorrs
*/

void				ft_errors(const char *name, char c, int mistake);

/*
** list block
*/

void				ft_make_list(t_curr **res, char *path, int *param,
									char *options);
t_curr				*ft_lcreate(char *name, char *path);
void				ft_ladd(t_curr **root, t_curr *new, char *options);
void				ft_str_del(t_curr **t);
int					ft_list_count(t_curr *list);
t_curr				*ft_get_elem(t_curr *list, int n);

void				ft_ladd_2(t_list **root, t_list *new);
void				ft_str_list(t_list **t);

/*
** recursion
*/

void				ft_recurse(t_curr *t, int *param, char *options);

/*
** print block
*/

void				ft_lprint(t_curr *root, int *param, char *options);
void				ft_print_x(t_curr *root, int *param, char color);
void				ft_print_n(t_curr *root, int *param, char color);
void				ft_print_long(t_curr *root, int *param, char color);

void				ft_pr_mode(t_curr *root);
void				ft_pr_type(t_curr *root);
void				ft_lprint_color(t_curr *root, int width);

#endif
