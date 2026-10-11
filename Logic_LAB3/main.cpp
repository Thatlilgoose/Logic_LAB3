#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include <limits>
using namespace std;


struct PriorityNode {
    string info;
    int priority;
    PriorityNode* next;

    PriorityNode(const string& val, int prio) : info(val), priority(prio), next(nullptr) {}
};


struct Node {
    string info;
    Node* next;

    Node(const string& val) : info(val), next(nullptr) {}
};


class PriorityQueue {
private:
    PriorityNode* head;

public:
    PriorityQueue() : head(nullptr) {}

    ~PriorityQueue() {
        while (head != nullptr) {
            PriorityNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    
    void enqueue(const string& val, int priority) {
        PriorityNode* newNode = new PriorityNode(val, priority);

        
        if (head == nullptr || priority > head->priority) {
            newNode->next = head;
            head = newNode;
            cout << "Элемент \"" << val << "\" (приоритет " << priority << ") добавлен.\n";
            return;
        }

       
        PriorityNode* current = head;
        while (current->next != nullptr && current->next->priority >= priority) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
        cout << "Элемент \"" << val << "\" (приоритет " << priority << ") добавлен.\n";
    }

    
    void change_priority(const string& val, int new_priority) {
        if (head == nullptr) {
            cout << "Очередь пуста\n";
            return;
        }
        int count = 0;
        PriorityNode* dummy = new PriorityNode("", 0);
        dummy->next = head;
        PriorityNode* current = dummy;

        while (head != nullptr && head->info == val) {
            PriorityNode* temp = head;
            head = head->next;
            delete temp;
            count++;
        }
        if (head != nullptr) {
            PriorityNode* current = head;
            while (current->next != nullptr) {
                if (current->next->info == val){
                    PriorityNode* temp = current->next;
                    current->next = temp->next;
                    delete temp;
                    count++;
                }else {
                    current = current->next;
                }
            }
        }
        if (count == 0) {
            cout << "Элемент с названием: " << val << "не найден.";
            return;
        }

        for (int i = 0; i < count; i++) {
            enqueue(val, new_priority);
        }
        cout << "Отредактировано элементов" << count << " Новый приоритет" << new_priority << "\n";
    }
    
    void dequeue() {
        if (head == nullptr) {
            cout << "Приоритетная очередь пуста!\n";
            return;
        }

        PriorityNode* temp = head;
        cout << "Извлечен элемент: " << temp->info << " (приоритет: " << temp->priority << ")\n";
        head = head->next;
        delete temp;
    }

  
    void display() const {
        if (head == nullptr) {
            cout << "Приоритетная очередь пуста.\n";
            return;
        }

        cout << "\n--- Содержимое приоритетной очереди ---\n";
        PriorityNode* current = head;
        while (current != nullptr) {
            cout << "Имя: " << current->info << " | Приоритет: " << current->priority << "\n";
            current = current->next;
        }
        cout << "--------------------------------------\n";
    }
};


class Queue {
private:
    Node* head;
    Node* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    ~Queue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

   
    void enqueue(const string& val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        cout << "Элемент \"" << val << "\" добавлен в очередь.\n";
    }

    void find(const string& val) {
        if (head == nullptr) {
            cout << "Очередь пуста\n";
            return;
        }

        cout << "Результаты поиска по зпросу" << val << "\n";
        Node* current = head;
        int count = 0;
        int position = 1;
        while (current != nullptr) {
            if (current->info.find(val) != string::npos) {
                cout << "Позиция: " << position << " |Имя: " << current->info << "\n";
                count++;
            }
            current = current->next;
            position++;
        }
        if (count == 0) {
            cout << "Элемент c названием: " << val << " не найден";
        }
    }
    
    void dequeue() {
        if (head == nullptr) {
            cout << "Очередь пуста!\n";
            return;
        }

        Node* temp = head;
        cout << "Извлечен элемент: " << temp->info << "\n";
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
    }

    
    void display() const {
        if (head == nullptr) {
            cout << "Очередь пуста.\n";
            return;
        }

        cout << "\n--- Содержимое очереди (FIFO) ---\n";
        Node* current = head;
        while (current != nullptr) {
            cout << "Имя: " << current->info << "\n";
            current = current->next;
        }
        cout << "----------------------------------\n";
    }
};


class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

   
    void push(const string& val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        cout << "Элемент \"" << val << "\" помещен в стек.\n";
    }

    
    void pop() {
        if (top == nullptr) {
            cout << "Стек пуст!\n";
            return;
        }

        Node* temp = top;
        cout << "Извлечен элемент: " << temp->info << "\n";
        top = top->next;
        delete temp;
    }

   
    void display() const {
        if (top == nullptr) {
            cout << "Стек пуст.\n";
            return;
        }

        cout << "\n--- Содержимое стека (LIFO) ---\n";
        Node* current = top;
        while (current != nullptr) {
            cout << "Имя: " << current->info << "\n";
            current = current->next;
        }
        cout << "-------------------------------\n";
    }
};


int main() {
    setlocale(LC_ALL, "rus");
    PriorityQueue pQueue;
    Queue queue;
    Stack stack;

    int choice = 0;
    while (choice != 4) {
        cout << "\n========== МЕНЮ ЛАБОРАТОРНОЙ РАБОТЫ №3 ==========\n";
        cout << "1. Работа с Приоритетной очередью\n";
        cout << "2. Работа с Обычной очередью (FIFO)\n";
        cout << "3. Работа со Стеком (LIFO)\n";
        cout << "4. Выход\n";
        cout << "Выберите структуру данных: ";
        if (!(cin >> choice)) {
            cout << "Введено не число\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        

        if (choice == 1) {
            int subChoice = 0;
            while (subChoice != 5) {
                cout << "\n--- ПРИОРИТЕТНАЯ ОЧЕРЕДЬ ---\n";
                cout << "1. Добавить элемент с приоритетом\n";
                cout << "2. Извлечь элемент (с высшим приоритетом)\n";
                cout << "3. Показать содержимое\n";
                cout << "4. Редактировать приоритет\n";
                cout << "5. Назад\n";
                cout << "Выберите действие: ";
                if (!(cin >> subChoice)) {
                    cout << "Введено не число\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (subChoice == 1) {
                    string name;
                    int prio;
                    cout << "Введите название объекта: ";
                    cin >> name;
                    cout << "Введите приоритет (целое число): ";
                    if (!(cin >> prio)) {
                        cout << "Введено не число\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    pQueue.enqueue(name, prio);
                }
                else if (subChoice == 2) {
                    pQueue.dequeue();
                }
                else if (subChoice == 3) {
                    pQueue.display();
                }
                else if (subChoice == 4) {
                    string name;
                    int new_prio;
                    cout << "Введите название объекта: ";
                    cin >> name;
                    cout << "Введите новый приоритет (целое число): ";
                    if (!(cin >> new_prio)) {
                        cout << "Введено не число\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    pQueue.change_priority(name, new_prio);
                }
            }
        }
        else if (choice == 2) {
            int subChoice = 0;
            while (subChoice != 5) {
                cout << "\n--- ОБЫЧНАЯ ОЧЕРЕДЬ (FIFO) ---\n";
                cout << "1. Добавить элемент (Enqueue)\n";
                cout << "2. Извлечь элемент (Dequeue)\n";
                cout << "3. Показать содержимое\n";
                cout << "4. Найти элемент\n";
                cout << "5. Назад\n";
                cout << "Выберите действие: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    string name;
                    cout << "Введите название объекта: ";
                    cin >> name;
                    queue.enqueue(name);
                }
                else if (subChoice == 2) {
                    queue.dequeue();
                }
                else if (subChoice == 3) {
                    queue.display();
                }
                else if (subChoice == 4) {
                    string name;
                    cout << "Введите имя: ";
                    cin >> name;
                    queue.find(name);
                    
                }
            }
        }
        else if (choice == 3) {
            int subChoice = 0;
            while (subChoice != 4) {
                cout << "\n--- СТЕК (LIFO) ---\n";
                cout << "1. Поместить элемент (Push)\n";
                cout << "2. Извлечь элемент (Pop)\n";
                cout << "3. Показать содержимое\n";
                cout << "4. Назад\n";
                cout << "Выберите действие: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    string name;
                    cout << "Введите название объекта: ";
                    cin >> name;
                    stack.push(name);
                }
                else if (subChoice == 2) {
                    stack.pop();
                }
                else if (subChoice == 3) {
                    stack.display();
                }
                
            }
        }
        
    }

    cout << "Программа завершена.\n";
    return 0;
}


