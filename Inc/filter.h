#include "main.h"
#include "math.h"
#include "arm_math.h"

typedef char INPUT_STREAM_STATE_FLAG;

#define FRAME_SIZE 400
#define FREC_TEST 1000

#define INPUT_STREAM_READY 1
#define INPUT_STREAM_NOTREADY 0


//User functions
void insertInputStreamSample(uint32_t * sample);
void insertInputStreamSampleMock(void );
float32_t * getOutputStreamSample(void);
void INITfilteringCoeffs(INPUT_STREAM_STATE_FLAG* inputStreamStateFlag, void (*overrunStreamCallback)(void));
void filterBuffers(void);
void adjustBandsGain(float32_t G0, float32_t G1, float32_t G2, float32_t G3, float32_t G4, float32_t G5, float32_t G6, float32_t G7);
////////////////////////////////

void rotateBuffers(void);
