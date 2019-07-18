# 42sh : in a nut-*shell*



*42sh* is the **last project** on the Unix path at [42](https://www.42.fr/). The goal is to write a **fully-fledged shell**, allowing the user to interact with our shell and execute commands. Please see the PDF file for more information.

<p align="center">
  <img width="424" height="304" src="/42sh.gif">
</p>

The shell must be **error-free**: no bug is to be found whatsoever, no infinite loop, no memory leak, no segmentation fault, **regardless of the user's potentially unexpected behavior**. If you do find a bug, please report it via an issue!

# Disclaimer

This program was not programmed to be portable. Indeed, the code was written to be [norme compliant](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf). Let us outline the key rules of the norme:
- 25 lines per function maximum.
- 5 functions per .c file maximum.
- Comments only allowed outside of functions.
- Declaring static function whenever possible.
- All defines, and typedef must be done in header files.
- Defines in header files must be defined after includes.

This program will probably NOT compile on any other machine than macOS. Sorry for the inconvenience!

# Installing, compiling and running

One-liner to download and run our shell :

`git clone https://github.com/pscott/42sh.git ; cd 42sh ; make ; ./42sh`


# Features
- Executing commands (`ls`, `pwd`, etc...)
- Line editing
	- <kbd>Left arrow</kbd> to move the cursor to the left.
	- <kbd>Right arrow</kbd> to move the cursor to the right.
	- <kbd>Home</kbd>  to move the cursor to the beginning of the command.
	- <kbd>End</kbd>  to move the cursor to the end of the command.
- Redirections (`>`, `>>`, `<`, `<<`, `>&`, `&<`)
- Pipes and logic operators (`|`, `&&`, `||`)
- Command separator (`;`)
- Posix compliant builtins (`cd`, `echo`, `exit`, `hash`, `type`, `set`, `unset`, `export`)
- Posix compliant job control (`jobs`, `fg`,  `bg`,  `&`)
- Quotes and backslashes (`'`, `"`, `/`)
- Arithmetic expansion (`$((a + b))`)
	- Incrementing and decrementing (`++`, `--`)
	- Addition, subtraction, multiplication, division, modulus (`+`, `-`, `*`, `/`, `%`)
	- Comparison (`>=`, `>`, `<=`, `<`)
	- Equality (`==`, `!=`)
	- AND and OR (`&&`, `||`)
- History:
	- <kbd>Up arrow</kbd> to get the previously typed command.
	- <kbd>Down arrow</kbd> to get the next command.
	- Expansions (`!!`, `!word`, `!number`, `!-number`)
	- Posix compliant `fc` builtin
	- Search in history with <kbd>Ctrl</kbd>+<kbd>r</kbd>
- `test` builtin along with different options:
	- `-b`, `-c`, `-d`, `-e`, `-f`, `-g`, `-L`, `-p`, `-r`, `-S`, `-s`, `-u`, `-w`, `-x`, `-z`, `=`, `!=`, `-eq`, `-ne`, `-ge`, `-lt`, `!`
- Copy / Cut / Paste:
	- Enter/quit visual mode by pressing <kdb>F1</kdb>
	- When in visual mode:
		- Press <kbd>Option</kbd>+<kbd>x</kbd> to cut the current selection.
		- Press <kbd>Option</kbd>+<kbd>c</kbd> to copy the current selection.
	- Press <kbd>Option</kbd>+<kbd>v</kbd> to paste the last copied or cut buffer.
	

# Extras

Line editing was done using the termcap library and not ncurses, as imposed by the subject.

Our shell is not entirely POSIX compliant but we did try to follow the POSIX guidelines as much as we could.

We learned a lot throughout these 4 months of hard work, and still have a lot of room for improvement. Code readibility, code structure, code maintainability…

# Authors
Developed by : [@aschoenh](https://github.com/aschoenh), [@benjyskan](https://github.com/benjyskan), [@neurochirurgie](https://github.com/neurochirurgie), and [@pscott](https://github.com/pscott).
