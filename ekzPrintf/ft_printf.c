#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>


int ft_putchar(char c)
{
    write(1, &c, 1);
	return (1);
}

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_putstr(char *s)
{
	int j = 0;
	while(s[j])
    {
        ft_putchar(s[j]);
        j++;
    }
	return (j);
}

int ft_print_spase(int sp)
{
    int r = sp;
	while(sp-- > 0)
		ft_putchar(' ');
	return (r);
}

int case_s_null(int width, int precision)
{
    int i = 0;
    if (precision >= 0 && precision < 6)
    {
        if (width > precision)
            i += ft_print_spase(width - precision);
        if(precision == 1)
            i += ft_putchar('(');
        else if(precision == 2)
        {
            i += ft_putchar('(');
            i += ft_putchar('n');
        }
        else if(precision == 3)
        {
            i += ft_putchar('(');
            i += ft_putchar('n');
            i += ft_putchar('u');
        }
        else if(precision == 4)
        {
            i += ft_putchar('(');
            i += ft_putchar('n');
            i += ft_putchar('u');
            i += ft_putchar('l');
        }
        else if(precision == 5)
        {
            i += ft_putchar('(');
            i += ft_putchar('n');
            i += ft_putchar('u');
            i += ft_putchar('l');
            i += ft_putchar('l');
        }
        return (i);
    }
    else 
    {
        if(width > 6)
            i += ft_print_spase(width-6);
        i += 6;
        ft_putstr("(null)");
        return (i);
    }   
}

int count_spase_s(char *s, int width, int precision)
{
    int res = 0;
    if (precision < ft_strlen(s) && precision >= 0 && width > precision)
        res += ft_print_spase(width - precision);
    else if (width > ft_strlen(s))
        res += ft_print_spase(width - ft_strlen(s));
    return (res);
}

int ft_case_s(va_list ap, int width, int precision)
{
    int i = 0;
    int j = 0;
    
    char *s = va_arg(ap, char *);
    if (precision == 0 && width == 0)
        return (0);
    if (!s)
		return(case_s_null(width, precision));
    i += count_spase_s(s, width, precision);
    if(precision < ft_strlen(s) && precision >= 0)
    {
        while (precision-- > 0)
			i += ft_putchar(s[j++]);
		return (i);
    }
    else
    return (i + ft_putstr(s));
}

int numlen(long num)
{
    int i = 0;
    if(num == 0)
        return (1);
    if(num < 0)
    {
        num = -num;
        i++;
    }
    while(num)
    {
        num = num/10;
        i++;
    }
    return (i);
}

void ft_putnbr(long num, int pres)
{
    if(num < 0)
    {
        if (pres > numlen(num) - 1)
        {
            ft_putchar('-');
            pres = pres - numlen(num) + 1;
            while(pres--)
                ft_putchar('0');
        }
        else
            ft_putchar('-');
        num = -num;
    }
    if (num < 10)
        ft_putchar(num + '0');
    else
    {
        ft_putnbr(num/10, pres);
        ft_putnbr(num%10, pres);
    }
}

int print_case_d_space(int num, int width, int precision)
{
    int res = 0;
    if(num < 0)
        precision++;
    if ((width >= precision) && (precision >= numlen(num)))//либо спейсы от точности, либо от числа
        res += ft_print_spase(width - precision);
    else if (width > numlen(num) && precision < numlen(num))
        res += ft_print_spase(width - numlen(num));
    return (res);
}

int ft_case_di(va_list ap, int width, int precision)
{
	int res = 0;
    int i = va_arg(ap, int); 
    if (precision == 0 && i == 0)
    {
        if (width > 0)
            return (ft_print_spase(width));
        return (0);
    }   
    res += print_case_d_space(i, width, precision);
    int p = precision - numlen(i);
    if (i >= 0)
        while(p-- > 0)
            ft_putchar('0');
    ft_putnbr(i, precision);
    if(i < 0 && (numlen(i) <= precision))
        res++;
    if (numlen(i) < precision)
        res += precision;
    else
        res += numlen(i);
    return (res);
}

int put_base(long long num, char *base)
{
    int c = 0;
	if (num < 0)
		num = 4294967296 + num;
    if(num >= 16)
        c = put_base(num / 16, base);
    c++;
    ft_putchar(base[num % 16]);
	return (c);   
}

int get_x_len(long long num, char *base)
{
int c = 0;
	if (num < 0)
		num = 4294967296 + num;
    if(num >= 16)
        c = get_x_len(num / 16, base);
    c++;
    return (c);
}

int case_x(int num, char *base, int width, int precision)
{
    if (precision == 0 && num == 0)
    {
        if (width > 0)
            return (ft_print_spase(width));
        return (0);
    }
    int i = 0;
    int len = get_x_len(num, base);

    if (precision > len && precision > 0 && width >= precision)
        i += ft_print_spase(width - precision);
    else if (width > len && precision <= len)
        i += ft_print_spase(width - len);
    
    if (precision > len)
    {
        precision = precision - len;
        while (precision--)
            i += ft_putchar('0');             
    }
    i += put_base(num, base);
    return (i);
}

static int	ft_print_param(char param, va_list ap, int width, int precision)
{
	if (param == 's')
		return (ft_case_s(ap, width, precision));
	if (param == 'd')
		return (ft_case_di(ap, width, precision));	
	if (param == 'x')
        return (case_x(va_arg(ap, int), "0123456789abcdef",  width, precision));	
	return (0);
}

int get_width(const char *s, int i)
{
    int res = 0;
    while((s[i] >= 48) && (s[i] <= 57))
    {
        res = res * 10 + (s[i] - '0');
        i++;
    }
    return (res);
}

int get_precision(const char *s, int i)
{
    int res = 0;
    while(s[i] != '.' && s[i]  && s[i] >= '0' && s[i] <= '9')
        i++;   
    if(s[i] != '.')
        return (-1);
    i++;    
    while(s[i] >= '0' && s[i] <= '9')
    {
        res = res * 10 + (s[i] - '0');
        i++;
    }
    //printf("res = %d", res);
    return (res);
}

int goI(const char *s, int i)
{
    int res = 0;
    while ((s[i] >= '0' && s[i] <= '9') ||  s[i] == '.')
    {
    res++;
    i++;
    }
    return (res);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		j;
    int width = 0;
    int precision = 0;

	i = 0;
	j = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{	
            width = get_width(str, i+1);
            precision = get_precision(str, i + 1);
			i = i + goI(str, i + 1);
            j += ft_print_param(str[i + 1], ap, width, precision);
            i++;
		}
		else
		{
			ft_putchar(str[i]);
			j++;
		}
		i++;
	}
	va_end(ap);
	return (j);
}

/*
int main()
{ 
   // char *s = NULL;
    ft_printf(".%5x\n", 1);
   printf(".%5x\n", 1);
    return (0);
}
 */
/*
int main()
{  
    int i = 0;
    char *s = NULL;
    int j = 0;
   
   i += printf("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
   j += ft_printf("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
   //int i = printf("%0.0d", 0);
   printf("\n");
   //int j = ft_printf("%0.0d", 0);
    printf("\n%d\n", i);
    printf("m %d\n", j);
   return (0);   
}
*/
