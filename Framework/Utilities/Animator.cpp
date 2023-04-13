#include "Framework.h"
#include "Animator.h"

// playRate�� 0 �̸��� ��� ������� ����
AnimationClip::AnimationClip(std::wstring clipName, Texture2D* srcTex,
                             UINT frameCount, Vector2 startPos, Vector2 endPos,
                             bool bReversed, float playRate,
                             Vector2 reposition)
    : clipName(clipName),
      frameCount(frameCount),
      bReversed(bReversed), 
      playRate(playRate) {

  srv = srcTex->GetSRV();

  // �ؽ����� �ʺ�� ����
  float imageWidth = srcTex->GetWidth();
  float imageHeight = srcTex->GetHeight();

  // Ŭ�� ������ ( �ִϸ��̼��� �׷��� �ִ� ��ü �ؽ����� ������ )
  Vector2 clipSize = endPos - startPos;

  // �� �������� ������
  frameSize.x = clipSize.x / frameCount;
  frameSize.y = clipSize.y;

  // �ؼ� ������ ���
  texelFrameSize.x = frameSize.x / imageWidth;
  texelFrameSize.y = frameSize.y / imageHeight;

  // �ؼ� ���� ��ġ
  Vector2 texelStartPos;
  texelStartPos.x = startPos.x / imageWidth;
  texelStartPos.y = startPos.y / imageHeight;

  Vector2 keyframe;

  for (UINT i = 0; i < frameCount; i++) {
    keyframe.x = texelStartPos.x + (texelFrameSize.x * i);
    keyframe.y = texelStartPos.y;

    keyframes.push_back(keyframe);
  }
}

Animator::Animator() {}

Animator::~Animator() {
  for (auto clip : animClips) {
    SAFE_DELETE(clip.second);
  }
}

void Animator::Update() {
  auto playRate = currentClip->playRate;
  auto currTime = Time::Get()->Running();

  // if (playRate < 0.0f) {
  auto deltaTime = currTime - prevTime;

  if (deltaTime > playRate) {
    if (currentClip->bReversed == false) {
      currentFrameIndex++;
      if (currentFrameIndex == currentClip->frameCount) {
        currentFrameIndex = 0;
      }
    } else {
      currentFrameIndex--;
      if (currentFrameIndex == -1) {
        currentFrameIndex = currentClip->frameCount - 1;
      }
    }
    prevTime = currTime;
  }

  //}
  currentFrame = currentClip->keyframes[currentFrameIndex];
}

void Animator::AddAnimClip(AnimationClip* animClip) {
  animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(std::wstring clipName) {
  if (currentClip == nullptr && CheckExist(clipName) == true) {
    currentClip = animClips.find(clipName)->second;
  } else if (currentClip != nullptr && currentClip->clipName == clipName)
    return;

  if (CheckExist(clipName)) {
    currentClip = animClips.find(clipName)->second;
    prevTime = .0f;
    
    // ������� Ȱ��ȭ ������ ���
    if (currentClip->bReversed == true) {
      currentFrameIndex = currentClip->frameCount - 1;
    } else {
      currentFrameIndex = 0;
    }
    // ���� ������ ������Ʈ
    currentFrame = currentClip->keyframes[currentFrameIndex];
    prevTime = Time::Get()->Running();
  }
}

void Animator::SetCurrentFrame(UINT index) {
  auto keyframes = currentClip->keyframes;
  if (index >= keyframes.size()) return;

  currentFrameIndex = index;
}

Animator* Animations::getKnight() {
  Texture2D* srcTex = new Texture2D(TexturePath + L"Ye_Oldy_Knight_Guy.png");

  Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

  AnimationClip* Idle =
      new AnimationClip(L"Idle", srcTex, 4, Vector2(0, 0), Vector2(64, 19),
                        false, 1.0f / 3.0f);  // 16, 20

  AnimationClip* Run =
      new AnimationClip(L"Run", srcTex, 6, Vector2(0, 21), Vector2(96, 41),
                        false, 1.0f / 6.0f);  // 16, 21

  AnimationClip* Jump = new AnimationClip(L"Jump", srcTex, 1, Vector2(0, 42),
                                          Vector2(16, 63));  // 17, 22

  AnimationClip* Hit = new AnimationClip(L"Hit", srcTex, 1, Vector2(64, 0),
                                         Vector2(85, 19));  // 22 x 20

  Animator* animator = new Animator();

  animator->AddAnimClip(Idle);
  animator->AddAnimClip(Run);
  animator->AddAnimClip(Jump);
  animator->AddAnimClip(Hit);

  animator->SetCurrentAnimClip(L"Idle");

  SAFE_DELETE(srcTex);
  return animator;
}

Animator* Animations::getEriUpperTest() {
  Texture2D* aimRifleTex = new Texture2D(TexturePath + L"upper_aim_rifle.png");

  AnimationClip* aimRifle =
      new AnimationClip(L"aimRifle", aimRifleTex, 10, Vector2(0, 0),
                        Vector2(459, 62), false, 1.0f / 3.0f);

  Animator* animator = new Animator();

  animator->AddAnimClip(aimRifle);

  animator->SetCurrentAnimClip(L"aimRifle");
  //animator->SetCurrentFrame(4);

  SAFE_DELETE(aimRifleTex);
  return animator;
}

Animator* Animations::getEriLowerTest() {

  Texture2D* srcTex = new Texture2D(TexturePath + L"eri_test.png");

  AnimationClip* idle =
      new AnimationClip(L"idle", srcTex, 1, Vector2(0, 30),
                        Vector2(19, 53), false, -1.0f);
  AnimationClip* run =
      new AnimationClip(L"run", srcTex, 12, Vector2(0, 208), Vector2(360, 234),
                        false, 1.0f / 12.0f);

  AnimationClip* jumpBeginRunning =
      new AnimationClip(L"jumpBeginRunning", srcTex, 3, Vector2(0, 54),
                        Vector2(104, 79), false, 1.0f / 3.0f);

    AnimationClip* jumpEndRunning =
      new AnimationClip(L"jumpEndRunning", srcTex, 3, Vector2(0, 80),
                        Vector2(104, 105), false, 1.0f / 3.0f);

    Animator* animator = new Animator();

    animator->AddAnimClip(idle);
    animator->AddAnimClip(run);
    animator->AddAnimClip(jumpBeginRunning);
    animator->AddAnimClip(jumpEndRunning);

    animator->SetCurrentAnimClip(L"run");

  SAFE_DELETE(srcTex);
  return animator;
}
