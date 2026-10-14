*This project has been created as part of the 42 curriculum by younes abyaa.*

# Get Next Line

## Description

**Get Next Line** is a C project whose goal is to program a function that returns one line at a time from a file descriptor:

```c
char *get_next_line(int fd);
```

Repeated calls to `get_next_line()` let the caller read a text file (or any other file descriptor, such as the standard input) **one line at a time**, until there is nothing left to read.

Key points of the behavior:

- The returned line includes the terminating `\n`, except when the end of the file is reached and the file does not end with a `\n`.
- `NULL` is returned when there is nothing else to read or when an error occurs.
- The function works with any `BUFFER_SIZE` value (for example `1`, `42`, `9999` or `10000000`).
- It works on regular files as well as on other file descriptors such as `stdin`.
- Only `read`, `malloc` and `free` are used. `libft`, `lseek()` and global variables are not used.

The main concept learned through this project is the use of **static variables** in C, which keep their value between function calls.

### Project files

| File | Role |
|------|------|
| `get_next_line.c` | Main function `get_next_line()` and its internal steps |
| `get_next_line_utils.c` | Helper functions used by `get_next_line()` |
| `get_next_line.h` | Prototypes, includes and the `BUFFER_SIZE` macro handling |

## Instructions

### Compilation

The files are compiled with `cc` and the usual flags. The buffer size used by `read()` is defined at compile time with `-D BUFFER_SIZE=n`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

The project also compiles without the `-D BUFFER_SIZE` flag:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```

### Usage

Include the header and call the function in a loop until it returns `NULL`:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

The returned line is allocated with `malloc`, so the caller must `free` it.

To read from the standard input, use `0` as the file descriptor:

```c
line = get_next_line(0);
```

## Algorithm

### Overview

The algorithm relies on a **static variable** that stores the data that has been read from the file descriptor but not yet returned to the caller (the *stash* or *remainder*). Because a static variable keeps its value between calls, the function remembers exactly where it stopped reading the last time.

Each call to `get_next_line(fd)` follows these steps:

1. **Validate the input.** If `fd` is invalid, `BUFFER_SIZE` is not positive, or `read()` fails, the function frees what it holds and returns `NULL`.
2. **Fill the stash.** While the stash does not contain a `\n`, `read()` is called with a buffer of `BUFFER_SIZE` bytes and the bytes read are appended to the stash. Reading stops as soon as a newline is found or the end of the file is reached (`read()` returns `0`).
3. **Extract the line.** The line is copied from the start of the stash up to and including the first `\n` (or up to the end of the stash if there is no `\n`).
4. **Update the stash.** Everything that comes after the returned line is kept in a new stash for the next call, and the old stash is freed. If nothing remains, the stash is freed and set to `NULL`.
5. **Return the line.** If the extracted line is empty (nothing left to read), `NULL` is returned.

### Justification

- **Static variable for the remainder:** since `read()` reads fixed-size chunks that rarely align with line boundaries, the extra bytes read past the end of a line must be kept somewhere. A static variable does this without using global variables, which are forbidden.
- **Reading only what is needed:** the function stops calling `read()` as soon as a newline is present in the stash. The whole file is never loaded in memory at once, which follows the subject's recommendation to read as little as possible on each call.
- **Independent of `BUFFER_SIZE`:** the stash accumulates chunks until a newline appears, so the result is the same whether `BUFFER_SIZE` is `1` (many small reads) or very large (one read can contain many lines, and the remainder is preserved for the next calls).
- **Correct end-of-file handling:** when the file does not end with a `\n`, the remaining content in the stash is returned as the last line without a trailing newline. The next call then returns `NULL`.
- **Memory safety:** every buffer allocated with `malloc` is freed when it is no longer needed, including on error paths and when the end of the file is reached, so no memory is leaked.

## Resources

### References

- `man 2 read`, `man 3 malloc`, `man 3 free`
- Static variables and storage duration in C (the C language standard and the `cppreference` documentation on storage-class specifiers)
- Documentation on file descriptors and the standard streams (`stdin`, `stdout`, `stderr`) on Linux

### Use of AI

AI was used only to help write and structure this `README.md` file.