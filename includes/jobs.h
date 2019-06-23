#ifndef JOB_H
# define JOB_H

# include <ftsh.h>
# include <libterm.h>
# include <termios.h>
# include "lexer.h"
# include "ast.h"

typedef enum			e_job_opt
{
	ERROR,
	DEFAULT,
	PID,
	LONG
}						t_job_opt;
typedef struct			s_process
{
	struct s_process	*next;       /* next process in pipeline */
	t_token				*token_list;
	char				*process_str;
	pid_t				pid;                  /* process ID */
	int					status;                 /* reported status value */
	char				completed;             /* true if process has completed */
	char				stopped;               /* true if process has stopped */
}						t_process;

typedef struct		s_job
{
	struct s_job		*next;           /* next active job */
	char				*command;
	struct s_process	*first_process;     /* list of processes in this job */
	int				fg;
	int				num;
	int				status;
	int				stdin;
	int				stdout;
	int				stderr;
	pid_t				pgid;                 /* process group ID */
	char				forked;
	char				notified;              /* true if user told about stopped job */
	char				current;
	struct termios	tmodes;
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

int				put_job_in_background(t_job *j, int cont);
int				put_job_in_foreground(t_job *j, int cont);


int				launch_job(t_job *j, int foreground);
int				launch_process(t_process *p, pid_t pgid, int fds[2], int foreground);
void			set_group_id(pid_t pgid, int fg);
t_job			*create_job(t_ast *root, int fg, int num);
t_job			*append_job(t_job **first_j, t_job *to_add);
t_process		*create_process_list(t_token *token_list);
int				get_processes_len(t_process *p);
int				get_last_num(t_job *j);
void			set_current(void);

char			*tokens_to_str(t_token *tokens, t_token_type delimiter);
/*
**
*/

int				special_wait(t_job *j, int opt);
int				wait_for_job(t_job *j, int opt);
void			update_status(void);

int				job_is_completed(t_job *j);
void			format_job_info(t_job *j, const char *status, const char *bg,
		t_job_opt opt);
int				job_is_stopped(t_job *j);

int				mark_process_status(pid_t pid, int status);

char			*copy_job_tokens(t_ast *root);
t_token			*copy_process_tokens(t_token *tokens);

int				print_job_status(t_job *j, int verbose, t_job_opt opt);
void			do_job_notification(int verbose, t_job_opt opt);

t_job			*find_job_by_pgid(pid_t pgid);
t_job			*find_job_by_current(char current);
t_job			*find_job_by_number(int num);
t_job			*find_job_by_command(const char *command);
t_job			*find_job_by_subcommand(const char *subcommand);
t_job			*get_job(const char *str, const char *builtin);

/*
**	Free functions
*/

void			free_job(t_job **j);
t_job			*free_job_from_list(t_job *j);
void			free_process_list(t_process *p);
void			free_job_list(t_job *j);


int				last_process_status(t_process *p);
const char			*get_signal_str(int signo);
#endif
