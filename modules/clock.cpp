#include <math.h>
#include "clock.h"

using namespace daisysp;

void Clock::Init(float sample_rate)
{
    sample_rate_ = sample_rate;
}

uint8_t Clock::Process()
{
  return 0;
}
