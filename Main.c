#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Buffer_size 100 

struct username
{
    int nameLength;
    int userID;
    char userNameAttempt[];
};
struct username *storeUsername(struct username *s, char username[])
{
    s = malloc(sizeof(*s) + sizeof(char) * strlen(username));
    s->nameLength = strlen(username);
    strcpy(s->userNameAttempt, username);
    return s;
}
struct password
{
    int passwordLength;
    char passwordAttempt[];
};
struct password *storePassword(struct password *s, char password[])
{
    s = malloc(sizeof(*s) + sizeof(char) * strlen(password));
    s->passwordLength = strlen(password);
    strcpy(s->passwordAttempt,password);
    return s;
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
                    return passwordCounter;
                }
                passwordCounter++;
            }
        }
        userCounter++;
    }
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
}

int main()
{
    int choice=2;
    char newUserName[Buffer_size];
    char newUserNameCompare[Buffer_size];
    char username[Buffer_size];
    char password[Buffer_size];
    int userID;
    FILE *userFile = fopen("users.txt","r");
    FILE *passwdFile= fopen("passwds.txt","r");
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
                    printf("Login Successful");
                    fgets( username, Buffer_size, userFile);
                    fgets( password, Buffer_size, userFile);
                    struct username *user = storeUsername(user,username);
                    struct password *passwd = storePassword(passwd,password);
                    user->userID = userID;
                    printf("");

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
    } 
}