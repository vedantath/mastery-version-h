# cs429-mastery-assignment
## [IMPORTANT] After you SSH into a lab machine: Note that
- **ALL git commands must be in the command line.**
- **ALL gdb debugging must be in the command line.**
- **ALL file system actions (eg. creating a file, navigating a file, etc) must be in the command line**

You are allowed to utilize the terminal of your choice for these actions, but they must be accomplished in-terminal.

*Note: SSHing and opening *this* repo via VS Code or another GUI is acceptable provided that the above actions are then accomplished via a terminal therein.*

# What this repo contains:
- `main.c`, `parser.c`, `grind.c` and their corresponding header files.
- A Makefile
- Some testcases in the `testcases` folder
- a reference executable called `ref.out`


# What this code does:
The given code is a baby implementation of memory leak tracking in valgrind. It reads in lines from an input file in the
format you have previously seen in MM Lab. `a <allocation id> <size>` and `f <allocation id>` to allocate and free
memory respectively. This parser is known to be correct. In grind.c, parsed lines are processed: allocations are stored 
in a hash map and frees remove the hash map entry. If a free can not find its alloc id, `GRIND_BAD_FREE` is returned,
if any other error occurs, `GRIND_FAILURE` is returned. If no errors are encountered, `GRIND_SUCCESS` is returned. Once 
the trace finishes, the results of the trace are printed as specified by the reference solution.
Note that notifications of unfreed memory are expected in some testcases.
Unfortunately, some aspects of `grind.c` may be incorrect. 

To run an individual testcase use
`bin/a.out -t <file>`. Use `ref.out -t <file>` for the reference output.

# Instructions:
1. ssh into your favorite UTCS lab machine
2. Create a file `~/.gdbinit`
3. Add the line `set history save on` to `~/.gdbinit`
4. Clone this repository
5. Read then use the Makefile
6. Debug the test cases using gdb; you must use gdb to pass this mastery assessment.
7. To the best of your ability, ensure your output matches the reference exactly.
8. Write the outputs of the `history` command to a file in this repo called `shell_logs.txt`
9. Ensure git tracking is enabled on  ./.gdbhistory 
10. Commit and push your changes. Do not forget to add `shell_logs.txt` and `gdb_logs.txt` to git.
11. Delete your local copy of this repository (you will need to use the r and f flags). If this results in any errors, please notify your proctor before leaving the room.
12. Please do not leave before your proctors tell you to do so. 
