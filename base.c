#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define array_size 1000000
#define wiki_string 2003

//holds the entire wiki dump file
char wiki_entry[array_size][wiki_string];

//function to put the file into the array
int wiki_to_array()
{
	FILE *file = fopen("/homes/dan/625/wiki_dump.txt", "r");
	
	int line_number;	
	char line[wiki_string];

	for(line_number = 0;fgets(line, wiki_string,file)!= NULL; line_number++)
	{
		strcpy(wiki_entry[line_number],line);

		printf("%d\n",line_number);

		//breaking the loop after a certain point
		//if(line_number == 500000)
		//{
		//        break;
		//}
	}			

	fclose(file);
	printf("done with the file");

	//printing out the array
	int count;
	for(count = 999999; count < 1000000; count++)
	{
		printf("%s\n",wiki_entry[count]);
	}
	return 0;
}

//main function 
int main()
{
	printf("hello\n");
	wiki_to_array();
}
