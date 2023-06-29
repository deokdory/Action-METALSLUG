#include "stdafx.h"
#include "Enemy.h"

#include "Agent.h"
#include "Utilities/EnemyAI/EnemyAI.h"

Enemy::Enemy(Vector3 position, Vector3 size)
  : Character(position, size)
{
  movement = new Movement(this);
  movement->SetXSpeedMax(4.0f);

  hpBar = new ProgressBar(position, { 30, 5, 0 }, 0.0f, Values::Red ,UI::FillType::LEFT_TO_RIGHT);

  detectionArea = new BoundingBox
  (position + Vector3(0, size.y / 2, 0), { 564, 256, 0 }, 0.0f, Color(0.5f, 1.0f, 0.5f, 0.1f));
  
  attackableArea = new BoundingBox
  (position + Vector3(0, size.y / 2, 0), { 192, 128, 0 }, 0.0f, Color(1.0f, 0.5f, 0.5f, 0.1f));

  enemyAI = new EnemyAI(this);

  // �⺻ ���� ���� = 576, 256
}

Enemy::~Enemy()
{
  SAFE_DELETE(enemyAI);
  SAFE_DELETE(attackableArea);
  SAFE_DELETE(detectionArea);

  SAFE_DELETE(hpBar);
  SAFE_DELETE(movement);
}

void Enemy::Update()
{

  if (currState == State::DEAD)
  {
    timerAfterDead += Time::Get()->WorldDelta(); // timer�� ���� �� �ӵ� �ݿ��� �ð� �߰�

    // ���� �� 2�ʰ� �����ٸ� �׷����� ���̵�ƿ� ȿ�� ����
    if (timerAfterDead > 2.0) graphic->FadeOut(1.0f, ObjectGraphic::Type::ANIMATION);

    // ���� �� 3�ʰ� �����ٸ� �����Ǳ� ��ٸ�
    if (timerAfterDead > 3.0) isWaitingDelete = true;
  }

  else if (isActived)// ��� �ִ� ����
  {
    if (hp <= 0.0f) Die(); // ü���� 0 ���϶�� ���

    detectionArea->Update(position + Vector3(0, size.y / 2, 0));
    attackableArea->Update(position + Vector3(0, size.y / 2, 0));

    enemyAI->Update();
    
    switch (currState)
    {
    //case Enemy::State::READY:
    //  if (findTarget() || GameManager::Get()->GetPlayerCurrentRoom() == currentRoom)
    //  {
    //    target = (Character*)GameManager::Get()->GetPlayer();
    //    
    //  }
    //  break;
    case Enemy::State::READY:
      if (movement->GetIsFalling())
      {
        // State�� Falling���� �ٲ�
      }
      
      if (std::abs(movement->GetXSpeedOrigin() > 1))
      {
        // �޸��� �ִϸ��̼� ���
      }

      // �޸��� �ߵ� �ƴϰ� �������� ���µ� �ƴ� = ������ �� �ִ� ����
      else
      {
        graphic->SetCurrentAnimation(L"idle");
      }

      

      break;
    //case Enemy::State::ATTACK:
    //  break;
    //case Enemy::State::RUN:
    //  break;
    case Enemy::State::HIT:
      movement->SlowDown();

      if (graphic->IsAnimationFinish(ObjectGraphic::Slot::NORMAL))
        currState = prevState;
      break;
    default:
      break;
    }
  }

  __super::Update(); // �θ�Ŭ����(ĳ����) ������Ʈ

  if (isActived)
  {
    hpBar->Update(); // ü�� ���� �� ������Ʈ
    movement->Update(); // �̵� ������Ʈ ������Ʈ

    // ü�� ���� ���� ��ġ�� ����
    Vector3 hpBarPosition = position;
    hpBarPosition.y += size.y;
    hpBar->SetPosition(hpBarPosition);
  }
}

void Enemy::Render()
{
  detectionArea->Render();
  attackableArea->Render();

  if (isActived)
  {
    __super::Render();
    movement->Render();
    hpBar->Render();
  }
}

void Enemy::Damaged(float damage)
{

  prevState = currState;
  currState = State::HIT;

  graphic->SetCurrentAnimation(L"hit"); // �ǰ� �ִϸ��̼� ȣ��
  __super::Damaged(damage); // Character�� Damaged ȣ�� ( ü�¿� ����� �ݿ� )

  hpBar->UpdateProgressBar(hp / hpMax); // ü�� ���� �� ������Ʈ
}

//void Enemy::Healed(float heal)
//{
//}

void Enemy::Die()
{
  isDead = true;

  movement->Stop();
  graphic->SetCurrentAnimation(L"die");
  currState = State::DEAD;
  timerAfterDead = 0.0;
}

bool Enemy::DetectPlayer()
{
  return BoundingBox::AABB(detectionArea, 
    GameManager::Get()->GetPlayer()->GetCollision()->GetBase());
}

bool Enemy::CanAttack(GameObject* object)
{
  return BoundingBox::AABB(attackableArea, object->GetCollision()->GetBase());
}

void Enemy::Scream()
{
  currState = State::SCREAM;
}

void Enemy::Attack(GameObject* target)
{
  movement->SlowDown();
}
