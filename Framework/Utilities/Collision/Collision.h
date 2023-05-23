#pragma once

class Collision {

 public:
   enum class Slot
   { TOP, BASE, BOTTOM };

  Collision(class GameObject* object);
  ~Collision();

  virtual void Update();
  virtual void Render();

  void InitializeBase();
  void InitializeTop();
  void InitializeBottom();

  void DeleteBase()   { SAFE_DELETE(base) };
  void DeleteTop()    { SAFE_DELETE(top) };
  void DeleteBottom() { SAFE_DELETE(bottom) };

  BoundingBox* GetBase() { return base; }
  BoundingBox* GetBottom() { return bottom; }
  BoundingBox* GetTop() { return top; }

  void SetAnchorPoint(AnchorPoint anchorPoint) { this->anchorPoint = anchorPoint; }

 protected:
  class GameObject* object = nullptr;

  Vector3 objPos, objSize;
  float objRotation;

  AnchorPoint anchorPoint = AnchorPoint::MID_BOT;

  BoundingBox* base = nullptr;
  BoundingBox* bottom = nullptr;
  BoundingBox* top = nullptr;

  const float collisionThickness = 4;
};