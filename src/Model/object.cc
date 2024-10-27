#include "object.h"

void s21::Object::Parser(std::string path) {
std::ifstream my_file;
my_file.open(path);
if (!my_file.is_open()) {
    std::cout<<"File is not opened"<<std::endl; // TODO throw exception
} else {
    std::cout << "MYPATH:" << path << std::endl;
    std::string str;
    while (!my_file.eof()) {
        std::getline(my_file, str, '\n');
    std::cout<<"STR:"<<str<<std::endl;
        std::string::const_iterator ch = str.cbegin();
        while (ch != str.end()) { // TODO starts_with
            if (*ch == 'v') {
                if (*(++ch) == ' ') {
                    ReadVertex(str);
                }
            }
            if (*ch == 'f') { // TODO starts_with
                if (*(++ch) == ' ') {
//                    ReadFacet(str);
                }
            }
        }
    }
} // file is opened
};

void s21::Object::ReadVertex(std::string &str) {
    std::string::const_iterator ch = str.cbegin()+2;
    double x = 0;
                while (ch != str.end()) {
                    if (std::isdigit(*ch) || (*ch) == '-') {
                        std::string sub1 = str.substr(2);
                        x = std::stod(sub1);
                        std::cout<<"STOD:"<<x<<std::endl;

                    }
                    break;
                }
}