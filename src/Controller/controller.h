#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/object.h"

class 3dViewer;

namespace s21 {
    class Controller {
    public:
        Controller(Model *m = nullptr) : model_(m) {}
        ~Controller() {}

    private:
        Model *model_;
    };
} // namespace s21

#endif // CONTROLLER_H