#include "controller.h"

bool s21::Controller::OpenFile(const std::string &path) {
    return object_->Parser(path);
}


void s21::Controller::MoveXRight(double value) {

    modify_class = std::make_unique<MoveObject>(object_);
//    object_->Modify(std::make_unique<MoveObject>(this->object_), value, 0, 0);
}
//void s21::Controller::MoveY(double value) {
//
//}
//void s21::Controller::MoveZ(double value) {
//
//}
