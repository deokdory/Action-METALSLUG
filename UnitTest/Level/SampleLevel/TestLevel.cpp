#include "stdafx.h"
#include "TestLevel.h"
#include "Character/Agent.h"

#include "Component/Input/AgentInput.h"

#include "Character/Animations.h"
#include "UI/HUD.h"

TestLevel::TestLevel() { init(); }

void TestLevel::init() {
  auto player = new Agent(Values::CenterOfScreen, Vector3(44, 80, 0.f));

  player->InitGraphic(Animations::getEriLower(), ObjectGraphic::Slot::LOWER);
  player->InitGraphic(Animations::getEriUpper(), ObjectGraphic::Slot::UPPER);

  player->GetMovement()->SetLevel(this);

  objects.push_back(player);

  terrains.push_back(new Terrain(Vector3(640, 100, 0), Vector3(640, 64, 0),
                                 TexturePath + L"SamplePlate.png"));

  terrains.push_back(new Terrain(Vector3(900, 150, 0), Vector3(100, 100, 0),
                                 TexturePath + L"SamplePlate.png"));

  terrains.push_back(new Terrain(Vector3(300, 400, 0), Vector3(100, 100, 0),
                                 TexturePath + L"SamplePlate.png"));

  playerHud = new HUD();

  __super::init();

  GameManager::Get()->SetCurrentLevel(this);
}

void TestLevel::Update() { 
  playerHud->Update();
  __super::Update(); }

void TestLevel::Render() {
  playerHud->Render();
  __super::Render(); }
