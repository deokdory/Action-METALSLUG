#pragma once

class LevelEditor
{
public:
  LevelEditor();
  ~LevelEditor();

  void Init();
  void Update();
  void Render();
  void GUI();

  Vector3 GetTileCenterPosition(Vector3 position); // ���� ��ġ�� �� Ÿ�� ��� �߾� ���������� ��ȯ

private:
  void save();
  void load();

  std::vector<Room*> rooms;
};