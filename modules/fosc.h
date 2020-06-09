
#pragma once
#ifndef DSY_FOSC_H
#define DSY_FOSC_H
#ifdef __cplusplus

namespace daisysp
{
class FOsc
{
  public:
    FOsc() {}
    ~FOsc() {}
    void Init(float sample_rate);

    float Process();

  private:
};
} // namespace daisysp
#endif
#endif
