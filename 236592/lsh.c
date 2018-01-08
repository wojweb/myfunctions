#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

void lsh_loop(void);
char *lsh_read_line(void);
char **lsh_split_line(char*);
int lsh_launch(char **);
void lsh_redirection_out(char **args, int position);
void lsh_redirection_in(char **args, int position);
int lsh_cd(char **args);
int lsh_exit(char **args);
int lsh_execute(char **args); 

int main(int argc, char **argv)
{
   //Load config files, if any.
   
   //Run command loop.
   lsh_loop();

   //Perform any shutdown/cleanup


   return EXIT_SUCCESS;
}

void lsh_loop(void)
{
   char *line;
   char **args;
   int status = 1;

   do{
	  printf("lsh: ");
	  line = lsh_read_line();
	  args = lsh_split_line(line);
	  
	  

	  status = lsh_launch(args);

	  //free(line);
	  //free(args);
   } while(status);
}

char *lsh_read_line(void)
{
   char *line = NULL;
   size_t bufsize = 0;
	   getline(&line, &bufsize, stdin);
   
   if(line[0] == '\0'){
	  printf("\n");
	  exit(0);
   }
   
   return line;
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *line)
{
   int bufsize = LSH_TOK_BUFSIZE, position = 0;
   char **tokens = malloc(bufsize * sizeof(char*));
   char *token;

   if(!tokens){
	  fprintf(stderr, "lsh: allocation error\n");
	  exit(EXIT_FAILURE);
   }
   
   token = strtok(line, LSH_TOK_DELIM);
   while(token != NULL){
	  tokens[position] = token;
	  position++;
	  
	  if(position >= bufsize){
		 bufsize += LSH_TOK_BUFSIZE;
		 tokens = realloc(tokens, bufsize *sizeof(char*));
		 if(!tokens){
	  	fprintf(stderr, "lsh: allocation error\n");
		  exit(EXIT_FAILURE);
		 }
	  }
   token = strtok(NULL, LSH_TOK_DELIM);
   }
   tokens[position] = NULL;
   return tokens;
}

void lsh_redirection_out(char **args, int position)
{
   int fd;
   args[position] = NULL; 
   if(args[position + 1] != NULL){
	  fd = open(args[position + 1], O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	  dup2(fd, 1);
	  close(fd);
   }
}

void lsh_redirection_in(char **args, int position)
{
   int fd;
   args[position] = NULL; 
   if(args[position + 1] != NULL){
	  fd = open(args[position + 1], O_RDONLY);
	  dup2(fd, 0);
	  close(fd);
   }
}

void lsh_pipe(char **args, int position)
{
   int pipefd[2];
   int pid;

   args[position] = NULL;
   pipe(pipefd);
   pid = fork();

   if(pid == 0)
   {
	  //replace standard input with input part of pipe
	  dup2(pipefd[0], 0);
	  close(pipefd[1]);
	  
	  if(execvp(args[position + 1], args + position + 1) == -1){
		 perror("lsh");
	  }
   } else {
	  //replace standard output with output part of pipe
	  dup2(pipefd[1], 1);
	  close(pipefd[0]);
	  
	  if(execvp(args[0], args) == -1){
		 perror("lsh");
	  }
   }
}
   
   
int lsh_launch(char **args)
{
   
   if(args[0] == NULL) //an empty command entered
	  return 1;

   if(strcmp(args[0], "cd") == 0)
	  return lsh_cd(args);

   if(strcmp(args[0], "exit") == 0)
	  return lsh_exit(args);
    


   pid_t pid, wpid;
   int status;

   pid = fork();
   if(pid == 0){
	  //Child process
	  
	  for(int i=0; args[i] != NULL; i++){
		 if(strcmp(args[i], ">>") == 0){
			lsh_redirection_out(args, i);
		 } else if(strcmp(args[i], "<<") == 0){
			lsh_redirection_in(args, i);
		 } else if(strcmp(args[i], "|") == 0){
			lsh_pipe(args, i);
		 }
	  }
	  if(execvp(args[0], args) == -1){
		 perror("lsh");
	  }
	  exit(EXIT_FAILURE);
   } else{
	  //parent process
	  do{
		 wpid = waitpid(pid, &status, WUNTRACED); //return process id
	  } while(!WIFEXITED(status) && !WIFSIGNALED(status));
   }
   return 1;
}

int lsh_cd(char **args)
{
   if(args[1] == NULL){
	  fprintf(stderr, "lsh: expected argument to \"cd\"\n");
   }else {
	  if(chdir(args[1]) != 0){
		 perror("lsh");
	  }
   }
   return 1;
}

int lsh_exit(char **args)
{
   return 0;
}
