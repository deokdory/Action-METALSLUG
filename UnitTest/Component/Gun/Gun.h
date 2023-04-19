#pragma once
#include "Bullet/Bullet.h"



class Gun {
  enum class FireMode {
    SEMI_AUTO, BURST, AUTO
  };

public:
  Gun(float rpm, float vertRecoil, float horiRecoil, float bulletSpeed, float magazine, float magazineMax, float ammo, float ammoMax);
  ~Gun();

  void Fire(Vector3 position, Vector3 axis);
  void Reload();
  void SupplyAmmo(UINT ammo);

  bool mgzIsEmpty() { return magazine == 0; }

protected:
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

  Bullet* bullet; // ź ����
};