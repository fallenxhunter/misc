#include <stdio.h>
#include <ctype.h>
#include <string.h>


void Encrypt(char EncryptKey[],char Sequence[])
{
    //Encrypt Function which takes Key and Plaintext as parameters
    
    for(int i = 0; Sequence[i] != '\0'; i++)
    {
        if (Sequence[i] >= 'A' && Sequence[i] <= 'Z')       //every ith alphabet is increased by the the value of key at ith index 
        {
            Sequence[i] = ( ( (Sequence[i]-'A') + (EncryptKey[i]-'A') ) % 26) + 'A';       // thus it's modulo is stored as encrypted msg
        }
        else if(Sequence[i] >= 'a' && Sequence[i] <= 'z')
        {
            Sequence[i] = ( ( (Sequence[i]-'a') + (EncryptKey[i]-'A') ) % 26) + 'a';
        }
    }

    printf("Encrypted Text: %s\n",Sequence);                //result is printed
}

void Decrypt(char EncryptKey[],char Sequence[])
{   
    //Decrypt Function which takes Key and Encrypted text as parameters

    for(int i = 0; Sequence[i] != '\0'; i++)                //every ith alphabet is decreased by the the value of key at ith index 
    {                                                       //26 is added to avoid negative values                   
        if (Sequence[i] >= 'A' && Sequence[i] <= 'Z')
        {
            Sequence[i] = ( ( (Sequence[i]-'A') - (EncryptKey[i]-'A') + 26 ) % 26) + 'A';   //it's modulo is stored as original plaintext
        }
        else if(Sequence[i] >= 'a' && Sequence[i] <= 'z')
        {
            Sequence[i] = ( ( (Sequence[i]-'a') - (EncryptKey[i]-'A') + 26 ) % 26) + 'a';
        }
    }

    printf("Decrypted Text: %s\n",Sequence);                    //result is printed
}

int main()
{

    char EncryptKey[100];
    printf("Enter The Key\n");
    scanf(" %[^\n]",EncryptKey);

    char Sequence[100];
    char Key[100] = "";
    int input = 0;

    do{                                                         //a do while menu driven program

        printf("What would you like to do\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");

        scanf("%d", &input);
        // fflush (stdin);

        if(input == 1)
        {
            printf("Enter The Sequence :  ");
            scanf(" %[^\n]",Sequence);
            int x = strlen(Key);
            int y = strlen(Sequence);
            while(x < y)
            {
                strcat(Key,EncryptKey);
                x = strlen(Key);
            }
            // printf("%s \n",Key);
            Encrypt(Key,Sequence);
        }
        else if(input == 2)
        {
            printf("Enter The Sequence :  ");
            scanf(" %[^\n]",Sequence);
            int x = strlen(Key);
            int y = strlen(Sequence);
            while(x < y)
            {
                strcat(Key,EncryptKey);
                x = strlen(Key);
            }
            // printf("%s \n",Key);
            Decrypt(Key,Sequence);
        }

    }while(input != 3);

    return 0;
}