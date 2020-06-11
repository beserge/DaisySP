#include <math.h>
#include "clock.h"
#include "metro.h"
#include "freqdetect.h"


using namespace daisysp;

static Metro tick_internal, tick;
static FreqDetect freq;

void Clock::Init(float sample_rate)
{
    sample_rate_ = sample_rate;
    tick_internal.Init(1, sample_rate);
    tick.Init(1, sample_rate);
    freq.Init(sample_rate);
    Reset();
    mode_ = CLK_INTERNAL;
    div_amount_ = 1;

    mult_amount_ = 1;
    mult_thresh_ = .9;
    last_ = false;
}

void SetFreq(float freq)
{
    tick.SetFreq(freq);
}

void Clock::ProcessExternal(float input)
{
    freq.Process(input);
    measure_freq_ = freq.GetFreqHz();
    if (measure_freq_ != freq_)
        SetFreq(measure_freq_);
}

uint8_t Clock::Divide(uint8_t input)
{
  if (input)
  {
      div_count_++;
      div_count_ %= div_amount_;
  }

  return div_count_ == 0;
}

uint8_t Clock::Multiply(uint8_t input)
{
    freq.Process(input);
    tick.SetFreq(freq.GetFreqHz());

    if (input > mult_thresh_)
    {
        if (!last_)
	{
	    tick.Reset();
	}
	last_ = true;
    }
    else
    {
	last_ = false;
    }
    
    return tick.Process();
}

uint8_t Clock::Process(uint8_t input)
{
    if (mode_ == CLK_OFF)
    {
        return 0;
    }

    if (mode_ == CLK_INTERNAL)
    {
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
