#include "controller.h"

bool s21::Controller::OpenFile(const std::string &path) {
    return object_->Parser(path);
}
