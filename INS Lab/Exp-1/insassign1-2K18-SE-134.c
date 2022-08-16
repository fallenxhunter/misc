#include <stdio.h>

void InsertionSort(int numbers[], int size)
{
    for(int i = 1; i < size; i++)
    {
        int current = numbers[i];
        int j = i-1;

        while (j >= 0 && numbers[j] > current) {
            numbers[j+1] = numbers[j];
            j = j-1;
        }
        numbers[j+1] = current;
    } 
}

int main()
{
    int num_size = 20;
    int numbers[25];

    //Input = 6 96 81 51 2 71 61 17 79 12 54 49 55 36 43 62 40 70 92 13

    FILE *outputfile = fopen("insassign1-2K18-SE-134.txt", "w");

    printf("Enter %d Numbers to Sort\n", num_size);

    for(int i = 0; i < num_size; i++)
    {
        scanf("%d", &numbers[i]);
    }

    InsertionSort(numbers, num_size);
    
    for(int i = 0; i < num_size; i++)
    {
        fprintf(outputfile,"%d",numbers[i]);
        fprintf(outputfile,",");
    }

    fclose(outputfile);

    return 0;
}