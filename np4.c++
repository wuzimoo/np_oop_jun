#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

enum Priority { Low, Medium, High };
enum Status { New, InProgress, Deferred, Done, Sent, Returned };
enum Subject { Programming, Math, Physics, Other };

string getPriorityName(Priority p) {
    switch (p) {
        case Low: return "Низький";
        case Medium: return "Середній";
        case High: return "Високий";
    }
    return "";
}

string getStatusName(Status s) {
    switch (s) {
        case New: return "Новий";
        case InProgress: return "Виконується";
        case Deferred: return "Відкладено";
        case Done: return "Виконано";
        case Sent: return "Відправлено";
        case Returned: return "Повернено з оцінкою";
    }
    return "";
}

string getSubjectName(Subject s) {
    switch (s) {
        case Programming: return "Програмування";
        case Math: return "Математика";
        case Physics: return "Фізика";
        case Other: return "Інше";
    }
    return "";
}

class Event {
protected:
    static int nextID;
    int id;
    time_t created;
    string description;
    string date;
    Priority priority;
    Status status;

public:
    Event(string desc, string d, Priority p, Status s) {
        id = nextID++;
        time(&created);
        description = desc;
        date = d;
        priority = p;
        status = s;
    }

    virtual void display() const {
        cout << "ID: " << id << endl;
        cout << "Зареєстровано: " << ctime(&created);
        cout << "Дата події: " << date << endl;
        cout << "Пріоритет: " << getPriorityName(priority) << endl;
        cout << "Стан: " << getStatusName(status) << endl;
        cout << "Опис: " << description << endl;
    }

    virtual bool isToday(const string& today) const {
        return date == today;
    }

    virtual bool isHighPriority() const {
        return priority == High;
    }

    virtual Status getStatus() const { return status; }
    virtual string getDate() const { return date; }
};

int Event::nextID = 1;

class Task : public Event {
    Subject subject;
    int estimatedTime;
    int mark;

public:
    Task(string desc, string d, Priority p, Status s, Subject subj, int time, int m)
        : Event(desc, d, p, s), subject(subj), estimatedTime(time), mark(m) {}

    void display() const override {
        Event::display();
        cout << "Дисципліна: " << getSubjectName(subject) << endl;
        cout << "Орієнтовний час: " << estimatedTime << " год." << endl;
        cout << "Оцінка: " << mark << endl;
    }
};

void showMenu() {
    cout << "====== МЕНЕДЖЕР ЗАДАЧ ======" << endl;
    cout << "1. Додати нову подію" << endl;
    cout << "2. Додати нове завдання" << endl;
    cout << "3. Показати задачі на сьогодні" << endl;
    cout << "4. Показати задачі у статусі 'виконується' або 'відкладено'" << endl;
    cout << "5. Показати прострочені невиконані задачі" << endl;
    cout << "6. Показати задачі з найвищим пріоритетом за період" << endl;
    cout << "7. Показати всі події та задачі" << endl;
    cout << "0. Вихід з програми" << endl;
    cout << "=============================" << endl;
    cout << "Оберіть пункт меню: ";
}

int main() {
    vector<Event*> events;
    int choice;
    string today = "2025-06-05"; // для демонстрації

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string desc, date;
            int p, s;
            cout << "Введіть опис події: "; getline(cin, desc);
            cout << "Введіть дату (у форматі РРРР-ММ-ДД): "; getline(cin, date);
            cout << "Пріоритет (0-низький, 1-середній, 2-високий): "; cin >> p;
            cout << "Стан (0-новий, 1-виконується, 2-відкладено, 3-виконано): "; cin >> s;
            events.push_back(new Event(desc, date, (Priority)p, (Status)s));

        } else if (choice == 2) {
            string desc, date;
            int p, s, subj, time, mark;
            cout << "Введіть опис завдання: "; getline(cin, desc);
            cout << "Введіть дату: "; getline(cin, date);
            cout << "Пріоритет (0-низький, 1-середній, 2-високий): "; cin >> p;
            cout << "Стан (0-новий, 1-виконується, 2-відкладено, 3-виконано, 4-відправлено, 5-повернено): "; cin >> s;
            cout << "Дисципліна (0-програмування, 1-математика, 2-фізика, 3-інше): "; cin >> subj;
            cout << "Орієнтовний час (години): "; cin >> time;
            cout << "Оцінка: "; cin >> mark;
            cin.ignore();
            events.push_back(new Task(desc, date, (Priority)p, (Status)s, (Subject)subj, time, mark));

        } else if (choice == 3) {
            cout << "\nЗадачі на сьогодні (" << today << "):" << endl;
            for (auto e : events)
                if (e->isToday(today)) e->display(), cout << "-------------------\n";

        } else if (choice == 4) {
            cout << "\nЗадачі у статусі 'виконується' або 'відкладено':" << endl;
            for (auto e : events) {
                Status s = e->getStatus();
                if (s == InProgress || s == Deferred) e->display(), cout << "-------------------\n";
            }

        } else if (choice == 5) {
            cout << "\nПрострочені невиконані задачі:" << endl;
            for (auto e : events)
                if (e->getDate() < today && e->getStatus() != Done) e->display(), cout << "-------------------\n";

        } else if (choice == 6) {
            string from, to;
            cout << "Введіть початкову дату: "; cin >> from;
            cout << "Введіть кінцеву дату: "; cin >> to;
            cin.ignore();
            cout << "\nЗадачі з високим пріоритетом за період:" << endl;
            for (auto e : events) {
                if (e->isHighPriority() && e->getDate() >= from && e->getDate() <= to)
                    e->display(), cout << "-------------------\n";
            }

        } else if (choice == 7) {
            cout << "\nВСІ ЗАДАЧІ І ПОДІЇ:" << endl;
            for (auto e : events) e->display(), cout << "-------------------\n";
        }

    } while (choice != 0);

    for (auto e : events) delete e;
    return 0;
}
