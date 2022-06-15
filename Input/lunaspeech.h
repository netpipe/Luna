#include "../config.h"
#ifdef SPEECH
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "speech2/reciter.h"

#define USEEXTERN
#include "speech2/sam.h"

#ifdef USESDL
	#include <SDL/SDL.h>
	#include <SDL/SDL_audio.h>
#endif





// Approximations of some Windows functions to ease portability
#if defined __GNU_LIBRARY__ || defined __GLIBC__
static int min(int l, int r) { return l < r ? l : r; }
static void strcat_s(char * dest, int size, char * str) {
    unsigned int dlen = strlen(dest);
    if (dlen >= size-1) return;
    strncat(dest+dlen, str, size - dlen - 1);
}
void fopen_s(FILE ** f, const char * filename, const char * mode) {
    *f = fopen(filename,mode);
}
#endif


void WriteWav(char* filename, char* buffer, int bufferlength)
{

	unsigned int filesize;
	unsigned int fmtlength = 16;
	unsigned short int format=1; //PCM
	unsigned short int channels=1;
	unsigned int samplerate = 22050;
	unsigned short int blockalign = 1;
	unsigned short int bitspersample=8;

	FILE *file;
	fopen_s(&file, filename, "wb");
	if (file == NULL) return;
	//RIFF header
	fwrite("RIFF", 4, 1,file);
	filesize=bufferlength + 12 + 16 + 8 - 8;
	fwrite(&filesize, 4, 1, file);
	fwrite("WAVE", 4, 1, file);

	//format chunk
	fwrite("fmt ", 4, 1, file);
	fwrite(&fmtlength, 4, 1, file);
	fwrite(&format, 2, 1, file);
	fwrite(&channels, 2, 1, file);
	fwrite(&samplerate, 4, 1, file);
	fwrite(&samplerate, 4, 1, file); // bytes/second
	fwrite(&blockalign, 2, 1, file);
	fwrite(&bitspersample, 2, 1, file);

	//data chunk
	fwrite("data", 4, 1, file);
	fwrite(&bufferlength, 4, 1, file);
	fwrite(buffer, bufferlength, 1, file);

	fclose(file);
}

void printUsage()
{
		printf("usage: sam [options] Word1 Word2 ....\n");
printf("options\n");
printf("	-phonetic 		enters phonetic mode. (see below)\n");
printf("	-pitch number		set pitch value (default=64)\n");
printf("	-speed number		set speed value (default=72)\n");
printf("	-throat number		set mouth value (default=128)\n");
printf("	-mouth number		set throat value (default=128)\n");
printf("	-wav filename		output to wav instead of libsdl\n");
printf("	-sing			special treatment of pitch\n");
printf("	-debug			print additional debug messages\n");
printf("\n");


printf("     VOWELS                            VOICED CONSONANTS	\n");
printf("IY           f(ee)t                    R        red		\n");
printf("IH           p(i)n                     L        allow		\n");
printf("EH           beg                       W        away		\n");
printf("AE           Sam                       W        whale		\n");
printf("AA           pot                       Y        you		\n");
printf("AH           b(u)dget                  M        Sam		\n");
printf("AO           t(al)k                    N        man		\n");
printf("OH           cone                      NX       so(ng)		\n");
printf("UH           book                      B        bad		\n");
printf("UX           l(oo)t                    D        dog		\n");
printf("ER           bird                      G        again		\n");
printf("AX           gall(o)n                  J        judge		\n");
printf("IX           dig(i)t                   Z        zoo		\n");
printf("				       ZH       plea(s)ure	\n");
printf("   DIPHTHONGS                          V        seven		\n");
printf("EY           m(a)de                    DH       (th)en		\n");
printf("AY           h(igh)						\n");
printf("OY           boy						\n");
printf("AW           h(ow)                     UNVOICED CONSONANTS	\n");
printf("OW           slow                      S         Sam		\n");
printf("UW           crew                      Sh        fish		\n");
printf("                                       F         fish		\n");
printf("                                       TH        thin		\n");
printf(" SPECIAL PHONEMES                      P         poke		\n");
printf("UL           sett(le) (=AXL)           T         talk		\n");
printf("UM           astron(omy) (=AXM)        K         cake		\n");
printf("UN           functi(on) (=AXN)         CH        speech		\n");
printf("Q            kitt-en (glottal stop)    /H        a(h)ead	\n");


}

#ifdef USESDL

int pos = 0;
void MixAudio(void *unused, Uint8 *stream, int len)
{
	int i;
	if (pos >= bufferpos) return;
	if ((bufferpos-pos) < len) len = (bufferpos-pos);
	for(i=0; i<len; i++)
	{
		stream[i] = buffer[pos];
		pos++;
	}
}


void OutputSound()
{
	bufferpos /= scale;
    //extern void mixaudio(void *unused, Uint8 *stream, int len);
    SDL_AudioSpec fmt;

    fmt.freq = 22050;
    fmt.format = AUDIO_U8;
    fmt.channels = 1;
    fmt.samples = 2048;
    fmt.callback = MixAudio;
    fmt.userdata = NULL;

    /* Open the audio device and start playing sound! */
    if ( SDL_OpenAudio(&fmt, NULL) < 0 )
    {
        printf("Unable to open audio: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_PauseAudio(0);
    //SDL_Delay((bufferpos)/7);

    while (pos < bufferpos)
    {
    	SDL_Delay(100);
    }

    SDL_CloseAudio();

}
#endif



int lunaSpeech(std::string etest,int *vpitch,int *vmouth,int *vthroat, int *vspeed,int vmode,int vvoice)
{
printf("testing speech");
//int argc;
//char **argv;
	int debug=1;
	int phonetic=0;
	int wavfilenameposition=-1;
	unsigned char output[256] = "";

	pitch=vpitch;
    throat = vthroat;
    speed=vspeed;
    mouth=vmouth;

    switch (vvoice){
        case 1://Elf
        speed=72;	pitch=64;    throat = 110;    mouth=160;
            break;
        case 2://Little Robot
           speed=92;	pitch=60;    throat = 190;    mouth=190;
            break;
        case 3://Stuffy Guy
       speed=82;	pitch=72;    throat = 110;    mouth=105;
            break;
        case 4://Little Old Lady
       speed=82;	pitch=32;    throat = 145;    mouth=145;
            break;
        case 5://Extra-Terrestrial
       speed=100;	pitch=64;    throat = 150;    mouth=200;
            break;
        case 6://SAM
       speed=72;	pitch=64;    throat = 128;    mouth=128;
            break;
    }

    switch (vmode){
    case 0:
        singmode = 1;
        break;
    case 1:
        phonetic = 1;
        break;
    }


	input[0]=0;
	strcat(input, " ");
	strcat(input, etest.c_str());
	strcat(input, " ");

	int i = 1;
//				 wavfilenameposition = i+1;
//				 i++;

//			if (strcmp(&argv[i][1], "phonetic")==0)
//			{
//				phonetic = 1;
//			} else
//pitch=100;
//pitch = atoi(0.5);
//speed=300;
	if ((pitch == 0) || (speed == 0) || (mouth == 0) || (throat == 0))
	{
		printUsage();
		return 1;
	}

	strcat(input, " ");
	for(i=0; input[i] != 0; i++)
		input[i] = toupper(input[i]);

	if (debug)
	{
		printf("say: %s\n", input);
	}

	if (!phonetic)
	{
		if (!TextToPhonemes(input)) return;
		if (debug)
			printf("text translation: %s\n", output);

		// strcpy(input, output);
	}


	strcat(input, " \x9b\0");

//#ifdef USESDL
//	if ( SDL_Init(SDL_INIT_AUDIO) < 0 )
//	{
//        	printf("Unable to init SDL: %s\n", SDL_GetError());
//        	exit(1);
//    	}
//	atexit(SDL_Quit);
//#endif


	//Init();
	if (!Code39771())
	{
		printUsage();
		return 1;
	}

	//if (wavfilenameposition > 0)
		WriteWav("test.wav", buffer, bufferpos/scale);
//	else
	//{
//#ifdef USESDL
//		OutputSound();
//#endif
	//}

//	if (debug) PrintDebug();

	return 0;

}






#endif
