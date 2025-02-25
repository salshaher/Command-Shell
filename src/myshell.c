#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <signal.h>
#include "queue.h"
#include "helper.h"
#include <errno.h>
#include <limits.h>
#define MAXCOM 1024 // max number of letters to be supported 
#define MAXLIST 100 // max number of commands to be supported

// Clearing the shell using escape sequences 
#define clear() printf("\033[H\033[J") 

/* This is the ready queue */
Queue *rear = NULL;
Queue *front = NULL;

int main() 
{
  /* Leave this clear() here */
  clear();
  // Loop forever 
  while(1) 
  {
  	// Print prompt
	printf("myshell> ");
	// Create a character array of size 1023 ( one slot reserved for '\0')
	char buf[MAXCOM];
	// Read user input
	// reads a line from stdin into the buffer pointed to by buf 
	fgets(buf,MAXCOM,stdin);
	char *word[MAXLIST];
	// Parse the user input into commands and arguments 
	split_string(buf,word);
	
			/*	Now check commands  */
	
	// if command is "start", execute the given process
	if (strcmp(word[0], "start") == 0)
	{
	    int pid = fork();
		if (pid == 0) 
		{
			/* This code is done by the child process */
			// int execvp(const char *file, char *const argv[]); *file -> command to execute , argv[] -> command arguemnts 
			execvp(word[1], &word[1]);
			// will only print if execvp fail
			printf("myshell: failed to execute %s - %s\n" , word[1] , strerror(errno));
		}
		else if (pid > 0)
		{
			/* This code is done by the parent process */
			// add the new child to the queue
			enqueue(&rear, &front, pid);
			printf("myshell: process %d has been executed\n" , pid);
		}
		// if fork() failed 
		else 
		{
			printf("myshell: failed to start %s\n" , word[1]);
		}
	} // end if start 
	// if command is "hold", wait for executing process to complete
	else if(strcmp(word[0], "hold") == 0)
	{ 
	    int status;
	    // if queue is empty 
	    if(isEmpty())
	      printf("myshell: no executing processes to wait for\n");
	    else
	    {
	      pid_t pid1 = wait(&status);
	      printf("myshell: process %d exited with status %d\n", pid1, status);	
	      // remove head of queue
	      dequeue(&front);	    	
	    }	
	} // end if hold
	// if command is "run", start then wait for given process to complete
	else if(strcmp(word[0], "run") == 0)
	{
	    int status;
		int pid2 = fork();
		if (pid2 == 0) 
		{
			/* This code is done by the child process */
			// int execvp(const char *file, char *const argv[]); *file -> command to execute , argv[] -> command arguemnts 
			execvp(word[1], &word[1]); 
			// will only print if execvp fail
			printf("myshell: failed to run %s - %s\n", word[1], strerror(errno));
		}
		else if (pid2 > 0)
		{
			/* This code is done by the parent process */
			enqueue(&rear, &front, pid2);
			printf("myshell: process %d has been executed\n", pid2);
			pid_t cid = waitpid(pid2, &status, 0);
			if (cid >0)
			  {
				printf("myshell: process %d exited with status %d\n", pid2, status);
				dequeue(&front);
			  }
		}
		// if fork() failed 
		else 
		{
			printf("myshell: failed to run %s\n", word[1]);
		}
	} // end if run
	// if command is "abort", kill the indicated process
	else if(strcmp(word[0], "abort") == 0)
	{
		// atoi() convert ascii to integer
		// int kill(pid, sig); SIGKILL -> terminate immediately/hard kill process with pid
		int ret = kill(atoi(word[1]),SIGKILL);
		// if kill fails
		if(ret == -1)
			printf("myshell: failed to terminate process %s\n",word[1]);
		else
			printf("myshell: process %s terminated\n",word[1]);
	} // end if abort
    // if command is "stop", suspend the indicated process
    else if (strcmp(word[0], "stop") == 0)
    {
		// atoi() convert ASCII to integer
		// int kill(pid, sig); SIGSTOP -> Pause the process
        int ret = kill(atoi(word[1]), SIGSTOP);
        if (ret == -1)
	    printf("myshell: process %s failed to stop\n" , word[1]);
        else
            printf("myshell: process %s has stopped\n" , word[1]);      
	} // end if stop
	// if command is "continue", resume the indicated process
	else if (strcmp(word[0], "continue") == 0)
	{
		// atoi() convert ascii to integer
		// int kill(pid, sig); SIGSTOP -> Resume process
		int ret = kill(atoi(word[1]), SIGCONT);
		if (ret == -1)
			printf("myshell: process %s failed to resume\n" , word[1]);
		else
			printf("myshell: process %s has resumed\n" , word[1]);
	} // end if continue 
	// if command is "quit", close the shell
	else if(strcmp(word[0], "quit") == 0)
	{
	  exit(0);
	}
	else if(strcmp(word[0], "") == 0)
	{
		continue;
	}
	else
	{
	  printf("myshell: unknown command - %s\n", buf);
	}
  } // end while
    
  return -1;
  
} // end main




