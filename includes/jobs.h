#ifndef JOB_H
# define JOB_H

# include <stdlib.h>
# include <termios.h>


typedef struct			s_process
{
	struct s_process	*next;       /* next process in pipeline */
	char				**argv;                /* for exec */
	pid_t				pid;                  /* process ID */
	char				completed;             /* true if process has completed */
	char				stopped;               /* true if process has stopped */
	int					status;                 /* reported status value */
}						t_process;

typedef struct		s_job
{
  struct s_job		*next;           /* next active job */
  char				*command;              /* command line, used for messages */
  struct s_process	*first_process;     /* list of processes in this job */
  pid_t				pgid;                 /* process group ID */
  char				notified;              /* true if user told about stopped job */
  struct termios	tmodes;      /* saved terminal modes */
  int				stdin, stdout, stderr;  /* standard i/o channels */
}					t_job;

static t_job *g_first_job = NULL;

#endif
