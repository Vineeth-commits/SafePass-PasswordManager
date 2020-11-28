#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Buffer_size 100 

struct username
{
    int nameLength;
    int userID;
    char userNameAttempt[];
};

struct password
{
    int passwordLength;
    char passwordAttempt[];
};

struct Node
{
    char data[Buffer_size];
    struct Node *next;
}*first=NULL;

void createNode(char logData[])
{
    struct Node *t,*last;
    first = (struct Node *)malloc(sizeof(struct Node));
    strcpy(first->data, logData);
    first->next=NULL;
    last=first;
}

void displayNode(struct Node *p)
{
    FILE *appendUser = fopen("./records-and-logs/loginLogs.txt", "a");
    while(p!=NULL)
    {
        // p->data[strlen(p->data)] = '\n';
        fputs(p->data,appendUser);
        p=p->next;
    }
    char lineBreak[] = "\n"; 
    fputs(lineBreak,appendUser);
    fclose(appendUser);
}

int countNode(struct Node *p)
{
    int counter=0;
    while(p!=NULL)
    {
        counter++;
        p=p->next;
    }
    return counter;
}

void insertionNode(struct Node *p,char dataLog[])
{
    struct Node *t, *last;
    int index = countNode(p);
    printf("%d",index);
    t = (struct Node *)malloc(sizeof(struct Node));
    strcpy(t->data, dataLog);
    t->next=NULL;
    last = first;
    last->next = t;
    last = t;
}

void encryption(char fileName[])
{
    char ch;
    FILE *fileOrg = fopen(fileName,"r");
    FILE *fileTemp = fopen("temp.txt","w");
    if((fileOrg == NULL)||(fileTemp == NULL))
    {
        printf("Unable to open the file\n");
        printf("Inspection of the file is needed\n");
        exit(-1);
    }
    ch = fgetc(fileOrg);
    while(ch != EOF)
    {
        ch = ch+100;
        fputc(ch, fileTemp);
        ch = fgetc(fileOrg);
    }
    fclose(fileOrg);
    fclose(fileTemp);
    fileOrg = fopen(fileName, "w");
    if(fileOrg == NULL)
    {
        printf("Unable to open the file\n");
        printf("Inspection of the file is needed\n");
        exit(-1);
    }
    fileTemp = fopen("temp.txt", "r");
    if(fileTemp == NULL)
    {
        printf("Unable to open the file\n");
        printf("Inspection of the file is needed\n");
        exit(-1);
    }
    ch = fgetc(fileTemp);
    while(ch != EOF)
    {
        ch = fputc(ch, fileOrg);
        ch = fgetc(fileTemp);
    }
    fclose(fileOrg);
    fclose(fileTemp);
}

void decryption(char fileName[])
{
    char ch;
    FILE *fileOrg = fopen(fileName,"r");
    FILE *fileTemp = fopen("temp.txt","w");
    if((fileOrg == NULL)||(fileTemp == NULL))
    {
        printf("Unable to open the file\n");
        printf("Inspection of the file is needed\n");
        exit(-1);
    }
    ch = fgetc(fileOrg);
    while(ch != EOF)
    {
        ch = ch-100;
        fputc(ch,fileTemp);
        ch = fgetc(fileOrg);
    }
    fclose(fileOrg);
    fclose(fileTemp);
    fileOrg = fopen(fileName, "w");
    if(fileOrg == NULL)
    {
        printf("Unable to open the file\n");
        printf("Inspection of the file is needed\n");
        exit(-1);
    }
    fileTemp = fopen("temp.txt", "r");
    if(fileTemp == NULL)
    {
        printf("Unable to open the file\n");
        printf("Inspection of the file is needed\n");
        exit(-1);
    }
    ch = fgetc(fileTemp);
    while(ch != EOF)
    {
        ch = fputc(ch, fileOrg);
        ch = fgetc(fileTemp);
    }
    fclose(fileOrg);
    fclose(fileTemp);
}

struct username *storeUsername(struct username *s, char username[])
{
    s = malloc(sizeof(*s) + sizeof(char) * strlen(username));
    s->nameLength = strlen(username);
    strcpy(s->userNameAttempt, username);
    return s;
}

struct password *storePassword(struct password *s, char password[])
{
    s = malloc(sizeof(*s) + sizeof(char) * strlen(password));
    s->passwordLength = strlen(password);
    strcpy(s->passwordAttempt,password);
    return s;
}

void storeLog(char username [], char password[], int userID)
{
    struct username *user = storeUsername(user,username);
    struct password *passwd = storePassword(passwd,password);
    user->userID = userID;
    printf("Login Successful");
    printf("\n Welcome %s",user->userNameAttempt);
    insertionNode(first,username);
}
int login(FILE *userFile,FILE *passwdFile)
{
    printf("Hey, you need to enter your username and password\nUsername: ");
    char nameEntered[Buffer_size];
    char passwdEntered[Buffer_size];
    int userCounter = 1;
    int passwordCounter = 1;
    scanf("%[^\n]%*c",nameEntered);
    char nameCompare[Buffer_size]; 
    char passwdCompare[Buffer_size];
    while(fgets(nameCompare, Buffer_size, userFile)!= NULL )
    {
        nameCompare[strlen(nameEntered)] = '\0';
        if(strcmp(nameEntered,nameCompare)==0)
        {
            printf("Enter your password: ");
            scanf("%[^\n]%*c",passwdEntered);
            while(fgets(passwdCompare, Buffer_size, passwdFile)!= NULL)
            {
                passwdCompare[strlen(passwdEntered)] = '\0';
                if((strcmp(passwdEntered,passwdCompare)==0)&&(passwordCounter==userCounter))
                {
                    storeLog(nameCompare,passwdCompare,passwordCounter);
                    return passwordCounter;
                }
                passwordCounter++;
            }
        }
        userCounter++;
    }
    fclose(userFile);
    fclose(passwdFile);
    printf("Username and/or Password incorrect\n");
    return -1; 
}

void newVault(char dataToAppend[])
{
    char dataToAppendPasswd[Buffer_size];
    FILE *appendUser = fopen("users.txt", "a");
    FILE *appendPasswd = fopen("passwds.txt","a");
    if (appendUser == NULL) 
    {
        printf("Unable to open the file\n");
        printf("Inspection of the file is needed\n");
        exit(-1);
    }
    dataToAppend[strlen(dataToAppend)] ='\n';
    fputs(dataToAppend, appendUser);
    printf("Enter the password:\n");
    fflush(stdin);
    fgets(dataToAppendPasswd,Buffer_size,stdin);
    fputs(dataToAppendPasswd,appendPasswd);
    printf("New vault has been created\n");
    printf("Login again to input entries into your vault\n");
    fclose(appendUser);
    fclose(appendPasswd);
}

int main()
{
    int choice=1;
    char newUserName[Buffer_size];
    char newUserNameCompare[Buffer_size];
    int userID;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    FILE *userFile = fopen("users.txt","r");
    FILE *passwdFile= fopen("passwds.txt","r");
    decryption("./records-and-logs/loginLogs.txt");
    decryption("users.txt");
    decryption("passwds.txt");
    createNode(asctime (timeinfo));
    returnChoice:
    printf("Select the options below:\n");
    printf("Press 1 to login in to your vault\n");
    printf("Press 2 to create a new vault\n");
    switch(choice){
        case 1:
                freopen("users.txt","r",userFile);
                freopen("passwds.txt","r",passwdFile);
                if(userFile==NULL||passwdFile==NULL)
                {
                    printf("Error! Could not open file\n"); 
                    printf("Inspection of the file is needed\n");
                    exit(-1);
                }
                userID = login(userFile,passwdFile);
                if(userID>=1)
                {
                    displayNode(first);
                }
                else
                {
                    printf("Login Failed\n");
                    printf("Try again\n");
                    goto returnChoice;
                }
                
                fclose(userFile);
                fclose(passwdFile);
                break;
        
        case 2:
                freopen("users.txt","r",userFile);
                freopen("passwds.txt","r",passwdFile);
                reUsername:
                printf("Enter your new Username to create a vault:\nUsername: ");
                scanf("%[^\n]%*c",newUserName);
                while(fgets(newUserNameCompare, Buffer_size, userFile)!= NULL)
                {
                    newUserNameCompare[strlen(newUserName)] = '\0';
                    if(strcmp(newUserNameCompare, newUserName)==0)
                    {
                        printf("Username is already taken\n");
                        printf("Enter a different username\n");
                        goto reUsername;
                    }
                }
                newVault(newUserName);
                fclose(userFile);
                fclose(passwdFile);
                break;
    }
    encryption("users.txt");
    encryption("passwds.txt");
    encryption("./records-and-logs/loginLogs.txt");
}