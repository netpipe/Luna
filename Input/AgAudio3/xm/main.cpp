
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <vector>

#include "./AgAudio3/CAudioDevice.h"

#include "testprog.h"

#define XM_BIG_ENDIAN false

static const unsigned int channels = 2;
static const unsigned int rate = 44100;
static const size_t buffer_size = 44100;

void puts_uint32_le(uint32_t i, FILE* f) {
	char* c = (char*)(&i);

	if (XM_BIG_ENDIAN) {
		putc(c[3], f);
		putc(c[2], f);
		putc(c[1], f);
		putc(c[0], f);
	}
	else {
		putc(c[0], f);
		putc(c[1], f);
		putc(c[2], f);
		putc(c[3], f);
	}
}

void puts_uint16_le(uint16_t i, FILE* f) {
	char* c = (char*)(&i);

	if (XM_BIG_ENDIAN) {
		putc(c[1], f);
		putc(c[0], f);
	}
	else {
		putc(c[0], f);
		putc(c[1], f);
	}
}

int main(int argc, char** argv)
{
	FILE* out;

	agEngine::audio::CAudioDevice* adevice = new agEngine::audio::CAudioDevice();
	agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./cAudioTheme1.ogg", 1));

	xm_context_t* ctx;
	uint32_t num_samples = 0;
	float buffer[buffer_size];	

	//if (argc != 3)
	//	FATAL("Usage: %s <xm-file-input> <wav-file-output>\n", argv[0]);

	//create_context_from_file(&ctx, rate, argv[1]);

	//out = fopen(argv[2], "wb");
	//if (out == NULL) FATAL_ERR("could not open output file for writing");



	char input_filename[] = "test.xm";
	create_context_from_file(&ctx, rate, input_filename);

	out = fopen("test.wav", "wb");

	

	if (ctx == NULL) exit(1);
	xm_set_max_loop_count(ctx, 1);

	std::vector<int16_t> pcm_buffer;

	while (xm_get_loop_count(ctx) == 0) 
	{
		xm_generate_samples(ctx, buffer, buffer_size / channels);

		for (size_t i = 0; i < buffer_size; i++)
		{
			float sampleFloat = buffer[i];
			sampleFloat *= 32767;

			int16_t sampleInt = (int16_t)sampleFloat;
			pcm_buffer.push_back(sampleInt);
		}

		num_samples += buffer_size;	
	}

	int16_t* newBuffer = new int16_t[num_samples];
	

	fputs("RIFF", out);
	puts_uint32_le(0, out); /* Chunk size. Will be filled later. */

	fputs("WAVE", out);

	fputs("fmt ", out); /* Start format chunk */
	puts_uint32_le(16, out); /* Format chunk size */
	puts_uint16_le(1, out); 
	puts_uint16_le(channels, out); /* Number of channels */
	puts_uint32_le(rate, out);  /* Frames/sec (sampling rate) */
	puts_uint32_le(rate * channels * sizeof(int16_t), out); /* nAvgBytesPerSec ? */
	puts_uint16_le(channels * sizeof(int16_t), out); /* nBlockAlign ? */
	puts_uint16_le(8 * sizeof(int16_t), out); /* wBitsPerSample ? */

	fputs("data", out); /* Start data chunk */
	puts_uint32_le(0, out); /* Data chunk size. Will be filled later. */

	for (size_t i = 0; i < num_samples; i++)
	{
		newBuffer[i] = pcm_buffer[i];
		puts_uint16_le(newBuffer[i], out);
	}

	fseek(out, 4, SEEK_SET);
	puts_uint32_le(36 + num_samples * sizeof(int16_t), out);

	fseek(out, 40, SEEK_SET);
	puts_uint32_le(num_samples * sizeof(int16_t), out);

	fclose(out);


	while (true)
	{
		if (!test->isPlaying())
			test->playFirstBuffer((char*)newBuffer, num_samples * sizeof(int16_t));
		else
			adevice->playBuffer((char*)newBuffer, num_samples * sizeof(int16_t));
	}

	delete newBuffer;

	xm_free_context(ctx);

	return 0;
}

