#include "stdafx.h"
#include "Enemy.h"

#include "Agent.h"
#include "Utilities/EnemyAI/EnemyAI.h"

Enemy::Enemy(Vector3 position, Vector3 size)
  : Character(position, size)
{
  init();
}

Enemy::Enemy(Vector3 position, Vector3 size, Room* spawnedRoom)
  : Character(position, size), spawnedRoom(spawnedRoom)
{
  init();
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
  if (state == State::DEAD)
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
    chasingArea->Update(position + Vector3(0, size.y / 2, 0));

    enemyAI->Update();
   
    switch (state)
    {
    case Enemy::State::SCREAM:

      if (graphic->GetIsAnimationFinish())
        StandBy();

      break;

    case Enemy::State::STANDBY:

      movement->SlowDown();
      graphic->SetCurrentAnimation(L"idle");

      if (hp < hpMax)
      {
        if (hpRegenTimer > 0.1)
        {
          hp += hpMax / 10;
          hpBar->UpdateProgressBar(hp / hpMax);
          hpRegenTimer = 0.0;
        }
        else
          hpRegenTimer += Time::Get()->WorldDelta();
      }
      else if (hp > hpMax)
        hp = hpMax;

      break;

    case Enemy::State::DETECT:

      if (movement->GetIsFalling())
      {
        // State�� Falling���� �ٲ�
      }

      // �޸��� �ִϸ��̼� ���
      if (movement->GetXSpeedOrigin() > 1.0f)
      {
        isFliped = false;
        graphic->SetCurrentAnimation(L"run");
      }
      else if (movement->GetXSpeedOrigin() < -1.0f)
      {
        isFliped = true;
        graphic->SetCurrentAnimation(L"run");
      }
      // �޸��� �ߵ� �ƴϰ� �������� ���µ� �ƴ� = ������ �� �ִ� ����
      else
      {
        graphic->SetCurrentAnimation(L"idle");
      }

      break;

    case Enemy::State::HIT:
      movement->SlowDown();

      if (graphic->GetIsAnimationFinish(ObjectGraphic::Slot::NORMAL))
        StandBy();

      break;

    case Enemy::State::RETURN:
      // �ӽ� ���� �� ȸ��
      if (hp < hpMax)
      {
        if (hpRegenTimer > 0.1)
        {
          hp += hpMax / 10;
          hpBar->UpdateProgressBar(hp / hpMax);
          hpRegenTimer = 0.0;
        }
        else
          hpRegenTimer += Time::Get()->WorldDelta();
      }
      else if (hp > hpMax)
        hp = hpMax;

      // ����� �� ��� ����� Ž
      if (currentRoom != spawnedRoom)
      {
        movement->SetIsDirectingDown(true);
        movement->SetIsDirectingUp(true);
      }

      // ������ ��� ����ϱ� �� ��� ���������� �ӽ� ���� ( y ������ )
      else if (spawnedPosition.y + 1 < position.y)
      {
        movement->SetIsDirectingUp(false);
        movement->SetIsDirectingDown(true);
      }
      else if (spawnedPosition.y - 1 > position.y)
      {
        movement->SetIsDirectingUp(true);
        movement->SetIsDirectingDown(false);
      }
      else
      {
        movement->SetIsDirectingUp(false);
        movement->SetIsDirectingDown(false);
      }

      // �ӽ� ���� x ������
      if (spawnedPosition.x + 1 < position.x)
      {
        movement->MoveLeft();
        isFliped = true;
      }
      else if (spawnedPosition.x - 1 > position.x)
      {
        movement->MoveRight();
        isFliped = false;
      }
      else
      {
        movement->Stop();
        StandBy();
      }

      break;

    case Enemy::State::ATTACK:

      if(movement->GetIsFalling() == false)
        movement->SlowDown();

      if (attacking)
      {
        if (graphic->GetIsAnimationFinish())
        {
          graphic->SetCurrentAnimation(L"knifeReverse");
          attacking = false;
        }
      }
      else
      {
        if (graphic->GetIsAnimationFinish())
        {
          StandBy();
        }
      }
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
  chasingArea->Render();
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
  if (state != State::RETURN)
  {
    state = State::HIT;

    graphic->SetCurrentAnimation(L"hit"); // �ǰ� �ִϸ��̼� ȣ��
  }
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
  state = State::DEAD;
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

bool Enemy::CanChasing(GameObject* object)
{
  return BoundingBox::AABB(chasingArea, object->GetCollision()->GetBase());
}

void Enemy::Look(Direction direction)
{
  switch (direction)
  {
  case Direction::LEFT:
    isFliped = true;
    break;
  case Direction::RIGHT:
    isFliped = false;
    break;
  default:
    break;
  }
}

void Enemy::Look(GameObject* object)
{
  if (object->GetPosition().x > position.x)
    isFliped = false;
  else
    isFliped = true;
}

void Enemy::Scream()
{
  state = State::SCREAM;
  graphic->SetCurrentAnimation(L"scream");
}

void Enemy::Return()
{
  hpRegenTimer = 0.0;
  movement->SetXSpeedMax(6.0f);
  state = State::RETURN;
}

void Enemy::StandBy()
{
  state = State::STANDBY;
  movement->SetXSpeedMax(6.0f);
}

void Enemy::Attack(GameObject* target)
{
  attacking = true;
  state = State::ATTACK;
  graphic->SetCurrentAnimation(L"knife1");
}

void Enemy::init()
{
  movement = new Movement(this);
  movement->SetXSpeedMax(6.0f);

  hpBar = new ProgressBar(position, { 30, 5, 0 }, 0.0f, Values::Red, UI::FillType::LEFT_TO_RIGHT);

  detectionArea = new BoundingBox
  (position + Vector3(0, size.y / 2, 0), { 564, 256, 0 }, 0.0f, Color(0.5f, 1.0f, 0.5f, 0.1f));

  attackableArea = new BoundingBox
  (position + Vector3(0, size.y / 2, 0), { 96, 128, 0 }, 0.0f, Color(1.0f, 0.5f, 0.5f, 0.1f));

  chasingArea = new BoundingBox
  (position + Vector3(0, size.y / 2, 0), { 960, 512, 0 }, 0.0f, Color(1.0f, 1.0f, 1.0f, 0.1f));

  enemyAI = new EnemyAI(this);
  spawnedPosition = this->position;

  // �⺻ ���� ���� = 576, 256
}
