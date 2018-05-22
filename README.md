# Get_Next_Line

A function that returns a line read from a file descriptor.

## Function prototype:

```C
int   get_next_line(const int fd, char **line)
```

 - The first parameter is the file descriptor that will be used to read.
 - The second parameter is the address of a pointer to a character that will be used to save the line read from the file descriptor.
 - The function returns its result without '\n'.
 - Calling `get_next_line` in a loop allows reading of text available on a file descriptor one line at a time until the end of the text.

### [Subject](https://github.com/fpetras/42-subjects/blob/master/get_next_line.en.pdf "get_next_line.en.pdf")
