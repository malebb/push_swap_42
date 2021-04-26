#ifndef CHECKER_H
# define CHECKER_H
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include "ft.h"
# define TRUE	1
# define FALSE	0

typedef struct		s_nbr
{
	int				value;
	struct s_nbr	*next;
}					t_nbr;

int		gnl(char **line);

#endif
