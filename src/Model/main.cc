#include "object.h"

using namespace std;

int main() {
    string str = "../object_files/test21.obj";
    s21::Object Obj;
    Obj.Parser(str);
//    string str2 = "1.000000";
//    std::stod(str2);
//    std::cout << std::stod(str2) << endl;
}

//#include <iostream>
//#include <sstream>
//#include <vector>
//#include <string>

//int main() {
//    std::string input;
//    std::cout << "Введите числа через пробел: ";
//    std::getline(std::cin, input); // Ввод строки
//
//    std::istringstream iss(input); // Создаем поток из строки
//    std::vector<double> numbers; // Вектор для хранения чисел
//    double number;
//
//    // Читаем числа из потока
//    while (iss >> number) {
//        numbers.push_back(number); // Добавляем число в вектор
//    }
//
//    // Выводим считанные числа
//    std::cout << "Считанные числа: ";
//    for (const auto& num : numbers) {
//        std::cout << num << " ";
//    }
//    std::cout << std::endl;
//
//    return 0;
//}