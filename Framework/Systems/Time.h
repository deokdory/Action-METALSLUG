#pragma once

class Time : public SingletonBase<Time> {
 public:
  friend class SingletonBase<Time>;

  static bool Stopped() { return isTimerStopped; }
  static double Delta() { return isTimerStopped ? 0.0f : timeElapsed; }

  void Update();

  void Start();
  void Stop();

  double FPS() const { return framePerSecond; }
  double Running() const { return runningTime; }

  void InitNewTimer(std::string name);
  void UpdateTimer(std::string name);
  double GetTimer(std::string name);
  double GetTimerDelta(std::string name);

 private:
  Time(void);
  ~Time(void);

	static bool isTimerStopped;///< Ÿ�̸� ����
	static float timeElapsed;///< ���� ���������κ��� ����ð�

	INT64 ticksPerSecond;///< �ʴ� ƽī��Ʈ
	INT64 currentTime;///< ���� �ð�
	INT64 lastTime;///< �����ð�
	INT64 lastFPSUpdate;///< ������ FPS ������Ʈ �ð�
	INT64 fpsUpdateInterval;///< fps ������Ʈ ����

	UINT frameCount;///< ������ ��
	double runningTime;///< ���� �ð�
	double framePerSecond;///< FPS

	std::map<std::string, double> timer;
};