#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define NUM_THREADS 5
int total_num= 0; // for saving total number of matches
int lenght = 0 ;// the lenght of each string that should be processed by each thread
pthread_mutex_t mutex ; // A lock for total_num shared variable


int n1 = 1000 , n2 = 1000; 
char * s1,*s2; // characters

void * Str_Function(void* startpos) ; // counting the number of matches
int match (char *a,char *b,int pos);
	
int main(int argc, char *argv[])
{

	pthread_mutex_init (&mutex, NULL) ;

	FILE *fp = fopen("strings.txt","r"); 
	s1 = (char*) malloc( n1 * sizeof( char* ));
	s2 = (char*) malloc( n2 *sizeof( char* ));	
	fgets( s1 , n1 , fp );
	fgets( s2, n2, fp );

	n1= strlen(s1) - 1 ; // omit null from the lenght
 	n2= strlen(s2) - 1 ; // omit null from the lenght

	lenght = n1 / NUM_THREADS ; // the lenght of each string that should be processed by each thread

	printf ("s1 %s\ns2 %s \nlenght to be processed by each thread %d\n", s1 , s2 , lenght);

	int i = 0 ;
	
	pthread_t worker[NUM_THREADS];

	for ( i =0 ; i< NUM_THREADS ; i++)
	{	
		//void* s;
		uintptr_t startpos = (i* (n1/NUM_THREADS)) ;
		//s =  malloc(sizeof(int));
		//*((int*)(s))  = startpos;
		//printf ("Startpos %d\n", startpos);

		if( pthread_create ( &worker[i] , NULL, Str_Function, (void*)startpos)) // create threads
		{
			fprintf(stderr, "Error creating thread\n");
			//free(s);
			return 1;
		}
			
	}	
	
	
	for ( i =0 ; i < NUM_THREADS ; i++) // wait for all to finish
	{
		if( pthread_join ( worker[i] , NULL)) 
		{
			fprintf(stderr, "Error creating thread\n");
			return 2;
		}
	}	
	
	FILE* output = fopen ("string.txt" , "w") ;

	fprintf(output,"%d Substring\n",total_num) ;
    fprintf(output,"%s",s1) ;
    fprintf(output,"%s",s2) ;

	fclose(output);

	
}


void * Str_Function(void* startpos)
{	
	int pos = ((int)startpos);
	 // the position in s1 that we should start from
	printf ("Start pos is<%d>\n", pos ) ;

	int temp = 0 ;
	int i = 0 ;
	for ( i=pos; i < pos+lenght ; i++) 
	// finding te matches
	temp += match(s1,s2, i);
	printf ("Start pos is<%d>\n", pos ) ;
	
	pthread_mutex_lock (&mutex) ;
	total_num += temp ; 
	// we need the lock to cange the total_num
	printf ("Total is now<%d>\n", total_num ) ;	
	pthread_mutex_unlock (&mutex) ;	

	//return NULL;
	pthread_exit (0);
}

int match (char *a,char *b,int pos)
{

 	int i = 0; 
	//printf (" string a : %s anb b : %s and pos : %d \n" , a , b , pos) ;

	int lenghtb = strlen (b) - 1 ;
	int num = 0 ;
	for (i =0 ; i < lenghtb ; i++ )
		if ( a[pos+i] != '\0'  && b[i] != '\0' && a[pos+i] == b[i] )
			num ++ ;
	//printf ( "lenghtb is : %d and matches are : %d \n" , lenghtb , num );	
	if ( num == lenghtb )
		return 1;
	else
		return 0;

}