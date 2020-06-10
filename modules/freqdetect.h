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
    inline float GetFreqMs() { return ((float)last_counter_ / (float)sample_rate_) * 1000.f; }

    /** \return Samples per tick */
    inline float GetFreqSamp() { return (float)last_counter_; }

    /** \return Ticks per second */
    float GetFreqHz();

    /** param thresh Level of signal's positive peak. Defaults to .95 */
    inline void SetThreshold(float thresh) { threshold_ = thresh; }
    
  private:
      float sample_rate_, threshold_;
      bool active_, last_;
      uint32_t counter_, last_counter_;
      void Increment();
};
} // namespace daisysp
#endif
#endif
