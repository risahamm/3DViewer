#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/Transformations/move_object.h"
#include "../Model/Transformations/transformations.h"
#include "../Model/Transformations/zoom_object.h"
#include "../Model/object.h"

namespace s21 {
    class Controller {

    public:

        explicit Controller(Object *obj = nullptr) : object_(obj) {};
        ~Controller() = default;

        bool OpenFile(const std::string &path);

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

        void MoveXRight(double value);
        void MoveXLeft(double value);
        void MoveYUp(double value);
        void MoveYDown(double value);
        void MoveZForward(double value);
        void MoveZBackward(double value);

        void ClearObject() { object_->Clear();}


    private:

      Object *object_;

    };
} // namespace s21

#endif // CONTROLLER_H
