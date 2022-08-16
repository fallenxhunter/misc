#include <stdio.h>
#include <ctype.h>

void Encrypt(char EncryptKey[],char Sequence[])
{
    //Encrypt Function which takes Key and Sequence as parameters
    
    for(int i = 0; Sequence[i] != '\0'; i++)
    {
        if (Sequence[i] >= 'A' && Sequence[i] <= 'Z')       //every letter is swapped with assigned letter
        {
            Sequence[i] = EncryptKey[Sequence[i] - 'A'];    
        }
        else if(Sequence[i] >= 'a' && Sequence[i] <= 'z')
        {
            Sequence[i] = EncryptKey[Sequence[i] - 'a'];
            Sequence[i] = tolower(Sequence[i]);
        }
    }

    printf("Encrypted Text: %s\n",Sequence);                //result is printed
}

void Decrypt(char EncryptKey[],char Sequence[])
{   

    for(int i = 0; Sequence[i] != '\0'; i++)                //every letter is swapped with index value letter
    {                                                       //after it is searched in the key                        
        if (Sequence[i] >= 'A' && Sequence[i] <= 'Z')
        {
            int temp = 0;
            for(int j = 0; j < 26; j++)
            {
                if(Sequence[i] == EncryptKey[j])
                {
                    temp = j;
                    break;
                }
            }
            Sequence[i] = 'A' + temp;           
        }
        else if(Sequence[i] >= 'a' && Sequence[i] <= 'z')
        {
            int temp = 0;
            Sequence[i] = toupper(Sequence[i]);
            for(int j = 0; j < 26; j++)
            {
                if(Sequence[i] == EncryptKey[j])
                {
                    temp = j;
                    break;
                }
            }
            Sequence[i] = 'a' + temp;
        }
    }

    printf("Decrypted Text: %s\n",Sequence);                    //result is printed
}

int main()
{

    char EncryptKey[100] = "AZERTYUIOPQSDFGHJKLMWXCVBN";
    char Sequence[100];
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

            Encrypt(EncryptKey,Sequence);
        }
        else if(input == 2)
        {
            printf("Enter The Sequence :  ");
            scanf(" %[^\n]",Sequence);

            Decrypt(EncryptKey,Sequence);
        }


    }while(input != 3);

    return 0;
}