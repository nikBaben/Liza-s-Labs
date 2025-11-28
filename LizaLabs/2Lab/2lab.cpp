#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <typeinfo>
#include <limits>

using namespace std;

// Базовый абстрактный класс
class Cat {
protected:
    string name;   // имя
    string sex;    // пол
    int age;       // возраст
    double weight; // вес

public:
    // Конструктор без параметров
    Cat() {
        cout << "[Cat] Конструктор без параметров, адрес: " << this << endl;
        name = "";
        sex = "";
        age = 0;
        weight = 0.0;
    }

    // Конструктор с параметрами
    Cat(string name, string sex, int age, double weight) {
        cout << "[Cat] Конструктор с параметрами, адрес: " << this << endl;
        this->name = name;
        this->sex = sex;
        this->age = age;
        this->weight = weight;
    }

    // Конструктор копирования
    Cat(const Cat &other) {
        cout << "[Cat] Конструктор копирования, адрес: " << this << endl;
        name = other.name;
        sex = other.sex;
        age = other.age;
        weight = other.weight;
    }

    // Виртуальный деструктор
    virtual ~Cat() {
        cout << "[Cat] Деструктор базового класса, адрес: " << this << endl;
    }

    // Сеттеры
    void set_name(const string &name)         { this->name = name; }
    void set_sex(const string &sex)           { this->sex = sex; }
    void set_age(int age)                     { this->age = (age < 0 ? 0 : age); }
    void set_weight(double weight)            { this->weight = (weight < 0 ? 0 : weight); }

    // Геттеры
    string get_name()   const { return name; }
    string get_sex()    const { return sex; }
    int    get_age()    const { return age; }
    double get_weight() const { return weight; }

    // Чисто виртуальные методы — общие для всех
    virtual void play() = 0;            // поиграть
    virtual void feed() = 0;            // покормить
    virtual void pet() = 0;             // погладить

    // Дополнительно общий "осуждающий взгляд"
    virtual void judgmentalLook() = 0;

    // Вывод имени класса
    virtual void classname() = 0;

    // Полная информация об объекте
    virtual void info() = 0;

    // Дружественные функции (как у одногруппника)
    friend ostream& operator<<(ostream &os, Cat &cat);
    friend istream& operator>>(istream &is, Cat &cat);
};

// Краткий вывод в поток
ostream& operator<<(ostream &os, Cat &cat) {
    os << "+========================================+" << endl;
    os << "| Краткие данные о кошке                 |" << endl;
    os << "+----------------------------------------+" << endl;
    os << "| Имя: "    << setw(30 + cat.name.length()/2) << left << cat.name << "|" << endl;
    os << "+----------------------------------------+" << endl;
    os << "| Пол: "    << setw(32 + cat.sex.length()/2)  << left << cat.sex  << "|" << endl;
    os << "+----------------------------------------+" << endl;
    os << "| Возраст: " << setw(26) << left << cat.age    << "| лет|" << endl;
    os << "+----------------------------------------+" << endl;
    os << "| Вес: "     << setw(31) << left << cat.weight << "| кг |" << endl;
    os << "+========================================+" << endl;
    return os;
}

// Ввод общих полей
istream& operator>>(istream &is, Cat &cat) {
    cout << "Введите имя: ";
    is >> ws;
    getline(is, cat.name);

    cout << "Введите пол (кот/кошка): ";
    getline(is, cat.sex);

    cout << "Введите возраст: ";
    is >> cat.age;
    cout << "Введите вес: ";
    is >> cat.weight;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    return is;
}

// Вислоухая
class ScottishFold : public Cat {
private:
    bool foldedEars; // признак вислоухости (для примера)

public:
    ScottishFold() : Cat() {
        cout << "[ScottishFold] Конструктор без параметров, адрес: " << this << endl;
        foldedEars = true;
    }

    ScottishFold(string name, string sex, int age, double weight, bool foldedEars)
        : Cat(name, sex, age, weight) {
        cout << "[ScottishFold] Конструктор с параметрами, адрес: " << this << endl;
        this->foldedEars = foldedEars;
    }

    ScottishFold(const ScottishFold &other)
        : Cat(other) {
        cout << "[ScottishFold] Конструктор копирования, адрес: " << this << endl;
        foldedEars = other.foldedEars;
    }

    ~ScottishFold() override {
        cout << "[ScottishFold] Деструктор, адрес: " << this << endl;
    }

    void set_foldedEars(bool f) { foldedEars = f; }
    bool get_foldedEars() const { return foldedEars; }

    // Общие методы
    void play() override {
        cout << "Шотландская вислоухая " << name << " лениво играет с мячиком." << endl;
    }

    void feed() override {
        cout << "Шотландская вислоухая " << name << " ест корм и довольно мурчит." << endl;
    }

    void pet() override {
        cout << "Шотландская вислоухая " << name << " подставляет ушки, чтобы её почесали." << endl;
    }

    void judgmentalLook() override {
        cout << "Шотландская " << name << " смотрит снизу вверх, как будто что-то подозревает." << endl;
    }

    void classname() override {
        cout << "Класс: ScottishFold (Шотландская вислоухая)" << endl;
    }

    void info() override {
        cout << "+=================================================+" << endl;
        cout << "| Тип: Шотландская вислоухая                      |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Имя: "     << setw(35 + name.length()/2) << left << name << "|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Пол: "     << setw(35 + sex.length()/2)  << left << sex  << "|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Возраст: " << setw(29) << left << age    << "| лет|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Вес: "     << setw(34) << left << weight << "| кг |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Ушки вислоухие: " << setw(19) << left << (foldedEars ? "Да" : "Нет") << "|" << endl;
        cout << "+=================================================+" << endl;
    }

    // Уникальный метод
    void curlEars() {
        cout << "Уникальный метод ScottishFold: " << endl;
        cout << name << " мило прижимает свои вислоухие ушки." << endl;
    }
};

// Мейн-кун 
class MaineCoon : public Cat {
private:
    double tailLength; // длина хвоста

public:
    MaineCoon() : Cat() {
        cout << "[MaineCoon] Конструктор без параметров, адрес: " << this << endl;
        tailLength = 0.0;
    }

    MaineCoon(string name, string sex, int age, double weight, double tailLength)
        : Cat(name, sex, age, weight) {
        cout << "[MaineCoon] Конструктор с параметрами, адрес: " << this << endl;
        this->tailLength = tailLength;
    }

    MaineCoon(const MaineCoon &other)
        : Cat(other) {
        cout << "[MaineCoon] Конструктор копирования, адрес: " << this << endl;
        tailLength = other.tailLength;
    }

    ~MaineCoon() override {
        cout << "[MaineCoon] Деструктор, адрес: " << this << endl;
    }

    void set_tailLength(double l) { tailLength = (l < 0 ? 0 : l); }
    double get_tailLength() const { return tailLength; }

    void play() override {
        cout << "Мейн-кун " << name << " громко носится по комнате, как маленький тигр." << endl;
    }

    void feed() override {
        cout << "Мейн-кун " << name << " с аппетитом поедает большую порцию корма." << endl;
    }

    void pet() override {
        cout << "Мейн-кун " << name << " урчит как трактор, когда его гладят." << endl;
    }

    void judgmentalLook() override {
        cout << "Мейн-кун " << name << " смотрит свысока, будто он хозяин квартиры." << endl;
    }

    void classname() override {
        cout << "Класс: MaineCoon (Мейн-кун)" << endl;
    }

    void info() override {
        cout << "+=================================================+" << endl;
        cout << "| Тип: Мейн-кун                                   |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Имя: "     << setw(35 + name.length()/2) << left << name << "|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Пол: "     << setw(35 + sex.length()/2)  << left << sex  << "|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Возраст: " << setw(29) << left << age    << "| лет|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Вес: "     << setw(34) << left << weight << "| кг |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Длина хвоста: " << setw(23) << left << tailLength << "| см|" << endl;
        cout << "+=================================================+" << endl;
    }

    // Уникальный метод
    void huntMouse() {
        cout << "Уникальный метод MaineCoon: " << endl;
        cout << name << " охотится на воображаемую мышь и гордо приносит её тебе." << endl;
    }
};

// Персидская
class Persian : public Cat {
private:
    double furLength; // длина шерсти

public:
    Persian() : Cat() {
        cout << "[Persian] Конструктор без параметров, адрес: " << this << endl;
        furLength = 0.0;
    }

    Persian(string name, string sex, int age, double weight, double furLength)
        : Cat(name, sex, age, weight) {
        cout << "[Persian] Конструктор с параметрами, адрес: " << this << endl;
        this->furLength = furLength;
    }

    Persian(const Persian &other)
        : Cat(other) {
        cout << "[Persian] Конструктор копирования, адрес: " << this << endl;
        furLength = other.furLength;
    }

    ~Persian() override {
        cout << "[Persian] Деструктор, адрес: " << this << endl;
    }

    void set_furLength(double l) { furLength = (l < 0 ? 0 : l); }
    double get_furLength() const { return furLength; }

    void play() override {
        cout << "Персидская кошка " << name << " нехотя гоняется за ленточкой." << endl;
    }

    void feed() override {
        cout << "Персидская кошка " << name << " ест только самый изысканный корм." << endl;
    }

    void pet() override {
        cout << "Персидская кошка " << name << " позволяет себя гладить по пушистой шерсти." << endl;
    }

    void judgmentalLook() override {
        cout << "Персидская " << name << " смотрит на тебя как на недостойного слугу." << endl;
    }

    void classname() override {
        cout << "Класс: Persian (Персидская кошка)" << endl;
    }

    void info() override {
        cout << "+=================================================+" << endl;
        cout << "| Тип: Персидская кошка                          |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Имя: "     << setw(35 + name.length()/2) << left << name << "|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Пол: "     << setw(35 + sex.length()/2)  << left << sex  << "|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Возраст: " << setw(29) << left << age    << "| лет|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Вес: "     << setw(34) << left << weight << "| кг |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Длина шерсти: " << setw(23) << left << furLength << "| см|" << endl;
        cout << "+=================================================+" << endl;
    }

    // Уникальный метод
    void combFur() {
        cout << "Уникальный метод Persian: " << endl;
        cout << name << " позволяет расчёсывать свою длинную шерсть (но недолго)." << endl;
    }
};

// Сфинкс 
class Sphynx : public Cat {
private:
    string skinColor; // цвет кожи

public:
    Sphynx() : Cat() {
        cout << "[Sphynx] Конструктор без параметров, адрес: " << this << endl;
        skinColor = "";
    }

    Sphynx(string name, string sex, int age, double weight, string skinColor)
        : Cat(name, sex, age, weight) {
        cout << "[Sphynx] Конструктор с параметрами, адрес: " << this << endl;
        this->skinColor = skinColor;
    }

    Sphynx(const Sphynx &other)
        : Cat(other) {
        cout << "[Sphynx] Конструктор копирования, адрес: " << this << endl;
        skinColor = other.skinColor;
    }

    ~Sphynx() override {
        cout << "[Sphynx] Деструктор, адрес: " << this << endl;
    }

    void set_skinColor(const string &c) { skinColor = c; }
    string get_skinColor() const { return skinColor; }

    void play() override {
        cout << "Сфинкс " << name << " активно бегает и прыгает по квартире." << endl;
    }

    void feed() override {
        cout << "Сфинкс " << name << " благодарно доедает всё до крошки." << endl;
    }

    void pet() override {
        cout << "Сфинкс " << name << " тёплый и гладкий, как грелка." << endl;
    }

    void judgmentalLook() override {
        cout << "Сфинкс " << name << " смотрит на тебя, будто ты забыл включить отопление." << endl;
    }

    void classname() override {
        cout << "Класс: Sphynx (Сфинкс)" << endl;
    }

    void info() override {
        cout << "+=================================================+" << endl;
        cout << "| Тип: Сфинкс                                     |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Имя: "     << setw(35 + name.length()/2) << left << name << "|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Пол: "     << setw(35 + sex.length()/2)  << left << sex  << "|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Возраст: " << setw(29) << left << age    << "| лет|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Вес: "     << setw(34) << left << weight << "| кг |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Цвет кожи: " << setw(27 + skinColor.length()/2) << left << skinColor << "|" << endl;
        cout << "+=================================================+" << endl;
    }

    // Уникальный метод
    void putOnSweater() {
        cout << "Уникальный метод Sphynx: " << endl;
        cout << name << " одел уютный свитер и выглядит очень стильно." << endl;
    }
};

// Вспомогательные функции
void pauseConsole() {
#ifdef _WIN32
    system("pause");
#else
    system("read -n 1 -s -p \"Нажмите enter, чтобы продолжить..\"; echo");
#endif
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Cat*> cats_array;
    // 6 стартовых кошек
    cats_array.push_back(new ScottishFold("Мурка", "кошка", 2, 3.5, true));
    cats_array.push_back(new MaineCoon("Барсик", "кот", 4, 7.2, 35.0));
    cats_array.push_back(new Persian("Снежок", "кот", 3, 4.1, 15.0));
    cats_array.push_back(new Sphynx("Лысик", "кот", 5, 4.0, "розовый"));
    cats_array.push_back(new ScottishFold("Луна", "кошка", 1, 2.8, true));
    cats_array.push_back(new MaineCoon("Рыжик", "кот", 6, 8.0, 38.0));

    int user = 0;

    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        cout << "+=================================================+" << endl;
        cout << "| ГЛАВНОЕ МЕНЮ                                    |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "|1 - Добавить новую кошку.                        |" << endl;
        cout << "|2 - Краткие сведения о каждой кошке.             |" << endl;
        cout << "|3 - Работа с выбранной кошкой (info/play/pet).   |" << endl;
        cout << "|4 - Поиграть со всеми кошками (метод play).      |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "|5 - Выход.                                       |" << endl;
        cout << "+=================================================+" << endl;
        cin >> user;

        switch (user) {
            case 1: {
                int typeChoice;
                do {
#ifdef _WIN32
                    system("cls");
#else
                    system("clear");
#endif
                    cout << "Какую кошку вы хотите добавить?" << endl;
                    cout << "+=========================================+" << endl;
                    cout << "|1 - Шотландская вислоухая (ScottishFold) |" << endl;
                    cout << "|2 - Мейн-кун (MaineCoon)                 |" << endl;
                    cout << "|3 - Персидская (Persian)                 |" << endl;
                    cout << "|4 - Сфинкс (Sphynx)                      |" << endl;
                    cout << "+-----------------------------------------+" << endl;
                    cout << "|5 - Выход в главное меню                 |" << endl;
                    cout << "+=========================================+" << endl;
                    cin >> typeChoice;

                    if (typeChoice >= 1 && typeChoice <= 4) {
                        string name, sex;
                        int age;
                        double weight;

                        cout << "Введите имя: ";
                        cin >> ws;
                        getline(cin, name);
                        cout << "Введите пол (кот/кошка): ";
                        getline(cin, sex);
                        cout << "Введите возраст: ";
                        cin >> age;
                        cout << "Введите вес: ";
                        cin >> weight;

                        switch (typeChoice) {
                            case 1: {
                                bool folded;
                                int temp;
                                cout << "Ушки вислоухие? (1 - да, 0 - нет): ";
                                cin >> temp;
                                folded = (temp != 0);
                                cats_array.push_back(new ScottishFold(name, sex, age, weight, folded));
                                break;
                            }
                            case 2: {
                                double tail;
                                cout << "Введите длину хвоста (см): ";
                                cin >> tail;
                                cats_array.push_back(new MaineCoon(name, sex, age, weight, tail));
                                break;
                            }
                            case 3: {
                                double fur;
                                cout << "Введите длину шерсти (см): ";
                                cin >> fur;
                                cats_array.push_back(new Persian(name, sex, age, weight, fur));
                                break;
                            }
                            case 4: {
                                string skin;
                                cout << "Введите цвет кожи: ";
                                cin >> ws;
                                getline(cin, skin);
                                cats_array.push_back(new Sphynx(name, sex, age, weight, skin));
                                break;
                            }
                        }
                        pauseConsole();
                    } else if (typeChoice != 5) {
                        cout << "Неверный выбор типа кошки!" << endl;
                        pauseConsole();
                    }
                } while (typeChoice != 5);
                break;
            }

            case 2: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                cout << "Найдено кошек: " << cats_array.size() << endl;
                for (size_t i = 0; i < cats_array.size(); ++i) {
                    cout << "Номер записи: " << i << endl;
                    cout << *cats_array[i];
                    pauseConsole();
#ifdef _WIN32
                    system("cls");
#else
                    system("clear");
#endif
                }
                break;
            }

            case 3: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                int indexChoice;
                cout << "Выберите номер кошки (0.." << cats_array.size() - 1 << "): ";
                cin >> indexChoice;
                if (indexChoice < 0 || indexChoice >= (int)cats_array.size()) {
                    cout << "Неверный номер!" << endl;
                    pauseConsole();
                    break;
                }

                int user3 = 0;
                do {
#ifdef _WIN32
                    system("cls");
#else
                    system("clear");
#endif
                    cout << "+=================================================+" << endl;
                    cout << "| Работа с объектом:                              |" << endl;
                    cats_array[indexChoice]->classname();
                    cout << "+-------------------------------------------------+" << endl;
                    cout << "|1 - Дополнительная информация (info).            |" << endl;
                    cout << "|2 - Поиграть (play).                             |" << endl;
                    cout << "|3 - Погладить (pet).                             |" << endl;
                    cout << "|4 - Покормить (feed).                            |" << endl;
                    cout << "|5 - Получить осуждающий взгляд.                  |" << endl;
                    cout << "|6 - Уникальный метод класса.                     |" << endl;
                    cout << "+-------------------------------------------------+" << endl;
                    cout << "|7 - Выход.                                       |" << endl;
                    cout << "+=================================================+" << endl;
                    cin >> user3;

                    switch (user3) {
                        case 1:
                            cats_array[indexChoice]->info();
                            pauseConsole();
                            break;
                        case 2:
                            cats_array[indexChoice]->play();
                            pauseConsole();
                            break;
                        case 3:
                            cats_array[indexChoice]->pet();
                            pauseConsole();
                            break;
                        case 4:
                            cats_array[indexChoice]->feed();
                            pauseConsole();
                            break;
                        case 5:
                            cats_array[indexChoice]->judgmentalLook();
                            pauseConsole();
                            break;
                        case 6: {
#ifdef _WIN32
                            system("cls");
#else
                            system("clear");
#endif
                            Cat *basePtr = cats_array[indexChoice];

                            // Сначала проверяем тип через typeid, затем dynamic_cast
                            if (typeid(*basePtr) == typeid(ScottishFold)) {
                                if (auto ptr = dynamic_cast<ScottishFold*>(basePtr))
                                    ptr->curlEars();
                            } else if (typeid(*basePtr) == typeid(MaineCoon)) {
                                if (auto ptr = dynamic_cast<MaineCoon*>(basePtr))
                                    ptr->huntMouse();
                            } else if (typeid(*basePtr) == typeid(Persian)) {
                                if (auto ptr = dynamic_cast<Persian*>(basePtr))
                                    ptr->combFur();
                            } else if (typeid(*basePtr) == typeid(Sphynx)) {
                                if (auto ptr = dynamic_cast<Sphynx*>(basePtr))
                                    ptr->putOnSweater();
                            } else {
                                cout << "Неизвестный тип кошки." << endl;
                            }
                            pauseConsole();
                            break;
                        }
                        case 7:
                            break;
                        default:
                            cout << "Неверный пункт меню!" << endl;
                            pauseConsole();
                            break;
                    }

                } while (user3 != 7);

                break;
            }

            case 4: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                cout << "Поиграем со всеми кошками:" << endl;
                cout << "--------------------------" << endl;
                for (size_t i = 0; i < cats_array.size(); ++i) {
                    cout << "Кошка #" << i << ": ";
                    cats_array[i]->classname();
                    cats_array[i]->play(); // общий метод базового класса (виртуальный)
                    cout << endl;
                }
                pauseConsole();
                break;
            }

            case 5:
                cout << "Завершение работы." << endl;
                break;

            default:
                cout << "Неверный пункт меню!" << endl;
                pauseConsole();
                break;
        }

    } while (user != 5);

    // Освобождаем память
    for (Cat* c : cats_array) {
        delete c;
    }

    return 0;
}
