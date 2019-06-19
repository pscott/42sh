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
  int				fg;
  int				num;
  char				current;
  int				stdin;
  int				stdout;
  int				stderr;
}					t_job;

t_job	*g_first_job;
pid_t	g_shell_pgid;
int		g_shell_is_interactive;

/*
**	Jobs functions
*/

void			init_shell(void);

/*
**	Processes functions
*/

t_process		*create_process(t_token *token_list);
t_process		*append_process(t_process **first_process, t_process *to_add);

void			put_job_in_background(t_job *j, int cont);
int				put_job_in_foreground(t_job *j, int cont);


int				launch_job(t_job *j, int foreground);
int				launch_process(t_process *p, pid_t pgid, int fds[2], int foreground);
void			set_group_id(pid_t pgid, int fg);
t_job			*create_job(t_token *tokens, int fg, int num);
t_job			*append_job(t_job **first_j, t_job *to_add);
t_process		*create_process_list(t_token *token_list);
int				get_processes_len(t_process *p);
int				get_last_num(t_job *j);
void			set_current(void);

char			*tokens_to_str(t_token *tokens);
/*
**
*/

int				wait_for_job(t_job *j);
void			update_status(void);

int				job_is_completed(t_job *j);
void			format_job_info(t_job *j, const char *status);
int				job_is_stopped(t_job *j);

int				mark_process_status(pid_t pid, int status);

t_token			*copy_job_tokens(t_token *tokens);
t_token			*copy_process_tokens(t_token *tokens);

void			do_job_notification(int verbose);

/*
**	Free functions
*/

void			free_job(t_job *j);
void			free_job_list(t_job *j);

#endif
