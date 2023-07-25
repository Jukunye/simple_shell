#include "shell.h"

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: A pointer to the value of the environment variable,
 *         or NULL if the variable is not found.
 */
char *_getenv(const char *name)
{
     char **env = environ;

    if (name == NULL || *name == '\0')
        return (NULL);

    while (*env)
    {
        if (_strcmp(*env, name) == 0)
        {
            char *value = *env;
            value += _strlen(name) + 1; /* Skip the variable name and '=' */
            return value;
        }

        env++;
    }

    return (NULL);
}
