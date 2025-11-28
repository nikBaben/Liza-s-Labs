#include <iostream>
#include <limits>

using namespace std;

// Макрос для очистки экрана
#ifdef _WIN32
    #define CLEAR_CONSOLE() system("cls")
#else
    #define CLEAR_CONSOLE() system("clear")
#endif

// Вспомогательная функция для паузы
void pauseConsole() {
#ifdef _WIN32
    system("pause");
#else
    system("read -n 1 -s -p \"Нажмите enter, чтобы продолжить..\"; echo");
#endif
}

// ЧАСТЬ 1. Шаблон функции
// Шаблон функции: заменить нечётные по номеру (1-based) элементы массива на нули.
template<typename Type>
void zeroOddIndexedElements(Type arr[], int size) {
    for (int i = 0; i < size; ++i) {
        if (i % 2 == 0) { // индексы 0,2,4,... -> номера 1,3,5...
            arr[i] = 0;
        }
    }
}

// Шаблон функции для тестирования: вывод до и после обработки
template<typename Type>
void testArray(Type array[], int size) {
    cout << "Начальный массив: ";
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;

    zeroOddIndexedElements(array, size);

    cout << "Массив после замены нечётных по номеру элементов на нули: ";
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// ЧАСТЬ 2. Шаблон класса (Стек)
template<typename Type>
class Stack {
    struct Node {
        Type value;
        Node* next;
        Node(const Type& v) : value(v), next(nullptr) {}
    };

private:
    Node* topNode;
    size_t stackSize;

public:
    Stack() : topNode(nullptr), stackSize(0) {}

    Stack(const Stack& other) : topNode(nullptr), stackSize(0) {
        if (other.topNode == nullptr) return;

        Node* cur = other.topNode;
        size_t count = 0;
        while (cur) {
            ++count;
            cur = cur->next;
        }

        Type* tmp = new Type[count];
        cur = other.topNode;
        for (size_t i = 0; i < count; ++i) {
            tmp[i] = cur->value;
            cur = cur->next;
        }

        for (int i = (int)count - 1; i >= 0; --i) {
            push(tmp[i]);
        }

        delete[] tmp;
    }

    Stack& operator=(const Stack& other) {
        if (this == &other) return *this;

        clear();

        if (other.topNode == nullptr) return *this;

        Node* cur = other.topNode;
        size_t count = 0;
        while (cur) {
            ++count;
            cur = cur->next;
        }

        Type* tmp = new Type[count];
        cur = other.topNode;
        for (size_t i = 0; i < count; ++i) {
            tmp[i] = cur->value;
            cur = cur->next;
        }

        for (int i = (int)count - 1; i >= 0; --i) {
            push(tmp[i]);
        }

        delete[] tmp;
        return *this;
    }

    ~Stack() {
        clear();
    }

    void push(const Type& value) {
        Node* p = new Node(value);
        p->next = topNode;
        topNode = p;
        ++stackSize;
    }

    void pop() {
        if (topNode != nullptr) {
            Node* t = topNode;
            topNode = topNode->next;
            delete t;
            --stackSize;
        } else {
            cout << "Стек пуст, удалять нечего!" << endl;
        }
    }

    Type& top() {
        return topNode->value;
    }

    const Type& top() const {
        return topNode->value;
    }

    bool empty() const {
        return topNode == nullptr;
    }

    size_t sizeStack() const {
        return stackSize;
    }

    void clear() {
        while (topNode != nullptr) {
            Node* t = topNode;
            topNode = topNode->next;
            delete t;
        }
        stackSize = 0;
    }

    void printStack() const {
        if (topNode == nullptr) {
            cout << "Стек пуст." << endl;
            return;
        }

        cout << "Содержимое стека (с вершины вниз): ";
        Node* cur = topNode;
        while (cur != nullptr) {
            cout << cur->value << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

// безопасный ввод int
int readInt() {
    int x;
    while (true) {
        cin >> x;
        if (cin) return x;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Вы ввели не целое число! Повторите ввод: ";
    }
}

// безопасный ввод float
float readFloat() {
    float x;
    while (true) {
        cin >> x;
        if (cin) return x;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Вы ввели не число с плавающей точкой! Повторите ввод: ";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int user = 0, user1 = 0, user2 = 0, userType = 0;

    Stack<int>   intStack;
    Stack<float> floatStack;

    do {
        CLEAR_CONSOLE();
        cout << "+=========================================+" << endl;
        cout << "| Главное меню                            |" << endl;
        cout << "+-----------------------------------------+" << endl;
        cout << "|1 - Шаблон класса (Стек, связный)        |" << endl;
        cout << "|2 - Шаблон функции (массив)              |" << endl;
        cout << "+-----------------------------------------+" << endl;
        cout << "|3 - Завершение работы                    |" << endl;
        cout << "+=========================================+" << endl;
        cin >> user;

        switch (user) {
            case 1: {
                do {
                    CLEAR_CONSOLE();
                    cout << "+=========================================+" << endl;
                    cout << "| Шаблон класса: Стек                     |" << endl;
                    cout << "+-----------------------------------------+" << endl;
                    cout << "|1 - Тип данных INT                       |" << endl;
                    cout << "|2 - Тип данных FLOAT                     |" << endl;
                    cout << "+-----------------------------------------+" << endl;
                    cout << "|3 - Назад                                |" << endl;
                    cout << "+=========================================+" << endl;
                    cin >> userType;

                    switch (userType) {
                        case 1: {
                            do {
                                CLEAR_CONSOLE();
                                cout << "+=========================================+" << endl;
                                cout << "| Тип данных: int                         |" << endl;
                                cout << "+-----------------------------------------+" << endl;
                                cout << "|1 - Добавить элемент (push)              |" << endl;
                                cout << "|2 - Удалить элемент (pop)                |" << endl;
                                cout << "|3 - Показать верхний элемент (top)       |" << endl;
                                cout << "|4 - Показать все элементы                |" << endl;
                                cout << "|5 - Очистить стек                        |" << endl;
                                cout << "|6 - Показать размер стека                |" << endl;
                                cout << "+-----------------------------------------+" << endl;
                                cout << "|7 - Назад                                |" << endl;
                                cout << "+=========================================+" << endl;
                                cin >> user1;

                                switch (user1) {
                                    case 1: {
                                        CLEAR_CONSOLE();
                                        cout << "Введите целое число для добавления в стек: ";
                                        int value = readInt();
                                        intStack.push(value);
                                        cout << "Элемент добавлен в стек." << endl;
                                        pauseConsole();
                                        break;
                                    }
                                    case 2: {
                                        CLEAR_CONSOLE();
                                        intStack.pop();
                                        pauseConsole();
                                        break;
                                    }
                                    case 3: {
                                        CLEAR_CONSOLE();
                                        if (!intStack.empty()) {
                                            cout << "Верхний элемент стека: " << intStack.top() << endl;
                                        } else {
                                            cout << "Стек пуст." << endl;
                                        }
                                        pauseConsole();
                                        break;
                                    }
                                    case 4: {
                                        CLEAR_CONSOLE();
                                        intStack.printStack();
                                        pauseConsole();
                                        break;
                                    }
                                    case 5: {
                                        CLEAR_CONSOLE();
                                        intStack.clear();
                                        cout << "Стек очищен." << endl;
                                        pauseConsole();
                                        break;
                                    }
                                    case 6: {
                                        CLEAR_CONSOLE();
                                        cout << "Размер стека: " << intStack.sizeStack() << endl;
                                        pauseConsole();
                                        break;
                                    }
                                }

                            } while (user1 != 7);
                            break;
                        }

                        case 2: {
                            do {
                                CLEAR_CONSOLE();
                                cout << "+=========================================+" << endl;
                                cout << "| Тип данных: float                       |" << endl;
                                cout << "+-----------------------------------------+" << endl;
                                cout << "|1 - Добавить элемент (push)              |" << endl;
                                cout << "|2 - Удалить элемент (pop)                |" << endl;
                                cout << "|3 - Показать верхний элемент (top)       |" << endl;
                                cout << "|4 - Показать все элементы                |" << endl;
                                cout << "|5 - Очистить стек                        |" << endl;
                                cout << "|6 - Показать размер стека                |" << endl;
                                cout << "+-----------------------------------------+" << endl;
                                cout << "|7 - Назад                                |" << endl;
                                cout << "+=========================================+" << endl;
                                cin >> user1;

                                switch (user1) {
                                    case 1: {
                                        CLEAR_CONSOLE();
                                        cout << "Введите число с плавающей точкой: ";
                                        float value = readFloat();
                                        floatStack.push(value);
                                        cout << "Элемент добавлен." << endl;
                                        pauseConsole();
                                        break;
                                    }
                                    case 2: {
                                        CLEAR_CONSOLE();
                                        floatStack.pop();
                                        pauseConsole();
                                        break;
                                    }
                                    case 3: {
                                        CLEAR_CONSOLE();
                                        if (!floatStack.empty()) {
                                            cout << "Верхний элемент: " << floatStack.top() << endl;
                                        } else {
                                            cout << "Стек пуст." << endl;
                                        }
                                        pauseConsole();
                                        break;
                                    }
                                    case 4: {
                                        CLEAR_CONSOLE();
                                        floatStack.printStack();
                                        pauseConsole();
                                        break;
                                    }
                                    case 5: {
                                        CLEAR_CONSOLE();
                                        floatStack.clear();
                                        cout << "Стек очищен." << endl;
                                        pauseConsole();
                                        break;
                                    }
                                    case 6: {
                                        CLEAR_CONSOLE();
                                        cout << "Размер: " << floatStack.sizeStack() << endl;
                                        pauseConsole();
                                        break;
                                    }
                                }

                            } while (user1 != 7);
                            break;
                        }
                    }

                } while (userType != 3);

                break;
            }

            case 2: {
                do {
                    CLEAR_CONSOLE();
                    cout << "+=========================================+" << endl;
                    cout << "| Шаблон функции                          |" << endl;
                    cout << "+-----------------------------------------+" << endl;
                    cout << "|1 - Тип INT                              |" << endl;
                    cout << "|2 - Тип FLOAT                            |" << endl;
                    cout << "+-----------------------------------------+" << endl;
                    cout << "|3 - Назад                                |" << endl;
                    cout << "+=========================================+" << endl;
                    cin >> user2;

                    switch (user2) {
                        case 1: {
                            CLEAR_CONSOLE();
                            cout << "Введите размер массива int: ";
                            int sizea;
                            cin >> sizea;
                            if (!cin || sizea <= 0) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Некорректный размер!" << endl;
                                pauseConsole();
                                break;
                            }

                            int* arr = new int[sizea];
                            cout << "Введите элементы: ";
                            for (int i = 0; i < sizea; ++i)
                                arr[i] = readInt();

                            cout << endl;
                            testArray(arr, sizea);

                            delete[] arr;
                            pauseConsole();
                            break;
                        }

                        case 2: {
                            CLEAR_CONSOLE();
                            cout << "Введите размер массива float: ";
                            int sizea;
                            cin >> sizea;

                            if (!cin || sizea <= 0) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Некорректный размер!" << endl;
                                pauseConsole();
                                break;
                            }

                            float* arr = new float[sizea];
                            cout << "Введите элементы: ";
                            for (int i = 0; i < sizea; ++i)
                                arr[i] = readFloat();

                            cout << endl;
                            testArray(arr, sizea);

                            delete[] arr;
                            pauseConsole();
                            break;
                        }
                    }

                } while (user2 != 3);
                break;
            }

            case 3:
                cout << "Завершение работы." << endl;
                break;

            default:
                cout << "Неверный пункт меню!" << endl;
                pauseConsole();
                break;
        }

    } while (user != 3);

    return 0;
}
