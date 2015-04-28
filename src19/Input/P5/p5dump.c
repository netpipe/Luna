#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h> /* exit */
#include <string.h> /* memset */

#include "p5glove.h"
	P5Glove glove;
static void dump_cooked(P5Glove glove,uint32_t mask)
{

	if (mask & P5GLOVE_DELTA_BUTTONS) {
		uint32_t buttons;

		p5glove_get_buttons(glove,&buttons);
		/* Buttons */
		printf("%c%c%c ",
			(buttons & P5GLOVE_BUTTON_A) ? 'A' : '.',
			(buttons & P5GLOVE_BUTTON_B) ? 'B' : '.',
			(buttons & P5GLOVE_BUTTON_C) ? 'C' : '.');
	}

	if (mask & P5GLOVE_DELTA_FINGERS) {
		double clench;
		int i;
printf("fingers");
		for (i=0; i < 5; i++) {
			/* Fingers */
			p5glove_get_finger(glove,i,&clench);
			printf("%.4lf%c",clench,i==4 ? ' ' : ',');
		}
	}

	if (mask & P5GLOVE_DELTA_POSITION) {
		double pos[3];

		p5glove_get_position(glove, pos);
		printf("[%.4f, %.4f, %.4f] ",
			pos[0], pos[1], pos[2]);
	}

	if (mask & P5GLOVE_DELTA_ROTATION) {
		double axis[3],angle;

		p5glove_get_rotation(glove, &angle, axis);
		printf("(%.4f, %.4f, %.4f, %.4f deg) ",
			axis[0], axis[1], axis[2], angle);
	}
}

/* Brain-Dead P5 data dump.
 */
int MainData(int argc, char **argv)
{

	int sample;

	glove=p5glove_open(0);
	if (glove == NULL) {
		fprintf(stderr, "%s: Can't open glove interface\n", argv[0]);
		return 1;
	}

	for (sample=0; sample < 10 ; ) { // to average it out.
		int i,err;

		err=p5glove_sample(glove, -1);
		if (err < 0 && errno == EAGAIN)
			continue;
		if (err < 0) {
			perror("Glove Failure");
			exit(1);
		}

		printf("%2d: ",sample);
		sample++;

		dump_cooked(glove,err);

		printf("\n");
	}

	//p5glove_close(glove);

    return 0;
}
