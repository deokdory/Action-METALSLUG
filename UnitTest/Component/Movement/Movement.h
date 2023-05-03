#pragma once

class MovementSpeedBox
{
public:
  enum class Slot
  {
    LEFT, RIGHT, TOP, BOTTOM
  };

  MovementSpeedBox(class GameObject* object);
  ~MovementSpeedBox();

  void Update(float xSpeed, float ySpeed);
  void Render();

  BoundingBox* GetBox(Slot slot);

private:
  // ���ǵ� Ȯ�� �� ���� ���� �ٿ���ڽ�
  BoundingBox* speedBoxL = nullptr;
  BoundingBox* speedBoxR = nullptr;
  BoundingBox* speedBoxT = nullptr;
  BoundingBox* speedBoxB = nullptr;

  class GameObject* object;
};

class Movement
{
public:
  Movement(class GameObject* object);
  virtual ~Movement();

  virtual void Update();
  virtual void Render();
  virtual void GUI();

  virtual void Falling();

  virtual void MoveLeft();
  virtual void MoveRight();
  virtual void SlowDown();

  virtual void Jump();

  virtual void UpdateAccel();

  bool GetIsFalling() { return isFalling; }

  float GetXSpeed() { return xSpeed; }
  float GetYSpeed() { return ySpeed; }

  float GetXSpeedOrigin() { return xSpeedOrigin; }
  float GetYSpeedOrigin() { return ySpeedOrigin; }

  float GetGravityOffset() { return gravityOffset; }
  float GetFallingSpeedMax() { return fallingSpeedMax; }

protected:
  virtual void collisionCheck();

protected:
  bool isFalling = false; // �������� �ִ°�

  float ySpeed = 0; // ���� �ӵ�
  float ySpeedOrigin = 0;
  float gravityOffset = 0; // ��ü�� �߷°� ���� ( �⺻ �߷°� + )
  float jumpPower = 5.f; // ���� ����

  float fallingSpeedMax = -20.f; // ���� ���� �ӵ� ����

  float xSpeed = 0; // ���� �ӵ�
  float xSpeedOrigin = 0; // ���� ���� �ӵ�
  float xSpeedMax = 6; // ���� �ӵ� ����

  float accel = 0; // ��Ȳ�� ���ӵ� ���� ���� 
  float accelOrigin = 0.3f; // �⺻ ���ӵ� ��

  class GameObject* object; // ������ ��ü
  MovementSpeedBox* speedBox; // �ӵ� ��� �����浹ü
};