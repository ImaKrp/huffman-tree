# Documentação das Funções

###### Júlio Carvalho Gonçalves e Marco Antônio Duz

---

## Função `printArray()`

```c
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
```

**Explicação:**

- Esta função imprime um array de inteiros no formato `[ element1, element2, ... ]`.
- Percorre o array `arr` até o tamanho `size`.
- Verifica se o elemento atual é o último para decidir se imprime vírgula ou não.

---

## Função `printNodeCharArray()`

```c
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
```

**Explicação:**

- Esta função imprime um array de ponteiros para `Node` no formato `[ charCode1, charCode2, ... ]`.
- Percorre o array `arr` até o tamanho `size`.
- Verifica se o ponteiro atual é nulo para imprimir "NULL" ou imprime o código de caractere (`charCode`) do nó associado.
- Adiciona vírgula entre os elementos, exceto após o último.

---

## Função `printNodeOccurrencesArray()`

```c
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
```

**Explicação:**

- Esta função imprime um array de ponteiros para `Node` no formato `[ occurrences1, occurrences2, ... ]`.
- Percorre o array `arr` até o tamanho `size`.
- Verifica se o ponteiro atual é nulo para imprimir "NULL" ou imprime o número de ocorrências (`occurrences`) do nó associado.
- Adiciona vírgula entre os elementos, exceto após o último.

---

## Função `toLower()`

```c
int toLower(char c)
{
    if (c >= 65 && c <= 90)
        return c + 32;
    return c;
}
```

**Explicação:**

- Esta função converte um caractere para minúsculo, se for uma letra maiúscula.
- Usa a tabela ASCII para verificar se o caractere está no intervalo das letras maiúsculas (`A` a `Z`).
- Retorna o próprio caractere se não for uma letra maiúscula.

---

<a id="orderValues"></a>

## Função `orderValues()`

```c
void orderValues(Node *values[], char string[], int times[], int actualSize)
{
    // Cria nós para cada caractere com suas ocorrências
    for (int i = 0; i < actualSize; i++)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->charCode = string[i];
        node->left = NULL;
        node->right = NULL;
        node->occurrences = times[i];
        values[i] = node;
    }

    // Ordena os nós com base nas ocorrências e nos caracteres associados
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
```

**Explicação:**

- Esta função ordena uma lista de nós (`values`) com base nas ocorrências e nos caracteres associados.
- Cria nós individuais para cada caractere com suas ocorrências.
- Usa um algoritmo de ordenação simples (bubble sort) para classificar os nós.
- Primeiro, ordena pelos números de ocorrências (`occurrences`).
- Em caso de empate, ordena pelos códigos de caractere (`charCode`).

---

<a id="createTree"></a>

## Função `createTree()`

```c
void createTree(Node *values[], int size)
{
    if (size == 1)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->charCode = '\0';
        node->left = values[0];
        node->right = NULL;
        node->occurrences = values[0

]->occurrences;
        values[0] = node;
    }
    for (int i = 0; i < size - 1; i++)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->charCode = '\0';
        node->left = values[0];
        node->right = values[1];
        int newOccurrences = values[0]->occurrences + values[1]->occurrences;
        node->occurrences = newOccurrences;

        values[0] = NULL;
        values[1] = NULL;

        int curr = 0;
        int spaced = 0;
        for (int j = 0; j < size - i; j++)
        {
            if (values[j] == NULL)
                continue;
            if (values[j]->occurrences < newOccurrences)
            {
                values[curr] = values[j];
                values[j] = NULL;
                curr++;
                continue;
            }
            if (values[j]->occurrences >= newOccurrences && spaced == 0)
            {
                spaced = 1;
                curr++;
            }
            if (values[j]->occurrences >= newOccurrences)
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
```

**Explicação:**

- Esta função cria uma árvore de Huffman a partir de uma lista de nós (`values`).
- Se houver apenas um nó na lista, cria um novo nó para representar a árvore.
- Caso contrário, itera para criar nós intermediários até que reste apenas um nó na lista.
- Usa o número de ocorrências (`occurrences`) para determinar a prioridade na criação dos nós.

---

<a id="printCodification"></a>

## Função `printCodification()`

```c
void printCodification(Node *root, char path[], int prevSize)
{
    if (root == NULL)
        return;

    // Se for um nó folha, imprime o caractere e o caminho até ele
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
        // Cria caminhos para os nós esquerdo e direito
        int size = prevSize + 2;
        char left[size];
        char right[size];

        // Inicializa os caminhos
        for (int i = 0; i < size; i++)
        {
            left[i] = '\0';
            right[i] = '\0';
        }

        // Copia o caminho atual para os caminhos esquerdo e direito
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

        // Chama recursivamente para os nós esquerdo e direito
        printCodification(root->left, left, size);
        printCodification(root->right, right, size);
    }
}
```

**Explicação:**

- Esta função imprime a codificação de Huffman para cada caractere na árvore.
- Verifica se o nó atual é nulo; se for, retorna.
- Se for um nó folha (sem filhos), imprime o caractere e o caminho (`path`) até ele.
- Para nós internos, cria caminhos para os filhos esquerdo e direito.
- Chama recursivamente para os filhos esquerdo (`'0'` no caminho) e direito (`'1'` no caminho).

---

## Função `codeLetter()`

```c
void codeLetter(FILE *output, char letter, Node *root, char path[], int prevSize)
{
    if (root == NULL)
        return;

    // Se encontrar o caractere, escreve o caminho no arquivo de saída
    if (root->charCode == letter)
    {
        fprintf(output, "%s", path);
        return;
    }
    else if (root->left == NULL && root->right == NULL)
        return;

    // Cria caminhos para os nós esquerdo e direito
    int size = prevSize + 2;
    char left[size];
    char right[size];

    // Inicializa os caminhos
    for (int i = 0; i < size; i++)
    {
        left[i] = '\0';
        right[i] = '\0';
    }

    // Copia o caminho atual para os caminhos esquerdo e direito
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

    // Chama recursivamente para os nós esquerdo e direito
    codeLetter(output, letter, root->left, left, size);
    codeLetter(output, letter, root->right, right, size);
}
```

**Explicação:**

- Esta função codifica um caractere específico (`letter`) usando a árvore de Huffman (`root`).
- Verifica se o nó atual é nulo ou se é um nó folha com o caractere desejado.
- Se encontrar o caractere, escreve o caminho (`path`) correspondente no arquivo de saída (`output`).
- Cria caminhos para os filhos esquerdo (`'0'` no caminho) e direito (`'1'` no caminho).
- Chama recursivamente para codificar o caractere nos filhos esquerdo e direito da árvore.

---

<a id="writeCoded"></a>

## Função `writeCoded()`

```c
void writeCoded(Node *root, char text[], int size)
{
    FILE *output = fopen("codificado.txt", "a");

    // Codifica cada caractere do texto e escreve no arquivo de saída
    for (int i = 0; i < size; i++)
        codeLetter(output, text[i], root, "", 0);

    fclose(output);
}
```

**Explicação:**

- Esta função escreve o texto codificado usando a árvore de Huffman em um arquivo de saída.
- Abre o arquivo "codificado.txt" em modo de adição (`"a"`), para acrescentar ao conteúdo existente.
- Itera sobre cada caractere no texto (`text`), chamando `codeLetter` para codificar e escrever o caractere codificado no arquivo.
- Fecha o arquivo de saída após escrever todo o texto codificado.

---

## Função `decodeLetter()`

```c
void decodeLetter(FILE *input, FILE *output, Node *root, Node *actual)
{
    char c = getc(input);

    // Verifica o final do arquivo ou nó atual nulo
    if (c == EOF || actual == NULL)
        return;

    // Decodifica o caractere usando a árvore de Huffman
    if (c == '1')
    {
        if (actual->right && actual->right->

charCode != '\0')
        {
            fprintf(output, "%c", actual->right->charCode);
            decodeLetter(input, output, root, root);
            return;
        }
        decodeLetter(input, output, root, actual->right);
    }
    else if (c == '0')
    {
        if (actual->left && actual->left->charCode != '\0')
        {
            fprintf(output, "%c", actual->left->charCode);
            decodeLetter(input, output, root, root);
            return;
        }
        decodeLetter(input, output, root, actual->left);
    }
}
```

**Explicação:**

- Esta função decodifica um caractere do texto codificado usando a árvore de Huffman.
- Lê um caractere do arquivo de entrada (`input`).
- Verifica se chegou ao final do arquivo (`EOF`) ou se o nó atual é nulo.
- Usa o caractere lido (`'0'` ou `'1'`) para percorrer a árvore de Huffman.
- Quando encontra um nó folha (`left` ou `right` nulos), escreve o caractere decodificado no arquivo de saída (`output`).
- Chama recursivamente para continuar decodificando o texto.

---

<a id="writeDecoded"></a>

## Função `writeDecoded()`

```c
void writeDecoded(Node *root)
{
    FILE *input = fopen("codificado.txt", "r");
    FILE *output = fopen("decodificado.txt", "a");

    // Decodifica o texto completo e escreve no arquivo de saída
    decodeLetter(input, output, root, root);

    fclose(input);
    fclose(output);
}
```

**Explicação:**

- Esta função lê o texto codificado do arquivo "codificado.txt" e decodifica usando a árvore de Huffman.
- Abre o arquivo de entrada ("codificado.txt") em modo de leitura (`"r"`) e o arquivo de saída ("decodificado.txt") em modo de adição (`"a"`).
- Chama `decodeLetter` para decodificar cada caractere do texto codificado e escrever o texto decodificado no arquivo de saída.
- Fecha os arquivos de entrada e saída após a decodificação.

---

## Função `main()`

```c
int main()
{
    FILE *origin = fopen("./amostra.txt", "r");

    // Remove arquivos de saída existentes
    remove("codificado.txt");
    remove("decodificado.txt");

    if (origin == NULL)
        exit(0); // Sai do programa se não foi possível abrir o arquivo

    // Conta o número de caracteres no arquivo de origem
    int count = 0;
    char c = getc(origin);
    while (c != EOF)
    {
        count++;
        c = getc(origin);
    }

    if (count == 0)
        exit(0); // Sai do programa se o arquivo estiver vazio

    // Declara arrays para armazenar os caracteres e suas ocorrências
    int times[count];
    char string[count];
    char text[count + 1];

    // Inicializa os arrays
    for (int i = 0; i < count; i++)
    {
        times[i] = -1;
        string[i] = '\0';
        text[i] = '\0';
    }
    text[count] = '\0';

    // Retorna ao início do arquivo
    rewind(origin);

    // Lê os caracteres do arquivo, conta suas ocorrências e os armazena
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
    }

    // Cria um array de nós para cada caractere com suas ocorrências
    Node *values[actualSize];

    // Ordena os nós com base nas ocorrências e nos caracteres associados
    orderValues(values, string, times, actualSize);

    // Cria a árvore de Huffman
    createTree(values, actualSize);

    // Define a raiz da árvore
    Node *root = values[0];

    // Imprime a codificação de Huffman
    printCodification(root, "", 0);

    // Escreve o texto codificado em um arquivo
    writeCoded(root, text, count);

    // Decodifica o texto e escreve em um arquivo
    writeDecoded(root);

    // Libera a memória alocada para os nós
    for (int i = 0; i < actualSize; i++)
        free(values[i]);

    // Fecha o arquivo de origem
    fclose(origin);

    return 0;
}
```

**Explicação:**

- Este é o ponto de entrada do programa.
- Abre o arquivo de origem para leitura.
- Remove arquivos de saída existentes para evitar conflitos.
- Conta o número de caracteres no arquivo de origem.
- Declara e inicializa arrays para armazenar caracteres e suas ocorrências.
- Lê os caracteres do arquivo, contando suas ocorrências e armazenando-os nos arrays.
- Cria uma lista de nós para cada caractere com suas ocorrências.
- Ordena os nós com base nas ocorrências e caracteres associados. [`orderValues`](#orderValues)
- Cria a árvore de Huffman. [`createTree`](#createTree)
- Define a raiz da árvore.
- Imprime a codificação de Huffman. [`printCodification`](#printCodification)
- Escreve o texto codificado em um arquivo. [`writeCoded`](#writeCoded)
- Decodifica o texto e escreve em um arquivo. [`writeDecoded`](#writeDecoded)
- Libera a memória alocada para os nós.
- Fecha o arquivo de origem.
- Retorna 0 para indicar o sucesso da execução.