#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"

char buffer[5120000];
char *args;

int tail(int fd, char *fname, int num)
{
  int totalLines;
  int n,i;
  int temp;
  int count = 0;

  temp = open("temp", O_CREATE | O_RDWR);

  while((n = read(fd, buffer, sizeof(buffer)))>0) 
  {
     write(temp, buffer, n);

     for(i=0; i<n; i++)
     {
       //To check if end of line is reached and count the total number of lines.
       if(buffer[i] != '\n')  
	 { continue; }
       else 
	 { totalLines++; }
     }
  }

  close(temp);
  

  if(n < 0)
  {
    printf(1,"Cannot Read File\n");
    exit();
  }

  temp = open("temp",0);

  while((n=read(temp, buffer, sizeof(buffer))) > 0)
  {
     for(i=0; i<n; i++)
     {
        if(count >= (totalLines - num))
        {    
	  printf(1, "%c", buffer[i]);
	}
	else if (totalLines < num) // check if total no of lines in fle are less than requested number
	{
	   printf(1, "%c", buffer[i]);
	}
	else if (buffer[i] == '\n')
	{
	   count++;
	}
     }
   }
   close(temp);
   unlink("temp");
  return 0;
  }


int main(int argc, char *argv[])
{
   int i;
   int fd = 0;
   int printLines = 10;
   char *fname;
   char option;

  fname = "";

  if (argc <= 1) //Take input from user and print default no of lines
  {
     tail(0,"",printLines);
     exit();
  }

  else
  {
     for(i=1; i<argc; i++)
     {
	option = *argv[i];
   
	if(option == '-')
	{
	   argv[i]++;
	   printLines = atoi(argv[i]++);
	}
	else
	{
	   if((fd = open(argv[i],0)) < 0)
	   {
	      printf(1,"Cannot open %s\n", argv[i]);
	      exit();
	    }
	 }
      }
      tail(fd,fname,printLines);
      close(fd);
      exit();
    }
  return 0;
  }

























/*int main(int argc, char *argv[])
{
  int fd;
  int i, r, numb;
  char no[20];
  
  if(argc <= 1)
  {
//    tail(0,10,"");
    printf(1,"Error enter file name:\n");
    exit();
  }

  else if(argc == 2)
  {
     for(r=1; r<argc; r++)
     {
        if((fd = open(argv[r], 0)) < 0)
	{
	   printf(1,"Here");
	   printf(1, "Cannot open %s\n", argv[r]);
	   exit();
	}
	tail(fd, argv[r], 0);
	close(fd);
     }
     exit();
  }

  else if(argc == 3)
  {
     for(r =2; r<argc; r++)
     {
        if((fd = open(argv[r],0)) < 0)
	{
	   printf(1, "Cannot open %s\n", argv[r]);
	   exit();
	}
        args = argv[1];
        for(i =1; args[i]!='\0';i++)
        {
	   no[i-1] = args[i];
        }
        no[i-1] = '\0';
        numb = atoi(no);
     
        if(args[0] != '-')
        {
	    printf(1, "Syntax error\n");
	    exit();
        }
        tail(fd, argv[r], numb);
        close(fd);
    }
    exit();
  }
  else
  {
     printf(1,"Error");
     exit();
  }
return 0;
}*/