#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#include<unistd.h>
#include <dirent.h>
#include<process.h>
#include<wchar.h>
#include <sys/types.h>//including respective header files

void Shell();

void Shell()
{
    //gcc main.c –o Shell -Wall -Werror -std=c99
    //C:\Users\huzai\Documents\GitHub\DNA-Profiling-Fiverr-6\DNA-Profiling\bin\Debug\DNA-Profiling.exe
    //C:\\Users\\huzai\\Documents\\GitHub\\DNA-Profiling-Fiverr-6\\DNA-Profiling\\bin\\Debug\\DNA-Profiling.exe
    int historycounter=0;
    char *history[100]={0};//variable declaration

    while(1)//looping infinite times
    {
        int status=0;
        int length=0;
        int count=0;
        char *token;
        char exe[100]={0};
        char path[100]={0};
        char command[1000]={0};
        char subcommand[1000]={0};//variable declarations, are initialized every time loop executes

        printf("sish> ");//printing message
        fgets(command, 1000, stdin);//getting command

        offsetexecution://label for goto command
        strcpy(subcommand, command);//copying command to subcommand
        token = strtok(command, " ");//tokenizing

        if(historycounter==100)//if history counter is 100, set it to 0 so it starts from beginning
        {
            historycounter=0;//setting zero
        }

        length=strlen(subcommand);

        while (count < 3){
            exe[count] = subcommand[length-4+count];
            count++;
        }
        exe[count] = '\0';

        if(strcmp(exe, "exe\n")==0 || strcmp(exe, "exe")==0)//checking if file is executable or not
        {
            token = strtok(subcommand, "\n");//tokenizing
            status=execlp(token,token,NULL);

            if(status==-1)//if file is not opened
            {
                printf("Unknown Error Occurred!\n\n");//printing message
            }
            history[historycounter]="execvp";
            historycounter++;//incrementing counter
        }
        else if(strcmp(token, "cd\n")==0 || strcmp(token, "cd")==0)//if command is "cd + path"
        {
            count=0;
            length=strlen(subcommand);//getting length

            while (count < length-4)//tokenizing the input to get subcommands
            {
                path[count] = subcommand[4+count-1];
                count++;
            }
            path[count] = '\0';//adding null character

            status=chdir(path);
            if(status<0)//if invalid path is entered
            {
                printf("Unable To Switch Directory!\n\n");//printing message
            }
            history[historycounter]= "cd";//saving command to history
            historycounter++;//incrementing counter
        }//end of else if
        else if(strcmp(token, "ls\n")==0  || strcmp(token, "ls")==0)//if command is "ls"
        {
            DIR *directory;//pointer to directory
            struct dirent *direct;//pointer to directory
            directory = opendir(".");//opening directory
            if (directory)
            {
                while ((direct = readdir(directory)) != NULL)//looping till every file is iterated
                {
                    printf("%s\n", direct->d_name);//printing file names
                }
                closedir(directory);//closing directory
                printf("\n");//new line
            }
            else//if path is invalid
            {
                printf("Invalid Directory Path!\n\n");//printing message
            }

            history[historycounter]="ls";//saving command to history
            historycounter++;//incrementing counter
        }//end of else if
        else if(strcmp(subcommand, "history\n")==0 || strcmp(subcommand, "history")==0)//if command is "history"
        {
            history[historycounter]="history";//saving command to history
            historycounter++;//incrementing counter

            for(int i=0;i<100;i++)//looping through array
            {
                if(history[i]!=0)
                {
                    printf("%d-%s\n",i,history[i]);//printing history with offset
                }
            }
            printf("\n");//new line
        }//end of else if
        else if(strcmp(subcommand, "history -c\n")==0 || strcmp(subcommand, "history -c")==0)//if command is "history -c"
        {
            history[historycounter]="history -c";//saving command to history
            historycounter++;//incrementing counter

            for(int i=0;i<100;i++)//looping
            {
                history[i]=0;//assigning zero
            }//end of for

            historycounter=0;//resetting counter
        }//end of else if
        else if(strcmp(token, "history\n")==0 || strcmp(token, "history")==0)//if user enters command of history with offset
        {
            count=0;
            history[historycounter]="history -o";//saving command to history
            historycounter++;//incrementing counter

            length=strlen(subcommand);//getting length

            while (count < length-10)//tokenizing the string
            {
                path[count] = subcommand[10+count-1];//storing in path
                count++;//incrementing count
            }
            path[count] = '\0';//adding null character

            if(count>=2)//if offset is two digit offset
            {
                int temp1=path[0]-'0';//converting char to int
                int temp2=path[1]-'0';//converting char to int

                int power=10;
                while(temp1>=power)
                    power*=10;

                status= (temp1*power)+temp2;//combining two integers
            }
            else//else if offset is 1 digit
            {
                status=(int)path[0];//storing in status
                status=status-48;//converting to int
            }//end f else

            if(status<0 || status>99 || status>historycounter)//if history counter is out of range
            {
                printf("Invalid Offset Value!\n");//printing message
            }//end of if
            else//inner else
            {
                strcpy(command, history[status]);//copying to command
                goto offsetexecution;//goto command
            }//end of inner else
        }//end of else if
        else if(strcmp(command, "exit\n")==0 || strcmp(command, "exit")==0)//if command is exit
        {
            history[historycounter]="exit";//saving command to history
            historycounter++;//incrementing counter
            exit(1);//exiting
            break;//break
        }//end of else if
        else//else
        {
            history[historycounter]="unknown command";//saving command to history
            historycounter++;//incrementing counter
            printf("Command is not recognized as an internal or external command, operable program or batch file.\n\n");//printing message if command is invalid
        }//end of else
    }//end of while loop
}//end of function
