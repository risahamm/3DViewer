#include "controller.h"


bool s21::Controller::OpenFile(const std::string &path) {
  return object_->Parse(path);
}


void s21::Controller::MoveXRight(double value) {
  object_->Modify(std::make_unique<s21::MoveObject>(object_), value, 0, 0);
}


void s21::Controller::MoveXLeft(double value) {
  object_->Modify(std::make_unique<s21::MoveObject>(object_), -value, 0, 0);
}


void s21::Controller::MoveYUp(double value) {
  object_->Modify(std::make_unique<s21::MoveObject>(object_), 0, value, 0);
}


void s21::Controller::MoveYDown(double value) {
  object_->Modify(std::make_unique<s21::MoveObject>(object_), 0, -value, 0);
}


void s21::Controller::MoveZForward(double value) {
  object_->Modify(std::make_unique<s21::MoveObject>(object_), 0, 0, value);
}


void s21::Controller::MoveZBackward(double value) {
  object_->Modify(std::make_unique<s21::MoveObject>(object_), 0, 0, -value);
}


void s21::Controller::Zoom(double value) {
  if (value != 0.0) {
    object_->Modify(std::make_unique<s21::ZoomObject>(object_), value, value, value);
  }
}


void s21::Controller::RoateXUp(double value){
  object_->Modify(std::make_unique<s21::RotateObject>(object_), 0, -value, -value);
}


void s21::Controller::RoateXDown(double value){
  object_->Modify(std::make_unique<s21::RotateObject>(object_), 0, value, value);
}



void s21::Controller::RoateYRight(double value){
  object_->Modify(std::make_unique<s21::RotateObject>(object_), -value, 0, -value);
}


void s21::Controller::RoateYLeft(double value){
  object_->Modify(std::make_unique<s21::RotateObject>(object_), value, 0, value);
}


void s21::Controller::RoateZClckWs(double value){
  object_->Modify(std::make_unique<s21::RotateObject>(object_), -value, -value, 0);
}


void s21::Controller::RoateZCClckWs(double value){
  object_->Modify(std::make_unique<s21::RotateObject>(object_), value, value, 0);
}
