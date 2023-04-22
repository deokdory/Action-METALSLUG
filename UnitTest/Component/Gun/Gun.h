#pragma once
#include "Bullet/Bullet.h"

class Gun {
  enum class FireMode {
    SEMI_AUTO, BURST, AUTO
  };

public:
  Gun(GameObject* owner, float rpm, float vertRecoil, float horiRecoil, 
    float bulletSpeed, , float bulletDamage, float magazine, float magazineMax, float ammo, float ammoMax);

  virtual ~Gun();

  static Gun* HeavyMachinegun() { return new Gun(4, 0, 0, 16, 30, 30, 180, 180); }

  void Update(Vector3 position, Vector3 axis);
  void Render();

  bool magazineIsEmpty() { return magazine == 0; }

  void PullTrigger();
  void ReleaseTrigger();

  void Reload();
  void SupplyAmmo(UINT ammo);

  void SwitchMode();

protected:
  void Fire(Vector3 position, Vector3 axis);
  void SetBullet(Bullet* bullet) { this->bullet = bullet; }
  void Recoil();

  float rpm; // ���� �ӵ�
  float vertRecoil; // ���� �ݵ�
  float horiRecoil; // �¿� �ݵ�
  float bulletSpeed; // ź��

  UINT magazine; // ���� źâ �� �ܿ� ź��
  UINT magazineMax; // ��ź

  float ammo; // ���� ���� ���� ź�� ��
  float ammoMax; // ���� ������ �ִ� ź�� ��

  FireMode mode = FireMode::AUTO;
  Bullet* bullet = nullptr; // ź ����

  double lastFire = 0.0;

  bool isTriggered = false;
  bool isTriggeredPrev = false;

  bool isBursting = false;

  UINT burstCount = 0;
};