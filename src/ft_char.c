#include "../includes/ft_printf.h"

void b_space(char *string, int width)
{
    int i;
    char *a;
    
    i = 0;
    a = (char*)string;
    while(width > 0)
    {
        a[i] = ' ';
        width--;
        i++;
    }
    a[i] = '\0';
}

char *ft_str_right_cpy(char *string, char *s, int precision, t_flags *t)
{
    int i;
    int j;

    if(!t->dot)
    {
        i = precision < ft_strlen(s) ? ft_strlen(string) - precision : ft_strlen(string) - ft_strlen(s);
        j = 0;
        while(j < precision && string[i] && s[j])
            string[i++] = s[j++];
    }
    return(string);
}

char *ft_str_left_cpy(char *string, char *s, int precision, t_flags *t)
{
    int i;

	i = 0;
    if (!t->dot)
    {
	    while (i < precision && s[i])
	    {
		    string[i] = s[i];
		    i++;
	    }
    }
	return (string);
}

void ft_char(t_flags *t, va_list *ap)
{
    ft_putchar((char)va_arg(*ap, int));
    t->pf_return++;
}

void ft_string(t_flags *t, va_list *ap, const char *format)
{
    char *s;
    char *string;
    int width;
    int precision;
    int p = 0;

    if(format[t->step] == '%')
    {
        s = strdup("%");
        p = 1;
    }
    else
        s = (char*)va_arg(*ap, char*); 
    //printf("width == %d, precision == %d, minus == %d\n", t->width, t->precision, t->minus);
    if (!t->width && t->precision == -1 && !t->dot)
        string = strdup(s);
    else
    {
        if (t->width && t->width > t->precision && t->width >= ft_strlen(s))
            width = t->width;
        else if (t->width && t->width > t->precision && t->width < ft_strlen(s) && t->precision >= 0)
            width = t->width;
        else if (t->width && t->width > t->precision && t->width < ft_strlen(s) && t->precision == -1)
            width = ft_strlen(s);
        else if (t->width && t->width <= t->precision && t->width > ft_strlen(s))
            width = t->width;
        else
            width = t->precision < ft_strlen(s) ? t->precision : ft_strlen(s);
        precision = t->precision > -1 ? t->precision : 9999;
        //printf("width == %d, precision == %d, minus == %d\n", t->width, t->precision, t->minus);
        if (!(string = (char*)malloc(sizeof(char) *  width + 1)))
            return;
        b_space(string, width);
        if(t->minus)
            string = ft_str_left_cpy(string, s, precision, t);
        else
            string = ft_str_right_cpy(string, s, precision, t);
    }
    ft_putstr(string);
    t->pf_return += ft_strlen(string);
    if(p)
        free(s);
    free(string);
}