#include <unistd.h>
#include <stdint.h>

int was_char(char *s, int index, char c)
{
	int i = 0;
	while(i < index)
	{
		if(s[i] == c)
			return (1);
		i++;
	}
	return (0);	
}

int char_in_str(char *s, char c)
{
	int i = 0;
	while(s[i])
	{
		if(s[i] == c)
			return (1);
		i++;
	}
	return (0);	
}
//корявое условие!!! Нужно сравнивать символы в первой строке со второй.
//Если символ есть во второй строке, и он не повторялся ранее в первой, то его печатаем.
//Т е итерируемся только по первой строке
int main(int argc, char **arg)
{
    if(argc != 3)
    	return (0);
	int i = 0;
	while (arg[1][i])
	{
		if(char_in_str(arg[2], arg[1][i]) && !(was_char(arg[1], i, arg[1][i])))
			write(1, &arg[1][i], 1);	
		i++;
	}
	write(1, "\n", 1);
    return (0);
}