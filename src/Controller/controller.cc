#include "controller.h"

void s21::Controller::OpenFile(const std::string &path) {
    object->Parser(path);
}

std::vector<s21::Point> s21::Controller::getVertices() {
    return object->getVertex();
}

std::vector<std::vector<int>> s21::Controller::getFacets() {
    return object->getFacet();
}

int s21::Controller::getVerticesCount() {
    return object->getVertexCount();
}

int s21::Controller::getEdgesCount() {
    return object->getEdgeCount();
}