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

  const BoundingBox* GetBox(Slot slot);

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

  virtual void MoveLeft();
  virtual void MoveRight();
  virtual void SlowDown();

  virtual void Jump();

protected:
  void collisionCheck();

protected:
  bool isFalling = false; // �������� �ִ°�

  float ySpeed = 0; // ���� �ӵ�
  float gravityOffset = 0; // ��ü�� �߷°� ���� ( �⺻ �߷°� + )
  float jumpPower = 2.5f; // ���� ����

  float fallingSpeedMax = -10.f; // ���� ���� �ӵ� �Ѱ谪

  float xSpeed = 0; // ���� �ӵ�
  float xSpeedMax = 4; // ���� �ӵ� �Ѱ谪

  float accel = 0; // ��Ȳ�� ���ӵ� ���� ���� 
  float accelOrigin = 0.2f; // �⺻ ���ӵ� ��

  class GameObject* object; // ������ ��ü
  MovementSpeedBox* speedBox; // �ӵ� ��� �����浹ü
};