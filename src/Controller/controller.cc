#include "controller.h"

//s21::Controller::Controller(s21::Object *obj) {
//    object_ = obj;
//}

void s21::Controller::OpenFile(const std::string &path) {
    object_->Parser(path);
}

std::vector<s21::Point> s21::Controller::getVertices() {
    return object_->getVertex();
}

std::vector<std::vector<int>> s21::Controller::getFacets() {
    return object_->getFacet();
}

int s21::Controller::getVerticesCount() {
    return object_->getVertexCount();
}

int s21::Controller::getEdgesCount() {
    return object_->getEdgeCount();
}