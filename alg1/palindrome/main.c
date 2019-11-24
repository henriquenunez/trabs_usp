#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

int check(char* to_be_chk)
{
	STACK* a_stack;
	char temp;
	int till;
	int the_flag = 0;
	int i;

	a_stack = stack_create(); 
	if (strlen(to_be_chk) % 2) the_flag = 1;
	for (i = 0 ; i < strlen(to_be_chk)/2 ; i++)
	{
		//printf("%c,", to_be_chk[i]);
		stack_push(a_stack, to_be_chk[i]);
	}
	//printf("\n=====\n");
	if (the_flag) i++;
	for ( ; i <= strlen(to_be_chk) ; i++)
	{	
		temp = stack_pop(a_stack); 
		//printf("%c,", temp);
		if ( temp != to_be_chk[i]) return -1;
	}
	return 0;
}

char* parse_input(char* input_string)
{
	int position = 0;
	int ret_pos = 0;
	char* ret_string = (char*) malloc (sizeof(char) * strlen(input_string));
	while(position <= strlen(input_string))
	{
		//printf("%c\n", input_string[position]);
		if (input_string[position] <= 90 && 
			input_string[position] >= 65)
		{
			ret_string[ret_pos++] = input_string[position++];
		}
		else if (input_string[position] <= 122 && 
			input_string[position] >= 97)
		{
			ret_string[ret_pos++] = input_string[position++]-32;
		}else position++;
	}
	ret_string[ret_pos] = 0;

	//printf("%s:%s\n", input_string, ret_string);

	return ret_string;
}

char* treatutf(char* in_string)
{
	int pos = 0;
	char utf8_0 = 0;
	char* parsed = (char*) malloc (strlen(in_string) + 1);
	for (int i = 0 ; i < strlen(in_string) ; i++)
	{
		if (utf8_0 == 0)
		if (!(in_string[i] & 0x80))
		{
			parsed[pos++] = in_string[i];
		}else
		{
			utf8_0 = in_string[i];
		}
      /* UTF-8 character. */
		else{
             #define c(f, l) (utf8_0 == (f) && in_string[i] == (l))
             if(
                    c(0xc3, 0xad) || c(0xc3, 0x8d)
                 || c(0xc3, 0xae) || c(0xc3, 0x8e))
                 /* I */
                 parsed[pos++] = 'I';
             else if(
                    c(0xc3, 0xb3) || c(0xc3, 0x93)
                 || c(0xc3, 0xb4) || c(0xc3, 0x94)
                 || c(0xc3, 0xb5) || c(0xc3, 0x95))
                 /* O */
                 parsed[pos++] = 'O';
             else if(
                    c(0xc3, 0xa1) || c(0xc3, 0x81)
                 || c(0xc3, 0xa2) || c(0xc3, 0x82)
                 || c(0xc3, 0xa3) || c(0xc3, 0x83))
                 /* A */
                 parsed[pos++] = 'A';
             else if(
                    c(0xc3, 0xa9) || c(0xc3, 0x89)
                 || c(0xc3, 0xaa) || c(0xc3, 0x84))
                 /* E */
                 parsed[pos++] = 'E';
             else if(
                    c(0xc3, 0xba) || c(0xc3, 0x9a)
                 || c(0xc3, 0xbb) || c(0xc3, 0x9b))
                 /* U */
                 parsed[pos++] = 'U';
             #undef c
		utf8_0 = 0;
		}
	}
	return parsed;
}

int main()
{
	#define MAX 100
	char in[MAX];
	char* parsed;
	char* cursed;
	int len;
	int ret;
	fgets(in, MAX, stdin);
	len = strlen(in);
	if (in[len-1] == '\n') 
	{
		in[len-1] = 0;
	}
	cursed = treatutf(in);
	//printf("%s\n", cursed);
	parsed = parse_input(cursed);
	//printf("%s\n", parsed);
	//printf("%s\n", parsed);
	ret = check(parsed);
	//printf("%d\n", ret);
	if (ret == 0)
		printf("É palíndromo.\n");
	else	
		printf("Não é palíndromo.\n");
	free(parsed);
	return 0;
}
