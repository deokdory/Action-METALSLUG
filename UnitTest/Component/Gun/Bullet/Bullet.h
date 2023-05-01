#pragma once
#include "Game/GameObject.h"

class Bullet : public GameObject {
public:
  // �Ʊ��� �� �Ѿ����� ������ �� �Ѿ�����
  enum class Side {
    PLAYER = 0, ENEMY
  };
  
  Bullet(GameObject* fired, Side side, float speed, float damage, std::wstring texturePath);
  ~Bullet();

  virtual void Update();
  virtual void Render();

  virtual void hit(GameObject* object); // �浹���� �� �浹�� ������Ʈ�� ���ڷ� ����

  Bullet* NewBullet(Vector3 position, Vector3 axis); // �ڽ��� �������� ������ �� ��ġ�� ������ �����Ͽ� ��ȯ

protected:
  // ������ ���� ���� ������
  Bullet(GameObject* fired, Side side, float speed, float damage, std::wstring texturePath, Vector3 position, Vector3 axis); 

  GameObject* fired; // �� ĳ����
  Side side;  // �Ʊ� | ����

  Vector3 axis = Values::ZeroVec3; // ���ư� ����

  float damage; // �����
  float speed; // ź��

  bool isHit = false; // �浹�ߴ°�

  double flyingTime = 0.0;

  std::wstring texturePath = L""; // �ڽ��� �ؽ��� ���� ���
};