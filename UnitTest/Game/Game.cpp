#include "stdafx.h"
#include "Game.h"

#include "GameWorld.h"

void Game::Init() { 
  prevTime = Time::Get()->Running(); }

void Game::Destroy() {}

void Game::Update() {
  double currTime = Time::Get()->Running();
  double elapsedTime = currTime - prevTime;
  prevTime = currTime;
  lag += elapsedTime;

  // �Է� ó�� ( ��Ʈ�� )

  while (lag >= MS_PER_UPDATE) {
    gameWorld->update();
    lag -= MS_PER_UPDATE;
  }
}

void Game::Render() { gameWorld->render(lag / MS_PER_UPDATE); }

void Game::PostRender() {}

void Game::GUI() {}
