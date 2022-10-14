# SeaShell  

A linux shell implementation written in C as part of an assignment during my Operating Systems (CSE-231) course at IIITD (Monsoon 2022).

To compile the project run `make` inside the project root. You need to have `make` installed on your OS.

To test and run the shell, execute the `shell` binary that is created inside the project root after `make` finishes compiling the project:
```
$ ./shell
```
You should see a welcome message and a prompt asking you to enter a command:
```
Welcome to SeaShell!
>> 
```

All external commands are suffixed with 'ss', so to run any external command, for example `cd`, run `cdss ...` instead.

SeaShell supports execution using threads instead of forking a new child process. To run a command in a thread, enter the command you wish to execute with an `&t` at the end:
```
mkdirss test &t
```

SeaShell supports the following 8 commands. Two command line options for each have been implemented.

Internal:
* [cd](#cd)
* [pwd](#pwd)
* [echo](#echo)

External:
* [ls](#ls)
* [cat](#cat)
* [rm](#rm)
* [mkdir](#mkdir)
* [date](#date)


## Commands

This section describes each command in detail: the syntax, arguments supported and any assumptions made.

### <a name="cd"></a>cd
`cd [-L | -P] [dir]`

Change the shell working directory.

Change the current directory to DIR.  The default DIR is the value of the HOME shell variable.

Options:

      -L        force symbolic links to be followed
      -P        use the physical directory structure without following
                symbolic links

The default is to follow symbolic links, as if `-L` were specified.

`..` is processed by removing the immediately previous pathname component
back to a slash or the beginning of DIR.

Edge cases:
- Trying to cd into a directory that does not exist gives a 'file does not exist' error.
- Trying to cd into a file gives a 'Not a directory' error.
- Doing a `cd ..` from `\` has no effect.

### <a name="pwd"></a>pwd
`pwd [-LP]`

Print the name of the current working directory.

Options:

      -L        print the value of $PWD, following symbolic links
      -P        print the physical directory, without any symbolic links

By default, `pwd` behaves as if `-L` were specified.

Edge cases:
- Giving an argument to the command prints a 'Too many arguments' error.
- When both options are set in the same command, `-P` overrides `-L`. 


### <a name="echo"></a>echo
`echo [OPTION]... [STRING]...`

Display a line of text

Options:

      -n        do not output the trailing newline
      -e        enable interpretation of backslash ecapes

      If -e is in effect, the following sequences are recognized:

       \\     backslash
       \a     alert (BEL)
       \b     backspace
       \e     escape
       \f     form feed
       \n     new line
       \r     carriage return
       \t     horizontal tab
       \v     vertical tab

Backslash interpretations are disabled by default.

### <a name="ls"></a>ls
`ls [OPTION]... [FILE]...`

List information about the FILEs (the current directory by default).

Options:

      -a        do not ignore entries starting with .
      -l        use a long listing format

By default, all entries are listed in directory order.

Edge cases:
- Running the command on a non-existing file prints the 'No such file or directory' error.
- For symlinks, contents of the directory they are pointing to are printed.

### <a name="cat"></a>cat
`cat [OPTION]... [FILE]...`

Concatenate FILE(s) to standard output.

Options:

      -E        display $ at end of each line
      -n        number all output lines

Edge cases:
- Running the command on a non-existing file prints the 'No such file or directory' error.
- Multiple files are printed in the order in which they are listed in the command.
- When no files are specified, shell prints the 'too few arguments' error.

### <a name="rm"></a>rm
`rm [OPTION]... [FILE]...`

Remove (unlink) the FILE(s).

Options:

      -f        ignore nonexistent files and arguments, never prompt
      -r        remove directories and their contents recursively

By default, `rm` does not remove directories.  Use the `-r` option to remove each listed directory, too, along with all of its contents.

Edge cases:
- Attempting to delete a directory without the `-r` flag gives the 'Is a directory' error.
- Deleting an already deleted file in the same command gracefully prints a 'No such file or directory' error.

### <a name="mkdir"></a>mkdir
`mkdir [OPTION]... DIRECTORY...`

Create the DIRECTORY(ies), if they do not already exist.

Options:

      -p        make parent directories as needed
      -v        print a message for each created directory

Edge cases:
- Creating an already existing directory gives a 'file exists' error.
- Creating nested directories when not existing gives a 'No such file or directory' error without the `-p` flag.

### <a name="date"></a>date
`date [OPTION]... [FORMAT]`

Display date and time in the given FORMAT.

Options:

      -R        output date and time in RFC 5322 format.
                Example: Mon, 14 Aug 2006 02:34:56 -0600
      -u        print the Coordinated Universal Time (UTC)

Edge cases:
- When both options are set in the same command, `-u` overrides `-R`.
- Entered format when a flag is set is ignored.
