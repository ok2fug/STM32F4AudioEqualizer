#include "filter.h"
#include "stm32f4xx_hal_adc.h"


//8 Bands constant Q = 1.179858 equalizer coefficients
//X = 2.279705, n=1.509869
//Fs = 80Khz

//------------------------------------------//

//F1 = 50.000000Hz
arm_biquad_casd_df1_inst_f32 S_1;
static float32_t firStateF32_1[8];
static float32_t firCoeffs_1[10] = { 0.00000000094754358164,
		0.00000000189508716328, 0.00000000094754358164, 1.99692021940218510000,
		-0.99694871896133841000, 2915.95045834950320000000,
		-5831.90091669900630000000, 2915.95045834950320000000,
		1.99834197091844580000, -0.99835029581741408000 };

//------------------------------------------//

//F2 = 113.985228Hz
arm_biquad_casd_df1_inst_f32 S_2;
static float32_t firStateF32_2[8];
static float32_t firCoeffs_2[10] = { 0.00000001689923616822,
		0.00000003379847233644, 0.00000001689923616822, 1.99290975941891760000,
		-0.99305758348298645000, 847.15866478976716000000,
		-1694.31732957953430000000, 847.15866478976716000000,
		1.99619988581698090000, -0.99624310503698610000 };

//------------------------------------------//

//F3 = 259.852645Hz
arm_biquad_casd_df1_inst_f32 S_3;
static float32_t firStateF32_3[8];
static float32_t firCoeffs_3[10] = { 0.00000030023790536174,
		0.00000060047581072348, 0.00000030023790536174, 1.98347908038118530000,
		-0.98424390437169829000, 246.12689473940972000000,
		-492.25378947881944000000, 246.12689473940972000000,
		1.99123159227960000000, -0.99145566351621406000 };

//------------------------------------------//

//F4 = 592.387259Hz
arm_biquad_casd_df1_inst_f32 S_4;
static float32_t firStateF32_4[8];
static float32_t firCoeffs_4[10] = { 0.00000528774306565085,
		0.00001057548613130170, 0.00000528774306565085, 1.96051146698833010000,
		-0.96444588581994239000, 71.51621024317120100000,
		-143.03242048634240000000, 71.51621024317120100000,
		1.97946614278487450000, -0.98062424758225797000 };

//------------------------------------------//

//F5 = 1350.467937Hz
arm_biquad_casd_df1_inst_f32 S_5;
static float32_t firStateF32_5[8];
static float32_t firCoeffs_5[10] = { 0.00009130432252982834,
		0.00018260864505965669, 0.00009130432252982834, 1.90085165799791020000,
		-0.92082512731553923000, 20.79292470396558200000,
		-41.58584940793116400000, 20.79292470396558200000,
		1.95039100712264380000, -0.95633401592462297000 };

//------------------------------------------//

//F6 = 3078.667918Hz
arm_biquad_casd_df1_inst_f32 S_6;
static float32_t firStateF32_6[8];
static float32_t firCoeffs_6[10] = { 0.00150822839332050150,
		0.00301645678664100300, 0.00150822839332050150, 1.73069058804171180000,
		-0.82902117231128647000, 6.06471254841306970000,
		-12.12942509682613900000, 6.06471254841306970000,
		1.87276503602386240000, -0.90275502639024374000 };

//------------------------------------------//

//F7 = 7018.453297Hz
arm_biquad_casd_df1_inst_f32 S_7;
static float32_t firStateF32_7[8];
static float32_t firCoeffs_7[10] = { 0.02259357380357221100,
		0.04518714760714442200, 0.02259357380357221100, 1.20649466215226920000,
		-0.65688796490491885000, 1.79876183201647090000,
		-3.59752366403294180000, 1.79876183201647090000, 1.64182062363325890000,
		-0.78690396405084084000 };

//------------------------------------------//

//F8 = 16000.000000Hz
arm_biquad_casd_df1_inst_f32 S_8;
static float32_t firStateF32_8[8];
static float32_t firCoeffs_8[10] = { 0.27221015820162170000,
		0.54442031640324340000, 0.27221015820162170000, -0.29739547055410254000,
		-0.44863740397052193000, 0.58507033443307133000,
		-1.17014066886614270000, 0.58507033443307133000, 0.91429491038655886000,
		-0.52523390884670329000 };

//------------------------------------------//

float32_t adcMockSignal[FRAME_SIZE];

float32_t circularBuffers[4][FRAME_SIZE];

//Pointer to input data stream
float32_t *inputStream;

//Pointer to data source for filtering (this points to input stream upon filling the input buffer)
float32_t *filterStreamSrc;

//Pointer to filtered data stream
float32_t *filterStreamDst;

//Pointer to output data stream
float32_t *outputStream;

//Gain for each band
float32_t bandGainArray[8];

void (*overrunStreamPrt)(void);

int32_t sampleCurrentIndex = 0;

INPUT_STREAM_STATE_FLAG* inputStreamFrameReadyFlag;

void INITfilteringCoeffs(INPUT_STREAM_STATE_FLAG* inputStreamStateFlag, void (*overrunStreamCallback)())
{
	int32_t i = 0;

	inputStreamFrameReadyFlag = inputStreamStateFlag;

	*inputStreamFrameReadyFlag = INPUT_STREAM_NOTREADY;

	overrunStreamPrt = overrunStreamCallback;

	arm_biquad_cascade_df1_init_f32(&S_1, 2, firCoeffs_1, firStateF32_1);

	arm_biquad_cascade_df1_init_f32(&S_2, 2, firCoeffs_2, firStateF32_2);

	arm_biquad_cascade_df1_init_f32(&S_3, 2, firCoeffs_3, firStateF32_3);

	arm_biquad_cascade_df1_init_f32(&S_4, 2, firCoeffs_4, firStateF32_4);

	arm_biquad_cascade_df1_init_f32(&S_5, 2, firCoeffs_5, firStateF32_5);

	arm_biquad_cascade_df1_init_f32(&S_6, 2, firCoeffs_6, firStateF32_6);

	arm_biquad_cascade_df1_init_f32(&S_7, 2, firCoeffs_7, firStateF32_7);

	arm_biquad_cascade_df1_init_f32(&S_8, 2, firCoeffs_8, firStateF32_8);

	//Initialize circular buffer pointers
	inputStream = &circularBuffers[0][0];
	filterStreamSrc = &circularBuffers[1][0];
	outputStream = &circularBuffers[2][0];
	filterStreamDst = &circularBuffers[3][0];


	//Init SRC buffer with a mock sine signal
	for (i = 0; i < FRAME_SIZE; i++) {
		filterStreamSrc[i] = 2048 * sinf(FREC_TEST * 2 * PI * i / (FRAME_SIZE * 200));
		adcMockSignal[i] = filterStreamSrc[i];
	}

	//Initialize gain for each band
	for (i = 0; i < 8; i++)
	{
		bandGainArray[i] = 1;
	}

	filterBuffers();
}

void filterBuffers()
{
	int32_t i = 0;
	static float32_t staging_buffer[FRAME_SIZE];

	arm_biquad_cascade_df1_f32(&S_1, filterStreamSrc, filterStreamDst,
			FRAME_SIZE);

	for (i = 0; i < FRAME_SIZE; i++) {
		staging_buffer[i] = filterStreamDst[i] * bandGainArray[0];
	}

	arm_biquad_cascade_df1_f32(&S_2, filterStreamSrc, filterStreamDst,
			FRAME_SIZE);

	for (i = 0; i < FRAME_SIZE; i++) {
		staging_buffer[i] += filterStreamDst[i] * bandGainArray[1];
	}

	arm_biquad_cascade_df1_f32(&S_3, filterStreamSrc, filterStreamDst,
			FRAME_SIZE);

	for (i = 0; i < FRAME_SIZE; i++) {
		staging_buffer[i] += filterStreamDst[i] * bandGainArray[2];
	}

	arm_biquad_cascade_df1_f32(&S_4, filterStreamSrc, filterStreamDst,
			FRAME_SIZE);

	for (i = 0; i < FRAME_SIZE; i++) {
		staging_buffer[i] += filterStreamDst[i] * bandGainArray[3];
	}

	arm_biquad_cascade_df1_f32(&S_5, filterStreamSrc, filterStreamDst,
			FRAME_SIZE);

	for (i = 0; i < FRAME_SIZE; i++) {
		staging_buffer[i] += filterStreamDst[i] * bandGainArray[4];
	}

	arm_biquad_cascade_df1_f32(&S_6, filterStreamSrc, filterStreamDst,
			FRAME_SIZE);

	for (i = 0; i < FRAME_SIZE; i++) {
		staging_buffer[i] += filterStreamDst[i] * bandGainArray[5];
	}

	arm_biquad_cascade_df1_f32(&S_7, filterStreamSrc, filterStreamDst,
			FRAME_SIZE);

	for (i = 0; i < FRAME_SIZE; i++) {
		staging_buffer[i] += filterStreamDst[i] * bandGainArray[6];
	}

	arm_biquad_cascade_df1_f32(&S_8, filterStreamSrc, filterStreamDst,
			FRAME_SIZE);

	for (i = 0; i < FRAME_SIZE; i++) {
		filterStreamSrc[i] = staging_buffer[i] + (filterStreamDst[i] * bandGainArray[7]);
	}

	rotateBuffers();

	*inputStreamFrameReadyFlag = INPUT_STREAM_NOTREADY;
}

void rotateBuffers()
{
static char i = 2;

	switch (i)
	{
	case 0:
		inputStream = &circularBuffers[1][0];
		filterStreamSrc = &circularBuffers[2][0];
		outputStream = &circularBuffers[0][0];
		i++;
		break;
	case 1:
		inputStream = &circularBuffers[0][0];
		filterStreamSrc = &circularBuffers[1][0];
		outputStream = &circularBuffers[2][0];
		i++;
		break;
	case 2:
		inputStream = &circularBuffers[2][0];
		filterStreamSrc = &circularBuffers[0][0];
		outputStream = &circularBuffers[1][0];
		i = 0;
		break;
	}
}

void insertInputStreamSample(uint32_t * sample)
{
	inputStream[sampleCurrentIndex] = (float32_t)*sample;
	sampleCurrentIndex++;
	sampleCurrentIndex %= FRAME_SIZE;
	if(*inputStreamFrameReadyFlag == INPUT_STREAM_READY && sampleCurrentIndex == 0)
	{
		(*overrunStreamPrt)();
		return;
	}
	if (sampleCurrentIndex == 0)
	*inputStreamFrameReadyFlag =  INPUT_STREAM_READY;
}

void insertInputStreamSampleMock()
{
	inputStream[sampleCurrentIndex] = adcMockSignal[sampleCurrentIndex];
	sampleCurrentIndex++;
	sampleCurrentIndex %= FRAME_SIZE;
	if(*inputStreamFrameReadyFlag == INPUT_STREAM_READY && sampleCurrentIndex == 0)
	{
		(*overrunStreamPrt)();
		return;
	}
	if (sampleCurrentIndex == 0)
	*inputStreamFrameReadyFlag =  INPUT_STREAM_READY;
}

float32_t * getOutputStreamSample(void)
{
	return &outputStream[sampleCurrentIndex];
}

void adjustBandsGain(float32_t G0, float32_t G1, float32_t G2, float32_t G3, float32_t G4, float32_t G5, float32_t G6, float32_t G7)
{
	bandGainArray[0] = G0;
	bandGainArray[1] = G1;
	bandGainArray[2] = G2;
	bandGainArray[3] = G3;
	bandGainArray[4] = G4;
	bandGainArray[5] = G5;
	bandGainArray[6] = G6;
	bandGainArray[7] = G7;
}
