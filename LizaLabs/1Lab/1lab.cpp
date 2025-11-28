#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Cat {
private:
    string breed;       // порода
    string sex;         // пол
    int age;            // возраст
    string furColor;    // цвет шерсти

    bool isHungry;      // голодна ли кошка
    bool isPlayful;     // хочет ли играть

public:
    // Конструктор без параметров
    Cat() {
        cout << "[Cat] Вызван конструктор без параметров" << endl;
        setBreed("Беспородная");
        setSex("Неизвестен");
        setAge(1);
        setFurColor("Серая");
        isHungry = true;
        isPlayful = false;
    }

    // Конструктор с параметрами
    Cat(const string &breed, const string &sex, int age, const string &furColor) {
        cout << "[Cat] Вызван конструктор с параметрами" << endl;
        setBreed(breed);
        setSex(sex);
        setAge(age);
        setFurColor(furColor);
        isHungry = true;
        isPlayful = true;
    }

    // Конструктор копирования
    Cat(const Cat &other) {
        cout << "[Cat] Вызван конструктор копирования" << endl;
        breed = other.breed;
        sex = other.sex;
        age = other.age;
        furColor = other.furColor;
        isHungry = other.isHungry;
        isPlayful = other.isPlayful;
    }

    // Деструктор
    ~Cat() {
        cout << "[Cat] Вызван деструктор" << endl;
    }

    // Сеттеры
    void setBreed(const string &breed) {
        cout << "[Cat] Вызван метод setBreed" << endl;
        this->breed = breed;
    }

    void setSex(const string &sex) {
        cout << "[Cat] Вызван метод setSex" << endl;
        this->sex = sex;
    }

    void setAge(int age) {
        cout << "[Cat] Вызван метод setAge" << endl;
        if (age < 0) age = 0;
        this->age = age;
    }

    void setFurColor(const string &furColor) {
        cout << "[Cat] Вызван метод setFurColor" << endl;
        this->furColor = furColor;
    }

    // Геттеры
    string getBreed() const {
        cout << "[Cat] Вызван метод getBreed" << endl;
        return breed;
    }

    string getSex() const {
        cout << "[Cat] Вызван метод getSex" << endl;
        return sex;
    }

    int getAge() const {
        cout << "[Cat] Вызван метод getAge" << endl;
        return age;
    }

    string getFurColor() const {
        cout << "[Cat] Вызван метод getFurColor" << endl;
        return furColor;
    }

    // Метод "поиграть"
    void play() {
        cout << "[Cat] Вызван метод play" << endl;
        if (isHungry) {
            cout << "Кошка смотрит на тебя с укоризной: \"Сначала покорми, потом играй!\"" << endl;
        } else {
            cout << "Кошка бегает за игрушкой и радостно мурчит." << endl;
            isPlayful = false;
        }
    }

    // Метод "покормить"
    void feed() {
        cout << "[Cat] Вызван метод feed" << endl;
        if (!isHungry) {
            cout << "Кошка сыта и лениво отвернулась от миски." << endl;
        } else {
            cout << "Кошка жадно ест из миски. Теперь она сыта и довольна." << endl;
            isHungry = false;
            isPlayful = true;
        }
    }

    // Метод "погладить"
    void pet() {
        cout << "[Cat] Вызван метод pet" << endl;
        if (isHungry) {
            cout << "Кошка терпит поглаживания, но явно ждёт еду." << endl;
        } else {
            cout << "Кошка громко мурчит и трётся о твою руку." << endl;
            isPlayful = true;
        }
    }

    // Метод "получить осуждающий взгляд"
    void judgmentalLook() {
        cout << "[Cat] Вызван метод judgmentalLook" << endl;
        cout << "Кошка смотрит на тебя так, будто знает о тебе что-то, чего не знаешь ты." << endl;
    }

    // Операция присваивания
    Cat & operator=(const Cat &other) {
        cout << "[Cat] Вызван оператор =" << endl;
        if (this != &other) {
            breed = other.breed;
            sex = other.sex;
            age = other.age;
            furColor = other.furColor;
            isHungry = other.isHungry;
            isPlayful = other.isPlayful;
        }
        return *this;
    }

    // Операции сравнения
    bool operator==(const Cat &other) const {
        cout << "[Cat] Вызван оператор ==" << endl;
        return (breed == other.breed &&
                sex == other.sex &&
                age == other.age &&
                furColor == other.furColor);
    }

    bool operator!=(const Cat &other) const {
        cout << "[Cat] Вызван оператор !=" << endl;
        return !(*this == other);
    }

    // Унарный оператор "~" – рассказ о кошке
    void operator~() {
        cout << "[Cat] Вызван оператор ~" << endl;
        cout << "=== Рассказ о кошке ===" << endl;
        cout << "Порода: " << breed << endl;
        cout << "Пол: " << sex << endl;
        cout << "Возраст: " << age << " год(лет)" << endl;
        cout << "Цвет шерсти: " << furColor << endl;
        cout << "Кошка смотрит на тебя и..." << endl;

        // Немного "сюжета" с использованием методов
        pet();
        if (isHungry) {
            cout << "Но, кажется, она всё ещё голодна..." << endl;
            feed();
        }
        play();
        judgmentalLook();
        cout << "=======================" << endl;
    }

    // Унарный постфиксный "++" – выполнить случайный метод
    Cat operator++(int) {
        cout << "[Cat] Вызван постфиксный оператор ++" << endl;
        int choice = rand() % 4; // 0..3

        switch (choice) {
            case 0:
                cout << "Кошка решила поиграть." << endl;
                play();
                break;
            case 1:
                cout << "Кошка решила попросить еду." << endl;
                feed();
                break;
            case 2:
                cout << "Кошка решила, что её нужно погладить." << endl;
                pet();
                break;
            case 3:
                cout << "Кошка одарила тебя осуждающим взглядом." << endl;
                judgmentalLook();
                break;
        }
        // Возвращаем старое состояние (классический постфиксный ++)
        Cat temp(*this);
        return temp;
    }

    // Дружественные функции для ввода/вывода
    friend ostream & operator<<(ostream &ost, const Cat &c);
    friend istream & operator>>(istream &ist, Cat &c);
};

// Операция вывода
ostream & operator<<(ostream &ost, const Cat &c) {
    cout << "[Cat] Вызван оператор <<" << endl;
    ost << "=== Информация о кошке ===" << endl;
    ost << "Порода: " << c.breed << endl;
    ost << "Пол: " << c.sex << endl;
    ost << "Возраст: " << c.age << " год(лет)" << endl;
    ost << "Цвет шерсти: " << c.furColor << endl;
    ost << "Состояние: " 
        << (c.isHungry ? "голодна, " : "сыта, ")
        << (c.isPlayful ? "хочет играть" : "не хочет играть")
        << endl;
    ost << "==========================" << endl;
    return ost;
}

// Операция ввода
istream & operator>>(istream &ist, Cat &c) {
    cout << "[Cat] Вызван оператор >>" << endl;
    cout << "Введите породу: ";
    ist >> ws;
    getline(ist, c.breed);

    cout << "Введите пол (кот/кошка): ";
    getline(ist, c.sex);

    cout << "Введите возраст: ";
    ist >> c.age;
    ist.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Введите цвет шерсти: ";
    getline(ist, c.furColor);

    // При вводе пусть по умолчанию будет голодна и хочет играть
    c.isHungry = true;
    c.isPlayful = true;

    return ist;
}

// Простое меню (как в примере с конструктором)
void pauseConsole() {
#ifdef _WIN32
    system("pause");
#else
    system("read -n 1 -s -p \"Нажмите enter, чтобы продолжить..\"; echo");
#endif
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(nullptr)));

    Cat cat;      // основная кошка
    Cat cat2;     // вторая кошка для сравнения / присваивания

    cout << "Заполните данные для кошки 'cat':" << endl;
    cin >> cat;

    int choice = 0;
    while (choice != 10) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        cout << "========== МЕНЮ ==========" << endl;
        cout << "1 - Показать информацию о кошке" << endl;
        cout << "2 - Поиграть с кошкой" << endl;
        cout << "3 - Покормить кошку" << endl;
        cout << "4 - Погладить кошку" << endl;
        cout << "5 - Получить осуждающий взгляд" << endl;
        cout << "6 - Рассказ о кошке (оператор ~)" << endl;
        cout << "7 - Непредсказуемое действие (оператор ++)" << endl;
        cout << "8 - Ввести данные второй кошки и сравнить" << endl;
        cout << "9 - Присвоить cat = cat2" << endl;
        cout << "10 - Выход" << endl;
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "================================" << endl;
                cout << cat;
                cout << "================================" << endl;
                pauseConsole();
                break;

            case 2:
                cout << "================================" << endl;
                cat.play();
                cout << "================================" << endl;
                pauseConsole();
                break;

            case 3:
                cout << "================================" << endl;
                cat.feed();
                cout << "================================" << endl;
                pauseConsole();
                break;

            case 4:
                cout << "================================" << endl;
                cat.pet();
                cout << "================================" << endl;
                pauseConsole();
                break;

            case 5:
                cout << "================================" << endl;
                cat.judgmentalLook();
                cout << "================================" << endl;
                pauseConsole();
                break;

            case 6:
                cout << "================================" << endl;
                ~cat; // оператор ~
                cout << "================================" << endl;
                pauseConsole();
                break;

            case 7:
                cout << "================================" << endl;
                cat++; // постфиксный ++
                cout << "================================" << endl;
                pauseConsole();
                break;

            case 8:
                cout << "================================" << endl;
                cout << "Введите данные для второй кошки 'cat2':" << endl;
                cin >> cat2;
                cout << "Сравнение cat и cat2:" << endl;
                if (cat == cat2) {
                    cout << "Кошки одинаковы (по полям)." << endl;
                } else {
                    cout << "Кошки различаются." << endl;
                }
                cout << "================================" << endl;
                pauseConsole();
                break;

            case 9:
                cout << "================================" << endl;
                cout << "Присваиваем cat = cat2" << endl;
                cat = cat2;
                cout << "Теперь данные кошки 'cat':" << endl;
                cout << cat;
                cout << "================================" << endl;
                pauseConsole();
                break;

            case 10:
                cout << "================================" << endl;
                cout << "Программа завершена." << endl;
                cout << "================================" << endl;
                break;

            default:
                cout << "Такого варианта нет! Попробуйте ещё раз." << endl;
                pauseConsole();
                break;
        }
    }

    return 0;
}
