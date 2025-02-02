#include "controller.h"

bool s21::Controller::OpenFile(const std::string &path) {
  return object_->Parse(path);
}


void s21::Controller::MoveXRight(double value) {
  object_->Modify(std::make_unique<MoveObject>(object_), value, 0, 0);
}


void s21::Controller::MoveXLeft(double value) {
  object_->Modify(std::make_unique<MoveObject>(object_), -value, 0, 0);
}


void s21::Controller::MoveYUp(double value) {
  object_->Modify(std::make_unique<MoveObject>(object_), 0, value, 0);
}


void s21::Controller::MoveYDown(double value) {
  object_->Modify(std::make_unique<MoveObject>(object_), 0, -value, 0);
}


void s21::Controller::MoveZForward(double value) {
  object_->Modify(std::make_unique<MoveObject>(object_), 0, 0, value);
}


void s21::Controller::MoveZBackward(double value) {
  object_->Modify(std::make_unique<MoveObject>(object_), 0, 0, -value);
}

