#pragma once
#define FLOOR_0_YPOS -1024.0f
#define FLOOR_1_YPOS   -64.0f
#define FLOOR_2_YPOS   896.0f

class Elevator : public GameObject
{
public:
  enum class Status { GETTING_ON, WAITING, MOVING };

  Elevator(Vector3 position);
  ~Elevator();

  void Update();

  void Interaction(GameObject* object) override;
  

private:

  void getOn(GameObject* object);
  void getOff(GameObject* object);

  class Agent* agent = nullptr;

  Status status = Status::WAITING;

  float prevPositionY = 0.0f; // ���� ��ġ
  float destPositionY = 0.0f; // ��ǥ ��ġ

  Vector3 prevPlayerPosition = Values::ZeroVec3;
  Vector3 elevatorTopPos = Values::ZeroVec3;

  void elevate(Direction direction);
  UINT currentFloor = -1;

  float elevateSpeed = 7.0f;
  float elevateAccel = 0.3f;
  
  // ��� ž���ߴ��� (
  // E�� ���� ���·� ������ ���� �������� Ÿ�ڸ��� ������ ���� ���� )
  bool justGetOn = false;
};