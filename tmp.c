int		input_loop_heredoc(t_st_cmd *st_cmd, t_vars *vars)
{
	char	buf[BUF_SIZE + 1];
	int		ret;

	ft_bzero(buf, BUF_SIZE + 1);
	retrieve_pos(&st_cmd->start_pos);
	print_prompt(st_cmd->st_prompt);
	while ((ret = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	{
	//	magic_print(buf);
		buf[ret] = 0;
		if (check_for_signal(buf))
			return (-1);
		else if (check_for_arrows(st_cmd, buf) || check_for_delete(st_cmd, buf)
			|| check_for_tab(st_cmd, buf, vars) || check_for_quit(st_cmd, buf))
			;
		else if (check_for_enter(buf))
		{
			ft_strncpy(buf, "\n", 1);
			st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;
			get_pos(st_cmd, st_cmd->st_txt->tracker);
			reposition_cursor(st_cmd);
			insert_txt(st_cmd, (const char*)buf);
			print_line(0);
			break ;
		}
		else if (buf[0] < 0 || buf[0] == '\x1b') // checks for unicode and ANSI
			continue ;
		else
			insert_txt(st_cmd, (const char*)buf);
		reposition_cursor(st_cmd);
	}
	if (ret >= 0)
		return (1);
	return (0);
}

static char	*get_doc(char *eof, unsigned char is_eof_quoted, t_vars *vars)
{
	char		*path;
	char		*txt;
	t_st_cmd	*st_cmd;

	st_cmd = init_st_cmd((const char **)vars->env_vars);
	st_cmd = append_st_cmd(st_cmd, "", "heredoc>");
	if (!(txt = ft_strdup("")))
		ERROR_MEM;
	
}
