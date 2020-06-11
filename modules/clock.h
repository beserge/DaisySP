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

    enum clockmode { 
        CLK_INTERNAL,
        CLK_EXTERNAL,
	CLK_OFF,
    };

    void Init(float sample_rate);

    uint8_t Process(uint8_t input);

    void SetMode(clockmode mode); 

    void SetFreq(float freq);
    
    inline void SetDiv(int div) { div_amount_ = div; }

    inline void SetMult(int mult) { mult_amount_ = mult; }
    
  private:
    float sample_rate_, measure_freq_, internal_freq_;
    int mult_amount_, div_amount_, div_count_;
    clockmode mode_;
    bool last_;
    
    void Reset();
    uint8_t Divide(uint8_t input);
    uint8_t Multiply(uint8_t input);
};
} // namespace daisysp
#endif
#endif
