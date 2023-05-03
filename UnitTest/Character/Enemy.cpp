#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Vector3 position, Vector3 size)
  : Character(position, size)
{
  movement = new Movement(this);
  hpBar = new ProgressBar(position, { 30, 5, 0 }, 0.0f, Values::Red ,UI::FillType::LEFT_TO_RIGHT);
}

Enemy::~Enemy()
{
  SAFE_DELETE(hpBar);
  SAFE_DELETE(movement);
}

void Enemy::Update()
{
  if (isDead) // ���� ����
  {
    timerAfterDead += Time::Get()->WorldDelta(); // timer�� ���� �� �ӵ� �ݿ��� �ð� �߰�

    // ���� �� 2�ʰ� �����ٸ� �׷����� ���̵�ƿ� ȿ�� ����
    if (timerAfterDead > 2.0) graphic->FadeOut(1.0f, ObjectGraphic::Type::ANIMATION);

    // ���� �� 3�ʰ� �����ٸ� �����Ǳ� ��ٸ�
    if (timerAfterDead > 3.0) isWaitingDelete = true;
  }
  else // ��� �ִ� ����
  {
    if (hp <= 0.0f) Die(); // ü���� 0 ���϶�� ���

    if (isHit) // �ǰ� �� �ִϸ��̼� ��� ��
    {
      if (hitAnimTimer > 0.22222222) // �ǰ� �ִϸ��̼� �ð� �ʰ� �ӽ� ����
      {
        graphic->SetCurrentAnimation(L"idle"); 
        isHit = false;
      }
      else hitAnimTimer += Time::Get()->WorldDelta(); // �ǰ� �ִϸ��̼� �ð� ��� �ӽ� ����
    }
    else
    {
      //movement->MoveLeft();
    }
  }

  hpBar->Update(); // ü�� ���� �� ������Ʈ
  __super::Update(); // �θ�Ŭ����(���� ������Ʈ) ������Ʈ
  movement->Update(); // �̵� ������Ʈ ������Ʈ

  // ü�� ���� ���� ��ġ�� ����
  Vector3 hpBarPosition = position;
  hpBarPosition.y += size.y / 2;
  hpBar->SetPosition(hpBarPosition);
}

void Enemy::Render()
{
  __super::Render();
  movement->Render();
  hpBar->Render();
}

void Enemy::Damaged(float damage)
{
  isHit = true;
  hitAnimTimer = 0.0;

  graphic->SetCurrentAnimation(L"hit"); // �ǰ� �ִϸ��̼� ȣ��
  __super::Damaged(damage); // Character�� Damaged ȣ�� ( ü�¿� ����� �ݿ� )

  hpBar->UpdateProgressBar(hp / hpMax); // ü�� ���� �� ������Ʈ
}

void Enemy::Healed(float heal)
{
}

void Enemy::Die()
{
  graphic->SetCurrentAnimation(L"die");
  isDead = true;
}
