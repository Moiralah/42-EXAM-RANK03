#include <unistd.h>
#include <stdarg.h>

int ft_putchar(char c)
{
    return(write(1, &c, 1));
}

int ft_putstr(char *c)
{
    int len = 0;

    if (!c)
        c = "(null)";

    while(*c)
    {
        len += ft_putchar(*c);
        c++;
    }
    return(len);
}

int ft_putbase(long long nbr, int base)
{
    int len = 0;

    if(nbr < 0)
    {
        len += ft_putchar('-');
        nbr *= -1;
    }
    if(nbr >= base)
    {
        len += ft_putbase(nbr / base, base);
    }
    len += ft_putchar("0123456789abcdef"[nbr % base]);
    return (len);
}

int ft_printf(const char *c, ...)
{
    int len = 0;
    int i = 0;
    va_list arg;

    va_start(arg, c);
    while (c[i])
    {
        if (c[i] != '%')
            len += ft_putchar(c[i]);
        if (c[i] == '%' && c[i+1])
        {
            i++;
            if(c[i] == 's')
                len += ft_putstr(va_arg(arg, char *));
            else if(c[i] == 'x')
                len += ft_putbase((long long)va_arg(arg, unsigned int), 16);
            else if(c[i] == 'd')
                len += ft_putbase((long long)va_arg(arg, int), 10);
            else
                len += ft_putchar(c[i]);
        }
        i++;
    }
    va_end(arg);
    return (len);
}

int main()
{
    ft_printf("Magic %s is %d\n", "number", 42);
}