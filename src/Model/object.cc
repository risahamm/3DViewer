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
//    std::cout<<"STR:"<<str<<std::endl;
        std::string::const_iterator ch = str.cbegin();
        while (ch != str.end()) { // TODO starts_with
            if (*ch == 'v') {
                if (*(++ch) == ' ') {
                    ReadVertex(str);
                }
            }
            break;
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
    const char *newstr = str.c_str();
    std::string sub2 = str.substr(2);
    std::istringstream iss(sub2);
    newstr = newstr + 2;
    char *next;
    double x;
//                while (*newstr != '\0') {
//                    if (std::isdigit(*newstr) || (*newstr) == '-') {
//                        std::string sub1 = str.substr(2);
//                        x = std::stod(sub1);
//                        std::cout<<"STOD:"<<x<<std::endl;
//                    }
//                    ch++;
//                    if ((*ch) == ' ') {
//
//                    }
//                    break;
//                }
while (iss >> x) {
    vertex_.push_back(x);

}
for (double i : vertex_) {
    std::cout<<"VERTEX_::"<<i<<std::endl;
    }
}