#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "json.hpp" // библиотека nlohmann::json

using namespace std;
using json = nlohmann::json;

struct Element {
    string name;      // Название (слово)
    long long first;  // Основной параметр
    long long second; // Вторичный параметр
};

// Шаг 1: Чтение слов из файла и построение множества
bool readWordsFromFile(const string& filename,
                       vector<string>& allWords,
                       set<string>& uniqueWords)
{
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return false;
    }

    string word;
    while (in >> word) {
        if (!word.empty()) {
            allWords.push_back(word);
            uniqueWords.insert(word);
        }
    }

    return true;
}

// Шаг 2: Словарь частот по первой букве слова
map<char, int> createLetterFrequencyMap(const vector<string>& allWords)
{
    map<char, int> freq;

    for (const auto& w : allWords) {
        if (w.empty()) continue;
        char c = static_cast<char>(tolower(static_cast<unsigned char>(w[0])));
        freq[c]++;
    }

    return freq;
}

// Вспомогательная функция — рандом
int randomInt(int left, int right) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(left, right);
    return dist(gen);
}

// Шаг 3: Генерация 100 структур
vector<Element> generateElements(const set<string>& words,
                                 const map<char, int>& freqMap)
{
    vector<Element> elements;

    if (words.empty() || freqMap.empty()) {
        cerr << "Ошибка: пустые входные данные.\n";
        return elements;
    }

    vector<string> wordVec(words.begin(), words.end());

    for (int i = 0; i < 100; ++i) {
        Element e;

        // случайное слово
        int widx = randomInt(0, (int)wordVec.size() - 1);
        e.name = wordVec[widx];

        // три случайных значения из карты
        long long product = 1;
        for (int k = 0; k < 3; k++) {
            int idx = randomInt(0, (int)freqMap.size() - 1);
            auto it = freqMap.begin();
            advance(it, idx);
            product *= it->second;
        }

        e.first = product;

        // квадрат значения по первой букве
        char c = static_cast<char>(tolower((unsigned char)e.name[0]));
        auto it = freqMap.find(c);
        if (it != freqMap.end()) {
            e.second = 1LL * it->second * it->second;
        } else {
            e.second = 0;
        }

        elements.push_back(e);
    }

    return elements;
}

// Шаг 4 — сортировка по убыванию названия
void sortElementsByNameDesc(vector<Element>& elements)
{
    sort(elements.begin(), elements.end(),
         [](const Element& a, const Element& b) {
             return a.name > b.name;
         });
}

// Шаг 5 — фильтрация по чётной разности first - second
vector<Element> filterEvenDifference(const vector<Element>& elements)
{
    vector<Element> filtered;

    copy_if(elements.begin(), elements.end(),
            back_inserter(filtered),
            [](const Element& e) {
                return ((e.first - e.second) % 2 == 0);
            });

    return filtered;
}

void printElementsBeautiful(const vector<Element>& elements) {
    cout << "=====================================================\n";
    for (const auto& e : elements) {
        cout << "Название:           " << e.name   << "\n";
        cout << "Основной параметр:  " << e.first  << "\n";
        cout << "Вторичный параметр: " << e.second << "\n";
        cout << "-----------------------------------------------------\n";
    }
    cout << "=====================================================\n";
}

// Шаг 6 — Сохранение списка в JSON-файл 
void saveToJson(const vector<Element>& elements, const string& filename)
{
    json j = json::array();

    for (const auto& e : elements) {
        json obj = json::object();
        obj["Название"]          = e.name;
        obj["ОсновнойПараметр"]  = e.first;
        obj["ВторичныйПараметр"] = e.second;
        j.push_back(obj);
    }

    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return;
    }

    out << j.dump(4);
}

// Шаг 7 — Загрузка JSON + создание списка
vector<Element> loadFromJson(const string& filename)
{
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Не удалось открыть JSON-файл: " << filename << endl;
        return {};
    }

    json j;
    in >> j;

    vector<Element> elements;

    for (const auto& item : j) {
        Element e;
        e.name   = item.at("Название").get<string>();
        e.first  = item.at("ОсновнойПараметр").get<long long>();
        e.second = item.at("ВторичныйПараметр").get<long long>();
        elements.push_back(e);
    }

    return elements;
}

// перемешивание + вывод
void shuffleAndDisplay(vector<Element>& elements)
{
    unsigned seed =
        chrono::system_clock::now().time_since_epoch().count();

    shuffle(elements.begin(), elements.end(), default_random_engine(seed));

    printElementsBeautiful(elements);
}

// меню
void printMenuInfo() {
    cout << "\n0 - продолжить\n";
    cout << "1 - вернуться в начало\n";
    cout << "3 - завершить программу\n";
}

void clearScreen() {
    cout << "\033c";
}

int main()
{
    setlocale(LC_ALL, "Russian");

    const string inputFilename = "data.txt";
    const string jsonFilename  = "result.json";

    int user = 0;

    while (user != 3) {
        clearScreen();
        cout << "=== Меню ===\n";
        cout << "1 - Начать выполнение практической работы\n";
        cout << "3 - Выход\n";
        cin >> user;

        if (user == 3) {
            cout << "Работа программы завершена.\n";
            break;
        }

        if (user != 1) continue;

        // Шаг 1
        clearScreen();
        vector<string> allWords;
        set<string> uniqueWords;

        cout << "Шаг 1: Чтение файла и создание множества слов\n";

        if (!readWordsFromFile(inputFilename, allWords, uniqueWords)) {
            return 0;
        }

        cout << "Уникальных слов: " << uniqueWords.size() << "\n\n";
        cout << "Список слов:\n";
        for (const auto& w : uniqueWords)
            cout << w << " ";
        cout << "\n";

        printMenuInfo();
        int user1;
        cin >> user1;
        if (user1 == 1) continue;
        if (user1 == 3) break;
        clearScreen();

        // Шаг 2 
        cout << "Шаг 2: Создание частотного словаря\n";
        auto freq = createLetterFrequencyMap(allWords);

        for (auto &p : freq)
            cout << "'" << p.first << "': " << p.second << "\n";

        printMenuInfo();
        cin >> user1;
        if (user1 == 1) continue;
        if (user1 == 3) break;
        clearScreen();

        // Шаг 3 
        cout << "Шаг 3: Генерация 100 структур\n";
        auto elements = generateElements(uniqueWords, freq);

        printElementsBeautiful(elements);

        printMenuInfo();
        cin >> user1;
        if (user1 == 1) continue;
        if (user1 == 3) break;
        clearScreen();

        // Шаг 4 
        cout << "Шаг 4: Сортировка по убыванию названия\n";
        sortElementsByNameDesc(elements);
        printElementsBeautiful(elements);

        printMenuInfo();
        cin >> user1;
        if (user1 == 1) continue;
        if (user1 == 3) break;
        clearScreen();

        // Шаг 5 
        cout << "Шаг 5: Фильтрация (чётная разность параметров)\n";
        auto filtered = filterEvenDifference(elements);
        printElementsBeautiful(filtered);

        printMenuInfo();
        cin >> user1;
        if (user1 == 1) continue;
        if (user1 == 3) break;
        clearScreen();

        // Шаг 6
        cout << "Шаг 6: Сохранение в JSON\n";
        saveToJson(filtered, jsonFilename);
        cout << "Сохранено в " << jsonFilename << "\n";

        printMenuInfo();
        cin >> user1;
        if (user1 == 1) continue;
        if (user1 == 3) break;
        clearScreen();

        // Шаг 7
        cout << "Шаг 7: Загрузка JSON, перемешивание, вывод\n";
        auto loaded = loadFromJson(jsonFilename);
        shuffleAndDisplay(loaded);

        printMenuInfo();
        cin >> user1;
        if (user1 == 3) break;
    }

    return 0;
}
