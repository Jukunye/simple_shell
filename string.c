#include "shell.h"

/**
 * _strcmp - Compare two strings.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 *
 * Return: Negative if str1 < str2,
 *         Positive if str1 > str2,
 *         0 if str1 is = str2.
 */
int _strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (unsigned char)(*str1) - (unsigned char)(*str2);
}

/**
 * _strlen - Compute the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string (excluding the null terminator).
 */
size_t _strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return (len);
}

/**
 * _strdup - Duplicate a string.
 * @src: The source string to be duplicated.
 *
 * Return: A pointer to the newly allocated duplicated string,
 *         or NULL if insufficient memory is available.
 */
char *_strdup(const char *src)
{
    char *dest;
    size_t len = 0;
    size_t i;

    while (src[len])
        len++;

    dest = malloc((len + 1) * sizeof(char));
    if (dest == NULL)
        return NULL;

    for (i = 0; i <= len; i++)
        dest[i] = src[i];

    return (dest);
}

/**
 * _strcpy - Copy a string to a buffer.
 * @dest: The destination buffer.
 * @src: The source string to be copied.
 *
 * Return: A pointer to the destination buffer.
 */
char *_strcpy(char *dest, const char *src) {
    char *dest_start = dest;

    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return (dest_start);
}

/**
 * _strcat - Concatenate two strings.
 * @dest: The dest buf where the resulting string will be stored.
 * @src: The source string to be appended to the dest.
 *
 * Return: A pointer to the dest buf.
 */
char *_strcat(char *dest, const char *src)
{
    char *temp = dest;

    while (*dest)
        dest++;

    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0'; /* Null-terminate the concatenated string*/

    return (temp);
}
