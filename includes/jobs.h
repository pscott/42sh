#ifndef JOB_H
# define JOB_H

# include <ftsh.h>
# include <libterm.h>
# include <termios.h>
# include "lexer.h"


typedef struct			s_process
{
	struct s_process	*next;       /* next process in pipeline */
	t_token				*token_list;
	pid_t				pid;                  /* process ID */
	char				completed;             /* true if process has completed */
	char				stopped;               /* true if process has stopped */
	int					status;                 /* reported status value */
}						t_process;

typedef struct		s_job
{
  struct s_job		*next;           /* next active job */
  t_token			*token_list;
  struct s_process	*first_process;     /* list of processes in this job */
  pid_t				pgid;                 /* process group ID */
  char				notified;              /* true if user told about stopped job */
  struct termios	tmodes;
}					t_job;

static t_job	*g_first_job = NULL;
static pid_t	g_shell_pgid;

/*
**	Jobs functions
*/

void			init_shell(void);

/*
**	Processes functions
*/

t_process		create_process(t_token *token_list, pid_t pid);
t_process		*append_process(t_process **first_process, t_process *to_add);

void			put_job_in_background(t_job *j, int cont);
void			put_job_in_foreground(t_job *j, int cont);
#endif
