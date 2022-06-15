#include "../../config.h"
#ifdef SPEECH
#include <stdio.h>
#include "sam.h"
#include "SamTabs.h"


unsigned char wait1 = 7;
unsigned char wait2 = 6;

unsigned char mem39;
unsigned char mem44;
unsigned char mem47;
unsigned char mem49;
unsigned char mem50;
unsigned char mem51;
unsigned char mem53;
unsigned char mem56;

unsigned char mem59=0;

unsigned char A1, X1, Y1;

unsigned char stress[256]; //numbers from 0 to 8
unsigned char phonemeLength[256]; //tab40160
unsigned char phonemeindex[256];


unsigned char phonemeIndexOutput[60]; //tab47296
unsigned char stressOutput[60]; //tab47365
unsigned char phonemeLengthOutput[60]; //tab47416

unsigned char tab44800[256];

unsigned char tab43008[256];

unsigned char frequency1[256];
unsigned char frequency2[256];
unsigned char frequency3[256];

unsigned char amplitude1[256];
unsigned char amplitude2[256];
unsigned char amplitude3[256];

//timetable for more accurate c64 simulation
unsigned oldtimetableindex = 0;

int timetable[5][5] =
{
	162, 167, 167, 127, 128,
	226, 60, 60, 0, 0,
	225, 60, 59, 0, 0,
	200, 0, 0, 54, 55,
	199, 0, 0, 54, 54
};


void Init();
int Parser1();
void Parser2();
int Code39771();
void Code41883();
void SetPhonemeLength();
void Code48619();
void Code41240();
void Insert(unsigned char position, unsigned char mem60, unsigned char mem59, unsigned char mem58);
void Code48431();
void Code47574();
void Code48547();
void Code48227();
void SetMouthThroat(unsigned char mouth, unsigned char throat);



// 168=tab43008
// 169=frequency1
// 170=frequency2
// 171=frequency3
// 172=amplitude1
// 173=amplitude2
// 174=amplitude3


void Init()
{
int i;

SetMouthThroat( mouth, throat);


/*
	freq2datA1 = &mem[45136];
	freq1datA1 = &mem[45056];
        freq3datA1 = &mem[45216];
*/
        //tab43008 = &mem[43008];
/*
        frequency1 = &mem[43264];
        frequency2 = &mem[43520];
        frequency3 = &mem[43776];
*/
/*
        amplitude1 = &mem[44032];
		amplitude2 = &mem[44288];
        amplitude3 = &mem[44544];
*/
        //phoneme = &mem[39904];
/*
        ampl1datA1 = &mem[45296];
        ampl2datA1 = &mem[45376];
	ampl3datA1 = &mem[45456];
*/

        for(i=0; i<256; i++)
        {
                tab43008[i] = 0;
		amplitude1[i] = 0;
		amplitude2[i] = 0;
                amplitude3[i] = 0;
                frequency1[i] = 0;
                frequency2[i] = 0;
		frequency3[i] = 0;
                stress[i] = 0;
                phonemeLength[i] = 0;
                tab44800[i] = 0;
        }

        for(i=0; i<60; i++)
		{
                phonemeIndexOutput[i] = 0;
                stressOutput[i] = 0;
                phonemeLengthOutput[i] = 0;
        }

}

//written by me because of different table positions.
// mem[47] = ...
// 168=tab43008
// 169=frequency1
// 170=frequency2
// 171=frequency3
// 172=amplitude1
// 173=amplitude2
// 174=amplitude3
unsigned char Read(unsigned char p, unsigned char Y)
{
switch(p)
{
        case 168: return tab43008[Y1];
        case 169: return frequency1[Y1];
        case 170: return frequency2[Y1];
        case 171: return frequency3[Y1];
	case 172: return amplitude1[Y1];
        case 173: return amplitude2[Y1];
        case 174: return amplitude3[Y1];
}
        printf("Error reading to tables");
        return 0;
}

void Write(unsigned char p, unsigned char Y, unsigned char value)
{

switch(p)
{
        case 168: tab43008[Y1] = value; return;
	case 169: frequency1[Y1] = value;  return;
        case 170: frequency2[Y1] = value;  return;
        case 171: frequency3[Y1] = value;  return;
        case 172: amplitude1[Y1] = value;  return;
	case 173: amplitude2[Y1] = value;  return;
	case 174: amplitude3[Y1] = value;  return;
}
        printf("Error writing to tables\n");

}




int Code39771()
{
	Init();
	phonemeindex[255] = 32; //to prevent buffer overflow

    int temp;
	//mem[39444] = 255;  //maybe errorposition
	if (!Parser1()) return 0;
	Parser2();
	Code41883();
	SetPhonemeLength();
	Code48619();
	Code41240();
	do
	{
		A1 = phonemeindex[X1];
		if (A1 > 80)
		{
			phonemeindex[X1] = 255;
			break; // error: delete all behind it
		}
		X1++;
	} while (X1 != 0);

//pos39848:
	Code48431();

	//mem[40158] = 255;

	Code48547();

	return 1;

}


//seems to delete all zeros in table phoneme and copies it and 2 other tables
void Code48547()
{
	A1 = 0;
	X1 = 0;
	Y1 = 0;

//pos48551:
while(1)
{
	A1 = phonemeindex[X1];
	if (A1 == 255)
        {
        	A1 = 255;
			phonemeIndexOutput[Y1] = 255;
			Code47574();
			return;
		}
	if (A1 == 254)
		{
			X1++;
			int temp = X1;
			//mem[48546] = X;
			phonemeIndexOutput[Y1] = 255;
			Code47574();
        	//X = mem[48546];
                X1=temp;
        	Y1 = 0;
			continue;
		}

	if (A1 == 0)
        {
        	X1++;
        	continue;
        }

	phonemeIndexOutput[Y1] = A1;
	phonemeLengthOutput[Y1] = phonemeLength[X1];
	stressOutput[Y1] = stress[X1];
	X1++;
	Y1++;
}

}

void Code48431()
{
        unsigned char mem54;
        unsigned char mem55;
        unsigned char index; //variable Y
	mem54 = 255;
	X1++;
	mem55 = 0;
	unsigned char mem66 = 0;
        while(1)
        {
//pos48440:
		X1 = mem66;
		index = phonemeindex[X1];
		if (index == 255) return;
		mem55 += phonemeLength[X1];

		if (mem55 < 232)
		{
			A1 = flags2[index]&1;
			if(A1 != 0)
			{
				X1++;
				mem55 = 0;
				Insert(X1, 254, mem59, 0);
				mem66++;
				mem66++;
				continue;
			}
			if (index == 0) mem54 = X1;
			mem66++;
			continue;
		}
		X1 = mem54;
		phonemeindex[X1] = 31;   // 'Q'
		phonemeLength[X1] = 4;
		stress[X1] = 0;
		X1++;
		mem55 = 0;
		Insert(X1, 254, mem59, 0);
		X1++;
		mem66 = X1;
	}

}


//add 1 to stress under some circumstances
void Code41883()
{
	unsigned char pos=0; //mem66
	while(1)
	{
	Y1 = phonemeindex[pos];
	if (Y1 == 255) return;
	if ((flags[Y1] & 64) == 0) {pos++; continue;}
	Y1 = phonemeindex[pos+1];
	if (Y1 == 255) //prevent buffer overflow
	{
		if ((65 & 128) == 0)  {pos++; continue;}
	} else
		if ((flags[Y1] & 128) == 0)  {pos++; continue;}

	Y1 = stress[pos+1];
	if (Y1 == 0)  {pos++; continue;}
	if ((Y1 & 128) != 0)  {pos++; continue;}
	stress[pos] = Y1+1;
	pos++;
	}

}


//void Code41014()
void Insert(unsigned char position/*var57*/, unsigned char mem60, unsigned char mem59, unsigned char mem58)
{
	int i;
	for(i=254; i >= position; i--)
        {
				phonemeindex[i+1] = phonemeindex[i];
                phonemeLength[i+1] = phonemeLength[i];
                stress[i+1] = stress[i];
        }

	phonemeindex[position] = mem60;
	phonemeLength[position] = mem59;
	stress[position] = mem58;
	return;
}


int Parser1()
{
	int i;
        unsigned char sign1;
        unsigned char sign2;
        unsigned char position=0;
   	X1 = 0;
	A1 = 0;
	Y1 = 0;
        for(i=0; i<256; i++)
                stress[i] = 0;

while(1)
{
//pos41078:
	sign1 = input[X1];
	if (sign1 == 155)
        {
        	phonemeindex[position] = 255;      //mark endpoint
		return 1;       //all ok
	}
	X1++;
	sign2 = input[X1];

	Y1 = 0;
pos41095:
        A1 = signInputTable1[Y1];
        if (A1 == sign1)
        {
               	A1 = signInputTable2[Y1];
                if ((A1 != '*') && (A1 == sign2))
                {
			phonemeindex[position] = Y1;
                	position++;
                	X1++;
                        continue;
                }
		}
	Y1++;
	if (Y1 != 81) goto pos41095;

	Y1 = 0;
pos41134:

		if (signInputTable2[Y1] == '*')
		{
                if (signInputTable1[Y1] == sign1)
                {
                	phonemeindex[position] = Y1;
                	position++;
			continue;
                }
        	}
	Y1++;
	if (Y1 != 81) goto pos41134; //81 is size of table


	Y1 = 8;
        while( (sign1 != stressInputTable[Y1]) && (Y1>0))
        {
                Y1--;
        }

        if (Y1 == 0)
        {
        	//mem[39444] = X;
                //41181: JSR 42043 //Error
        	return 0;
        }

	stress[position-1] = Y1;
} //while


}

//change phonemelength depedendent on stress
//void Code41203()
void SetPhonemeLength()
{
        unsigned char A1;
        int position = 0;
		while(phonemeindex[position] != 255 )
        {
        		A1 = stress[position];
                //41218: BMI 41229
                if ((A1 == 0) || ((A1&128) != 0))
		{
                	phonemeLength[position] = phonemeLengthTable1[phonemeindex[position]];
                } else
                {
                	phonemeLength[position] = phonemeLengthTable2[phonemeindex[position]];
                }
                position++;
		}
}


void Code41240()
{
		unsigned char pos=0;

while(phonemeindex[pos] != 255)
{
	unsigned char index; //register AC
	X1 = pos;
	index = phonemeindex[pos];
	if ((flags[index]&2) == 0)
	{
		pos++;
		continue;
	} else
	if ((flags[index]&1) == 0)
	{
		Insert(pos+1, index+1, phonemeLengthTable1[index+1], stress[pos]);
		Insert(pos+2, index+2, phonemeLengthTable1[index+2], stress[pos]);
		pos += 3;
		continue;
	 }

	 do
	 {
		 X1++;
		 A1 = phonemeindex[X1];
	 } while(A1==0);

	if (A1 != 255)
	{
		if ((flags[A1] & 8) != 0)  {pos++; continue;}
		if ((A1 == 36) || (A1 == 37)) {pos++; continue;} // '/H' '/X'
	}

	Insert(pos+1, index+1, phonemeLengthTable1[index+1], stress[pos]);
	Insert(pos+2, index+2, phonemeLengthTable1[index+2], stress[pos]);
	pos += 3;
};

}

//void Code41397()
void Parser2()
{
	unsigned char pos = 0; //mem66;
	unsigned char mem58 = 0;

while(1)
{
	X1 = pos;
	A1 = phonemeindex[pos];

	if (A1 == 0)
	{
		pos++;
		continue;
	}
	if (A1 == 255) return;

	Y1 = A1;

	if ((flags[A1] & 16) == 0) goto pos41457;
	mem58 = stress[pos];
	A1 = flags[Y1] & 32;
	if (A1 == 0) A1 = 20; else A1 = 21;    // 'WX' = 20 'YX' = 21
//pos41443:
	Insert(pos+1, A1, mem59, mem58);
	X1 = pos;
	goto pos41749;

pos41457:
	A1 = phonemeindex[X1];
	if (A1 != 78) goto pos41487;  // 'UL'
	A1 = 24;         // 'L'                 //change 'UL' to 'AX L'
pos41466:
	mem58 = stress[X1];
	phonemeindex[X1] = 13;  // 'AX'
	Insert(X1+1, A1, mem59, mem58);
    pos++;
	continue;

pos41487:
	if (A1 != 79) goto pos41495;   // 'UM'
	A1 = 27; // 'M'  //changle 'UM' to  'AX M'
		goto pos41466;
pos41495:
	if (A1 != 80) goto pos41503; // 'UN'
	A1 = 28;         // 'N' //change UN to 'AX N'
		goto pos41466;
pos41503:
	Y1 = A1;
	A1 = flags[A1] & 128;

		if (A1 != 0)
		{
			A1 = stress[X1];
			if (A1 != 0)
			{
				X1++;
				A1 = phonemeindex[X1];
				if (A1 == 0)
				{
					X1++;
					Y1 = phonemeindex[X1];
					if (Y1 == 255) //buffer overflow
						A1 = 65&128;
					else
						A1 = flags[Y1] & 128;

					if (A1 != 0)
					{
						A1 = stress[X1];
						if (A1 != 0)
						{
							// 31 = 'Q'
							Insert(X1, 31, mem59, 0);
							pos++;
							continue;
						}
					}
				}
			}
		}


	X1 = pos;
	A1 = phonemeindex[pos];
	if (A1 != 23) goto pos41611;     // 'R'
	X1--;
	A1 = phonemeindex[pos-1];
//pos41567:
	if (A1 == 69)                    // 'T'
	{
		phonemeindex[pos-1] = 42;
		goto pos41779;
	}

	if (A1 == 57)                    // 'D'
	{
		phonemeindex[pos-1] = 44;
		goto pos41788;
	}

	A1 = flags[A1] & 128;
	if (A1 != 0) phonemeindex[pos] = 18;  // 'RX'
	pos++;
	continue;

pos41611:
	if (A1 == 24)    // 'L'
	{
		if ((flags[phonemeindex[pos-1]] & 128) == 0) {pos++; continue;}
		phonemeindex[X1] = 19;     // 'LX'
		pos++;
		continue;
	}

	if (A1 == 32)    // 'S'
	{
		if (phonemeindex[pos-1] != 60) {pos++; continue;}
		phonemeindex[pos] = 38;    // 'Z'
		pos++;
		continue;
	}

	if (A1 == 72)    // 'K'
	{
		Y1 = phonemeindex[pos+1];
		A1 = flags[Y1] & 32;
		if (A1 == 0) phonemeindex[pos] = 75;  // 'KX'
	}
	else
	if (A1 == 60)   // 'G'
	{
		unsigned char index = phonemeindex[pos+1];
		if (index == 255)
		{
			if ((65 & 32) != 0) {pos++; continue;}//prevent buffer overflow
		}
		else
		if ((flags[index] & 32) != 0) {pos++; continue;}
		phonemeindex[pos] = 63; // 'GX'
		pos++;
		continue;
	}
	Y1 = phonemeindex[pos];
//pos41719:
	A1 = flags[Y1] & 1;
	if (A1 == 0) goto pos41749;
	A1 = phonemeindex[pos-1];
	if (A1 != 32)    // 'S'
	{
		A1 = Y1;
		goto pos41812;
	}
	phonemeindex[pos] = Y1-12;
	pos++;
	continue;



pos41749:
	A1 = phonemeindex[X1];
	if (A1 == 53)    // 'UW'
	{
		Y1 = phonemeindex[X1-1];
		A1 = flags2[Y1] & 4;
		if (A1 == 0) {pos++; continue;}
		phonemeindex[X1] = 16;
		pos++;
		continue;
	}
pos41779:

	if (A1 == 42)    // 'CH'
	{
//        pos41783:
		Insert(X1+1, A1+1, mem59, stress[X1]);
		pos++;
		continue;
	}

pos41788:
	if (A1 == 44) // 'J'
	{
		Insert(X1+1, A1+1, mem59, stress[X1]);
		pos++;
		continue;
	}
pos41812:
	if (A1 != 69)    // 'T'
		if (A1 != 57) {pos++; continue;}       // 'D'
//pos41825:

	if ((flags[phonemeindex[X1-1]] & 128) == 0) {pos++; continue;}
	X1++;
	A1 = phonemeindex[X1];
//pos41841
		if (A1 != 0)
		{
			if ((flags[A1] & 128) == 0) {pos++; continue;}
			if (stress[X1] != 0) {pos++; continue;}
pos41856:
			phonemeindex[pos] = 30;       // 'DX'
		} else
		{
			A1 = phonemeindex[X1+1];
			if (A1 == 255) //prevent buffer overflow
				A1 = 65 & 128;
			else
			A1 = flags[A1] & 128;

			if (A1 != 0) phonemeindex[pos] = 30;  // 'DX'
		}

		pos++;

} // while


}

//change phoneme length
void Code48619()
{
	X1 = 0;
	unsigned char index;

	unsigned char mem66=0;
	while(1)
	{
		index = phonemeindex[X1];
		if (index == 255) break;
		if((flags2[index] & 1) == 0)
		{
			X1++;
			continue;
		}
		mem66 = X1;
pos48644:
		X1--;
		if(X1 == 0) break;
		index = phonemeindex[X1];

		if (index != 255) //inserted to prevent access overrun
		if((flags[index] & 128) == 0) goto pos48644;

		//pos48657:
		do
		{
			index = phonemeindex[X1];
			if (index != 255)//inserted to prevent access overrun
			if(((flags2[index] & 32) == 0) || ((flags[index] & 4) != 0))     //nochmal überprüfen
			{
				//A1 = flags[Y1] & 4;
				//if(A1 == 0) goto pos48688;
				A1 = phonemeLength[X1];
				A1 = (A1 >> 1) + A1 + 1;   // 3/2*A+1 ???
				phonemeLength[X1] = A1;
			}

			X1++;
		} while (X1 != mem66);
		//	if (X != mem66) goto pos48657;

		X1++;
	}  // while

mem66 = 0;
//pos48697

while(1)
{
	X1 = mem66;
	index = phonemeindex[X1];
	if (index == 255) return;
	A1 = flags[index] & 128;
	if (A1 != 0)
	{

	X1++;
	index = phonemeindex[X1];
	if (index == 255)
		mem56 = 65;
	else
		mem56 = flags[index];

	if ((flags[index] & 64) == 0)
	{
		if ((index == 18) || (index == 19))  // 'RX' & 'LX'
		{
			X1++;
			index = phonemeindex[X1];
			if ((flags[index] & 64) != 0)
				phonemeLength[mem66]--;
			 mem66++;
			 continue;
		}
		mem66++;
		continue;
	}

	if ((mem56 & 4) == 0)
	{
		if((mem56 & 1) == 0) {mem66++; continue;}
		X1--;
		mem56 = phonemeLength[X1] >> 3;
		phonemeLength[X1] -= mem56;
		mem66++;
		continue;
	}
	A1 = phonemeLength[X1-1];
	phonemeLength[X1-1] = (A1 >> 2) + A1 + 1;     // 5/4*A1 + 1
	mem66++;
	continue;

	}

//pos48821:

	if((flags2[index] & 8) != 0)
		{
			X1++;
			index = phonemeindex[X1];
			if (index == 255) A1 = 65&2;  //prevent buffer overflow
        	else
			A1 = flags[index] & 2;
			if(A1 != 0)
				{
					phonemeLength[X1] = 6;
					phonemeLength[X1-1] = 5;
				}
				mem66++;
				continue;

        }


        if((flags[index] & 2) != 0)
        {
                do
                {
                        X1++;
						index = phonemeindex[X1];
                } while(index == 0);
			if (index == 255) //buffer overflow
			{
				if ((65 & 2) == 0) {mem66++; continue;}
			} else
				if ((flags[index] & 2) == 0) {mem66++; continue;}

			phonemeLength[X1] = (phonemeLength[X1] >> 1) + 1;
			X1 = mem66;
        	phonemeLength[mem66] = (phonemeLength[mem66] >> 1) + 1;
			mem66++;
			continue;
        }


	if ((flags2[index] & 16) != 0)
	{
		index = phonemeindex[X1-1];
		if((flags[index] & 2) != 0) phonemeLength[X1] -= 2;
	}

	mem66++;
	continue;
}


//	goto pos48701;
}

// -------------------------------------------------------------------------

void Code47503(unsigned char mem52)
{

	Y1 = 0;
	if ((mem53 & 128) != 0)
	{
		mem53 = -mem53;
		Y1 = 128;
	}
	mem50 = Y1;
	A1 = 0;
	for(X1=8; X1 > 0; X1--)
	{
		int temp = mem53;
		mem53 = mem53 << 1;
		A1 = A1 << 1;
		if (temp >= 128) A1++;
		if (A1 >= mem52)
		{
			A1 = A1 - mem52;
			mem53++;
		}
	}

	mem51 = A1;
	if ((mem50 & 128) != 0) mem53 = -mem53;

}

// -------------------------------------------------------------------------


void Code48227(unsigned char *mem66)
{
int k;
int tempA;
int address;
int i;
	mem49 = Y1;
	A1 = mem39&7;
	X1 = A1-1;
	mem56 = X1;
	mem53 = tab48426[X1];
	mem47 = X1;      //46016+mem[56]*256
	A1 = mem39 & 248;
	if(A1 == 0)
		{
			Y1 = mem49;
			A1 = tab43008[mem49] >> 4;
			goto pos48315;
		}
	Y1 = A1 ^ 255;
pos48274:
	mem56 = 8;
		A1 = randomtable[mem47*256+Y1];
pos48280:

		tempA = A1;
		A1 = A1 << 1;
		//48281: BCC 48290
		if ((tempA & 128) == 0)
		{
			X1 = mem53;
			//mem[54296] = X;
				//timetable 1
				bufferpos += timetable[oldtimetableindex][1];
				oldtimetableindex = 1;

				for(k=0; k<5; k++)
					buffer[bufferpos/scale + k] = (X1 & 15)*16;
//				Memo1->Lines->Add(X);
			if(X1 != 0) goto pos48296;
		}
		//timetable 2;
		bufferpos += timetable[oldtimetableindex][2];
		oldtimetableindex = 2;
		for(k=0; k<5; k++)
			buffer[bufferpos/scale + k] = (5 & 15)*16;

//48295: NOP
pos48296:

		for(i=0; i<wait1; i++) //wait
		X1 = 0;

		mem56--;
	if (mem56 != 0) goto pos48280;
	Y1++;
	if (Y1 != 0) goto pos48274;
	mem44 = 1;
	Y1 = mem49;
	return;


unsigned char phase1;

pos48315:
// Error Error Error

	phase1 = A1 ^ 255;
	Y1 = *mem66;
do
{
//pos48321:

	mem56 = 8;
	//A1 = Read(mem47, Y);
    A1 = randomtable[mem47*256+Y1];     //???


//pos48327:
	do
	{
	//48327: ASL A
	//48328: BCC 48337
		tempA = A1;
		A1 = A1 << 1;
		if ((tempA & 128) != 0)
		{
			X1 = 26;
			//timetable 3
			bufferpos += timetable[oldtimetableindex][3];
			oldtimetableindex = 3;
			for(k=0; k<5; k++)
				buffer[bufferpos/scale + k] = (X1 & 15)*16;

		} else
		{
			//timetable 4
			X1=6;
			bufferpos += timetable[oldtimetableindex][4];
			oldtimetableindex = 4;
			for(k=0; k<5; k++)
				buffer[bufferpos/scale + k] = (X1 & 15)*16;
		}

		for(X1 = wait2; X1>0; X1--); //wait
		mem56--;
	} while(mem56 != 0);

	Y1++;
	phase1++;

} while (phase1 != 0);
//	if (phase1 != 0) goto pos48321;
	A1 = 1;
	mem44 = 1;
	*mem66 = Y1;
	Y1 = mem49;
	return;

//exit(1);


//Error Error Error
}

void Special1(unsigned char mem48, unsigned char phase1)
{

//pos48372:
//	mem48 = 255;
pos48376:
	mem49 = X1;
	A1 = X1;
	int Atemp = A1;
	A1 = A1 - 30;
	if (Atemp <= 30) A1=0; // ???
	X1 = A1;


while( tab43008[X1] == 127) X1++;


pos48398:
//48398: CLC
//48399: ADC 48
        A1 += mem48;
	phase1 = A1;
	tab43008[X1] = A1;
pos48406:
	X1++;
	if (X1 == mem49) return; //goto pos47615;
	if (tab43008[X1] == 255) goto pos48406;
	A1 = phase1;
	goto pos48398;
}


void Code47574()
{
	int k;
	unsigned char phase1;  //mem43
	unsigned char phase2;
	unsigned char phase3;
	unsigned char mem66;
	unsigned char mem38;
	unsigned char mem40;
	unsigned char speedcounter; //mem45
	unsigned char mem48;
	int i;
	int carry;
	int address;
	if (phonemeIndexOutput[0] == 255) return; //exit if no data

	A1 = 0;
	X1 = 0;
	mem44 = 0;
pos47587:
	Y1 = mem44;
	A1 = phonemeIndexOutput[mem44];
	mem56 = A1;
	if (A1 == 255) goto pos47694;
	if (A1 == 1)
	{
		//pos48366:
		A1 = 1;
		mem48 = 1;
		//goto pos48376;
		Special1(mem48, phase1);
	}
	/*
	if (A1 == 2) goto pos48372;
	*/
	if (A1 == 2)
	{
		mem48 = 255;
		Special1(mem48, phase1);
	}
//	pos47615:

	phase1 = tab47492[stressOutput[Y1] + 1];
	phase2 = phonemeLengthOutput[Y1];
	Y1 = mem56;
	do
	{
		frequency1[X1] = freq1data[Y1];
		frequency2[X1] = freq2data[Y1];
		frequency3[X1] = freq3data[Y1];
		amplitude1[X1] = ampl1data[Y1];
		amplitude2[X1] = ampl2data[Y1];
		amplitude3[X1] = ampl3data[Y1];
		tab44800[X1] = tab45936[Y1];
		tab43008[X1] = pitch + phase1;
		X1++;
		phase2--;
	} while(phase2 != 0);
	mem44++;

	if(mem44 != 0) goto pos47587;

pos47694:

	A1 = 0;
	mem44 = 0;
	mem49 = 0;
	X1= 0;
while(1) //while No. 1
{

//pos47701:
	Y1 = phonemeIndexOutput[X1];
	A1 = phonemeIndexOutput[X1+1];
	X1++;
	if (A1 == 255) break;//goto pos47970;
	X1 = A1;
	mem56 = tab45856[A1];
	A1 = tab45856[Y1];
	if (A1 == mem56)
	{
		phase1 = tab45696[Y1];
		phase2 = tab45696[X1];
	} else
	if (A1 < mem56)
	{
		phase1 = tab45776[X1];
		phase2 = tab45696[X1];
	} else
	{
		phase1 = tab45696[Y1];
		phase2 = tab45776[Y1];
	}

	Y1 = mem44;
	A1 = mem49 + phonemeLengthOutput[mem44];
	mem49 = A1;
	A1 = A1 + phase2; //Maybe Problem because of carry flag
//47776: ADC 42
	speedcounter = A1;
	mem47 = 168;
	phase3 = mem49 - phase1;
	A1 = phase1 + phase2;
	mem38 = A1;
	X1 = A1;
	X1 -= 2;
//47805: BPL 47810
if ((X1 & 128) == 0)
do   //while No. 2
{
//pos47810:

	mem40 = mem38;
	if (mem47 == 168)     //for amplitude1
        {
                unsigned char mem36, mem37;
			mem36 = phonemeLengthOutput[mem44] >> 1;
        	mem37 = phonemeLengthOutput[mem44+1] >> 1;
        	mem40 = mem36 + mem37;
        	mem37 += mem49;
        	mem36 = mem49 - mem36;
                A1 = Read(mem47, mem37);
                //A1 = mem[address];
                Y1 = mem36;
				mem53 = A1 - Read(mem47, mem36);
        } else
        {
                A1 = Read(mem47, speedcounter);
                Y1 = phase3;
                mem53 = A1 - Read(mem47, phase3);
        }
       	Code47503(mem40);
       	X1 = mem40;
       	Y1 = phase3;

	mem56 = 0;
//47907: CLC
//pos47908:
		while(1)     //while No. 3
		{
			A1 = Read(mem47, Y1) + mem53; //carry alway cleared

			mem48 = A1;
			Y1++;
			X1--;
			if(X1 == 0) break;

			mem56 += mem51;
			if (mem56 >= mem40)  //???
			{
			/*
			47927: CMP 40
			47927: BCC 47945
			*/
			//47931: SBC 40
			 mem56 -= mem40; //carry? is set
			 //if ((mem56 & 128)==0)
			 if ((mem50 & 128)==0)
			 {
				 //47935: BIT 50
				 //47937: BMI 47943
				if(mem48 != 0) mem48++;
			 } else mem48--;
			 }
		 //pos47945:
			 Write(mem47, Y1, mem48);
		 //47949: CLC
		 //47950: BCC 47908

		//goto pos47908;

        } //while No. 3

//pos47952:
	mem47++;
	//if (mem47 != 175) goto pos47810;
} while (mem47 != 175);     //while No. 2
//pos47963:
	mem44++;
	X1 = mem44;
}  //while No. 1

//goto pos47701;
//pos47970:

	mem48 = mem49 + phonemeLengthOutput[mem44];
	if (!singmode)
	{
		for(i=0; i<256; i++)
			tab43008[i] -= (frequency1[i] >> 1);
	}

	phase1 = 0;
	phase2 = 0;
    phase3 = 0;
	mem49 = 0;
	speedcounter = 72; //sam standard speed

	//amplitude rescaling
	for(i=255; i>=0; i--)
	{
		amplitude1[i] = amplitudeRescale[amplitude1[i]];
		amplitude2[i] = amplitudeRescale[amplitude2[i]];
		amplitude3[i] = amplitudeRescale[amplitude3[i]];
	}

	Y1 = 0;
	A1 = tab43008[0];
	mem44 = A1;
	X1 = A1;
	mem38 = A1 - (A1>>2);     // 3/4*A1 ???

//finally the loop for sound output
//pos48078:
while(1)
{
	A1 = tab44800[Y1];
	mem39 = A1;
	A1 = A1 & 248;
	if(A1 != 0)
	{
		Code48227(&mem66);
		Y1 += 2;
		mem48 -= 2;
	} else
	{
		mem56 = multtable[sinus[phase1] | amplitude1[Y1]];

		carry = 0;
		if ((mem56+multtable[sinus[phase2] | amplitude2[Y1]] ) > 255) carry = 1;
		mem56 += multtable[sinus[phase2] | amplitude2[Y1]];
		A1 = mem56 + multtable[rectangle[phase3] | amplitude3[Y1]] + (carry?1:0);
		A1 = ((A1 + 136) & 255) >> 4; //there must be also A1 carry
		//mem[54296] = A;
		//timetable 0
		bufferpos += timetable[oldtimetableindex][0];
		oldtimetableindex = 0;

		for(k=0; k<5; k++)
			buffer[bufferpos/scale + k] = (A1 & 15)*16;
//		Memo1->Lines->Add(A);
		speedcounter--;
		if (speedcounter != 0) goto pos48155;
		Y1++; //go to next amplitude
		mem48--;
	}
	if(mem48 == 0) return;
	speedcounter = speed;
pos48155:
	mem44--;
	if(mem44 == 0)
	{
pos48159:

		A1 = tab43008[Y1];
		mem44 = A1;
		A1 = A1 - (A1>>2);
		mem38 = A1;
		phase1 = 0;
		phase2 = 0;
		phase3 = 0;
		continue;
	}
	mem38--;
	if((mem38 != 0) || (mem39 == 0))
	{
		phase1 += frequency1[Y1];
		phase2 += frequency2[Y1];
		phase3 += frequency3[Y1];
		continue;
	}
	Code48227(&mem66);
	goto pos48159;
} //while

//--------------------------
//pos48315:
int tempA;
	phase1 = A1 ^ 255;
	Y1 = mem66;
do
{
//pos48321:

	mem56 = 8;
	A1 = Read(mem47, Y1);

//pos48327:
	do
	{
	//48327: ASL A
	//48328: BCC 48337
		tempA = A1;
		A1 = A1 << 1;
		if ((tempA & 128) != 0)
		{
			X1 = 26;
			// mem[54296] = X;
			bufferpos += 150;
			buffer[bufferpos/scale] = (X1 & 15)*16;
//			Memo1->Lines->Add(X);
		} else
		{
			//mem[54296] = 6;
			X1=6;
			bufferpos += 150;
			buffer[bufferpos/scale] = (X1 & 15)*16;
//			Memo1->Lines->Add(X);
		}

		for(X1 = wait2; X1>0; X1--); //wait
		mem56--;
	} while(mem56 != 0);

	Y1++;
	phase1++;

} while (phase1 != 0);
//	if (phase1 != 0) goto pos48321;
	A1 = 1;
	mem44 = 1;
	mem66 = Y1;
	Y1 = mem49;
	return;
}

//return = (mem39212*mem39213) >> 1
unsigned char trans(unsigned char mem39212, unsigned char mem39213)
{
//pos39008:
   unsigned char carry;
   int temp;
   unsigned char mem39214, mem39215;
	A1 = 0;
	mem39215 = 0;
	mem39214 = 0;
	X1 = 8;
		do
		{
				carry = mem39212 & 1;
				mem39212 = mem39212 >> 1;
				if (carry != 0)
				{
						/*
						39018: LSR 39212
						39021: BCC 39033
						*/
						carry = 0;
					A1 = mem39215;
						temp = (int)A1 + (int)mem39213;
						A1 = A1 + mem39213;
						if (temp > 255) carry = 1;
					mem39215 = A1;
				}
				temp = mem39215 & 1;
				mem39215 = (mem39215 >> 1) | (carry?128:0);
				carry = temp;
				//39033: ROR 39215
			X1--;
		} while (X1 != 0);
		temp = mem39214 & 128;
		mem39214 = (mem39214 << 1) | (carry?1:0);
		carry = temp;
		temp = mem39215 & 128;
		mem39215 = (mem39215 << 1) | (carry?1:0);
		carry = temp;

		return mem39215;
}

void SetMouthThroat(unsigned char mouth, unsigned char throat)
{

	unsigned char mem39216;
        unsigned char mem39212;
        unsigned char mem39213;
        unsigned char mem39215;
        //unsigned char mouth; //mem38880
        //unsigned char throat; //mem38881

        unsigned char tab39140[30] = {0, 0, 0, 0, 0, 10,
14, 19, 24, 27, 23, 21, 16, 20, 14, 18, 14, 18, 18,
16, 13, 15, 11, 18, 14, 11, 9, 6, 6, 6};

        unsigned char tab39170[30] = {255, 255,
255, 255, 255, 84, 73, 67, 63, 40, 44, 31, 37, 45, 73, 49,
36, 30, 51, 37, 29, 69, 24, 50, 30, 24, 83, 46, 54, 86};

        //there must be no zeros in this 2 tables
        unsigned char tab39200[6] = {19, 27, 21, 27, 18, 13};
        unsigned char tab39206[6] = {72, 39, 31, 43, 30, 34};

        unsigned char pos = 5; //mem39216
//pos38942:
		while(pos != 30)
        {
        	mem39213 = tab39140[pos];
			if(mem39213 != 0) mem39215 = trans(mouth, mem39213);
                freq1data[pos] = mem39215;
        	mem39213 = tab39170[pos];
        	if(mem39213 != 0) mem39215 = trans(throat, mem39213);
        	freq2data[pos] = mem39215;
                pos++;
        }

//pos39059:
	pos = 48;
	Y1 = 0;
        while(pos != 54)
        {
        	mem39213 = tab39200[Y1];
        	mem39215 = trans(mouth, mem39213);
        	freq1data[pos] = mem39215;
        	mem39213 = tab39206[Y1];
               	mem39215 = trans(throat, mem39213);
        	freq2data[pos] = mem39215;
        	Y1++;
                pos++;
        }

}


void PrintDebug()
{
		int pos = 0;
		printf("phoneme  length  stress\n");
		printf("-----------------------\n");

		while((phonemeindex[pos] != 255) && (pos < 255))
		{

			if (phonemeindex[pos] < 81)
			{
				printf(" %c%c       %3i       %i\n",
					signInputTable1[phonemeindex[pos]],
					signInputTable2[phonemeindex[pos]],
					phonemeLength[pos],
					stress[pos]
					);
			} else
			{
				printf("unknown %i\n", phonemeindex[pos]);
			}
 		pos++;
		}

}


#endif
