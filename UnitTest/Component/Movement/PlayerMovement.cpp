#include "stdafx.h"
#include "PlayerMovement.h"

#include "Game/GameObject.h"

//#include "Level/Level.h"

PlayerMovement::PlayerMovement(GameObject* object)
  : Movement(object)
{
}

PlayerMovement::~PlayerMovement()
{

}

void PlayerMovement::Update()
{
  // ���ӵ� ����
    if (isFalling) isSliding = false;
    __super::Update();
}

void PlayerMovement::UpdateAccel()
{
  accel = accelOrigin * Time::Get()->GetGlobalSpeed();
  if (isSliding) accel /= 8;
}

void PlayerMovement::Jump()
{
    ySpeedOrigin = jumpPower;     // ���� ( �ּ� ���� ���� )
    isFalling = true;
}

void PlayerMovement::Jumping()
{
  ySpeedOrigin = jumpPower;  // ���� ���� ����
}
