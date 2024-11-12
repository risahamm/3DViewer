#include "controller.h"

void s21::Controller::OpenFile(const std::string &path) {
    object_->Parser(path);
}