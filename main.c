#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int stringSize = 30;

typedef struct tree_t {
    int value;
    struct tree_t *left;
    struct tree_t *right;
} tree_t;

void addValue(tree_t *root);
void insertion(tree_t *root, int inputValue);
void nodesOnLevel(tree_t *root);
int findNumOfNodes(tree_t *node, int level);
void printTree(tree_t *node);
int inputNumericalData();
void freeTree(tree_t *node);
void checkHelpKey(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    checkHelpKey(argc, argv);
    char command[stringSize];
    tree_t *root;
    root = (tree_t *) calloc(1, sizeof(tree_t));
    while (1) {
        printf("\nEnter command:\n");
        printf("    1 - Add value\n");
        printf("    2 - Find nodes at level\n");
        printf("    3 - Print tree\n");
        printf("    4 - Exit\n");
        fgets(command, stringSize, stdin);
        switch (command[0]) {
        case '1':
            addValue(root);
            break;
        case '2':
            nodesOnLevel(root);
            break;
        case '3':
            printTree(root);
            break;
        case '4':
            freeTree(root);
            return 0;
        default:
            printf("Wrong command. Try again.\n");
        }
    }
    return 0;
}

void addValue(tree_t *root)
{
    int inputValue;
    static int isFirstValue = 1;
    printf("Enter the value of the new node: ");
    inputValue = inputNumericalData();
    if (isFirstValue) {
        root->value = inputValue;
        isFirstValue = 0;
    } else {
        insertion(root, inputValue);
    }
}

void insertion(tree_t *node, int inputValue)
{
    if (inputValue < node->value) {
        if (node->right) {
            insertion(node->right, inputValue);
            return;
        } else {
            node->right = (tree_t *) calloc(1, sizeof(tree_t));
            node->right->value = inputValue;
            return;
        }
    } else if (inputValue > node->value) {
        if (node->left) {
            insertion(node->left, inputValue);
            return;
        } else {
            node->left = (tree_t *) calloc(1, sizeof(tree_t));
            node->left->value = inputValue;
            return;
        }
    } else if (inputValue == node->value) {
        printf("Node with that value already exists.\n");
    }
    return;
}

void nodesOnLevel(tree_t *root)
{
    int level, numOfNodes;
    printf("Enter level: \n");
    level = inputNumericalData();
    if (level < 1) {
        printf("Wrong level.\n");
        return;
    }
    numOfNodes = findNumOfNodes(root, level);
    if (!numOfNodes) {
        printf("There are no nodes at level %d\n", level);
    } else {
        printf("There are %d nodes at level %d\n", numOfNodes, level);
    }
    return;
}

int findNumOfNodes(tree_t *node, int level)
{
    static int currLevel = 0;
    int numOfNodes = 0;
    currLevel++;
    if (currLevel == level) {
        if (node->value) {
            numOfNodes++;
        }
        currLevel--;
        return numOfNodes;
    }
    if (node->left) {
        numOfNodes += findNumOfNodes(node->left, level);
    }
    if (node->right) {
        numOfNodes += findNumOfNodes(node->right, level);
    }
    currLevel--;
    return numOfNodes;
}

void printTree(tree_t *node)
{
    static int level = 0;
    int i;
    level++;
    if (node->right) {
        printTree(node->right);
    }
    for (i = 1; i < level; i++) {
        printf("   ");
    }
    printf("%3d\n", node->value);
    if (node->left ) {
        printTree(node->left);
    }
    level--;
}

int inputNumericalData()
{
    char buffer[stringSize], *bufferPointer;
    int num;
    bufferPointer = buffer;
    do {
        fgets(buffer, stringSize, stdin);
        num = strtol(buffer, &bufferPointer, 10);
        if (num == 0) {
            if (*(--bufferPointer) == '0') {
                break;
            }
            printf("Incorrect value. Try again: ");
            continue;
        }
        break;
    } while (1);
    return num;
}

void freeTree(tree_t *node)
{
    if (node->left) {
        freeTree(node->left);
    }
    if (node->right ) {
        freeTree(node->right);
    }
    free(node);
}

void checkHelpKey(int argc, char *argv[])
{
    if (argc == 1) {
        return;
    }
    if (!strcmp("-h", argv[1]))
    {
        printf("=================================================================\n");
        printf("                               MANUAL\n");
        printf("Commands: 1 2 3 4\n");
        printf("    1 - Add value\n");
        printf("        DESCRIPTION: Added value into the binary tree.\n");
        printf("        USAGE:       After entering command you must enter a value.\n");
        printf("                     The value must not be equal to zero.\n");
        printf("    2 - Find nodes at level\n");
        printf("        DESCRIPTION: Finds and displays the number of nodes at a given level.\n");
        printf("        USAGE:       After entering command you must enter required level.\n");
        printf("                     Levels starts from one\n");
        printf("    3 - Print tree\n");
        printf("        DESCRIPTION: Print all values of tree.\n");
        printf("    4 - Exit\n");
        printf("        DESCRIPTION: Close the programm.\n");
        printf("=================================================================\n\n");
        exit(0);
    }
}
