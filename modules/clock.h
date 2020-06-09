#pragma once
#ifndef DSY_CLOCK_H
#define DSY_CLOCK_H
#include <stdint.h>
#ifdef __cplusplus

namespace daisysp
{

class Clock
{
  public:
    Clock() {}
    ~Clock() {}
    void Init(float sample_rate);

    uint8_t Process();


  private:
    float sample_rate_;
};
} // namespace daisysp
#endif
#endif
