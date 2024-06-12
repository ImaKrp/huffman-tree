#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char charCode;
    struct node *left;
    struct node *right;
} Node;

void printArray(int arr[], int size)
{
    printf("[ ");
    for (int i = 0; i < size; i++)
    {
        if (i < size - 1)
            printf("%d, ", arr[i]);
        else
            printf("%d", arr[i]);
    }
    printf(" ]\n");
}

void printCArray(char arr[], int size)
{
    printf("[ ");
    for (int i = 0; i < size; i++)
    {
        if (i < size - 1)
            printf("%c, ", arr[i]);
        else
            printf("%c", arr[i]);
    }
    printf(" ]\n");
}

int toLower(char c)
{
    if (c >= 65 && c <= 90)
    {
        return c + 32;
    }
    return c;
}

void getUniqueCharacters(char string[], int size, char *uniqueChars, int *uniqueSize)
{
    int actualSize = 0;
    int flag = -1;
    for (int i = 0; i < size; i++)
    {
        char c = string[i];
        for (int j = 0; j < actualSize; j++)
        {
            if (uniqueChars[j] == c)
            {
                flag = j;
                break;
            }
        }
        if (flag < 0)
        {
            uniqueChars[actualSize] = c;
            actualSize++;
        }
        flag = -1;
    }

    *uniqueSize = actualSize;
}

void createTree(char string[], int size)
{
    char characters[size];
    int actualSize;

    getUniqueCharacters(string, strlen(string), characters, &actualSize);

    int repeatTimes[actualSize];

    for (int i = 0; i < actualSize; i++)
    {
        repeatTimes[i] = 0;
    }

    int flag = -1;

    for (int i = 0; i < size; i++)
    {
        char c = string[i];
        for (int j = 0; j < actualSize; j++)
        {
            if (characters[j] == c)
            {
                flag = j;
                break;
            }
        }

        if (flag == -1)
        {
            repeatTimes[i] = 1;
        }
        else
        {
            repeatTimes[flag]++;
        }
        flag = -1;
    }

    int swapped = 0;
    for (int i = 0; i < actualSize; i++)
    {
        for (int j = 0; j < actualSize; j++)
        {
            if (repeatTimes[i] < repeatTimes[j])
            {
                int temp = repeatTimes[i];
                repeatTimes[i] = repeatTimes[j];
                repeatTimes[j] = temp;

                char tempChar = characters[i];
                characters[i] = characters[j];
                characters[j] = tempChar;
                swapped = 1;
            }
            if (repeatTimes[i] == repeatTimes[j])
            {
                if (characters[i] < characters[j])
                {
                    char tempChar = characters[i];
                    characters[i] = characters[j];
                    characters[j] = tempChar;
                    swapped = 1;
                }
            }
        }
        if (swapped == 0)
            break;
    }
    printCArray(characters, actualSize);
    printArray(repeatTimes, actualSize);
}

int main()
{
    FILE *origin = fopen("./amostra.txt", "r");

    if (origin == NULL)
    {
        exit(0);
    }

    char *string = (char *)malloc(sizeof(char));

    char c = getc(origin);
    int newSize;
    while (c != EOF)
    {
        newSize = strlen(string) + 1;

        char *characters = (char *)realloc(string, newSize);

        if (characters == NULL)
        {
            fclose(origin);
            exit(1);
        }

        c = toLower(c);

        string = characters;
        string[newSize - 1] = c;

        c = getc(origin);
    }

    createTree(string, newSize);

    return 0;
}
