#include <stdio.h>
#include <ctype.h>
#include <string.h>


void Encrypt(int Key[][3],int SeqMat[][1])
{
                                                                     //temp variable to store letter position in key     
    int Result[3][1];
    char temp;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            Result[i][j] = 0;
            for(int k = 0; k < 3; k++)
            {
                Result[i][j] = Result[i][j] + (Key[i][k] * SeqMat[k][j]);
            }
        }
    }

    for(int i = 0 ; i < 3; i++)
    {
        temp = (Result[i][0] % 26) + 'A';
        printf("%c",temp);
    }
}

void HillEncrypt(int Key[][3],char Sequence[])
{

    int Seqmat[3][1];
    if(strlen(Sequence) % 3 != 0)
    {
        int x = strlen(Sequence);
        while( x % 3 != 0)
        {
            Sequence[x] = 'A';
            x++;
        }
        Sequence[x] = '\0';
    }

    printf("Encrypted Text : ");
    for(int i = 0; i < strlen(Sequence); i = i+3)
    {
        Seqmat[0][0] = Sequence[i] - 'A';
        Seqmat[1][0] = Sequence[i+1] - 'A';
        Seqmat[2][0] = Sequence[i+2] - 'A';

        Encrypt(Key,Seqmat);
    }
    printf("\n");
}

void Decrypt(int Key[][3],int SeqMat[][1])
{
    int Result[3][1];
    char temp;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            Result[i][j] = 0;
            for(int k = 0; k < 3; k++)
            {
                Result[i][j] = Result[i][j] + (Key[i][k] * SeqMat[k][j]);
            }
        }
    }

    for(int i = 0 ; i < 3; i++)
    {
        temp = (Result[i][0] % 26) + 'A';
        printf("%c",temp);
    }
}

void HillDecrypt(int Key[][3],char Sequence[])
{   
    int Seqmat[3][1];

    printf("Decrypted Text : ");
    for(int i = 0; i < strlen(Sequence); i = i+3)
    {
        Seqmat[0][0] = Sequence[i] - 'A';
        Seqmat[1][0] = Sequence[i+1] - 'A';
        Seqmat[2][0] = Sequence[i+2] - 'A';

        Decrypt(Key,Seqmat);
    }
    printf("\n");
}

int main()
{

    char EncryptKey[100]; 

    char Sequence[100];
    int Key[3][3];
    int input = 0;

    do{                                                     //a do while menu driven program

        printf("What would you like to do\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");

        scanf("%d", &input);
        // fflush (stdin);

        if(input == 1)
        {
            printf("Enter The Sequence :  ");               //Taking Input from user for Plaintext
            scanf(" %[^\n]",Sequence);

            printf("Enter The Key : \n");                     //Taking Input from user for Key
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    scanf("%d",&Key[i][j]);
                }
            }

            HillEncrypt(Key,Sequence);
        }
        else if(input == 2)
        {
            printf("Enter The Sequence :  ");               //Taking Input from user for Plaintext
            scanf(" %[^\n]",Sequence);                      
            
            printf("Enter The Key : ");                     //Taking Input from user for Key
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    scanf("%d",&Key[i][j]);
                }
            }                       

            HillDecrypt(Key,Sequence);                          
        }

    }while(input != 3);

    return 0;
}

