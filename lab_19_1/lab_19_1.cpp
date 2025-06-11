//Дан вектор V0, целое число N(> 0) и набор векторов V1, …, VN.Известно, что
//размер вектора V0 не превосходит размера любого из векторов V1, …, VN.Найти количество
//векторов VI, I = 1, …, N, в которых содержатся все элементы вектора V0(без учета их
//повторений).Использовать алгоритм includes, применяя его в цикле к двум множествам, одно
//из которых создано на основе вектора V0, а другое на очередной итерации содержит элементы
//очередного из векторов VI, I = 1, …, N.
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void coutvector(const vector<int>& v) {
    for (auto a : v) {
        cout << a << " ";
    }
    cout << endl;
}

void inputVector(vector<int>& vec, const string& prompt) {
    cout << prompt;
    int value;
    while (true) {
        cin >> value;
        if (value == -1) break;
        vec.push_back(value);
    }
}

void addConsole(vector<vector<int>>& vectors, int N, int min_size) {
    for (int i = 0; i < N; ++i) {
        cout << "Введите элементы вектора " << i + 1 << " (закончите ввод -1): ";
        vector<int> vec;
        inputVector(vec, "");
        if (vec.size() < min_size) {
            min_size = vec.size();
        }
        vectors.push_back(vec);
    }
}

void addRandom(vector<vector<int>>& vectors, int N, const vector<int>& V0) {
    srand(time(0));
    for (int i = 0; i < N; ++i) {
        vector<int> vec;

        int size = V0.size() + rand() % 10 / 2;
        for (int k = 0; k < size; ++k) {
            vec.push_back(rand() % 10 + 1);
        }
        cout << "Сгенерированный вектор " << i + 1 << ": ";
        coutvector(vec);
        vectors.push_back(vec);
    }
}

void fromFile(vector<vector<int>>& vectors, const string& filename, int min_size) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return;
    }

    int value;
    while (file >> value) {
        vector<int> vec;
        do {
            vec.push_back(value);
            if (!(file >> value)) break;
        } while (value != -1);

        if (vec.size() < min_size) {
            min_size = vec.size();
        }
        vectors.push_back(vec);
    }
    file.close();
}

int processVectors(const vector<vector<int>>& vectors, const vector<int>& V0) {
    set<int> setV0(V0.begin(), V0.end());
    int count = 0;

    for (const auto& vec : vectors) {
        set<int> currentSet(vec.begin(), vec.end());
        if (includes(currentSet.begin(), currentSet.end(),
            setV0.begin(), setV0.end())) {
            count++;
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<vector<int>> vectors;
    vector<int> V0;
    int N;
    string filename;

    cout << "Введите элементы вектора V0 (закончите ввод -1): ";
    inputVector(V0, "");

    int min_size = V0.size();

    cout << "Вектор V0: ";
    coutvector(V0);

    cout << "Введите количество векторов (N): ";
    cin >> N;

    int choice;
    cout << "Выберите способ ввода данных:\n";
    cout << "1. Ввод с консоли\n";
    cout << "2. Генерация случайных векторов\n";
    cout << "3. Чтение из файла\n";
    cin >> choice;

    switch (choice) {
    case 1:
        addConsole(vectors, N, min_size);
        break;
    case 2:
        addRandom(vectors, N, V0);
        break;
    case 3:
        cout << "Введите имя файла: ";
        cin >> filename;
        fromFile(vectors, filename, min_size);
        break;
    default:
        cout << "Ошибка ввода." << endl;
        return 1;
    }

    if (vectors.empty()) {
        cout << "Не было введено ни одного вектора!" << endl;
        return 1;
    }

    int count = processVectors(vectors, V0);
    cout << "Количество векторов, содержащих все элементы V0: " << count << endl;

    return 0;
}