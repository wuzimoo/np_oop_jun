//
//  np2.cpp
//  labs_oop
//
//  Created by Даниил Бологан on 05.06.2025.
//

#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string name;
    double caloriesPer100g;
    double weight;

public:
    // Конструктори
    Product() : name(""), caloriesPer100g(0), weight(0) {}
    Product(string n, double cal, double w) : name(n), caloriesPer100g(cal), weight(w) {}

    // Метод для загальної калорійності
    double totalCalories() const {
        return (caloriesPer100g / 100.0) * weight;
    }

    // Перевантаження оператора введення >>
    friend istream& operator>>(istream& in, Product& p) {
        cout << "Введіть назву продукту: ";
        in >> p.name;
        cout << "Введіть калорійність на 100г: ";
        in >> p.caloriesPer100g;
        cout << "Введіть вагу продукту (г): ";
        in >> p.weight;
        return in;
    }

    // Перевантаження оператора виводу <<
    friend ostream& operator<<(ostream& out, const Product& p) {
        out << "Назва: " << p.name << ", Калорійність/100г: " << p.caloriesPer100g
            << ", Вага: " << p.weight << " г, Загальна калорійність: "
            << p.totalCalories() << " ккал";
        return out;
    }

    // Перевантаження оператора +
    Product operator+(const Product& other) const {
        if (name == other.name && caloriesPer100g == other.caloriesPer100g) {
            return Product(name, caloriesPer100g, weight + other.weight);
        } else {
            cout << "Продукти не однакові. Додавання неможливе.\n";
            return *this;
        }
    }

    // Перевантаження оператора -
    Product operator-(const Product& other) const {
        if (name == other.name && caloriesPer100g == other.caloriesPer100g) {
            double newWeight = weight - other.weight;
            if (newWeight < 0) newWeight = 0;
            return Product(name, caloriesPer100g, newWeight);
        } else {
            cout << "Продукти не однакові. Віднімання неможливе.\n";
            return *this;
        }
    }

    // Префіксний ++
    Product& operator++() {
        weight += 5;
        return *this;
    }

    // Постфіксний ++
    Product operator++(int) {
        Product temp = *this;
        weight += 5;
        return temp;
    }

    // Префіксний --
    Product& operator--() {
        weight -= 5;
        if (weight < 0) weight = 0;
        return *this;
    }

    // Постфіксний --
    Product operator--(int) {
        Product temp = *this;
        weight -= 5;
        if (weight < 0) weight = 0;
        return temp;
    }

    // Перевантаження =
    Product& operator=(const Product& other) {
        if (this != &other) {
            name = other.name;
            caloriesPer100g = other.caloriesPer100g;
            weight = other.weight;
        }
        return *this;
    }

    // Перевантаження логічних операторів
    bool operator==(const Product& other) const {
        return name == other.name && caloriesPer100g == other.caloriesPer100g && weight == other.weight;
    }

    bool operator!=(const Product& other) const {
        return !(*this == other);
    }

    bool operator>(const Product& other) const {
        return totalCalories() > other.totalCalories();
    }

    bool operator<(const Product& other) const {
        return totalCalories() < other.totalCalories();
    }

    bool operator>=(const Product& other) const {
        return totalCalories() >= other.totalCalories();
    }

    bool operator<=(const Product& other) const {
        return totalCalories() <= other.totalCalories();
    }
};

// Головна функція
int main() {
    Product p1, p2;
    cout << "Введення першого продукту:\n";
    cin >> p1;
    cout << "\nВведення другого продукту:\n";
    cin >> p2;

    cout << "\nПерший продукт:\n" << p1 << endl;
    cout << "Другий продукт:\n" << p2 << endl;

    cout << "\nСпроба додати два продукти:\n";
    Product sum = p1 + p2;
    cout << sum << endl;

    cout << "\nПрефіксний ++ до p1:\n";
    ++p1;
    cout << p1 << endl;

    cout << "\nПостфіксний -- до p2:\n";
    p2--;
    cout << p2 << endl;

    cout << "\nЧи однакові p1 і p2? " << (p1 == p2 ? "Так" : "Ні") << endl;

    cout << "\nПрисвоєння p2 = p1\n";
    p2 = p1;
    cout << "Новий p2:\n" << p2 << endl;

    return 0;
}
