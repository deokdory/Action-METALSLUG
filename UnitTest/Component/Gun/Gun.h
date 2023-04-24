#pragma once
#include "Bullet/Bullet.h"

class Gun {
  enum class FireMode {
    SEMI_AUTO, BURST, AUTO
  };

public:

  virtual ~Gun();

  void Update(Vector3 position, Vector3 axis);
  void Render();
  void GUI();

  bool magazineIsEmpty() { return magazine == 0; }

  void PullTrigger();
  void ReleaseTrigger();

  void Reload();
  void SupplyAmmo(UINT ammo);

  void SwitchMode();

  static Gun* InitHMG(GameObject* owner);

protected:
  Gun(GameObject* owner, float rpm, float vertRecoil, float horiRecoil, 
    float bulletSpeed, float bulletDamage, UINT magazine, UINT magazineMax, UINT ammo, UINT ammoMax);

  void Fire(Vector3 position, Vector3 axis);
  void SetBullet(Bullet* bullet) { this->bullet = bullet; }
  void Recoil();

  float rpm; // ���� �ӵ�
  float vertRecoil; // ���� �ݵ�
  float horiRecoil; // �¿� �ݵ�
  float bulletSpeed; // ź��

  UINT magazine; // ���� źâ �� �ܿ� ź��
  UINT magazineMax; // ��ź

  UINT ammo; // ���� ���� ���� ź�� ��
  UINT ammoMax; // ���� ������ �ִ� ź�� ��

  FireMode mode = FireMode::AUTO;
  Bullet* bullet = nullptr; // ź ����

  double lastFire = -1.0;

  bool isTriggered = false;
  bool isTriggeredPrev = false;

  //bool isBursting = false;

  UINT burstCount = 0;
};