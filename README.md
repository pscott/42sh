# 42sh : in a nut-*shell*

*42sh* is the **last project** on the Unix path at [42](https://www.42.fr/). The goal is to write a **fully-fledged shell**, allowing the user to interact with our shell and execute commands.

The shell must be **error-free**: no bug is to be found whatsoever, no infinite loop, no segmentation fault, **regardless of the user's potentially unexpected behavior**. If you do find a bug, please report it via an issue!

<p align="center">
  <img width="460" height="300" src="/42sh.gif">
</p>

# Features
- Executing commands (`ls`, `pwd`, etc...)
- Line editing
	- `Left arrow` to move the cursor to the left.
	- `Right arrow` to move the cursor to the right.
	- `Home`  to move the cursor to the beginning of the command.
	- `End`  to move the cursor to the end of the command.
- Redirections (`>`, `>>`, `<`, `<<`, `>&`, `&<`)
- Pipes and logic operators (`|`, `&&`, `||`)
- Command separator (`;`)
- Posix compliant builtins (`cd`, `echo`, `exit`, `hash`, `type`, `set`, `unset`)
- Job control (`jobs`, `fg`,  `bg`,  `&`)
- Quotes and backslashes (`'`, `"`, `/`)
- Arithmetic expansion (`$((a + b))`)
	- Incrementing and decrementing (`++`, `--`)
	- Addition, subtraction, multiplication, division, modulus (`+`, `-`, `*`, `/`, `%`)
	- Comparison (`>=`, `>`, `<=`, `<`)
	- Equality (`==`, `!=`)
	- AND and OR (`&&`, `||`)
- History:
	- Up arrow to get the previously typed command.
	- Down arrow to get the next command.
	- Expansions (`!!`, `!word`, `!number`, `!-number`)
	- Posix compliant `fc` builtin
	- Search in history with `ctrl + R`
- `test` builtin along with different options:
	- `-b`, `-c`, `-d`, `-e`, `-f`, `-g`, `-L`, `-p`, `-r`, `-S`, `-s`, `-u`, `-w`, `-x`, `-z`, `=`, `!=`, `-eq`, `-ne`, `-ge`, `-lt`, `!`

# Authors
Developed by : [@aschoenh](https://github.com/aschoenh), [@benjyskan](https://github.com/benjyskan), [@neurochirurgie](https://github.com/neurochirurgie), and [@pscott](https://github.com/pscott).
