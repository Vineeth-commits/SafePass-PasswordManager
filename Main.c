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
int login()
{
    printf("Hey you need to enter your username and password \nUsername: ");
    char name[20];
    scanf("%[^\n]%*c",name);
    if(strcmp(name,"Vineeth")==0)
    {
        printf("Enter your password: ");
        char password[50];
        scanf("%s",password);
        if(strcmp(password,"afjdlsk")==0)
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
    if(login()==1)
    {
        printf("Login Successful");
        struct username *user1 = storeUsername(user1,"Vineeth");
        struct password *pass1 = storePassword(pass1,"afjdlsk");
    }
    else
    {
        printf("Login Failed");
    }
}