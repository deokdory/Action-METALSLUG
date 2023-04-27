#pragma once
#include "Component/Gun/Gun.h"

class PlayerCombat
{
public:
  PlayerCombat(class GameObject& agent);
  ~PlayerCombat();

  void Update(class Agent& agent);
  void Render();
  void GUI();

  void ThrowGrenade(); // ����ź ������
  bool GetIsThrowing() { return isThrowing; } // ������ ��� ��� ������
  bool IsLeftGrenade() { return grenadeCount != 0; } // ����ź�� ���Ҵ���

  Gun* GetRifle() { return rifle; } // �ܺο��� �� ������Ʈ�� �����ϱ� ����

protected:
  Gun* rifle; // �� ������Ʈ
  
  UINT grenadeCount = 3; // ����ź ����

  double throwProgress = 0.0; // ������ ��� ���ӽð� ������
  double throwSpeed = 0.5; // ������ ��� ���ӽð�
  bool isThrowing = false; // ������ ��� ��� ������
};