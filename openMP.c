#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
//#include <omp.h>
#define WIKI_ARRAY_SIZE 1000000
#define WIKI_STRING_SIZE 2003 /* The number of characters in each wiki entry. Must account for newline and terminating characters. */
#define WORDS_ARRAY_SIZE 50000 /* The number of words being searched for in each wiki entry. Should be 50000 for production. */
#define WORDS_STRING_SIZE 11 /* The number of characters taken up by a word. Must account for newline and terminating characters. */


/* All of the wiki entries. */
//char *wiki_array[WIKI_ARRAY_SIZE][WIKI_STRING_SIZE];
//char wiki_array[WIKI_ARRAY_SIZE][WIKI_STRING_SIZE];
char* wiki_array = malloc(sizeof(char) * 1000000);

/* All of the words being searched for. */
char words_array[WORDS_ARRAY_SIZE][WORDS_STRING_SIZE];

/* Results of the word search*/
char results_array[WORDS_ARRAY_SIZE][WIKI_ARRAY_SIZE];

/* Initialize the results array to all zero */
void init_array()
{
    int i, j;

    for(i = 0; i < WORDS_ARRAY_SIZE; i++)
    {
        for(j= 0; j < WIKI_ARRAY_SIZE; j++)
        {
            results_array[i][j] = 'f';
        }
    }
}

/* Read all of the wiki entries and words into local data structures from thier resprctive files. */
int read_to_memory()
{
    /* Read the wiki article into memory line by line. */
    FILE *file = fopen("/homes/dan/625/wiki_dump.txt", "r");

    if(file == NULL)
    {
        printf("fail");
        return -1;
    }

    /* Read each wiki line into memory. */
    int line_num = 0;
    char line[WIKI_STRING_SIZE];
    while(fgets(line, WIKI_STRING_SIZE, file) != NULL)
    {

        strcpy(wiki_array[line_num], line);

        printf("line: %d\n",line_num);
        //if(line_num == 10)
        //{
        //      break;
        //}
        line_num++;
    }
    fclose(file);
        printf("hello %s\n",wiki_array[999999]);



    return 0;
}


int main()
{
    printf("hello!!!@@!!");
    //init_array();

    printf("array has been initialized.");
/*
    if(read_to_memory() == 0)
    {
        printf("it worked!");
    }
    else
    {
        printf("ERROR!");
        return -1;
    }*/
    //pthread_exit(NULL);
}
