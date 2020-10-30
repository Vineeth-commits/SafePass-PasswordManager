#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct username
{
    int nameLength;
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
    printf("Hey you need to enter your username and password \nUsername: ");
    char nameEntered[20];
    char passwdEntered[30];
    scanf("%[^\n]%*c",nameEntered);
    char nameCompare[20]; 
    char passwdCompare[20];
    fgets(nameCompare, 20, userFile);
    nameCompare[strlen(nameEntered)] = '\0';
    if(strcmp(nameEntered,nameCompare)==0)
    {
        printf("Enter your password: ");
        scanf("%[^\n]%*c",passwdEntered);
        fgets(passwdCompare, 20, passwdFile);
        passwdCompare[strlen(passwdEntered)] = '\0';
        if(strcmp(passwdEntered,passwdCompare)==0)
        {
            return 1;
        }
        else
        {
            printf("Password Incorrect \n");
            return -1;
        }
    }
    else
    {
    printf("Username Incorrect \n");
    return -1;
    }
    
}
int main()
{
    FILE *userFile = fopen("users.txt","r");
    FILE *passwdFile = fopen("passwds.txt","r");
    char username[50];
    char password[50];
    if(userFile==NULL||passwdFile==NULL)
    {
        printf("Error! Could not open file\n"); 
        exit(-1);
    }

    if(login(userFile,passwdFile)==1)
    {
        printf("Login Successful");
        fgets( username, 50, userFile);
        fgets( password, 50, userFile);
        struct username *user1 = storeUsername(user1,username);
        struct password *pass1 = storePassword(pass1,password);
    }
    else
    {
        printf("Login Failed");
    }
}