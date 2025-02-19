#include "libft.h"

double  ft_atof(const char *str)
{
    double  result;
    double  fraction;
    int sign;

    result = 0.0;
    fraction = 1.0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
        sign = (*str++ == '-') ? -1 : 1;
    while (*str >= '0' && *str <= '9')
        result = result * 10.0 + (*str++ - '0');
    if (*str == '.')
    {
        str++;
        while (*str >= '0' && *str <= '9')
        {
            fraction *= 0.1;
            result += (*str++ - '0') * fraction;
        }
    }
    return (result * sign);
}