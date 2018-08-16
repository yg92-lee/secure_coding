#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void swap(char*str1, char*str2) {
	 char tem[256];
	 strcpy(tem,str1);
	 strcpy(str1,str2);
	 strcpy(str2,tem);
}

int main( int argc, char *argv[] )
{
	/* sanity check */
	printf("\n%s : %d, enter\n", __FILE__, __LINE__);

	char input1[256], input2[256], input3[256];
  input1[255] = input2[255] = input3[255] = '\0';
	printf("Gets 3 sting values from stdin:\n");
	fgets( input1, 255, stdin );
  fflush(stdin);
	fgets( input2, 255, stdin );
  fflush(stdin);
	fgets( input3, 255, stdin );
  fflush(stdin);

  if (strcmp(input1, input2)>0) swap(input1, input2);
  if (strcmp(input2, input3)>0) swap(input2, input3);
  if (strcmp(input1, input2)>0) swap(input1, input2);
  
	printf("%s\n %s\n %s\n",input1, input2, input3);
	printf("\n%s : %d, exit\n", __FILE__, __LINE__);
	return 0;
}
