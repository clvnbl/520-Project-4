#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define array_size 1000000

#define wiki_string 2003
char wiki_entry[array_size][wiki_string];
//int ** LCSuf = malloc(sizeof(int*)*wiki_string*wiki_string);
int LCSuf [wiki_string][wiki_string];
char results_array[array_size][wiki_string];


int wiki_to_array()
{
	FILE *file = fopen("/homes/dan/625/wiki_dump.txt", "r");
	
	int line_number;	
	char line[wiki_string];

	for(line_number = 0;fgets(line, wiki_string,file)!= NULL; line_number++)
	{
		strcpy(wiki_entry[line_number],line);

		//printf("%d\n",line_number);
               /* if(line_number == 1000)
                {
                        break;
                *///}
	}		

	fclose(file);
	printf("done with the file\n");
	fflush(stdout);
	//printing out the array	
	/* int count;
	for(count = 999999; count < 1000000; count++)
	{
		printf("%s\n",wiki_entry[count]);
	} */
	
	//char string1[1];
	//strcpy(string1, wiki_entry[1]);
	//printf("did it work?: %s",string1);

	return 0;
}

char * LargestCommonSubstring()
{
	int inner;
	int outer;
	int string;

	char result[wiki_string];
	//printf("hello!!!\n");
	//fflush(stdout);
	//gets the string
	for(outer = 0; outer < 1000000; outer++)
	{
		//printf("loop: %d\n",outer);
		//fflush(stdout);
		int m = strlen(wiki_entry[outer]);
		int n = strlen(wiki_entry[outer+1]);
		
		//printf("----------------------------------------------------------------------------------------\n");
		//printf("string from: %d to %d\n\n",outer+1,outer+2);
		findThings(wiki_entry[outer],wiki_entry[outer+1],m,n,outer);
		//printf("in string1: %s\n",wiki_entry[outer]);
		//printf("in string2: %s\n\n\n\n",wiki_entry[outer+1]);

		//printf("string1 length: %d\n",m);	
		//printf("string2 length: %d\n",n);	
		

		//char buffer[10000];
		//sprintf(buffer,"thing: %s\n\n",string2);
		//printf("%s",buffer);
		/*for(outer = 0; outer < wiki_string; outer++)
		{
			if(string1[outer] == string2[outer])
			{
				strcat(result,string1[outer]);
			}
		}*/
		

		//gets the character from the first string
		/*for(outer = 0; outer < wiki_string; outer++)
		{
			
		}*/
	}
	//printf("output of result:  %s\n", result);
}

int findThings(char* string1, char* string2, int m, int n,int counter)
{

	//printf("string1: %s\n",string1);
	//printf("string2: %s\n",string2);
	/*printf("m: %d\n",m);
	printf("n: %d\n\n\n",n);*/
	//printf("Hello! I am in the findThings function! \n");
	//printf("m: %d\n",m);
	//printf("n: %d\n",n);

	//printf("before\n");
	//int LCSuff [1818][1212];
	//int LCSuff [m+1][n+1];
	//int *LCSuff = (int *)malloc((m+1) *(n+1) * sizeof(int));
	//printf("after\n");
	
	int len = 0;

	int row,col,i,j;
	
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			if (i == 0 || j ==0)
			{
				//printf("before");
				LCSuf[i][j] = 0;
				//printf("after");
			}
			else if (string1[i - 1] == string2[j - 1])
			{
				//printf("before");
				LCSuf[i][j] = LCSuf[i - 1][j - 1] + 1;
				//printf("after");
				if (len < LCSuf[i][j])
				{
					len = LCSuf[i][j];
					row = i;
					col = j;
				}
			}
			else
			{
				LCSuf[i][j] = 0;
			}
		}
	}
	
	
	//printf("before maloc\n");
	char* resultStr = (char*)malloc((len + 1) * sizeof(char)); 

	while (LCSuf[row][col] != 0)
	{
		resultStr[--len] = string1[row - 1];
		row--;
		col--;
	}
	//printf("most common substring: %s\n\n",resultStr);
	

	//char integer[32];
        //sprintf(integer, "%d: ", counter);
	//strcat(results_array[counter],integer);
	
	strcpy(results_array[counter],resultStr);
		
	//free(resultStr);	
	return 0;
}

int print()
{	int count;
	for(count = 0; count < 1000000; count++)
	{
		printf("job %d: %s\n",count,results_array[count]);
	}
	return 0;
}

int main()
{
	//printf("hello\n");
	wiki_to_array();
	LargestCommonSubstring();
	print();
}
