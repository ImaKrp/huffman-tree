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
        if (!arr[i])
            printf("NULL");
        if (arr[i])
            printf("%c", arr[i]->charCode);
        if (i < size - 1)
            printf(", ");
    }
    printf(" ]\n");
}

void printNodeOccurrencesArray(Node *arr[], int size)
{
    printf("[ ");
    for (int i = 0; i < size; i++)
    {
        if (!arr[i])
            printf("NULL");
        if (arr[i])
            printf("%d", arr[i]->occurrences);
        if (i < size - 1)
            printf(", ");
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
    for (int i = 0; i < size - 1; i++)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->charCode = '\0';
        node->left = values[0];
        node->right = values[1];
        int newOccurences = values[0]->occurrences + values[1]->occurrences;
        node->occurrences = newOccurences;

        values[0] = NULL;
        values[1] = NULL;

        int curr = 0;
        int spaced = 0;
        for (int j = 0; j < size - i; j++)
        {
            if (values[j] == NULL)
                continue;
            if (values[j]->occurrences < newOccurences)
            {
                values[curr] = values[j];
                values[j] = NULL;
                curr++;
                continue;
            }
            if (values[j]->occurrences >= newOccurences && spaced == 0)
            {
                spaced = 1;
                curr++;
            }
            if (values[j]->occurrences >= newOccurences)
            {
                values[curr] = values[j];
                values[j] = NULL;
                curr++;
                continue;
            }
        }
        int j = 0;
        while (1)
        {
            if (values[j] == NULL)
            {
                values[j] = node;
                break;
            }
            j++;
        }
    }
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

    for (int i = 0; i < actualSize; i++)
    {
        for (int j = 0; j < actualSize; j++)
        {
            if (values[i]->occurrences < values[j]->occurrences)
            {
                Node *temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
            else if (values[i]->occurrences == values[j]->occurrences)
            {
                if (values[i]->charCode < values[j]->charCode)
                {
                    Node *temp = values[i];
                    values[i] = values[j];
                    values[j] = temp;
                }
            }
        }
    }
}

void printCodification(Node *root, char path[], int prevSize)
{
    if (root->left == NULL && root->right == NULL)
    {
        if(root->charCode == '\n')
        printf("/n");
        else printf("%c", root->charCode);
        printf(": %s\n", path);
    }
    else
    {
        int size = prevSize + 2;
        char left[size];
        char right[size];

        for (int i = 0; i < size; i++)
        {
            left[i] = '\0';
            right[i] = '\0';
        }

        for (int i = 0; i < size; i++)
        {
            if (i == strlen(path))
            {
                left[i] = '0';
                right[i] = '1';
                break;
            }
            else
            {
                left[i] = path[i];
                right[i] = path[i];
            }
        }

        printCodification(root->left, left, size);
        printCodification(root->right, right, size);
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

    orderValues(values, string, times, actualSize);

    createTree(values, actualSize);

    Node *root = values[0];
    printCodification(root, "", 0);
    fclose(origin);
    return 0;
}