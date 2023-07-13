#include "stdafx.h"
#include "EnemyAI.h"

#include "Character/Enemy.h"
#include "Character/Agent.h"

EnemyAI::EnemyAI(Enemy* enemy)
  : enemy(enemy)
{
  spawnedRoom = enemy->GetSpawnedRoom();
}

void EnemyAI::Update()
{

  // AI�� �ʿ��� Enemy�� ���� �̸� ��������
  Enemy::State state = enemy->GetState();
  Movement* movement = enemy->GetMovement();
  Room* currentRoom = enemy->GetCurrentRoom();
  Vector3 position = enemy->GetPosition();

  int currentFloor = -1;

  if (enemy->GetMovement()->GetLastStanded())
    currentFloor = enemy->GetMovement()->GetLastStanded()->GetFloor();

  // AI�� �ʿ��� Player�� ���� �̸� ��������
  int currentPlayerFloor = GameManager::Get()->GetLastStandedTerrainFloor();

  //if (delay > 0.0)
  //{
  //  delay -= Time::Get()->WorldDelta();
  //  return;
  //}

  switch (state)
  {
  case Enemy::State::SPAWNED:
    if (enemy->DetectPlayer())
    {
      target = GameManager::Get()->GetPlayer();
      enemy->Look(target);
      enemy->Scream();
    }
    break;
  case Enemy::State::STANDBY:
    if (target)
    {
      enemy->SetState(Enemy::State::DETECT);
      break;
    }

    if (enemy->DetectPlayer())
    {
      target = GameManager::Get()->GetPlayer();
      enemy->Look(target);
      delay = 0.5;
      enemy->SetState(Enemy::State::DETECT);
    }
    break;
  case Enemy::State::DETECT:
    if (delay > 0.0)
    {
      delay -= Time::Get()->WorldDelta();
      break;
    }
    
    // �÷��̾ �ν��� ����
    if (target)
    {
      Vector3 targetPosition = target->GetPosition();

      // ���� ������ ��� �÷��̾ �� �ۿ� �ְų� �ڽ��� �� �ۿ� ���� �� ����
      if ((GameManager::Get()->GetPlayerCurrentRoom() != spawnedRoom 
        && !enemy->CanChasing(target)) || (currentRoom != spawnedRoom))
      {
        target = nullptr;
        enemy->Return();

        break;
      }

      if (enemy->CanAttack(target))
      {
        enemy->Look(target);
        enemy->Attack(target);
        break;
      }
    
      // �÷��̾�� ���� ���ǿ� ���� ��
      if (currentPlayerFloor <= currentFloor)
      {
        movement->SetIsDirectingUp(false);
        movement->SetIsDirectingDown(false);

        currDest = nullptr;

        if (target->GetPosition().x > enemy->GetPosition().x)
          movement->MoveRight();
        else
          movement->MoveLeft();

        if (currentPlayerFloor < currentFloor && DXMath::GetDistance(targetPosition, position).x < 192.f)
        {
          movement->DropDown();
        }
      }

      // �÷��̾�� ���� ���ǿ� ���� ��
      else
      {
        movement->SetIsDirectingUp(true);
        movement->SetIsDirectingDown(false);

        // �̹� ���� ����� ������ �� ��� �������� �̵�
        if (currDest)
        {
          if (currDirection == Direction::RIGHT)
            movement->MoveRight();
          else
            movement->MoveLeft();
        }

        // ���� ����� ã��
        else
        {
          auto& stairs = currentRoom->GetTerrains(Room::Layer::STAIRS);

          if (!stairs.empty())
          {
            for (auto stair : stairs)
            {
              if (stair->GetFloor() == currentFloor)
              {
                if (currDest == nullptr)
                  currDest = stair;
                else
                  // �÷��̾�� �� ����� ����� ��ǥ�� ����
                  if (DXMath::GetDistance(currDest->GetPosition(), targetPosition).x >
                    DXMath::GetDistance(stair->GetPosition(), targetPosition).x)
                    currDest = stair;
              }
            }

            // ����� ���⿡ ���� �̵������� ����
            if (currDest)
            {
              if (currDest->GetPosition().x > position.x)
                currDirection = Direction::RIGHT;
              else
                currDirection = Direction::LEFT;
            }
          }
        }
      }

      //if (targetPosition.y > position.y)
      //{
      //  movement->SetIsDirectingUp(true);
      //  movement->SetIsDirectingDown(false);
      //}
      //
      //else if (targetPosition.y < position.y)
      //{
      //  movement->SetIsDirectingUp(false);
      //  movement->SetIsDirectingDown(true);
      //}
    }
    else
    {
      if (enemy->DetectPlayer())
        target = GameManager::Get()->GetPlayer();
    }
    break;
  case Enemy::State::ATTACK:
    delay = 2.0;
    break;
  case Enemy::State::RETURN:
    break;
  case Enemy::State::HIT:
    break;
  case Enemy::State::DEAD:
    break;
  default:
    break;
  }
}

void EnemyAI::GUI()
{
}
