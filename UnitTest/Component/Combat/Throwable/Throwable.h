#pragma once
#include "Game/GameObject.h"

class Throwable : public GameObject
{
public:
  enum class Side { PLAYER, ENEMY };

  Throwable(GameObject* thrown, Side side, float gravityOffset, float damage, float range, std::wstring texturePath);
  ~Throwable();

  virtual void Update();
  virtual void Render();

  virtual bool hit(GameObject* object); // �浹���� �� �浹�� ������Ʈ�� ���ڷ� ����

  virtual Throwable* NewThrowable(Vector3 position, Vector3 axis, float strength); // �ڽ��� �������� ������ �� ��ġ�� ����, ������ ���⸦ �����Ͽ� ��ȯ

  static Throwable* InitGrenade(GameObject* object); // �⺻ ����ź ������

  float GetGravityOffset() { return gravityOffset; }
  float GetFallingSpeedMax() { return fallingSpeedMax; }

protected:
  // ������ ���� ���� ������
  Throwable(GameObject* thrown, Side side, float gravityOffset, float strength, float damage, float range, std::wstring texturePath, Vector3 position, Vector3 axis);

  bool collisionCheck();
  void bomb();

  GameObject* thrown; // ���� ��ü
  Side side; // �Ʊ� | ����

  Vector3 axis = Values::ZeroVec3; // ���ư� ����

  float xSpeed = 0.0f;
  float ySpeed = 0.0f;

  float fallingSpeedMax = -20.f; // ���� �ӵ� ����

  double sinceThrown = 0.0;

  float gravityOffset; // �߷� ������

  float damage; // �����
  float strength = 0; // ������ ����
  float range; // ���� ���� (���� ���� ����)

  bool isBombed = false; // �����°�

  std::wstring texturePath = L""; // �ڽ��� �ؽ��� ���� ���
};