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
        std::vector<s21::Point> getVertices() {return object_->getVertex();};
        std::vector<std::vector<int>> getFacets() {return object_->getFacet();};
        int getVerticesCount() {return object_->getVertexCount(); };
        int getEdgesCount() {return object_->getEdgeCount();};
        double getMaxCoordinateX() {return object_->getMaxX();};
        double getMinCoordinateX() {return object_->getMinX();};
        double getMaxCoordinateY() {return object_->getMaxY();};
        double getMinCoordinateY() {return object_->getMinY();};
        double getMaxCoordinateZ() {return object_->getMaxZ();};
        double getMinCoordinateZ() {return object_->getMinZ();};


    private:
        Object *object_;
    };
} // namespace s21

#endif // CONTROLLER_H
