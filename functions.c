#include "main.h"

int print_char(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int print_int(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
			int flags, int width, int precision, int size);

/**
 * print_char - prints a char
 * @types: va_list of arguments to be printed
 * @buffer: buffer array to handle print
 * @flags: flag modifiers
 * @width: width modifiers
 * @precision: precision modifiers
 * @size: size modifiers
 *
 * Return: number of bytes printed
*/

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - prints a string
 * @types: va_list of arguments to be printed
 * @buffer: buffer array to handle print
 * @flags: flag modifiers
 * @width: width modifiers
 * @precision: precision modifiers
 * @size: size modifiers
 *
 * Return: number of bytes printed
*/

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, i;
	char *string = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (string == NULL)
	{
		string = "(null)";
		if (precision >= 6)
			string = " ";
	}

	while (string[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &string[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &string[0], len);
			return (width);
		}
	}

	return (write(1, string, len));
}

 /**
 * print_percent - prints a percent sign
 * @types: va_list of arguments to be printed
 * @buffer: buffer array to handle print
 * @flags: flag modifiers
 * @width: width modifiers
 * @precision: precision modifiers
 * @size: size modifiers
 *
 * Return: number of bytes printed
*/

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - priint int
 * @types: va_list of arguments to be printed
 * @buffer: buffer array to handle print
 * @flags: flag modifiers
 * @width: width modifiers
 * @precision: precision modifiers
 * @size: size modifiers
 *
 * Return: number of bytes printed
*/

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int b = va_arg(types, long int);
	unsigned long int numb;

	b = convert_size_number(b, size);

	if (b == 0)
		buffer[a--] = '\0';

	buffer[BUFF_SIZE - 1] = '\0';
	numb = (unsigned long int)b;

	if (b < 0)
	{
		numb = (unsigned long int)((-1) * b);
		is_negative = 1;
	}

	while (numb > 0)
	{
		buffer[a--] = (numb % 10) + '0';
		numb /= 10;
	}

	a++;

	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}

/**
 * print_binary - print an unsigned number
 * @types: va_list of arguments to be printed
 * @buffer: buffer array to handle print
 * @flags: flag modifiers
 * @width: width modifiers
 * @precision: precision modifiers
 * @size: size modifiers
 *
 * Return: number of bytes printed
*/

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int j, k, i, sum;
	unsigned int a[32];
	int count;


	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	j = va_arg(types, unsigned int);
	k = 2147483648;
	a[0] = j / k;
	for (i = 1; i < 32; i++)
	{
		k /= 2;
		a[i] = (j / k) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
