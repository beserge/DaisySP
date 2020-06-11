#include "daisysp.h"
#include "daisy_seed.h"

using namespace daisysp;
using namespace daisy;

static DaisySeed  seed;
static Clock      clock, subdiv, mult;
static Oscillator osc_sine;
static AdEnv env;

static void AudioCallback(float *in, float *out, size_t size)
{
    float   sine, env_out;
    uint8_t tic;
    for(size_t i = 0; i < size; i += 2)
    {
        tic = clock.Process(0);
        if(mult.Process(tic))
        {
	    env.Trigger();
	}

	if(subdiv.Process(tic))
	{
	    env.Trigger();
	}
	
	env_out = env.Process();
	osc_sine.SetAmp(env_out);
        sine = osc_sine.Process();

        // left out
        out[i] = sine;

        // right out
        out[i + 1] = sine;
    }
}

int main(void)
{
    // initialize seed hardware and daisysp modules
    float sample_rate;
    seed.Configure();
    seed.Init();
    sample_rate = seed.AudioSampleRate();

    // initialize Clock object
    clock.Init(sample_rate);
    clock.SetFreq(4.f);

    // init subdivision
    subdiv.Init(sample_rate);
    subdiv.SetMode(Clock::CLK_EXTERNAL);
    subdiv.SetDiv(2);

    // init multiply
    mult.Init(sample_rate);
    mult.SetMode(Clock::CLK_EXTERNAL);
    mult.SetDiv(4);
    mult.SetMult(3);
    
    // set parameters for sine oscillator object
    osc_sine.Init(sample_rate);
    osc_sine.SetWaveform(Oscillator::WAVE_SIN);
    osc_sine.SetFreq(400);
    osc_sine.SetAmp(1);

    //Set envelope parameters
    env.Init(sample_rate);
    env.SetTime(ADENV_SEG_ATTACK, .01);
    env.SetTime(ADENV_SEG_DECAY, .05);
    env.SetMax(.5);
    env.SetMin(0);
    env.SetCurve(0);
    
    // start callback
    seed.StartAudio(AudioCallback);

    while(1) {}
}
