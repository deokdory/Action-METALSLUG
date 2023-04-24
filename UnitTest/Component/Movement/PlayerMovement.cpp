#include "stdafx.h"
#include "PlayerMovement.h"

#include "Game/GameObject.h"

#include "Level/Level.h"

PlayerMovement::PlayerMovement(GameObject* object)
  : Movement(object)
{
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::JumpBegin()
{
  auto currTime = Time::Get()->Running();
  // ���� �ִٸ� ����
  if (isFalling == false) {
    jumpStarted = currTime;  // ����Ű ������ ���� ���� ����
    isJumping = true;     // ����Ű�� ������ ����
    ySpeed = jumpPower;     // ���� ( �ּ� ���� ���� )
    isFalling = true;
  }
}

void PlayerMovement::Jumping()
{
  auto currTime = Time::Get()->Running();
  // ���߿� �ְ� ���� �����̽��ٸ� ������ ����
  if (isFalling) {
    // �����̽��ٸ� ������ �ִ� �ð��� 0.2�� �̳����
    if (currTime - jumpStarted <= 0.2) {
      ySpeed = jumpPower;  // ���� ���� ����
    }
  }
}

void PlayerMovement::JumpEnding()
{
  if (isJumping)
  {
    isJumping = false;
  }
}
