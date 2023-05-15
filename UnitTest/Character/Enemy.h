#pragma once
#include "Character/Character.h"

#include "Game/UI/ProgressBar.h"

class Enemy : public Character
{
public:
  Enemy(Vector3 position, Vector3 size);
  virtual ~Enemy();

  virtual void Update();
  virtual void Render();

  virtual void Damaged(float damage) override;
  virtual void Healed(float heal) override;

  virtual void Die();
protected:

  ProgressBar* hpBar = nullptr; // ü�� ���� ��

  Movement* movement; // �̵� ������Ʈ

  double hitAnimTimer = 0.0; // �ǰ� �ִϸ��̼� �ð� üũ �뵵
  bool isHit = false; // �ǰݵǰ� �ִϸ��̼� ���� ������

  double timerAfterDead = 0.0; // �װ� �� �� �ð� üũ (3�� �� ����)
};