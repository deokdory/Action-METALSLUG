#pragma once

#include "Geometries/TextureRect.h"
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

class ObjectGraphic {
public:
  enum class Slot { NORMAL, LOWER, UPPER }; // ���� ���� (�⺻, ��ü, ��ü)
  enum class Type { TEXTURE, ANIMATION }; // Ÿ�� ���� (�ؽ���, �ִϸ��̼�)

  ObjectGraphic(class GameObject* object);
  ~ObjectGraphic();

  void Update();
  void Render();
  
  // Ȱ��ȭ ���� ����
  void SetVisible(bool visible, Type type, Slot slot = Slot::NORMAL);

  // ������Ʈ�� �ʱ�ȭ
  bool InitTexture(std::wstring path, Slot slot = Slot::NORMAL);
  bool InitAnimation(Animator* animator, Slot slot = Slot::NORMAL);

  // ������Ʈ�� ����
  void DeleteGraphic(Type type, Slot slot);

  // �ִϸ��̼� ���� ���
  void SetCurrentAnimation(std::wstring name, Slot slot = Slot::NORMAL);
  void SetCurrentFrame(UINT index, Slot slot = Slot::NORMAL);

  // ������Ʈ�� �߽��� ����
  void SetAnchorPoint(AnchorPoint anchor, Type type, Slot slot = Slot::NORMAL);

  void AddRotation(float rotation, Type type, Slot slot = Slot::NORMAL);

  // �ִϸ����� 
  // Animator* GetAnimator(Slot slot = Slot::NORMAL);

protected:
  class GameObject* object; // �׷��� ������Ʈ�� ��ü

  bool texVisible[3]; // �ؽ��� ������Ʈ�� Ȱ�� ����
  std::vector<TextureRect*> texRects = {};

  bool animVisible[3]; // �ִϸ��̼� ������Ʈ�� Ȱ�� ����
  std::vector<AnimationRect*> animRects = {}; // �ִϸ��̼� ��Ʈ
  std::vector<Animator*> animators = {}; // �ִϸ�����
};