#include "shell.h"

/**
 * _atoi - convert a string to an integer
 * @s: char to check
 *
 * Return: the converted integer
 */

int _atoi(char *s)
{
	int a = 1;
	unsigned int i = 0;
	int sign = 1; /* Initialize the sign as positive*/

	/* Skip leading white spaces*/
	while (*s == ' ')
		s++;

	/* Handle the sign*/
	if (*s == '-')
	{
		sign = -1;
		s++;
	}

	do {
		if (*s >= '0' && *s <= '9')
		{
			i = i * 10 + (*s - '0');
		}
		else if (i > 0)
		{
			/* Stop parsing if non-digit characters appear after digits*/
			break;
		}
		s++;
	} while (*s);

	return (i * a * sign);
}
