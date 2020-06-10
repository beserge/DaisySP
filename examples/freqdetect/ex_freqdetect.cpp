#include "daisysp.h"
#include "daisy_seed.h"

using namespace daisysp;
using namespace daisy;

static DaisySeed  seed;
static Oscillator osc_square, osc_sine, lfo;
static FreqDetect freqdetect;

static void AudioCallback(float *in, float *out, size_t size)
{
    float   sine_out, square_out, lfo_out;

    osc_sine.SetFreq(freqdetect.GetFreqHz());
    
    for(size_t i = 0; i < size; i += 2)
    {
        sine_out = osc_sine.Process();
	lfo_out = lfo.Process() + 250;

	osc_square.SetFreq(lfo_out);
	square_out = osc_square.Process();

	freqdetect.Process(square_out);
	
        // left out
        out[i] = square_out * .5;

        // right out
        out[i + 1] = sine_out;
    }
}

int main(void)
{
    // initialize seed hardware and daisysp modules
    float sample_rate;
    seed.Configure();
    seed.Init();
    sample_rate = seed.AudioSampleRate();

    //Init freq detect object
    freqdetect.Init(sample_rate);
    freqdetect.SetThreshold(.8);
    
    // set parameters for sine oscillator object
    osc_sine.Init(sample_rate);
    osc_sine.SetWaveform(Oscillator::WAVE_SIN);
    osc_sine.SetFreq(600);
    osc_sine.SetAmp(1);

    // Set parameters for square object
    osc_square.Init(sample_rate);
    osc_square.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_square.SetFreq(300);
    osc_square.SetAmp(1);

    //Set parameters for lfo
    lfo.Init(sample_rate);
    lfo.SetWaveform(Oscillator::WAVE_TRI);
    lfo.SetFreq(1);
    lfo.SetAmp(250);
    

    // start callback
    seed.StartAudio(AudioCallback);


    while(1) {}
}
