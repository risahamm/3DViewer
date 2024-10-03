#include "object.h"

void s21::Object::Parser(std::string path) {
std::ifstream my_file;
my_file.open(path);
//std::cout<<"MYPATH:"<<path<<std::endl;
std::string str;
while(!my_file.eof()) {
   std::getline(my_file, str, '\n');
    ReadVertex(str);
}
};

void s21::Object::ReadVertex(std::string &str) {
    std::string::const_iterator ch = str.cbegin();
    while (ch != str.end()) {
        if (*ch == 'v') { // считываем первый символ
            if (*(++ch) == ' ') { // сдвигаем на следующий символ
                while (ch != str.end()) {
                    ch++;
                    if (std::isdigit(*ch)) { // проверяем, что там число
                        std::stod(str);
                    }
                }
            }
            else return;
        }
    }
}