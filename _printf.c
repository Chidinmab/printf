#include "main.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * 
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    return (write(1, &c, 1));
}

/**
 * _puts - writes the string s to stdout
 * @str: The string to print
 *
 * Return: Number of characters printed
 */
int _puts(char *str)
{
    int count = 0;

    while (*str)
    {
        _putchar(*str++);
        count++;
    }
    return (count);
}

/**
 * _print_number - prints an integer
 * @n: The integer to print
 */
void _print_number(int n)
{
    if (n < 0)
    {
        _putchar('-');
        n = -n;
    }
    if (n / 10)
        _print_number(n / 10);
    _putchar(n % 10 + '0');
}

/**
 * _print_unsigned_number - prints an unsigned integer
 * @n: The unsigned integer to print
 */
void _print_unsigned_number(unsigned int n)
{
    if (n / 10)
        _print_unsigned_number(n / 10);
    _putchar(n % 10 + '0');
}

/**
 * _print_hex - prints an unsigned long int in hexadecimal
 * @n: The number to print
 * @uppercase: Flag to indicate if uppercase letters are to be used
 */
void _print_hex(unsigned long int n, int uppercase)
{
    char *hex = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    if (n / 16)
        _print_hex(n / 16, uppercase);
    _putchar(hex[n % 16]);
}

/**
 * _printf - produces output according to a format
 * @format: A character string composed of zero or more directives
 *
 * Return: the number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    int precision = -1;

    va_start(args, format);

    while (format && *format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == '.')
            {
                format++;
                precision = 0;
                while (*format >= '0' && *format <= '9')
                {
                    precision = precision * 10 + (*format - '0');
                    format++;
                }
            }
            if (*format == 'c')
            {
                char c = va_arg(args, int);
                count += _putchar(c);
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);
                if (!str)
                    str = "(null)";
                if (precision >= 0)
                {
                    for (int i = 0; str[i] && i < precision; i++)
                        count += _putchar(str[i]);
                }
                else
                    count += _puts(str);
            }
            else if (*format == '%')
            {
                count += _putchar('%');
            }
            else if (*format == 'd' || *format == 'i')
            {
                int num = va_arg(args, int);
                _print_number(num);
                count += num < 0 ? 1 : 0;
                count += num == 0 ? 1 : 0;
                while (num != 0)
                {
                    count++;
                    num /= 10;
                }
            }
            else if (*format == 'u')
            {
                unsigned int num = va_arg(args, unsigned int);
                _print_unsigned_number(num);
                count += num == 0 ? 1 : 0;
                while (num != 0)
                {
                    count++;
                    num /= 10;
                }
            }
            else if (*format == 'p')
            {
                unsigned long int addr = (unsigned long int)va_arg(args, void *);
                count += _puts("0x");
                _print_hex(addr, 0);
                while (addr != 0)
                {
                    count++;
                    addr /= 16;
                }
            }
            else
            {
                count += _putchar('%');
                count += _putchar(*format);
            }
        }
        else
        {
            count += _putchar(*format);
        }
        format++;
    }

    va_end(args);
    return (count);
}
