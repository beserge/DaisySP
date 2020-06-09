#pragma once
#ifndef DSY_FREQDETECT_H
#define DSY_FREQDETECT_H
#include <stdint.h>
#ifdef __cplusplus

namespace daisysp
{

class FreqDetect
{
  public:
    FreqDetect() {}
    ~FreqDetect() {}

    void Init(float sample_rate);

    void Process(float in);

    /** \return ms per tick */
    inline float GetFreqMs() { return (last_counter_ / sample_rate_) * 1000; }

    /** \return Samples per tick */
    inline float GetFreqSamp() { return last_counter_; }

    /** \return Ticks per second */
    inline float GetFreqHz() { return sample_rate_ / last_counter_; }
    
  private:
      float sample_rate_;
      bool active_;
      uint32_t counter_, last_counter_;
      void Increment();
};
} // namespace daisysp
#endif
#endif
