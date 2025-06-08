//
//  np3.c++
//  labs_oop
//
//  Created by Даниил Бологан on 08.06.2025.
//
#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Product {
private:
    string name;
    int quantity;
    double cost;

public:
    Product() : name(""), quantity(0), cost(0.0) {}

    Product(string n, int q, double c) {
        name = n;
        quantity = q;
        cost = c;
    }

    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getCost() const { return cost; }

    void show() const {
        cout << "Назва: " << name << ", Кількість: " << quantity << ", Ціна: " << cost << " грн" << endl;
    }
};

class Shop {
private:
    vector<Product> products;

public:
    void addProduct(const Product& p) {
        products.push_back(p);
        cout << "Продукт додано!\n";
    }

    void findByName(const string& name) const {
        bool found = false;
        for (const auto& product : products) {
            if (product.getName() == name) {
                product.show();
                found = true;
            }
        }
        if (!found) {
            cout << "Товар з назвою \"" << name << "\" не знайдено.\n";
        }
    }

    void findMinCostProduct() const {
        if (products.empty()) {
            cout << "Список товарів порожній.\n";
            return;
        }

        const Product* minProduct = &products[0];
        for (const auto& product : products) {
            if (product.getCost() < minProduct->getCost()) {
                minProduct = &product;
            }
        }

        cout << "Товар з мінімальною ціною:\n";
        minProduct->show();
    }

    void showAll() const {
        if (products.empty()) {
            cout << "Магазин порожній.\n";
        } else {
            for (const auto& product : products) {
                product.show();
            }
        }
    }
};

int main() {
    Shop myShop;
    int choice;

    do {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Додати продукт\n";
        cout << "2. Пошук за назвою\n";
        cout << "3. Знайти товар з мінімальною ціною\n";
        cout << "4. Показати всі товари\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищення буфера

        switch (choice) {
            case 1: {
                string name;
                int quantity;
                double cost;
                cout << "Назва продукту: ";
                getline(cin, name);
                cout << "Кількість: ";
                cin >> quantity;
                cout << "Ціна: ";
                cin >> cost;
                myShop.addProduct(Product(name, quantity, cost));
                break;
            }
            case 2: {
                string searchName;
                cout << "Введіть назву продукту для пошуку: ";
                getline(cin, searchName);
                myShop.findByName(searchName);
                break;
            }
            case 3:
                myShop.findMinCostProduct();
                break;
            case 4:
                myShop.showAll();
                break;
            case 0:
                cout << "Завершення роботи.\n";
                break;
            default:
                cout << "Невірний вибір!\n";
        }
    } while (choice != 0);

    return 0;
}
