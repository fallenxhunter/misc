#include <stdio.h>

void Encrypt(char Sequence[], int ShiftValue, char result[])
{
    /*  Increase the letter by shiftvalue
        */
    FILE *outputfile = fopen("insassign2-2K18-SE-134.txt", "a+");
    for(int i = 0; Sequence[i] != '\0'; i++)
    {
        if (Sequence[i] >= 'A' && Sequence[i] <= 'Z')
        {
            result[i] = ((Sequence[i] + ShiftValue - 'A') % 26) + 'A';

        }
        else if(Sequence[i] >= 'a' && Sequence[i] <= 'z')
        {
            result[i] = ((Sequence[i] + ShiftValue - 'a') % 26) + 'a';
        }
        else
            result[i] = Sequence[i];
    }

    fprintf(outputfile,"Encrypted Text: %s\n",result);
    fclose(outputfile);
}

void Decrypt(char result[], int ShiftValue, char Sequence[])
{   
    /*  Instead of decreasing by Shiftvalue, we Increase the letter by 26-shiftvalue
        */
    FILE *outputfile = fopen("insassign2-2K18-SE-134.txt", "a+");
    ShiftValue = 26 - ShiftValue;                                       
    for(int i = 0; Sequence[i] != '\0'; i++)
    {
        if (Sequence[i] >= 'A' && Sequence[i] <= 'Z')
        {
            result[i] = ((Sequence[i] + ShiftValue - 'A') % 26) + 'A';

        }
        else if(Sequence[i] >= 'a' && Sequence[i] <= 'z')
        {
            result[i] = ((Sequence[i] + ShiftValue - 'a') % 26) + 'a';
        }
        else
            result[i] = Sequence[i];
    }

    fprintf(outputfile,"Decrypted Text: %s\n",result);
    fclose(outputfile);
}

int main()
{
    // Variable for storing shiftvalue and plaintext.
    int ShiftValue;
    char Sequence[100];
    char Encrypted[100];

    //input: meet me after the toga party 3
    
    printf("Enter The Sequence\n");
    scanf("%[^\n]s",Sequence);
    printf("Enter ShiftValue\n");
    scanf("%d", &ShiftValue);

    int input = 0;
    do{

        printf("What would you like to do\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n\n");

        scanf("%d", &input);
        
        switch (input)
        {
        case 1:
            Encrypt(Sequence,ShiftValue,Encrypted);
            break;
        case 2: 
            Decrypt(Sequence,ShiftValue,Encrypted);
            break;
        case 3: 
            input = 3;
            break;  
        default:
            printf("Invalid Input\n");
            break;
        }

    }while(input != 3);

    return 0;
}