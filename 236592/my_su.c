#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char ** argv)
{
    if(setuid(0))
   {
	  perror("setuid");
	  return 1;
   }
   //I am now root!
   system("/bin/bash");
}
