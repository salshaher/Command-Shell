#include <string.h>
#include "helper.h"

void split_string(char *str, char **words)
{

	char delim[] = " ";

	int i = 0;
	words[i] = strtok(str, delim);
	while(words[i] != NULL)
	{
		/* Remove \n from word, if exists */
		remove_char(words[i], '\n'); 

		/* Get next word */		
		i++;
		words[i] = strtok(NULL, " ");
	}

	return;

}

void remove_char(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}
