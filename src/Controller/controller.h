#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/object.h"

//class 3dViewer;

namespace s21 {
    class Controller {
    public:
        Controller(Object *obj = nullptr) : object(obj) {}
        ~Controller() {}
        void OpenFile(const std::string &path);
        std::vector<s21::Point> getVertices();
        std::vector<std::vector<int>> getFacets();
        int getVerticesCount();
        int getEdgesCount();

    private:
        Object *object;
    };
} // namespace s21

#endif // CONTROLLER_H