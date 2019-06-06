#include "ftsh.h"

void		print_introduction(void)
{
	ft_printf(
	"            ____  _     _     \n"
	"           |___ \\/ |___| |__  \n"
	"             __) | / __| '_ \\ \n"
	"            / __/| \\__ \\ | | |\n"
	"           |_____|_|___/_| |_|\n\n"
	"`Left arrow` to move the cursor to the left\n"
	"`Right arrow` to move the cursor to the right\n"
	"`Home` to move the cursor to the beginning of the line\n"
	"`End` to move the cursor to the end of the line\n"
	"`Up arrow` to display the previous history entry\n"
	"`Down arrow` to display the next history entry\n"
	"`Ctrl + b` to move the cursor to the previous word\n"
	"`Ctrl + f` to move the cursor to the next word\n"
	"`Ctrl + r` to search a command in the history\n"
	"`Option + up` to move one line up\n"
	"`Option + c` to copy the current line from the cursor to the end\n"
	"`Option + x` to cut the current line from the cursor to the end\n"
	"`Option + v` to paste the saved line where the cursor is\n"
	"`Option + down` to move one line down\n");
}
