#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int historycounter=0;

void Shell();
void ReadHistory();
void WriteHistory(char *history);
void WriteHistoryCounter(int count);
void ReadHistoryCounter();
void ClearHistory();


void Shell()
{
    //WriteHistoryCounter(0);
    ReadHistoryCounter();

    while(1)
    {
        char command[1000]={0};

        printf("sish> ");
        fgets(command, 1000, stdin);

        if(strcmp(command, "history\n")==0)
        {
            WriteHistory("history");
            ReadHistory();
        }
        else if(strcmp(command, "history -c\n")==0)
        {
            WriteHistory("exit");
            ClearHistory();
            historycounter=0;
        }
        else if(strcmp(command, "exit\n")==0)
        {
            WriteHistory("exit");
            WriteHistoryCounter(historycounter);
            exit(1);
            break;
        }
        else
        {
            //WriteHistory(command);
            WriteHistory("unrecognized command");
            printf("Command is not recognized as an internal or external command, operable program or batch file.\n\n");
        }
    }
}
void ClearHistory()
{
    FILE *fileptr;
    fileptr=fopen("HistoryCounter.txt","w");
    fclose(fileptr);
    fileptr=fopen("History.txt","w");
    fclose(fileptr);
}

void WriteHistoryCounter(int count)
{
    FILE *fileptr;
    fileptr=fopen("HistoryCounter.txt","w");
    fprintf(fileptr,"%d\n",count);
    fclose(fileptr);
}

void ReadHistoryCounter()
{
    FILE *fileptr;
    fileptr=fopen("HistoryCounter.txt","r");
    fscanf(fileptr,"%d",&historycounter);
    fclose(fileptr);
}

void WriteHistory(char *history)
{
    FILE *fileptr;
    historycounter++;
    fileptr=fopen("History.txt","a");
    fprintf(fileptr,"%d %s\n",historycounter,history);
    fclose(fileptr);
}

void ReadHistory()
{
    char character;
    FILE *fileptr;
    fileptr=fopen("History.txt","r");

    if(fileptr==NULL)
    {
        printf("Unable to read history.");
    }
    else
    {
        do
        {
            character = fgetc(fileptr);
            printf("%c", character);
        }
        while (character != EOF);
        fclose(fileptr);
    }
    printf("\n");
}
