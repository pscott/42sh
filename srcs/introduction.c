#include "ftsh.h"

void		print_introduction(void)
{
	ft_printf("            ____  _     _     \n");
	ft_printf("           |___ \\/ |___| |__  \n");
	ft_printf("             __) | / __| '_ \\ \n");
	ft_printf("            / __/| \\__ \\ | | |\n");
	ft_printf("           |_____|_|___/_| |_|\n\n");
	ft_printf("`Left arrow` to move the cursor to te left\n");
	ft_printf("'Right arrow` to move the cursor to the right\n");
	ft_printf("`Up arrow` to display the previous history entry\n");
	ft_printf("`Down arrow` to display the next history entry\n");
	ft_printf("`Home` to move the cursor to the beginning of the line\n");
	ft_printf("`End` to move the cursor to the end of the line\n");
	ft_printf("`Ctrl + r` to search a command in the history\n");
	ft_printf("`Option + up` to move to the upper line\n");
	ft_printf("`Option + down` to move to the downer line\n");
	ft_printf("`Option + left` to move the cursor to the previous word\n");
	ft_printf("`Option + right` to move the cursor to the next word\n");
}
