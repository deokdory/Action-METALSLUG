#pragma once
#include "Character/Character.h"
#include "Game/UI/ProgressBar.h"

class Enemy : public Character
{
public:
  enum class State
  { SPAWNED, SCREAM, READY, MOVE, ATTACK, RUNAWAY, HIT, DEAD };

  Enemy(Vector3 position, Vector3 size);
  virtual ~Enemy();

  virtual void Update();
  virtual void Render();

  virtual void Damaged(float damage) override;
  //virtual void Healed(float heal) override;

  virtual void Die();

  bool DetectPlayer();
  bool CanAttack(GameObject* object);

  void SetState(State state) { this->currState = state; }
  State GetState() { return currState; }

  void Scream();
  void Attack(GameObject* target);

  Movement* GetMovement() { return movement; }
protected:
  
  Room* spawnedRoom = nullptr;
  Vector3 spawnedPosition = Values::ZeroVec3;

  State currState = State::SPAWNED;
  State prevState = State::READY;

  ProgressBar* hpBar = nullptr; // ü�� ���� ��

  Movement* movement; // �̵� ������Ʈ

  double timerAfterDead = 0.0; // �װ� �� �� �ð� üũ (3�� �� ����)

  BoundingBox* detectionArea = nullptr;
  BoundingBox* attackableArea = nullptr;

  class EnemyAI* enemyAI = nullptr;
};