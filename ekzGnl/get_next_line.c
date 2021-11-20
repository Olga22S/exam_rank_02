#include "get_next_line.h"

int ft_strlen(char *s)
{
    int i = 0;
    if(!s)
        return 0;
    while (s[i])
    i++;
    return (i);
}

char *join_s(char *rem, char *buf)
{
    if (!rem && !buf)
        return (NULL);
    char *s;
    int i = 0;
    int j = 0;
    int size = ft_strlen(rem) + ft_strlen(buf)+1;
    s = malloc(sizeof(char) * size);
    if(rem)
    {
        while (rem[i])
        {
            s[i] = rem[i];
            i++;
        }  
    }
    while (buf[j])
    {
        s[i] = buf[j];
        i++;
        j++;
    }
    s[i] = '\0';
    free(rem);
    return (s);
}

char *get_l(char *rem)
{
    int i = 0;
    char *s;
    while(rem[i] != '\n' && rem[i])
        i++;
    s = malloc(sizeof(char) * (i+1));
    i = 0;
    while (rem[i] && rem[i] != '\n')
    {
        s[i] = rem[i];
        i++;
    }
    s[i] = '\0';
    return(s);   
}

char *getrem(char *rem)
{
    int i = 0;
    int j = 0;
    while(rem[i] != '\n' && rem[i])
        i++;
    if(!rem[i])
    {
        free(rem);
        return NULL;
    }
    char *s;
    s = malloc(sizeof(char) * (ft_strlen(rem) - i + 1));
    i++;//если рем стоит на \n то идем на след элемент, иначе rem[i] нет и выходим
    while (rem[i])
    {
        s[j] = rem[i];
        i++;
        j++;
    }
    s[j] = '\0';
    free(rem);
    return (s);  
}

int     get_next_line(char **line)
{
    static char *rem;
    char buf[2];
    int c = 1;

    if(!line)
        return -1;
    while (buf[0] != '\n' && c != 0)
    {
        c = read(0, buf, 1);
        if (c == -1)
            return (-1);
        buf[c] = '\0';
        rem = join_s(rem, buf);
    }
    if(!rem)
        return (0);
    *line = get_l(rem);
    rem = getrem(rem);
    return ((c == 0)? 0 : 1);
}
