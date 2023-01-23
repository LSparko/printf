#include "main.h"

int _printf(const char *format, ...);
void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - performs printf function
 * @format: a character string, composed of zero or more directives
 * @...: variable number of char strings to be printed
 *
 * Return: the number of characters printed
 * (excluding the null byte used to end output to strings)
*/

int _printf(const char *format, ...)
{
	va_list arg;
	int a, printed = 0, printed_chars = 0;
	int width, flags, size, precision, buff_ind = 0;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(arg, format);

	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			buffer[buff_ind++] = format[a];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);

			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &a);
			width = get_width(format, &a, arg);
			size = get_size(format, &a);
			precision = get_precision(format, &a, arg);
			++a;
			printed = handle_print(format, &a, arg, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(arg);

	return (printed_chars);
}

/**
 * print_buffer - prints contents of the buffer if it exists
 * @buffer: array of chars
 * @buff_ind: index to add the next char
*/

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
