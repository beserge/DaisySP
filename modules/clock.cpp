#include <math.h>
#include "clock.h"
#include "metro.h"
#include "freqdetect.h"


using namespace daisysp;

Metro tick_internal, tick;
FreqDetect freq;

void Clock::Init(float sample_rate)
{
    sample_rate_ = sample_rate;

    tick_internal.Init(1.f, sample_rate);
    tick.Init(1.f, sample_rate);
    freq.Init(sample_rate);
    
    mode_ = CLK_INTERNAL;

    div_amount_ = 1;

    mult_amount_ = 1;

    last_ = false;
}

void Clock::SetFreq(float freq)
{
    internal_freq_ = freq;
}

uint8_t Clock::Multiply(uint8_t input)
{
    freq.Process((float)input);
    //    tick.SetFreq(freq.GetFreqHz() * mult_amount_);
    tick.SetFreq(2);
    if (input)
    {
        if (!last_)
	{
	  //tick.Reset();
	}
	last_ = true;
    }
    else
    {
	last_ = false;
    }
    
    return tick.Process();
}

uint8_t Clock::Divide(uint8_t input)
{
  if (input)
  {
      div_count_++;
      div_count_ %= div_amount_;
      return div_count_ == 0;
  }
  return 0;
}

uint8_t Clock::Process(uint8_t input)
{
    if (mode_ == CLK_OFF)
    {
        return 0;
    }

    if (mode_ == CLK_INTERNAL)
    {
        tick_internal.SetFreq(internal_freq_);
	input = tick_internal.Process();
    }

    input = Divide(input);
    return Multiply(input);
}

void Clock::SetMode(clockmode mode)
{
    if( mode != mode_)
    {
	mode_ = mode;
	Reset();
    }
}

void Clock::Reset()
{
    
}
