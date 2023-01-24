#include "main.h"

int print_unsigned(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int print_hexa(va_list types, char map_to[],
		char buffer[], int flags, char flag_ch, int width, int precision, int size);

/**
 * print_unsigned - prints an unsigned number
 * @types: va_list of arguments to be printed
 * @buffer: buffer array to handle print
 * @flags: flag modifiers
 * @width: width modifiers
 * @precision: precision modifiers
 * @size: size modifiers
 *
 * Return: number of bytes printed
*/

int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '\0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/**
 * print_octal - prints an unsigned number in octal notations
 * @types: va_list of arguments to be printed
 * @buffer: buffer array to handle print
 * @flags: flag modifiers
 * @width: width modifiers
 * @precision: precision modifiers
 * @size: size modifiers
 *
 * Return: number of bytes printed
 */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[a--] = '0';

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - prints an unsigned number in hexadecimal notations
 * @types: va_list of arguments to be printed
 * @buffer: buffer array to handle print
 * @flags: flag modifiers
 * @width: width modifiers
 * @precision: precision modifiers
 * @size: size modifiers
 *
 * Return: number of bytes printed
 */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef",
		buffer, flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - prints an unsigned number in upper hexadecimal notations
 * @types: va_list of arguments to be printed
 * @buffer: buffer array to handle print
 * @flags: flag modifiers
 * @width: width modifiers
 * @precision: precision modifiers
 * @size: size modifiers
 *
 * Return: number of bytes printed
*/

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - prints a hexadecimal number in lower or upper
 * @types: va_list of arguments to be printed
 * @map_to: Array if values to map the number to
 * @buffer: buffer array to handle print
 * @flags: flag modifiers
 * @flag_ch: flag modifiers
 * @width: width modifiers
 * @precision: precision modifiers
 * @size: size modifiers
 *
 * Return: number of bytes printed
*/

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
		int a = BUFF_SIZE - 2;
		unsigned long int num = va_arg(types, unsigned long int);
		unsigned long int init_num = num;

		UNUSED(width);

		num = convert_size_unsgnd(num, size);

		if (num == 0)
			buffer[a--] = '0';

		buffer[BUFF_SIZE - 1] = '\0';

		while (num > 0)
		{
			buffer[a--] = map_to[num % 16];
			num /= 16;
		}

		if (flags & F_HASH && init_num != 0)
		{
			buffer[a--] = flag_ch;
			buffer[a--] = '0';
		}

		a++;

		return (write_unsgnd(0, a, buffer, flags, width,
			precision, size));
}
