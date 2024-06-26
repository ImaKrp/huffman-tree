// Júlio Carvalho Gonçalves - 2311100012
// Marco Antônio Duz - 2311100006

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

int toLower(char c)
{
    if (c >= 65 && c <= 90)
        return c + 32;
    return c;
}

void createTree(Node *values[], int size)
{
    if (size == 1)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->charCode = '\0';
        node->left = values[0];
        node->right = NULL;
        node->occurrences = values[0]->occurrences;
        values[0] = node;
    }
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
        int spaced = -1;
        for (int j = 0; j < size - i; j++)
        {
            if (values[j] == NULL)
                continue;
            if (values[j]->occurrences >= newOccurences && spaced == -1)
            {
                spaced = curr;
                curr++;
            }
            values[curr] = values[j];
            values[j] = NULL;
            curr++;
        }
        int j = 0;
        if (spaced == -1)
            values[size - i - 2] = node;
        else
            values[spaced] = node;
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

    for (int i = 0; i < actualSize - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < actualSize - i - 1; j++)
        {
            if (values[j]->occurrences > values[j + 1]->occurrences)
            {
                Node *temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
                swapped = 1;
            }
            if (values[j]->occurrences == values[j + 1]->occurrences)
            {
                if (values[j]->charCode > values[j + 1]->charCode)
                {
                    Node *temp = values[j];
                    values[j] = values[j + 1];
                    values[j + 1] = temp;
                    swapped = 1;
                }
            }
        }
        if (swapped == 0)
            break;
    }
}

void printCodification(Node *root, char path[], int prevSize)
{
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
    {
        if (root->charCode == '\n')
            printf("/n");
        else
            printf("%c", root->charCode);
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

        int i = 0;
        while (i < size)
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
            i++;
        }

        printCodification(root->left, left, size);
        printCodification(root->right, right, size);
    }
}

void codeLetter(FILE *output, char letter, Node *root, char path[], int prevSize)
{
    if (root == NULL)
        return;
    if (root->charCode == letter)
    {
        fprintf(output, "%s", path);
        return;
    }

    int size = prevSize + 2;
    char left[size];
    char right[size];

    for (int i = 0; i < size; i++)
    {
        left[i] = '\0';
        right[i] = '\0';
    }

    int i = 0;
    while (i < size)
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
        i++;
    }

    codeLetter(output, letter, root->left, left, size);
    codeLetter(output, letter, root->right, right, size);
}

void writeCoded(Node *root, char text[], int size)
{
    FILE *output = fopen("codificado.txt", "a");
    for (int i = 0; i < size; i++)
        codeLetter(output, text[i], root, "", 0);
    fclose(output);
    return;
}

void decodeLetter(FILE *input, FILE *output, Node *root, Node *actual)
{
    if (actual == NULL)
        return;

    if (actual->charCode != '\0')
    {
        fprintf(output, "%c", actual->charCode);
        decodeLetter(input, output, root, root);
        return;
    }
    char c = getc(input);

    if (c == EOF)
        return;

    if (c == '1')
        decodeLetter(input, output, root, actual->right);
    else
        decodeLetter(input, output, root, actual->left);
}

void writeDecoded(Node *root)
{
    FILE *input = fopen("codificado.txt", "r");
    FILE *output = fopen("decodificado.txt", "a");
    decodeLetter(input, output, root, root);
    fclose(input);
    fclose(output);
    return;
}

int main()
{
    FILE *origin = fopen("./amostra.txt", "r");

    remove("codificado.txt");
    remove("decodificado.txt");

    if (origin == NULL)
        exit(0);

    int count = 0;
    char c = getc(origin);
    while (c != EOF)
    {
        count++;
        c = getc(origin);
    }

    if (count == 0)
    {
        FILE *coded = fopen("codificado.txt", "w");
        fclose(coded);
        FILE *decoded = fopen("decodificado.txt", "w");
        fclose(decoded);
        exit(0);
    }

    int times[count];
    char string[count];
    char text[count + 1];

    for (int i = 0; i < count; i++)
    {
        times[i] = 0;
        string[i] = '\0';
        text[i] = '\0';
    }

    text[count] = '\0';
    rewind(origin);
    int actualSize = 0;

    for (int i = 0; i < count; i++)
    {
        int flag = -1;
        char c = toLower(getc(origin));
        text[i] = c;
        int j = 0;
        while (j < actualSize)
        {
            if (string[j] == c)
            {
                flag = j;
                break;
            }
            j++;
        }
        if (flag < 0)
        {
            string[actualSize] = c;
            times[actualSize] = 1;
            actualSize++;
        }
        else
            times[flag]++;

        flag = -1;
    }

    Node *values[actualSize];

    orderValues(values, string, times, actualSize);
    createTree(values, actualSize);
    Node *root = values[0];
    printCodification(root, "", 0);
    writeCoded(root, text, count);
    writeDecoded(root);

    for (int i = 0; i < actualSize; i++)
        free(values[i]);

    fclose(origin);
    return 0;
}
