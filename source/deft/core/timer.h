#ifndef __DEFT_TIMER_H__
#define __DEFT_TIMER_H__

#include <chrono>

namespace deft {

class Timer {
 public:
  void initialize() {
    _startTime = _lastSecondTime = std::chrono::steady_clock::now();
  }

  void tick() {
    auto duration = _currentFrameTime - _lastSecondTime;
    if (duration > std::chrono::seconds(1)) {
      _fps            = _frameCount;
      _frameCount     = 0;
      _lastSecondTime = _currentFrameTime;
    } else {
      ++_frameCount;
    }
    _currentFrameTime = std::chrono::steady_clock::now();

    _deltaTime     = _currentFrameTime - _lastFrameTime;
    _lastFrameTime = _currentFrameTime;

    _totalTime = _currentFrameTime - _startTime;
  }

  int   getFps() { return _fps; }
  float getTotalTime() { return _totalTime.count() / 1000000000.0f; }
  float getDeltaTime() { return _deltaTime.count() / 1000000000.0f; }

 private:
  std::chrono::time_point<std::chrono::steady_clock> _startTime;
  std::chrono::time_point<std::chrono::steady_clock> _currentFrameTime;
  std::chrono::time_point<std::chrono::steady_clock> _lastFrameTime;
  std::chrono::time_point<std::chrono::steady_clock> _lastSecondTime;

  std::chrono::nanoseconds _deltaTime;
  std::chrono::nanoseconds _totalTime;

  int _frameCount;
  int _fps;
};

}  // namespace deft

#endif  // __DEFT_TIMER_H__