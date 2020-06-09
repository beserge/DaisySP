#include <math.h>
#include "freqdetect.h"

#ifndef MAX_32
#define MAX_32 0xFFFFFFFFU
#endif

using namespace daisysp;

void FreqDetect::Init(float sample_rate)
{
    sample_rate_ = sample_rate;
}

void FreqDetect::Increment()
{
    if (active_)
    {
	counter_ ++;
    }
    if (counter_ ==  MAX_32)
    {
	counter_ = 0;
    }
}

void FreqDetect::Process(float input)
{
    Increment();
  
    if (!active_ && counter_ != 0)
      {
	last_counter_ = counter_;
	counter_ = 0;
      }
    
    if (input > .95)
      {
	active_ = ! active_;
      }
}
