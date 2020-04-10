# STM32F4AudioEqualizer

_Sample code to read frames from ADC into circular buffer, filter samples using CMSIS DSP and write filtered samples to the DAC._

## 8 bands equalizer

_Each band is a band-pass 2nd order butterworth, coefficients can be adapted using Matlab script **Butter_Script**._



### Device settings:

_**Fs:** 80Khz_
_**Target:** STM32F429 MCU, but should work with any CortexM4 or above microcontroller_

```
Da un ejemplo
```

### Requirements:

_Timer interruptions to read samples from ADC at Fs_

_insertInputStreamSample(uint32_t * sample) <- inserts sample into buffer_

_float32_t * getOutputStreamSample(void) <- reads sample from buffer_

_INITfilteringCoeffs(INPUT_STREAM_STATE_FLAG* inputStreamStateFlag, void (*overrunStreamCallback)(void)) <- init function, Flag states indicates that buffers can be filtered on the main loop, overrunStreamCallback() is called if filtering takes longer that it should_

_filterBuffers(void) if inputStreamStateFlag==INPUT_STREAM_READY call this function_
