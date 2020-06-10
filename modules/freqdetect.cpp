#include <math.h>
#include "freqdetect.h"

#ifndef MAX_32
#define MAX_32 0xFFFFFFFFU
#endif

using namespace daisysp;

void FreqDetect::Init(float sample_rate)
{
    sample_rate_ = sample_rate;
    last_ = false;
    active_ = false;
    last_counter_ = 0;
    counter_ = 0;
    threshold_ = .95;
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

    if (input > threshold_)
    {
	if (!last_)
	{
	    active_ = ! active_;
	}
	
	last_ = true;
    }
    else
    {
	last_ = false;
    }
}

float FreqDetect::GetFreqHz(){
  if (last_counter_ != 0)
  {
      return (float)sample_rate_ / (float)last_counter_;
  }
  return 0;
}
