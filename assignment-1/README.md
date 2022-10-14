# Seashell  

A linux shell implementation written in C. It supports the following 8 commands: 
* [cd](#cd)
* [pwd](#pwd)
* [echo](#echo)
* [ls](#ls)
* [cat](#cat)
* [rm](#rm)
* [mkdir](#mkdir)
* [date](#date)

Two command line options for each command have been implemented.

## Commands

This section describes each command in detail namely the syntax, arguments supported and any assumptions made.

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

### <a name="pwd"></a>pwd
`pwd [-LP]`

Print the name of the current working directory.

Options:

      -L        print the value of $PWD, following symbolic links
      -P        print the physical directory, without any symbolic links

By default, `pwd` behaves as if `-L` were specified.

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

### <a name="cat"></a>cat
`cat [OPTION]... [FILE]...`

Concatenate FILE(s) to standard output.

Options:

      -E        display $ at end of each line
      -n        number all output lines

### <a name="rm"></a>rm
`rm [OPTION]... [FILE]...`

Remove (unlink) the FILE(s).

Options:

      -f        ignore nonexistent files and arguments, never prompt
      -r        remove directories and their contents recursively

By default, `rm` does not remove directories.  Use the `-r` option to remove each listed directory, too, along with all of its contents.

### <a name="mkdir"></a>mkdir
`mkdir [OPTION]... DIRECTORY...`

Create the DIRECTORY(ies), if they do not already exist.

Options:

      -p        make parent directories as needed
      -r        print a message for each created directory


### <a name="date"></a>date
`date [OPTION]... [FORMAT]`

Display date and time in the given FORMAT.

Options:

      -R        output date and time in RFC 5322 format.
                Example: Mon, 14 Aug 2006 02:34:56 -0600
      -u        print the Coordinated Universal Time (UTC)
