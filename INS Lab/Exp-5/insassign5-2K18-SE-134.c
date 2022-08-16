#include <stdio.h>
#include <ctype.h>
#include <string.h>


void GenerateKey(char Key[5][5],int KeySize, char EncryptKey[])
{
    int Hash[26] = {0};                                     //TO generate the Key Matrix
    Hash['J'-'A'] = -1;

    for(int i = 0; i < KeySize; i++)                        //Creating a Hash to store the letters provided by the users
    {
        if(EncryptKey[i] != 'J')
            Hash[EncryptKey[i]-'A'] = 1;
    }

    int i = 0, j = 0;
    
    for(int x = 0; x < KeySize; x++)                        //Adding the letters provided by user first 
    {
        if(Hash[EncryptKey[x] - 'A'] == 1)
        {
            Key[i][j] = EncryptKey[x];
            Hash[EncryptKey[x] - 'A'] = -1;
            j++;
            if(j == 5)
            {
                i++;
                j = 0;
            }
        }

    }
    
    for(int x = 0; x < 26; x++)                             //The Remaining letters are added 
    {
        if(Hash[x] == 0)
        {
            Key[i][j] = x + 'A';
            j++;
            if(j == 5)
            {
                i++;
                j = 0;
            }
        }
    }
}

void SearchMatrix(char Key[5][5], char First, char Second, int temp[])
{ 
    if (First == 'J')                           //Replacing J with I
        First = 'I';
    if (Second == 'J')
        Second = 'I';
 
    for (int i = 0; i < 5; i++)                 //A simple search in 2D Array(Matrix)
    {
        for (int j = 0; j < 5; j++)
        {
            if (Key[i][j] == First)
            {
                temp[0] = i;
                temp[1] = j;
            }
            else if (Key[i][j] == Second)
            {
                temp[2] = i;
                temp[3] = j;
            }
        }
    }
}

int TakeMod(int num) 
{ 
    return (num % 5); 
}

void CheckDouble(char Sequence[], int SeqSize)  
{
    char Result[100] = "";                      //Removes any double characters
    int curr = 0;
    for(int i = 0 ; i < SeqSize;)
    {
        if(Sequence[i] == Sequence[i+1])        //if there are consecutive same letters
        {
            Result[curr++] = Sequence[i];
            Result[curr++] = 'X';

            i = i + 1;
        }
        else 
        {
            Result[curr++] = Sequence[i];       //not same letters
            Result[curr++] = Sequence[i+1];

            i = i + 2;
        }
    }

    for(int i = 0; i < curr; i++)
    {
        Sequence[i] = Result[i];
    }

    Sequence[curr] = '\0';
}

void Encrypt(char EncryptKey[],char Sequence[])
{
    char Key[5][5];
    int KeySize = strlen(EncryptKey);
    GenerateKey(Key,KeySize,EncryptKey);

    int SeqSize = strlen(Sequence);
    CheckDouble(Sequence,SeqSize);

    // printf(" %s", Sequence);
    SeqSize = strlen(Sequence);

    
    if(SeqSize % 2 != 0)
    {
        Sequence[SeqSize++] = 'X';
        Sequence[SeqSize] = '\0';
    }
    
    int temp[4];                                                        //temp variable to store letter position in key     
 
    for (int i = 0; i < SeqSize; i += 2) {
 
        SearchMatrix(Key, Sequence[i], Sequence[i + 1], temp);
 
        if (temp[0] == temp[2]) {                                       //if Both have same row
            Sequence[i] = Key[temp[0]][TakeMod(temp[1] + 1)];
            Sequence[i + 1] = Key[temp[0]][TakeMod(temp[3] + 1)];
        }
        else if (temp[1] == temp[3]) {                                  //if Both have same column
            Sequence[i] = Key[TakeMod(temp[0] + 1)][temp[1]];
            Sequence[i + 1] = Key[TakeMod(temp[2] + 1)][temp[1]];
        }
        else {
            Sequence[i] = Key[temp[0]][temp[3]];                        //taking the grid of two
            Sequence[i + 1] = Key[temp[2]][temp[1]];
        }
    }

    printf("Encrypted Text: %s\n",Sequence);                //result is printed
}

void Decrypt(char EncryptKey[],char Sequence[])
{   
    char Key[5][5];
    int KeySize = strlen(EncryptKey);
    GenerateKey(Key,KeySize,EncryptKey);

    int SeqSize = strlen(Sequence);
    int temp[4];

    for (int i = 0; i < SeqSize; i += 2) {
 
        SearchMatrix(Key, Sequence[i], Sequence[i + 1], temp);
 
        if (temp[0] == temp[2]) {
            Sequence[i] = Key[temp[0]][TakeMod(5 + temp[1] - 1)];           //if Both have same row
            Sequence[i + 1] = Key[temp[0]][TakeMod(5 + temp[3] - 1)];
        }
        else if (temp[1] == temp[3]) {                                      //if Both have same column
            Sequence[i] = Key[TakeMod(5 + temp[0] - 1)][temp[1]];
            Sequence[i + 1] = Key[TakeMod(5 + temp[2] - 1)][temp[1]];
        }
        else {
            Sequence[i] = Key[temp[0]][temp[3]];                            //the Grid Case
            Sequence[i + 1] = Key[temp[2]][temp[1]];    
        }
    }

    printf("Decrypted Text: %s\n",Sequence);               //result is printed
}

int main()
{

    char EncryptKey[100]; 

    char Sequence[100];
    char Key[100] = "";
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

            printf("Enter The Key : ");                     //Taking Input from user for Key
            scanf(" %s[^\n]",Key);

            Encrypt(Key,Sequence);
        }
        else if(input == 2)
        {
            printf("Enter The Sequence :  ");               //Taking Input from user for Plaintext
            scanf(" %[^\n]",Sequence);                      
            
            printf("Enter The Key : ");
            scanf(" %s[^\n]",Key);                          //Taking Input from user for Key

            Decrypt(Key,Sequence);                          
        }

    }while(input != 3);

    return 0;
}