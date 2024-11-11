#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/object.h"

//class 3dViewer;

namespace s21 {
    class Controller {
    public:
        Controller(Object *obj = nullptr) : object_(obj) {};
        ~Controller() = default;
        void OpenFile(const std::string &path);
        std::vector<s21::Point> getVertices();
        std::vector<std::vector<int>> getFacets();
        int getVerticesCount();
        int getEdgesCount();

//        int check1 = object_->check;

    private:
        Object *object_;
    };
} // namespace s21

#endif // CONTROLLER_H