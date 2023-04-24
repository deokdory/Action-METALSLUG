#pragma once
#include "Component/Movement/Movement.h"
#include "Character/Agent.h"

class PlayerMovement : public Movement
{
public:
  PlayerMovement(class GameObject* object);
  ~PlayerMovement();

  void JumpBegin();
  void Jumping();
  void JumpEnding();

private:
  double jumpStarted = 0; // ����Ű�� ó�� ���� �ð�
  bool isJumping = false; // ����Ű�� ������ �ְ� ���� �����ð��� ��������
};