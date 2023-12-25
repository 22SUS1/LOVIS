#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <locale.h>

using namespace std;

const int way = -3, wall = -2, pass = -1;

bool deadend(int x, int y, int maze[][99], int height, int width) {
    int a = 0;

    if (x != 1) {
        if (maze[y][x - 2] == pass)
            a += 1;
    }
    else
        a += 1;

    if (y != 1) {
        if (maze[y - 2][x] == pass)
            a += 1;
    }
    else
        a += 1;

    if (x != width - 2) {
        if (maze[y][x + 2] == pass)
            a += 1;
    }
    else
        a += 1;

    if (y != height - 2) {
        if (maze[y + 2][x] == pass)
            a += 1;
    }
    else
        a += 1;

    return a == 4;
}

bool ended(int maze[][99], int height, int width) {
    bool b = true;

    for (int i = 1; i < (height - 1); i += 2)
        for (int j = 1; j < (width - 1); j += 2)
            if (maze[i][j] == wall)
                b = false;

    return b;
}

void mazemake(int maze[][99], int height, int width) {
    int x, y, c, a;
    bool b;

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            maze[i][j] = wall;

    x = 3; y = 3; a = 0;
    while (1)
    {
        a++;
        if (a % 100 == 0)
            if (ended(maze, height, width))
                break;
        maze[y][x] = pass;
        while (1) {
            c = rand() % 4;
            switch (c) {
            case 0: if (y != 1)
                if (maze[y - 2][x] == wall) {
                    maze[y - 1][x] = pass;
                    maze[y - 2][x] = pass;
                    y -= 2;
                }
                  break;
            case 1: if (y != height - 2)
                if (maze[y + 2][x] == wall) {
                    maze[y + 1][x] = pass;
                    maze[y + 2][x] = pass;
                    y += 2;
                }
                  break;
            case 2: if (x != 1)
                if (maze[y][x - 2] == wall) {
                    maze[y][x - 1] = pass;
                    maze[y][x - 2] = pass;
                    x -= 2;
                }
                  break;
            case 3: if (x != width - 2)
                if (maze[y][x + 2] == wall) {
                    maze[y][x + 1] = pass;
                    maze[y][x + 2] = pass;
                    x += 2;
                }
                  break;
            }
            if (deadend(x, y, maze, height, width))
                break;
        }

        if (deadend(x, y, maze, height, width))
            do {
                x = 2 * (rand() % ((width - 1) / 2)) + 1;
                y = 2 * (rand() % ((height - 1) / 2)) + 1;
            } while (maze[y][x] != pass);
    }
}

void drawing(int map[][99], int size) {
    system("cls");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (map[i][j] == wall)
                cout << "# ";
            else if (map[i][j] == way)
                cout << "1 ";
            else
                cout << "- ";
        }
        cout << '\n';
    }
}

void saveToFile(const char* filename, int map[][99], int size) {
    ofstream file(filename, ios_base::out);
    if (file.is_open()) {
        file << size << '\n';
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file << map[i][j] << " ";
            }
            file << '\n';
        }
        file.close();
        cout << "Maze has been saved to " << filename << endl;
    }
    else {
        cout << "Unable to open the file for writing." << endl;
    }
}

void loadFromFile(const char* filename, int map[][99], int& size) {
    ifstream file(filename, ios_base::in);
    if (file.is_open()) {
        file >> size;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file >> map[i][j];
            }
        }
        file.close();
        cout << "Maze has been loaded from " << filename << endl;
    }
    else {
        cout << "Unable to open the file for reading." << endl;
    }
}

void start() {
    int map_size;
    do {
        cout << "Введите размер лабиринта - только нечетные числа (от 5 до 99): ";
        cin >> map_size;

        if (cin.fail() || map_size <= 4 || map_size >= 100 || map_size % 2 == 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный размер лабиринта! Повторите попытку." << endl;
        }
        else {
            break;
        }
    } while (true);

    int map[99][99];
    mazemake(map, map_size, map_size);

    // Запись лабиринта в файл перед поиском расстояния
    saveToFile("lab_search.txt", map, map_size);

    drawing(map, map_size);
    map[1][1] = pass;
    vector<pair<int, int>> oldWave;
    oldWave.push_back(pair<int, int>(1, 1));
    int nstep = 0;
    map[1][1] = nstep;
    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { -1, 0, 1, 0 };
    while (!oldWave.empty()) {
        ++nstep;
        vector<pair<int, int>> wave;
        for (const auto& i : oldWave) {
            for (int d = 0; d < 4; ++d) {
                int nx = i.first + dx[d];
                int ny = i.second + dy[d];
                if (nx >= 0 && nx < map_size && ny >= 0 && ny < map_size && map[nx][ny] == pass) {
                    wave.push_back(pair<int, int>(nx, ny));
                    map[nx][ny] = nstep;
                    if (nx == map_size - 2 && ny == map_size - 2) {
                        oldWave.clear();
                        break;
                    }
                }
            }
        }
        oldWave = wave;
    }

    int x = map_size - 2;
    int y = map_size - 2;
    vector<pair<int, int>> wave;
    wave.push_back(pair<int, int>(x, y));
    while (map[x][y] != 0) {
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && nx < map_size && ny >= 0 && ny < map_size && map[x][y] - 1 == map[nx][ny]) {
                x = nx;
                y = ny;
                wave.push_back(pair<int, int>(x, y));
            }
        }
    }
    for (const auto& i : wave) {
        map[i.first][i.second] = way;
    }
    drawing(map, map_size);
    getchar();
    getchar();
}

int main() {
    setlocale(LC_ALL, "RUS");

    srand(time(NULL));

    cout << "\t" << "Курсовая работа" << endl << "Тема: реализация алгоритма поиска путей в лабиринте" << endl << "\n"
        << "Выполнил: ст. гр. 22ВВВ1" << endl << "Уткин М.М." << endl;
    system("pause");
    int choice;
    do {
        system("cls");
        cout << "1)Поиск расстояния между вершинами." << endl;
        cout << "2)Выход." << endl;
        cout << "Выберите действие:";
        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            start();
            break;
        case 2:
            system("cls");
            break;
        default:
            cout << endl;
            cout << "Неверный выбор! Повторите попытку.";
            cout << endl;
            break;
        }
    } while (choice != 2);

    return 0;
}
