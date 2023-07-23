//Для работы концепта необходимо включить стандрат С++ 20
//Есть проблема в том, что код не компилируется, при этом тут не подчеркивает никаких ошибок
//При попытке компиляции показывает следующее: 
// error C7571: "ComplexConcept": шаблон переменной уже инициализирован
//При этом если убрать участки кода с реализацией метода hash() все работает нормально.
#include <iostream>
#include <concepts>
#include <string>

template <typename T> concept ComplexConcept = requires(const T v) { // Создаем концепт который переводит передаваемое значение в string
    { v.toString() }
    ->std::convertible_to<std::string>;
};

template <typename T> concept ComplexConcept = requires(const T v) { // Создаем концепт который переводит передаваемое значение в string
    { v.hash() }
    ->std::convertible_to<long>;
};

template <typename T>
concept ComplexConcept = std::same_as<T, int> || std::same_as<T, std::string>; // Ограничение  типа Т, который должен быть либо long либо string

struct Number { // Создаем структуру, которая содержит переменную типа int, которую мы переводим в string  или long
    int _num{ 0 };
    long _long_number = _num;
    std::string toString() const { return std::to_string(_num); };
    long hash() const { return _long_number; };
   };

void PrintTypeString(ComplexConcept auto& t) { std::cout << t.toString() << '\n'; } // Эта функция выводит результат в консоль для string
void PrintTypeLong(ComplexConcept auto& t) { std::cout << t.hash() << '\n'; } // Эта функция выводит результат в консоль для long 

int main()
{
    Number x{ 42 }; //Создаем и передаем в методы переменную
    PrintTypeString(x);
    PrintTypeLong(x);

    std::cout << std::boolalpha; //Проверка на наличие виртуального деструктора
    std::cout << "has_virtual_destructor:"<< std::endl;
    std::cout << "Number: "<< std::has_virtual_destructor<Number>::value<< std::endl;
  
    return 0;
}

