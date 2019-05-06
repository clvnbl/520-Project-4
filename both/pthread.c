#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/resource.h>
#include <sys/time.h>

#define array_size 1000000
#define wiki_string 2003

char wiki_entry[array_size][wiki_string];
int LCSuf [wiki_string][wiki_string];
char results_array[array_size][wiki_string];
int thread_amount = 1;

pthread_mutex_t lockVar = PTHREAD_MUTEX_INITIALIZER;


//function to copy the file into the array
int wiki_to_array()
{
	FILE *file = fopen("/homes/dan/625/wiki_dump.txt", "r");
	
	int line_number;	
	char line[wiki_string];

	//add the file to the wiki_entry array
	for(line_number = 0;fgets(line, wiki_string,file)!= NULL; line_number++)
	{
		strcpy(wiki_entry[line_number],line);
	}		

	fclose(file);

	return 0;
}

//function to get the prework done for the findThings function. 
void * LargestCommonSubstring(void *myID)
{
	int inner;
	int outer;
	int string;
		
	//getting start and end positions for the multithreading. 
	int startPos = ((int) myID) * (array_size / thread_amount);
	int endPos = startPos + (array_size / thread_amount);
	
	if((int)myID == thread_amount -1)
	{
		endPos = array_size;
	} 
	
	//calling the findThings function with only 2 strings from the wiki_entry array
	for(outer = startPos; outer < endPos; outer++)
	{
		//gathers the length of each string
		int m = strlen(wiki_entry[outer]);
		int n = strlen(wiki_entry[outer+1]);

		//calls the findThings function
		findThings(wiki_entry[outer],wiki_entry[outer+1],m,n,myID);
	}
	pthread_exit(NULL);
}

//function to find the largest common substring
int findThings(char* string1, char* string2, int m, int n,void *myID)
{
	int len = 0;

	int row,col,i,j;
	
	//finds the largest common substring through magic
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			//pthread_mutex_lock(&lockVar);
			if (i == 0 || j ==0)
			{
				LCSuf[i][j] = 0;
			}
			else if (string1[i - 1] == string2[j - 1])
			{
				LCSuf[i][j] = LCSuf[i - 1][j - 1] + 1;
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
			
			//pthread_mutex_unlock(&lockVar);
		}
	}
	
	
	char* resultStr = (char*)malloc((len + 1) * sizeof(char)); 

	//adds the substring to the resultStr 
	while (LCSuf[row][col] != 0)
	{
		resultStr[--len] = string1[row - 1];
		row--;
		col--;
	}	
	//copies the substring to the results_array
	strcpy(results_array[counter],resultStr);
	
	return 0;
}

//function to print the results_array
int print()
{	int count;

	//loops through the array and prints it
	for(count = 0; count < array_size; count++)
	{
		printf("job %d: %s\n",count,results_array[count]);
	}
	return 0;
}

//main function
int main()
{
	//struct for time
	struct timeval t1, t2, t3, t4, t5;
 	int elapsedTime;
	
	//gathering memory stats
	struct rusage r_usage;
	getrusage(RUSAGE_SELF,&r_usage);
	printf("-----------------------------------------------------------------------------------\n");
    printf("Memory usage before the wiki is loaded: %ld kilobytes\n",r_usage.ru_maxrss);

	//gets the current time
	gettimeofday(&t1, NULL);

	//calls the wiki_to_array
	wiki_to_array();
	
	//gets the current time, and figures out how much time was spent 
	gettimeofday(&t2, NULL);
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000; //sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000; // us to ms
	printf("time spent loading the file: %d ms\n", elapsedTime);

	//get how much memory is being used.
	getrusage(RUSAGE_SELF,&r_usage);
    printf("Memory usage after the wiki is loaded: %ld kilobytes\n",r_usage.ru_maxrss);
	fflush(stdout);

	//all the things needed for pthreads
	pthread_t thread_list[thread_amount];
	pthread_attr_t attribute;
	void *status;
	pthread_attr_init(&attribute);	
	pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_JOINABLE);
	
	
	int count,rc;
	
	gettimeofday(&t3, NULL);
	for(count = 0; count < thread_amount; count++)
	{	
		//finds the largest common substring
		rc = pthread_create(&thread_list[count], &attribute, LargestCommonSubstring, (void *)count);
		if(rc)
		{
			printf("error with the thread first loop: %d\n",rc);
		}
	}

	for(count = 0; count < thread_amount; count++)
	{
		rc = pthread_join(thread_list[count], &status);
		if(rc)
		{
			printf("error with the thread: %d\n", rc);
			exit(-1);
		
		}
	}
	
	//gets the current time, and figures out how much time was spent 
	gettimeofday(&t4, NULL);
	elapsedTime = (t4.tv_sec - t3.tv_sec) * 1000; 
	elapsedTime += (t4.tv_usec - t3.tv_usec) / 1000; 
	fflush(stdout);
	printf("time spent comparing substrings: %d ms\n", elapsedTime);
	
	//get how much memory is being used
  	getrusage(RUSAGE_SELF,&r_usage);
	printf("Memory usage after the thread work has been done: %ld kilobytes\n\n",r_usage.ru_maxrss);	
	printf("-----------------------------------------------------------------------------------\n");
	fflush(stdout);
	
	//prints out the results array
	print();

	//get how much memory is being used
	getrusage(RUSAGE_SELF,&r_usage);
	printf("-----------------------------------------------------------------------------------\n");
	printf("\nMemory usage after printing everything: %ld kilobytes\n",r_usage.ru_maxrss);

	//gets the current time, and figures out how much time was spent 
	gettimeofday(&t5, NULL);
	elapsedTime = (t5.tv_sec - t1.tv_sec) * 1000; 
	elapsedTime += (t5.tv_usec - t1.tv_usec) / 1000; 
	printf("total run time of the program: %d ms\n", elapsedTime);
	fflush(stdout);
	
	
	pthread_exit(NULL);
}
