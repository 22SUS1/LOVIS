#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

void VideleniePamyati(int** arr, int size)
{
    *arr = (int*)malloc(size * sizeof(int));

    if (*arr == NULL) {
        printf("Не удалось выделить память!\n");
        return;
    }
}

void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void zapolnenieshell(int size)// заполнение под сортировку shell
{
    int* a = NULL;
    int i;
    double T1 = 0.0;
    double T2 = 0.0;
    double T3 = 0.0;
    double T4 = 0.0;
    clock_t start, end;
    FILE* Shell1, * Shell2, * Shell3, * Shell4;

    //Последовательное
    VideleniePamyati(&a, size);

    Shell1 = fopen("ShellUp.txt", "w");
    fprintf(Shell1, "До сортировки\n");

    for (i = 0; i < size; i++)
    {
        a[i] = i;
        fprintf(Shell1, "%d\t", a[i]);
    }

    start = clock();
    shell(a, size);
    end = clock();
    T1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(Shell1, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(Shell1, "%d\t", a[i]);
    }
    fclose(Shell1);

    free(a);

    //Убывающее
    VideleniePamyati(&a, size);

    Shell2 = fopen("ShellDown.txt", "w");
    fprintf(Shell2, "До сортировки\n");

    for (i = 0; i < size; i++)
    {
        a[i] = size - i - 1;
        fprintf(Shell2, "%d\t", a[i]);
    }

    start = clock();
    shell(a, size);
    end = clock();
    T2 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(Shell2, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(Shell2, "%d\t", a[i]);
    }
    fclose(Shell2);

    free(a);

    //Половинное
    VideleniePamyati(&a, size);

    Shell3 = fopen("ShellHalf.txt", "w");
    fprintf(Shell3, "До сортировки\n");

    for (i = 0; i < size / 2; i++)
    {
        a[i] = i;
    }

    for (i = size / 2; i < size; i++)
    {
        a[i] = size - i - 1;
    }

    for (i = 0; i < size; i++)
    {
        fprintf(Shell3, "%d\t", a[i]);
    }

    start = clock();
    shell(a, size);
    end = clock();
    T3 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(Shell3, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(Shell3, "%d\t", a[i]);
    }
    fclose(Shell3);

    free(a);

    //Случайное
    VideleniePamyati(&a, size);

    Shell4 = fopen("ShellRand.txt", "w");
    fprintf(Shell4, "До сортировки\n");

    for (i = 0; i < size; i++)
    {
        a[i] = rand() % 100;
        fprintf(Shell4, "%d\t", a[i]);
    }

    start = clock();
    shell(a, size);
    end = clock();
    T4 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(Shell4, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(Shell4, "%d\t", a[i]);
    }
    fclose(Shell4);

    free(a);

    printf("|  Sh  |   %f   |    %f   |   %f    |   %f  |\n", T1, T2, T3, T4);

    FILE* resultFile = fopen("results.txt", "a"); // Открываем файл для добавления (режим "a")
    if (resultFile == NULL) {
        printf("Не удалось открыть файл для записи результатов!\n");
        return;
    }

    fprintf(resultFile, "Shell Sort:\n");
    fprintf(resultFile, "|  Sh  |   %f   |    %f   |   %f    |   %f  |\n", T1, T2, T3, T4);

    fclose(resultFile);
}

void qs(int* items, int left, int right)
{
    int stack[100];
    int top = -1;
    int x, y;
    int j, i;

    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        right = stack[top--];
        left = stack[top--];

        i = left; j = right;
        x = items[(left + right) / 2];
        do {
            while ((items[i] < x) && (i < right)) i++;
            while ((x < items[j]) && (j > left)) j--;

            if (i <= j) {
                y = items[i];
                items[i] = items[j];
                items[j] = y;
                i++; j--;
            }
        } while (i <= j);

        if (left < j) {
            stack[++top] = left;
            stack[++top] = j;
        }
        if (i < right) {
            stack[++top] = i;
            stack[++top] = right;
        }
    }
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void zapolneniequick(int size)
{
    int* a = NULL;
    int i;
    double T1 = 0.0;
    double T2 = 0.0;
    double T3 = 0.0;
    double T4 = 0.0;
    clock_t start, end;
    FILE* qs1, * qs2, * qs3, * qs4;

    //Последовательное
    VideleniePamyati(&a, size);

    qs1 = fopen("qsUp.txt", "w");
    fprintf(qs1, "До сортировки\n");

    for (i = 0; i < size; i++)
    {
        a[i] = i;
        fprintf(qs1, "%d\t", a[i]);
    }

    start = clock();
    qs(a, 0, size - 1);
    end = clock();
    T1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(qs1, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(qs1, "%d\t", a[i]);
    }
    fclose(qs1);

    free(a);

    //Убывающее
    VideleniePamyati(&a, size);

    qs2 = fopen("qsDown.txt", "w");
    fprintf(qs2, "До сортировки\n");

    for (i = 0; i < size; i++)
    {
        a[i] = size - i - 1;
        fprintf(qs2, "%d\t", a[i]);
    }

    start = clock();
    qs(a, 0, size - 1);
    end = clock();
    T2 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(qs2, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(qs2, "%d\t", a[i]);
    }
    fclose(qs2);

    free(a);

    //Половинное
    VideleniePamyati(&a, size);

    qs3 = fopen("qsHalf.txt", "w");
    fprintf(qs3, "До сортировки\n");

    for (i = 0; i < size / 2; i++)
    {
        a[i] = i;
    }

    for (i = size / 2; i < size; i++)
    {
        a[i] = size - i - 1;
    }

    for (i = 0; i < size; i++)
    {
        fprintf(qs3, "%d\t", a[i]);
    }

    start = clock();
    qs(a, 0, size - 1);
    end = clock();
    T3 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(qs3, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(qs3, "%d\t", a[i]);
    }
    fclose(qs3);

    free(a);

    //Случайное
    VideleniePamyati(&a, size);

    qs4 = fopen("qsRand.txt", "w");
    fprintf(qs4, "До сортировки\n");

    for (i = 0; i < size; i++)
    {
        a[i] = rand() % 100;
        fprintf(qs4, "%d\t", a[i]);
    }

    start = clock();
    qs(a, 0, size - 1);
    end = clock();
    T4 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(qs4, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(qs4, "%d\t", a[i]);
    }
    fclose(qs4);

    free(a);

    printf("|  qs  |   %f   |    %f   |   %f    |   %f  |\n", T1, T2, T3, T4);

    FILE* resultFile = fopen("results.txt", "a"); // Открываем файл для добавления (режим "a")
    if (resultFile == NULL) {
        printf("Не удалось открыть файл для записи результатов!\n");
        return;
    }

    fprintf(resultFile, "qs:\n");
    fprintf(resultFile, "|  qs  |   %f   |    %f   |   %f    |   %f  |\n", T1, T2, T3, T4);

    fclose(resultFile);
}

void zapolenieqsort(int size)//заполнение qsort
{
    int* a = NULL;
    int i;
    double T1 = 0.0;
    double T2 = 0.0;
    double T3 = 0.0;
    double T4 = 0.0;
    clock_t start, end;
    FILE* qsort1, * qsort2, * qsort3, * qsort4;

    //Последовательное
    VideleniePamyati(&a, size);

    qsort1 = fopen("qsortUp.txt", "w");
    fprintf(qsort1, "До сортировки\n");

    for (i = 0; i < size; i++)
    {
        a[i] = i;
        fprintf(qsort1, "%d\t", a[i]);
    }

    start = clock();
    qsort(a, size, sizeof(int), compare);
    end = clock();
    T1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(qsort1, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(qsort1, "%d\t", a[i]);
    }
    fclose(qsort1);

    free(a);

    //Убывающее
    VideleniePamyati(&a, size);

    qsort2 = fopen("qsortDown.txt", "w");
    fprintf(qsort2, "До сортировки\n");

    for (i = 0; i < size; i++)
    {
        a[i] = size - i - 1;
        fprintf(qsort2, "%d\t", a[i]);
    }

    start = clock();
    qsort(a, size, sizeof(int), compare);
    end = clock();
    T2 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(qsort2, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(qsort2, "%d\t", a[i]);
    }
    fclose(qsort2);

    free(a);

    //Половинное
    VideleniePamyati(&a, size);

    qsort3 = fopen("qsortHalf.txt", "w");
    fprintf(qsort3, "До сортировки\n");

    for (i = 0; i < size / 2; i++)
    {
        a[i] = i;
    }

    for (i = size / 2; i < size; i++)
    {
        a[i] = size - i - 1;
    }

    for (i = 0; i < size; i++)
    {
        fprintf(qsort3, "%d\t", a[i]);
    }

    start = clock();
    qsort(a, size, sizeof(int), compare);
    end = clock();
    T3 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(qsort3, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(qsort3, "%d\t", a[i]);
    }
    fclose(qsort3);

    free(a);

    //Случайное
    VideleniePamyati(&a, size);

    qsort4 = fopen("qsortRand.txt", "w");
    fprintf(qsort4, "До сортировки\n");

    for (i = 0; i < size; i++)
    {
        a[i] = rand() % 100;
        fprintf(qsort4, "%d\t", a[i]);
    }

    start = clock();
    qsort(a, size, sizeof(int), compare);
    end = clock();
    T4 = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(qsort4, "\n\nПосле сортировки\n");
    for (i = 0; i < size; i++)
    {
        fprintf(qsort4, "%d\t", a[i]);
    }
    fclose(qsort4);

    free(a);

    printf("| qsort|   %f   |    %f   |   %f    |   %f  |\n", T1, T2, T3, T4);

    FILE* resultFile = fopen("results.txt", "a"); // Открываем файл для добавления (режим "a")
    if (resultFile == NULL) {
        printf("Не удалось открыть файл для записи результатов!\n");
        return;
    }

    fprintf(resultFile, "qsort:\n");
    fprintf(resultFile, "|    |   %f   |    %f   |   %f    |   %f  |\n", T1, T2, T3, T4);

    fclose(resultFile);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    int size;
    printf("Введите размер массива:");
    scanf("%d", &size);

    printf("\n*------*--------------*---------------*---------------*-------------*\n");
    printf("|      |       В      |       У\       |      В-У\       |      *      |\n");
    printf("*------*--------------*---------------*---------------*-------------*\n");
    zapolnenieshell(size);
    printf("*------*--------------*---------------*---------------*-------------*\n");
    zapolneniequick(size);
    printf("*------*--------------*---------------*---------------*-------------*\n");
    zapolenieqsort(size);
    printf("*------*--------------*---------------*---------------*-------------*\n");

    getch();

    return 0;
}