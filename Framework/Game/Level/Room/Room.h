#pragma once

class Room
{
public:
  enum class Type { EMPTY, UPGRADE, BATTLE, ROOT, BOSS, ELIMINATE, ELEVATE, PASSAGE };
  enum class Layer { BACKGROUND, MIDDLEGROUND, FOREGROUND };

  // ������ �� ����, ����Ǵ� ���� ��, ����Ǵ� ����
  Room(Type type, Room* prevRoom, Direction direction);

  // �� ������ ���� �����Ͽ� ����
  Room(Type type, std::wstring mapDataFilePath, Room* prevRoom, Direction direction);

  // ��� ���� ( 0��, 1��, 2�� Ȥ�� -1(��� ��)
  Room(int enterFloorL, int enterFloorR);

  Room(Type type); // TEST
  ~Room();

  void Update();
  void Render();
  void ForegroundRender();

  Vector3 GetPosition() { return this->position; }
  Vector3 GetSize() { return this->size; }

  UINT GetEnterFloor(bool isLeft) { return isLeft ? enterFloorL : enterFloorR; }

  void SetLinkedRoom(Direction direction, Room* linkedRoom);
  Room* GetLinkedRoom(Direction direction);

  BoundingBox* GetArea() { return area; }
  Type GetRoomType() { return type; }

  std::vector<Terrain*>& GetTerrains(Layer layer);

private:
  Color getAreaColor(Type type);

  bool initTerrains(std::wstring mapDataFilePath, Room* prevRoom = nullptr, Direction direction = NONEDIRECTION);
  void moveTerrainsToRoomPosition(Room* prevRoom, Direction direction);
  Vector3 tilePosToVector3(Terrain::Type trnType, UINT tilePositionX, UINT tilePositionY);
  Type type = Type::EMPTY;

  // ���� �Ա� ���� ( 0 ~ 2 )
  int enterFloorL = -1;
  int enterFloorR = -1;

  Vector3 position = Values::ZeroVec3;
  Vector3 size = Values::ZeroVec3;

  UINT totalTileX = 0;
  UINT totalTileY = 0;
  
  GameObject* elevator = nullptr;

  std::vector<Terrain*> trnBackground;
  std::vector<Terrain*> trnMiddleground;
  std::vector<Terrain*> trnForeground;

  wstring mapDataFilePath = L"";

  Room* linkedRoomLeft = nullptr;
  Room* linkedRoomRight = nullptr;

  BoundingBox* area = nullptr;
  // ENEMIES
  // PROPS
  // TRAPS
  // 
};