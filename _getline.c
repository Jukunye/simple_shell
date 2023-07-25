#include "shell.h"
/**
  * refillBuffer - Refill the buffer with data from the stream.
  * @stream: Input stream from which to read the data
  * @buf: A buffer to store the read data
  * @buf_index: Pointer to the index showing the current position
  * @bytes_remaining: Pointer to the num of bytes to be read
  * 
  * Return: Num of bytes read,
  * or -1 on failure(EOF or error)
  */
#define BUFFER_SIZE 1024

ssize_t refillBuffer(FILE *stream, char buf[], size_t *buf_index, ssize_t *bytes_remaining) {
    *bytes_remaining = read(fileno(stream), buf, BUFFER_SIZE);
    *buf_index = 0;
    return (*bytes_remaining);
}

/**
  * resizeLineBuffer - Resize the line buf to store more data
  * @lineptr: Pointer to the line buffer that needs resizing
  * @n: Pointer to current size of buffer
  * @bytes_read: Num of bytes read so far,showing current buf size.
  * Return: Pointer to the resized buf
  * or NULL on failure
  */

char *resizeLineBuffer(char *lineptr, size_t *n, ssize_t bytes_read)
{
  char *temp;
  *n += BUFFER_SIZE;
  temp = malloc(*n);

  if (temp == NULL)
  {
    perror("malloc failed");
    return (NULL);
  }
  memcpy(temp, lineptr, bytes_read);
  free(lineptr);
  return (temp);
}

/**
  * _getline - Read input using a buf and minimize the use of read system call
  * @lineptr: A pointer to a pointer that will store the read line.
  * @n: A pointer tohe size of the buf pointed by lineptr.
  * @stream: Input stream from which to read the data.
  * Return: The num of bytes read,
  * or -1 on failure
  */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
    static char buf[BUFFER_SIZE];
    static size_t buf_index = 0;
    static ssize_t bytes_remaining = 0;
    ssize_t bytes_read = 0;

    /*initialize the line buffer*/
    if (*lineptr == NULL || *n == 0)
    {
        *n = BUFFER_SIZE;
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
        {
            perror("malloc failed");
            return (-1);
        }
    }
    while (1)
    {
        /* Refill the buffer if necessary */
        if ((ssize_t)buf_index >= bytes_remaining)
        {
            if (refillBuffer(stream, buf, &buf_index, &bytes_remaining) <= 0)
            {
                /* End of file or error */
                if (bytes_read == 0)
                {
                    /* No bytes read, return -1 to indicate failure */
                    return (-1);
                }
                else
                {
                    /* Return bytes read so far */
                    return (bytes_read);
                }
            }
        }
        /* Copy bytes from the buffer to the line */
        (*lineptr)[bytes_read] = buf[buf_index];
        bytes_read++;
        buf_index++;

        /* Break if end of line is reached */
        if ((*lineptr)[bytes_read - 1] == '\n')
        {
            (*lineptr)[bytes_read] = '\0';
            return (bytes_read);
        }

        /* Resize the line buffer if necessary */
        if ((size_t)bytes_read >= *n)
        {
            *lineptr = resizeLineBuffer(*lineptr, n, bytes_read);
            if (*lineptr == NULL)
               {
                return (-1);
            }
        }
    }
}
