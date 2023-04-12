#include "stdafx.h"
#include "IPlayerMovement.h"

IPlayerMovement::IPlayerMovement(GameObject* object) : IMovement(object) {}

void IPlayerMovement::jumpBegin() {
  auto currTime = Time::Get()->Running();
    // ���� �ִٸ� ����
    if (isFalling == false) {
      jumpedTime = currTime;  // ����Ű ������ ���� ���� ����
      isJumping = true;     // ����Ű�� ������ ����
      ySpeed = jumpPower;     // ���� ( �ּ� ���� ���� )
      isFalling = true;

      //auto move = Vector3(xSpeed, ySpeed, 0) * delta;
      //object->move(move);
    }
  }

void IPlayerMovement::jumping() {
  auto currTime = Time::Get()->Running();
  // ���߿� �ְ� ���� �����̽��ٸ� ������ ����
  if (isFalling) {
    // �����̽��ٸ� ������ �ִ� �ð��� 0.2�� �̳����
    if (currTime - jumpedTime <= 0.2) {
      ySpeed = jumpPower;  // ���� ���� ����
    }
  }
}

void IPlayerMovement::jumpEnd() { isJumping = false; }

void IPlayerMovement::update() {

  auto& status = object->GetState();

  if (Keyboard::Get()->Press('A') && !Keyboard::Get()->Press('D')) {
    moveLeft();
  } else if (Keyboard::Get()->Press('D') && !Keyboard::Get()->Press('A')) {
    moveRight();
  } else {
    SlowDown();
  }

  if (Keyboard::Get()->Down(VK_SPACE))
    jumpBegin();
  else if (Keyboard::Get()->Press(VK_SPACE))
    jumping();
  else
    jumpEnd();

  __super::update();
}
    




