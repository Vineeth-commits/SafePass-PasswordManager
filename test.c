#include <stdio.h>
#include <string.h>
#define Buffer_size 100
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
int main()
{
    int i;
    FILE *file = fopen("users.txt", "r");
    char line[50];
    char test[50]="Pavan";
    while(fgets( line, 50, file ) != NULL ) /* read a line */
      {
         line[strlen(test)] = '\0';
         if(strcmp(test, line)==0){
             printf("done");
         } /* write the line */
      }
      fclose ( file );
    return 0;
}