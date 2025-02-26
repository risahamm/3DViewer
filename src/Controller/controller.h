#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/Transformations/move_object.h"
#include "../Model/Transformations/zoom_object.h"
#include "../Model/object.h"

namespace s21 {
class Controller {
 public:
  Controller(Object *obj = nullptr) : object_(obj) {};
  ~Controller() = default;

  bool OpenFile(const std::string &path);

  std::vector<s21::Point> getVertices() { return object_->GetVertices(); };
  std::vector<std::vector<int>> getFacets() { return object_->GetFacets(); };

  int getVerticesCount() { return object_->GetVertexCount(); };
  int getEdgesCount() { return object_->GetEdgeCount(); };

  double getMaxCoordinateX() { return object_->GetMaxX(); };
  double getMinCoordinateX() { return object_->GetMinX(); };
  double getMaxCoordinateY() { return object_->GetMaxY(); };
  double getMinCoordinateY() { return object_->GetMinY(); };
  double getMaxCoordinateZ() { return object_->GetMaxZ(); };
  double getMinCoordinateZ() { return object_->GetMinZ(); };

  void MoveXRight(double value);
  void MoveXLeft(double value);
  void MoveYUp(double value);
  void MoveYDown(double value);
  void MoveZForward(double value);
  void MoveZBackward(double value);

  void Zoom(double value);

  void RoateXUp(double value);
  void RoateXDown(double value);
  void RoateYRight(double value);
  void RoateYLeft(double value);
  void RoateZClckWs(double value);   ///< вращение по часовой
  void RoateZCClckWs(double value);  ///< вращение против часовой

  void ClearObject() { object_->Clear(); }

 private:
  Object *object_;
};
}  // namespace s21

#endif  // CONTROLLER_H
