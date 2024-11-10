#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/object.h"

//class 3dViewer;

namespace s21 {
    class Controller {
    public:
        Controller(Object *obj = nullptr) : object(obj) {}
        ~Controller() {}

    private:
        Object *object;
    };
} // namespace s21

#endif // CONTROLLER_H