//
//  np1.cpp
//  labs_oop
//
//  Created by Даниил Бологан on 05.06.2025.
//

#include <iostream>
#include <string>
using namespace std;

// Оголошення Product
class Product {
private:
    string name;
    int quantity;
    double cost;

public:
    // Конструктор за замовчуванням
    Product() {
        name = "Невідомо";
        quantity = 0;
        cost = 0.0;
    }

    // Конструктор з параметрами
    Product(string n, int q, double c) {
        name = n;
        quantity = q;
        cost = c;
    }

    // Селектори (гетери)
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getCost() const { return cost; }

    // Мутатори (сетери)
    void setName(string n) { name = n; }
    void setQuantity(int q) { quantity = q; }
    void setCost(double c) { cost = c; }

    // Функціональний метод: підрахунок загальної вартості
    double totalPrice() const {
        return quantity * cost;
    }

    // Метод для виводу інформації про товар
    void display() const {
        cout << "Назва товару: " << name << endl;
        cout << "Кількість: " << quantity << endl;
        cout << "Ціна за одиницю: " << cost << " грн" << endl;
        cout << "Загальна вартість: " << totalPrice() << " грн" << endl;
    }
};

// Головна функція
int main() {
    // Створення об'єкту за замовчуванням
    Product defaultProduct;
    cout << "Об'єкт за замовчуванням:\n";
    defaultProduct.display();
    cout << "-----------------------\n";

    // Створення об'єкту з параметрами
    Product customProduct("Хліб", 5, 20);
    cout << "Об'єкт з параметрами:\n";
    customProduct.display();
    cout << "-----------------------\n";

    // Зміна значень через методи
    defaultProduct.setName("Молоко");
    defaultProduct.setQuantity(10);
    defaultProduct.setCost(34.99);
    cout << "Оновлений об'єкт:\n";
    defaultProduct.display();

    return 0;
}
