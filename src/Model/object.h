#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace s21 {


    class Object {
    public:
        Object() = default;
        ~Object() = default;
    /**
     *
     * @param path путь к файлу
     */
    void Parser(std::string path);
    void ReadVertex(std::string &str);

    private:
        std::vector<double> vertex_;
        std::vector<int> facet_;
        std::vector<int> vertex_count_;
    };

} // namespace s21

#endif // OBJECT_H