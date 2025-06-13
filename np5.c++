//
//  np5.c++
//  labs_oop
//
//  Created by Даниил Бологан on 13.06.2025.
//

#include <iostream>
#include <concepts>
#include <type_traits>


template<typename T>
concept Arithmetic = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;
};

template<Arithmetic T>
class Calculator {
public:
    T add(T a, T b) {
        return a + b;
    }

    T subtract(T a, T b) {
        return a - b;
    }

    T multiply(T a, T b) {
        return a * b;
    }

    T divide(T a, T b) {
        if (b == 0) {
            throw std::runtime_error("Ділення на нуль!");
        }
        return a / b;
    }
};

int main() {
    Calculator<int> intCalc;
    std::cout << "Сума: " << intCalc.add(5, 3) << std::endl;
    std::cout << "Різниця: " << intCalc.subtract(10, 7) << std::endl;
    std::cout << "Добуток: " << intCalc.multiply(4, 6) << std::endl;
    std::cout << "Ділення: " << intCalc.divide(20, 5) << std::endl;

    Calculator<double> doubleCalc;
    std::cout << "Double сума: " << doubleCalc.add(1.5, 2.3) << std::endl;



    return 0;
}
