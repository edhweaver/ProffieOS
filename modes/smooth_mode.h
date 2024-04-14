#ifndef MODES_SMOOTH_MODE_H
#define MODES_SMOOTH_MODE_H

#include "mode.h"
#include "select_cancel_mode.h"

namespace mode {

template<class SPEC>
struct SmoothWraparoundMode : public SPEC::SelectCancelMode {
  // 3 rotations to get back to the original color
  virtual float revolutions() { return 3.0f; }
  void mode_activate(bool onreturn) override {
    last_angle_ = fusor.angle2();
    angle_ = (get() + 0.5) * M_PI * 2 * revolutions() / 32768;
  }

  // x = 0-32767
  virtual int get() = 0;
  virtual void set(int x) = 0;

  void mode_Loop() override {
    float a = fusor.angle2();
    float delta = a - last_angle_;
    last_angle_ = a;
    angle_ = fmodf(angle_ + delta, M_PI * 2 * revolutions());
    set(0x7fff & (int32_t)(a * (32768 / (M_PI * 2 * revolutions()))));
  }
  
  float angle_;
  float last_angle_;
};

template<class SPEC>
struct SmoothMode : public SPEC::SelectCancelMode {
  virtual float revolutions() { return 3.0f; }
  void mode_activate(bool onreturn) override {
    last_angle_ = fusor.angle2();
<<<<<<< HEAD
    angle_ = (get() + 0.5) * M_PI * 2 * revolutions() / 32768;
=======
    val_ = get();
    angle_ = (val_ + 0.5) * M_PI * 2 * revolutions() / 32768;
>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e
  }

  // x = 0-32767
  virtual int get() = 0;
  virtual void set(int x) = 0;
<<<<<<< HEAD
=======
  virtual void save() {}

  void select() override {
    save();
    popMode();
  }

  void exit() override {
    set(val_);
  }
>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e

  void mode_Loop() override {
    float a = fusor.angle2();
    float delta = a - last_angle_;
    last_angle_ = a;
    angle_ += delta;
    if (angle_ < 0.0) {
      angle_ = 0.0;
      // play "min reached" sound?
    }
    if (angle_ > M_PI * 2 * revolutions()) {
      angle_ = M_PI * 2 * revolutions();
      // play "max reached" sound?
    }
    set((int32_t)(a * (32767 / (M_PI * 2 * revolutions()))));
  }
  
  float angle_;
  float last_angle_;
<<<<<<< HEAD
};

// TODO: Smooth mode without wraparound.

=======
  int val_;
};

>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e
} // namespace mode

#endif
