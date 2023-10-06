#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* CreateTree(struct Node* root, int data) {
    if (root == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }

        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (data < root->data) {
        root->left = CreateTree(root->left, data);
    }
    else if (data > root->data) {
        root->right = CreateTree(root->right, data);
    }
    // Игнорируем добавление элемента с тем же значением,
    // которое уже существует в дереве

    return root;
}

void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf(" ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

struct Node* Search(struct Node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return Search(root->left, value);
    }
    else {
        return Search(root->right, value);
    }
}

int CountOccurrences(struct Node* root, int value) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;

    if (root->data == value) {
        count = 1;
    }

    count += CountOccurrences(root->left, value);
    count += CountOccurrences(root->right, value);

    return count;
}

int main() {
    setlocale(LC_ALL, "RU");
    int D, start = 1;
    struct Node* root = NULL; // Declare root node

    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, D); 
        }
    }

    print_tree(root, 0);

    printf("Введите значение для поиска: ");
    scanf("%d", &D);

    struct Node* result = Search(root, D);
    if (result != NULL) {
        printf("Значение найдено: %d\n", result->data);
        printf("Введите значение для подсчета вхождений: ");
        int searchValue;
        scanf("%d", &searchValue);
        int count = CountOccurrences(root, searchValue);
        printf("Число вхождений: %d\n", count);
    }
    else {
        printf("Значение не найдено\n");
    }

    return 0;
}