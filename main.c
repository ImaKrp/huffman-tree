#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char charCode;
    int occurrences;
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

void printNodeCharArray(Node *arr[], int size)
{
    printf("[ ");
    for (int i = 0; i < size; i++)
    {
        if (i < size - 1)
            printf("%c, ", arr[i]->charCode);
        else
            printf("%c", arr[i]->charCode);
    }
    printf(" ]\n");
}

void printNodeOccurrencesArray(Node *arr[], int size)
{
    printf("[ ");
    for (int i = 0; i < size; i++)
    {
        if (i < size - 1)
            printf("%d, ", arr[i]->occurrences);
        else
            printf("%d", arr[i]->occurrences);
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

void createTree(Node *values[], int size)
{
    printNodeCharArray(values, size);
    printNodeOccurrencesArray(values, size);
}

void orderValues(Node *values[], char string[], int times[], int actualSize)
{
    for (int i = 0; i < actualSize; i++)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->charCode = string[i];
        node->left = NULL;
        node->right = NULL;
        node->occurrences = times[i];
        values[i] = node;
    }

    int swapped = 0;
    for (int i = 0; i < actualSize; i++)
    {
        for (int j = 0; j < actualSize; j++)
        {
            if (values[i]->occurrences < values[j]->occurrences)
            {
                Node *temp = values[i];
                values[i] = values[j];
                values[j] = temp;
                swapped = 1;
            }
            if (values[i]->occurrences == values[j]->occurrences)
            {
                if (values[i]->charCode < values[j]->charCode)
                {
                    Node *temp = values[i];
                    values[i] = values[j];
                    values[j] = temp;
                    swapped = 1;
                }
            }
        }
        if (swapped == 0)
            break;
    }
}

int main()
{
    FILE *origin = fopen("./amostra.txt", "r");

    if (origin == NULL)
    {
        exit(0);
    }

    int count = 0;
    char c = getc(origin);
    while (c != EOF)
    {
        count++;
        c = getc(origin);
    }

    int times[count];
    char string[count];

    for (int i = 0; i < count; i++)
    {
        times[i] = -1;
        string[i] = '\0';
    }

    rewind(origin);

    int actualSize = 0;
    for (int i = 0; i < count; i++)
    {
        int flag = -1;
        char c = toLower(getc(origin));
        for (int j = 0; j < actualSize; j++)
        {
            if (string[j] == c)
            {
                flag = j;
                break;
            }
        }
        if (flag < 0)
        {
            string[actualSize] = c;
            times[actualSize] = 1;
            actualSize++;
        }
        else
        {
            times[flag]++;
        }
        flag = -1;
    }

    Node *values[actualSize];
    int orderedTimes[actualSize];

    orderValues(values, string, times, actualSize);

    createTree(values, actualSize);

    fclose(origin);
    return 0;
}
