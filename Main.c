#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
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
    printf("Login Successful \n");
    printf("Welcome %s \n",user->userNameAttempt);
    insertionNode(first,username);
}
int login(FILE *userFile,FILE *passwdFile)
{
    printf("Hey, you need to enter your username and password\nUsername: ");
    char nameEntered[Buffer_size];
    char passwdEntered[Buffer_size];
    int userCounter = 1;
    int passwordCounter = 1;
    scanf("%s",nameEntered);
    char nameCompare[Buffer_size]; 
    char passwdCompare[Buffer_size];
    while(fgets(nameCompare, Buffer_size, userFile)!= NULL)
    {
        nameCompare[strlen(nameEntered)] = '\0';
        if(strcmp(nameEntered,nameCompare)==0)
        {
            printf("Enter your password: ");
            scanf("%s",passwdEntered);
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

void newVault(char dataToAppend[Buffer_size])
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
    // dataToAppend[strlen(dataToAppend)] ='\n';
    fputs(dataToAppend, appendUser);
    printf("Enter the password:\n");
    // scanf("%s",dataToAppendPasswd);
    // dataToAppendPasswd[strlen(dataToAppendPasswd)] = '\n';
    fflush(stdin);
    fgets(dataToAppendPasswd,Buffer_size,stdin);
    fputs(dataToAppendPasswd,appendPasswd);
    printf("New vault has been created\n");
    printf("Login again to input entries into your vault\n");
    fclose(appendUser);
    fclose(appendPasswd);
}

int usersCount()
{
    int userCounter = 0;
    char pseudoCh[Buffer_size];
    FILE *users = fopen("users.txt","r");
    if(users == NULL)
    {
        printf("Unable to open the file\n");
        printf("Inspection of the file is needed\n");
        exit(-1);
    }
    while (fgets(pseudoCh, Buffer_size, users)!= NULL)
    {
        userCounter++;
    }
    return userCounter;
}

int isEmpty(FILE *file)
{
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        return 0;
    }
    fseek(file, savedOffset, SEEK_SET);
    return 1;
}

void userEntry(int userID)
{
    char fileName[Buffer_size];
    char recordData[Buffer_size];
    FILE *recordFile;
    sprintf(fileName,"%d", userID);
    strcat(fileName,".txt");
    fileName[strlen(fileName)] = '\0';
    recordFile = fopen(fileName,"a");
    printf("Enter your password or any record to store it:\n");
    scanf("%s",recordData);
    recordData[strlen(recordData)] = '\n';
    fputs(recordData,recordFile);
    printf("Your data has been saved and updated to your vault");
    fclose(recordFile);
}

void displayEntry(int userID)
{
    char fileName[Buffer_size];
    char recordStore[Buffer_size];
    sprintf(fileName,"%d", userID);
    strcat(fileName,".txt");
    FILE *recordFile = fopen(fileName,"r");
    fileName[strlen(fileName)] = '\0';
    if(isEmpty(recordFile)==1)
    {
        printf("Your entered records are:\n");
        while (fgets(recordStore, Buffer_size, recordFile)!= NULL)
        {
            recordStore[strlen(recordStore)] = '\0';
            printf("%s\n",recordStore);
        }
    }
    else
    {
        printf("No records are present\n");
    }
}

int deleteEntry(int userID)
{
    int lno, ctr = 0;
    char ch;
    FILE *fptr1, *fptr2;
	char fileName[Buffer_size];
    char str[Buffer_size], temp[] = "temp2.txt"; 
    sprintf(fileName,"%d", userID);
    strcat(fileName,".txt");
    fileName[strlen(fileName)] = '\0';		
    fptr1 = fopen(fileName, "r");
    if (!fptr1) 
	{
        printf(" File not found or unable to open the input file!!\n");
        return 0;
    }
    fptr2 = fopen(temp, "w");
    if (!fptr2) 
	{
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr1);
        return 0;
    }
    displayEntry(userID);
    printf("Input the line you want to remove:\n");
    scanf("%d", &lno);
	lno++;
    while (!feof(fptr1)) 
    {
        strcpy(str, "\0");
        fgets(str, Buffer_size, fptr1);
        if (!feof(fptr1)) 
        {
            ctr++;
            if (ctr != lno) 
            {
                fprintf(fptr2, "%s", str);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(fileName); 
    rename(temp, fileName);
    printf("The record has been deleted\n");
    printf("Edited record:\n");
    displayEntry(userID);
    return 0;
}

void generatePassword(int userID)
{
    srand((unsigned int)(time(NULL)));
    int i;
    int choice;
    int num;
    char fileName[Buffer_size];
    FILE *recordFile;
    generate:
    printf("Enter your password length\n");
    scanf("%d",&num);
    char pass[num];
    printf("Press enter to get a twelve alpha-number-character password\n");
    getchar();
    for(i = 0; i < num; i++)
    {
        pass[i] = 33 + rand() % 94;
    }
    pass[i] = '\0';
    printf("%s\n",pass);
    printf("Press 1 to save this as record in your vault\n");
    printf("Press 2 to generate another password\n");
    printf("Press 0 to exit\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        sprintf(fileName,"%d", userID);
        strcat(fileName,".txt");
        fileName[strlen(fileName)] = '\0';
        recordFile = fopen(fileName,"a");
        pass[strlen(pass)] = '\n';
        fputs(pass,recordFile);
        printf("Your generated password has been saved and updated to your vault");
        fclose(recordFile);
    }
    else if(choice==2)
    {
        goto generate;
    }
    else 
    {}

}

void recordEncrypt()
{
    char fileName[Buffer_size];
    int num = usersCount();
    for(int i=1;i<=num;i++)
    {
        sprintf(fileName,"%d", i);
        strcat(fileName,".txt");
        fileName[strlen(fileName)] = '\0';
        encryption(fileName);
    }
}

void recordDecrypt()
{
    char fileName[Buffer_size];
    int num = usersCount();
    for(int i=1;i<=num;i++)
    {
        sprintf(fileName,"%d", i);
        strcat(fileName,".txt");
        fileName[strlen(fileName)] = '\0';
        decryption(fileName);
    }
}

int main()
{
    int choice;
    int innerChoice;
    char newUserName[Buffer_size];
    char newUserNameCompare[Buffer_size];
    char fileName[Buffer_size];
    int userID;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    FILE *userFile = fopen("users.txt","r");
    FILE *passwdFile = fopen("passwds.txt","r");
    FILE *newUserFile;
    decryption("./records-and-logs/loginLogs.txt");
    decryption("users.txt");
    decryption("passwds.txt");
    recordDecrypt();
    createNode(asctime (timeinfo));
    returnChoice:
    printf("Select the options below:\n");
    printf("Press 1 to login in to your vault\n");
    printf("Press 2 to create a new vault\n");
    printf("Press 0 to exit\n");
    scanf("%d",&choice);
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
                    innerChoice:
                    printf("Enter the choices below:\n");
                    printf("Press 1 to make an entry\n");
                    printf("Press 2 to display all the entries\n");
                    printf("Press 3 to delete an entry\n");
                    printf("Press 4 to generate a random password\n");
                    printf("Press 5 to logout\n");
                    printf("Press 0 to exit\n");
                    scanf("%d",&innerChoice);
                    switch (innerChoice)
                    {
                        case 1: userEntry(userID);
                                goto innerChoice;

                        case 2: displayEntry(userID);
                                goto innerChoice;

                        case 3: deleteEntry(userID);
                                goto innerChoice;
                                
                        case 4: generatePassword(userID);
                                goto innerChoice;

                        case 5: goto returnChoice;

                        case 0: break;
                        
                    }
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
                // scanf("%s",newUserName);
                getchar();
                fflush(stdin);
                fgets(newUserName,Buffer_size,stdin);
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
                printf("%s",newUserName);
                newVault(newUserName);
                sprintf(fileName,"%d", usersCount());
                strcat(fileName,".txt");
                fileName[strlen(fileName)] = '\0';
                newUserFile = fopen(fileName,"w");
                fclose(newUserFile);
                fclose(userFile);
                fclose(passwdFile);
                break;
    }
    encryption("users.txt");
    encryption("passwds.txt");
    encryption("./records-and-logs/loginLogs.txt");
    recordEncrypt();
    free(first);
}