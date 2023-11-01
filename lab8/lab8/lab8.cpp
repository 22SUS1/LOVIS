#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Структура для представления узла связного списка 
struct Node {
    int value;
    Node* next;
};

// Класс для реализации очереди на связном списке
class line {
private:
    Node* head;
    Node* tip;

public:
    line() {
        head = nullptr;
        tip = nullptr;
    }
    // Добавление элемента в конец очереди
    void insert(int x) {
        Node* newNode = new Node({ x, nullptr });
        // Если очередь не пуста, связываем с последним элементом
        if (tip != nullptr) {
            tip->next = newNode;
        }
        // Обновляем указатель на конец очереди
        tip = newNode;
        // Если очередь была пуста, head тоже указывает на добавленный элемент
        if (head == nullptr) {
            head = newNode;
        }
    }

    // Удаление элемента из начала очереди 
    int del() {
        if (head == nullptr) {
            return -1;
        }
        Node* temp = head;
        int result = temp->value;
        head = head->next;
        if (head == nullptr) {
            tip = nullptr;
        }
        delete temp;
        return result;
    }
    bool isEmpty() {
        return head == nullptr;
    }
};

void evade(vector<vector<int>>& Matr, int n) {
    vector<bool> entered(n, false);
    vector<int> result;

    line q;

    for (int i = 0; i < n; i++) {
        if (!entered[i]) {

            bool isolated = true;
            for (int j = 0; j < n; j++) {
                if (Matr[i][j] == 1) {
                    isolated = false;
                    break;
                }
            }
            if (!isolated) {
                q.insert(i);
                entered[i] = true;
                while (!q.isEmpty()) {
                    int v = q.del();
                    result.push_back(v);
                    for (int j = 0; j < n; j++) {
                        if (Matr[v][j] == 1 && !entered[j]) {
                            q.insert(j);
                            entered[j] = true;
                        }
                    }
                }
            }
        }
    }

    // вывод
    cout << "\nОбход матрицы в ширину\n";
    for (int v : result) {
        cout << v + 1 << " ";
    }
    cout << endl;

}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int n;
    cout << "Введите кол-во вершин: ";
    cin >> n;

    vector<vector<int>> Matr(n, vector<int>(n));
    vector<vector<int>> list(n);

    // Матрица 1
    cout << "Матрица смежности " << endl;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                Matr[i][j] = 0;
            }
            else {
                Matr[i][j] = rand() % 2;
                Matr[j][i] = Matr[i][j];
            }
        }
    }

    // Вывод матрицы 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << Matr[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n";

    vector<bool> entered(n, false);

    cout << "\nОбход матрицы в ширину:\n";

    //обход матрицы в ширину
    for (int i = 0; i < n; i++) {
        if (!entered[i]) {
            bool isolated = true;
            for (int j = 0; j < n; j++) {
                if (Matr[i][j] == 1) {
                    isolated = false;
                    break;
                }
            }
            if (!isolated) {
                queue<int> q;
                q.push(i);
                entered[i] = true;
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();

                    cout << v + 1 << " ";

                    for (int j = 0; j < n; j++) {
                        if (Matr[v][j] == 1 && !entered[j]) {
                            q.push(j);
                            entered[j] = true;
                        }
                    }
                }
            }
        }
    }

    //обход матрицы в ширину на основе списка из ЛР№3
    evade(Matr, n);

    // Заполнение списка смежности на основе матрицы
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (Matr[i][j] == 1) {
                list[i].push_back(j);
                //list[j].push_back(i); // добавляем обратное ребро
            }
        }
    }

    // Вывод списка смежности
    cout << "\n";
    cout << "\nСписок смежности:\n";

    for (int i = 0; i < n; ++i) {
        cout << "Верш. № " << i + 1 << ": ";

        for (int j = 0; j < list[i].size(); ++j) {
            cout << list[i][j] + 1 << " ";
        }

        cout << "\n";
    }

    cout << "\nОбход списка в ширину:\n";

    vector<bool> entered2(n, false);

    //обход матрицы в ширину списка смежности
    for (int i = 0; i < n; i++) {
        if (!entered2[i]) {
            bool isolated = list[i].empty();
            if (!isolated) {
                queue<int> q;
                q.push(i);
                entered2[i] = true;
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();

                    cout << v + 1 << " ";

                    for (int j = 0; j < list[v].size(); j++) {
                        int u = list[v][j];
                        if (!entered2[u]) {
                            q.push(u);
                            entered2[u] = true;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
