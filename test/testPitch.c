// clang -g ../pitch/*.c ../pitch/*/*.c testPitch.c -o pitch

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#include "test1.h"

static void testPEF(char *name);
static void testLHS(char *name);
static void testHPS(char *name);
static void testNCF(char *name);
static void testCEP(char *name);

int runNum=1;

int main(int argc, char const *argv[]){
	struct timeval tv;
	long t1=0,t2=0;

	gettimeofday(&tv, NULL);
	t1=tv.tv_sec*1000+tv.tv_usec/1000;

	testPEF(argv[1]);
	testLHS(argv[1]);
	testHPS(argv[1]);
	testNCF(argv[1]);
	testCEP(argv[1]);

	gettimeofday(&tv, NULL);
	t2=tv.tv_sec*1000+tv.tv_usec/1000;
	printf("cost time is %0.3f\n",(t2-t1)/1000.0);

	return 0;
}

static void testPEF(char *audioName){
	PitchPEFObj pitch=NULL;
	
	int samplate=32000;

	float lowFre=32;
	float highFre=2000;
	float cutFre=4000;

	int radix2Exp=12; // 4096
	int slideLength=(1<<radix2Exp)/4;

	WindowType winType=Window_Hamm;

	int isContinue=0;

	int timeLength=0;
	float *freArr=NULL;

	float *dataArr=NULL;
	int dataLength=0;
	int offset=0;
	
	dataLength=util_readWave(audioName, &dataArr);
	printf("dataLength is %d\n",dataLength);

	pitchPEFObj_new(&pitch,
				&samplate, &lowFre, &highFre, &cutFre,
				&radix2Exp, &slideLength, &winType,
				NULL,NULL,NULL,
				&isContinue);

	timeLength=pitchPEFObj_calTimeLength(pitch,dataLength);
	freArr=__vnew(timeLength, NULL);

	for(int i=0;i<runNum;i++){
		pitchPEFObj_pitch(pitch,dataArr+offset,dataLength,freArr);

		for(int i=0;i<timeLength;i++){
			printf("index[%d], %.3f: %.1f\n",
				i,i*0.032,freArr[i]);
		}
	}
	
	free(dataArr);
	free(freArr);

	pitchPEFObj_free(pitch);
}

static void testLHS(char *audioName){
	PitchLHSObj pitch=NULL;
	
	int samplate=32000;

	float lowFre=32;
	float highFre=2000;

	int hc=5;

	int radix2Exp=12; // 4096
	int slideLength=(1<<radix2Exp)/4;

	WindowType winType=Window_Hamm;

	int isContinue=0;

	int timeLength=0;
	float *freArr=NULL;

	float *dataArr=NULL;
	int dataLength=0;
	int offset=0;
	
	dataLength=util_readWave(audioName, &dataArr);
	printf("dataLength is %d\n",dataLength);

	pitchLHSObj_new(&pitch,
				&samplate, &lowFre, &highFre,
				&radix2Exp, &slideLength, &winType,
				&hc,
				&isContinue);

	timeLength=pitchLHSObj_calTimeLength(pitch,dataLength);
	freArr=__vnew(timeLength, NULL);

	for(int i=0;i<runNum;i++){
		pitchLHSObj_pitch(pitch,dataArr+offset,dataLength,freArr);

		for(int i=0;i<timeLength;i++){
			printf("index[%d], %.3f: %.1f\n",
				i,i*0.032,freArr[i]);
		}
	}
	
	free(dataArr);
	free(freArr);

	pitchLHSObj_free(pitch);
}

static void testHPS(char *name){
	PitchHPSObj pitch=NULL;
	
	int samplate=32000;

	float lowFre=32;
	float highFre=2000;

	int hc=5;

	int radix2Exp=12; // 4096
	int slideLength=(1<<radix2Exp)/4;

	WindowType winType=Window_Hamm;

	int isContinue=0;

	int timeLength=0;
	float *freArr=NULL;

	float *dataArr=NULL;
	int dataLength=0;
	int offset=0;
	
	dataLength=util_readWave(name, &dataArr);
	printf("dataLength is %d\n",dataLength);

	pitchHPSObj_new(&pitch,
				&samplate, &lowFre, &highFre,
				&radix2Exp, &slideLength, &winType,
				&hc,
				&isContinue);

	timeLength=pitchHPSObj_calTimeLength(pitch,dataLength);
	freArr=__vnew(timeLength, NULL);

	for(int i=0;i<runNum;i++){
		pitchHPSObj_pitch(pitch,dataArr+offset,dataLength,freArr);

		for(int i=0;i<timeLength;i++){
			printf("index[%d], %.3f: %.1f\n",
				i,i*0.032,freArr[i]);
		}
	}
	
	free(dataArr);
	free(freArr);

	pitchHPSObj_free(pitch);
}

static void testNCF(char *name){
	PitchNCFObj pitch=NULL;
	
	int samplate=32000;

	float lowFre=32;
	float highFre=2000;

	int radix2Exp=12; // 4096
	int slideLength=(1<<radix2Exp)/4;

	WindowType winType=Window_Rect;

	int isContinue=0;

	int timeLength=0;
	float *freArr=NULL;

	float *dataArr=NULL;
	int dataLength=0;
	int offset=0;
	
	dataLength=util_readWave(name, &dataArr);
	printf("dataLength is %d\n",dataLength);

	pitchNCFObj_new(&pitch,
				&samplate, &lowFre, &highFre,
				&radix2Exp, &slideLength, &winType,
				&isContinue);

	timeLength=pitchNCFObj_calTimeLength(pitch,dataLength);
	freArr=__vnew(timeLength, NULL);

	for(int i=0;i<runNum;i++){
		pitchNCFObj_pitch(pitch,dataArr+offset,dataLength,freArr);

		for(int i=0;i<timeLength;i++){
			printf("index[%d], %.3f: %.1f\n",
				i,i*0.032,freArr[i]);
		}
	}
	
	free(dataArr);
	free(freArr);

	pitchNCFObj_free(pitch);
}

static void testCEP(char *name){
	PitchCEPObj pitch=NULL;
	
	int samplate=32000;

	float lowFre=32;
	float highFre=2000;

	int radix2Exp=12; // 4096
	int slideLength=(1<<radix2Exp)/4;

	WindowType winType=Window_Hamm;

	int isContinue=0;

	int timeLength=0;
	float *freArr=NULL;

	float *dataArr=NULL;
	int dataLength=0;
	int offset=0;
	
	dataLength=util_readWave(name, &dataArr);
	printf("dataLength is %d\n",dataLength);

	pitchCEPObj_new(&pitch,
				&samplate, &lowFre, &highFre,
				&radix2Exp, &slideLength, &winType,
				&isContinue);

	timeLength=pitchCEPObj_calTimeLength(pitch,dataLength);
	freArr=__vnew(timeLength, NULL);

	for(int i=0;i<runNum;i++){
		pitchCEPObj_pitch(pitch,dataArr+offset,dataLength,freArr);

		for(int i=0;i<timeLength;i++){
			printf("index[%d], %.3f: %.1f\n",
				i,i*0.032,freArr[i]);
		}
	}
	
	free(dataArr);
	free(freArr);

	pitchCEPObj_free(pitch);
}





