#include "../../config.h"
#ifdef SPEECH
//some flags
unsigned char tab36376[] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 2, 2, 2, 2, 2, 2, 130,
	0, 0, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 2, 2, 2, 2, 2, 2,
	2, 192, 168, 176, 172, 192, 160, 184,
	160, 192, 188, 160, 172, 168, 172, 192,
	160, 160, 172, 180, 164, 192, 168, 168,
	176, 192, 188, 0, 0, 0, 2, 0,
	32, 32, 155, 32, 192, 185, 32, 205,
	163, 76, 138, 142
};


unsigned int rules[] =
{
93, 193, 32, 40, 65, 46, 41, 61, 69, 72, 52, 89, 46, 160, 40, 65, 41, 32, 61, 65, 200, 32, 40, 65, 82, 69, 41, 32, 61, 65, 65, 210,
32, 40, 65, 82, 41, 79, 61, 65, 88, 210, 40, 65, 82, 41, 35, 61, 69, 72, 52, 210, 32, 94, 40, 65, 83, 41, 35, 61, 69, 89, 52, 211,
40, 65, 41, 87, 65, 61, 65, 216, 40, 65, 87, 41, 61, 65, 79, 181, 32, 58, 40, 65, 78, 89, 41, 61, 69, 72, 52, 78, 73, 217, 40, 65,
41, 94, 43, 35, 61, 69, 89, 181, 35, 58, 40, 65, 76, 76, 89, 41, 61, 85, 76, 73, 217, 32, 40, 65, 76, 41, 35, 61, 85, 204, 40, 65,
71, 65, 73, 78, 41, 61, 65, 88, 71, 69, 72, 52, 206, 35, 58, 40, 65, 71, 41, 69, 61, 73, 72, 202, 40, 65, 41, 94, 37, 61, 69, 217,
40, 65, 41, 94, 43, 58, 35, 61, 65, 197, 32, 58, 40, 65, 41, 94, 43, 32, 61, 69, 89, 180, 32, 40, 65, 82, 82, 41, 61, 65, 88, 210,
40, 65, 82, 82, 41, 61, 65, 69, 52, 210, 32, 94, 40, 65, 82, 41, 32, 61, 65, 65, 53, 210, 40, 65, 82, 41, 61, 65, 65, 53, 210, 40,
65, 73, 82, 41, 61, 69, 72, 52, 210, 40, 65, 73, 41, 61, 69, 89, 180, 40, 65, 89, 41, 61, 69, 89, 181, 40, 65, 85, 41, 61, 65, 79,
180, 35, 58, 40, 65, 76, 41, 32, 61, 85, 204, 35, 58, 40, 65, 76, 83, 41, 32, 61, 85, 76, 218, 40, 65, 76, 75, 41, 61, 65, 79, 52,
203, 40, 65, 76, 41, 94, 61, 65, 79, 204, 32, 58, 40, 65, 66, 76, 69, 41, 61, 69, 89, 52, 66, 85, 204, 40, 65, 66, 76, 69, 41, 61,
65, 88, 66, 85, 204, 40, 65, 41, 86, 79, 61, 69, 89, 180, 40, 65, 78, 71, 41, 43, 61, 69, 89, 52, 78, 202, 40, 65, 84, 65, 82, 73,
41, 61, 65, 72, 84, 65, 65, 52, 82, 73, 217, 40, 65, 41, 84, 79, 77, 61, 65, 197, 40, 65, 41, 84, 84, 73, 61, 65, 197, 32, 40, 65,
84, 41, 32, 61, 65, 69, 212, 32, 40, 65, 41, 84, 61, 65, 200, 40, 65, 41, 61, 65, 197, 93, 194, 32, 40, 66, 41, 32, 61, 66, 73, 89,
180, 32, 40, 66, 69, 41, 94, 35, 61, 66, 73, 200, 40, 66, 69, 73, 78, 71, 41, 61, 66, 73, 89, 52, 73, 72, 78, 216, 32, 40, 66, 79,
84, 72, 41, 32, 61, 66, 79, 87, 52, 84, 200, 32, 40, 66, 85, 83, 41, 35, 61, 66, 73, 72, 52, 218, 40, 66, 82, 69, 65, 75, 41, 61,
66, 82, 69, 89, 53, 203, 40, 66, 85, 73, 76, 41, 61, 66, 73, 72, 52, 204, 40, 66, 41, 61, 194, 93, 195, 32, 40, 67, 41, 32, 61, 83,
73, 89, 180, 32, 40, 67, 72, 41, 94, 61, 203, 94, 69, 40, 67, 72, 41, 61, 203, 40, 67, 72, 65, 41, 82, 35, 61, 75, 69, 72, 181, 40,
67, 72, 41, 61, 67, 200, 32, 83, 40, 67, 73, 41, 35, 61, 83, 65, 89, 180, 40, 67, 73, 41, 65, 61, 83, 200, 40, 67, 73, 41, 79, 61,
83, 200, 40, 67, 73, 41, 69, 78, 61, 83, 200, 40, 67, 73, 84, 89, 41, 61, 83, 73, 72, 84, 73, 217, 40, 67, 41, 43, 61, 211, 40, 67,
75, 41, 61, 203, 40, 67, 79, 77, 77, 79, 68, 79, 82, 69, 41, 61, 75, 65, 65, 52, 77, 65, 72, 68, 79, 72, 210, 40, 67, 79, 77, 41,
61, 75, 65, 72, 205, 40, 67, 85, 73, 84, 41, 61, 75, 73, 72, 212, 40, 67, 82, 69, 65, 41, 61, 75, 82, 73, 89, 69, 217, 40, 67, 41,
61, 203, 93, 196, 32, 40, 68, 41, 32, 61, 68, 73, 89, 180, 32, 40, 68, 82, 46, 41, 32, 61, 68, 65, 65, 52, 75, 84, 69, 210, 35, 58,
40, 68, 69, 68, 41, 32, 61, 68, 73, 72, 196, 46, 69, 40, 68, 41, 32, 61, 196, 35, 58, 94, 69, 40, 68, 41, 32, 61, 212, 32, 40, 68,
69, 41, 94, 35, 61, 68, 73, 200, 32, 40, 68, 79, 41, 32, 61, 68, 85, 215, 32, 40, 68, 79, 69, 83, 41, 61, 68, 65, 72, 218, 40, 68,
79, 78, 69, 41, 32, 61, 68, 65, 72, 53, 206, 40, 68, 79, 73, 78, 71, 41, 61, 68, 85, 87, 52, 73, 72, 78, 216, 32, 40, 68, 79, 87,
41, 61, 68, 65, 215, 35, 40, 68, 85, 41, 65, 61, 74, 85, 215, 35, 40, 68, 85, 41, 94, 35, 61, 74, 65, 216, 40, 68, 41, 61, 196, 93,
197, 32, 40, 69, 41, 32, 61, 73, 89, 73, 89, 180, 35, 58, 40, 69, 41, 32, 189, 39, 58, 94, 40, 69, 41, 32, 189, 32, 58, 40, 69, 41,
32, 61, 73, 217, 35, 40, 69, 68, 41, 32, 61, 196, 35, 58, 40, 69, 41, 68, 32, 189, 40, 69, 86, 41, 69, 82, 61, 69, 72, 52, 214, 40,
69, 41, 94, 37, 61, 73, 89, 180, 40, 69, 82, 73, 41, 35, 61, 73, 89, 52, 82, 73, 217, 40, 69, 82, 73, 41, 61, 69, 72, 52, 82, 73,
200, 35, 58, 40, 69, 82, 41, 35, 61, 69, 210, 40, 69, 82, 82, 79, 82, 41, 61, 69, 72, 52, 82, 79, 72, 210, 40, 69, 82, 65, 83, 69,
41, 61, 73, 72, 82, 69, 89, 53, 211, 40, 69, 82, 41, 35, 61, 69, 72, 210, 40, 69, 82, 41, 61, 69, 210, 32, 40, 69, 86, 69, 78, 41,
61, 73, 89, 86, 69, 72, 206, 35, 58, 40, 69, 41, 87, 189, 64, 40, 69, 87, 41, 61, 85, 215, 40, 69, 87, 41, 61, 89, 85, 215, 40, 69,
41, 79, 61, 73, 217, 35, 58, 38, 40, 69, 83, 41, 32, 61, 73, 72, 218, 35, 58, 40, 69, 41, 83, 32, 189, 35, 58, 40, 69, 76, 89, 41,
32, 61, 76, 73, 217, 35, 58, 40, 69, 77, 69, 78, 84, 41, 61, 77, 69, 72, 78, 212, 40, 69, 70, 85, 76, 41, 61, 70, 85, 72, 204, 40,
69, 69, 41, 61, 73, 89, 180, 40, 69, 65, 82, 78, 41, 61, 69, 82, 53, 206, 32, 40, 69, 65, 82, 41, 94, 61, 69, 82, 181, 40, 69, 65,
68, 41, 61, 69, 72, 196, 35, 58, 40, 69, 65, 41, 32, 61, 73, 89, 65, 216, 40, 69, 65, 41, 83, 85, 61, 69, 72, 181, 40, 69, 65, 41,
61, 73, 89, 181, 40, 69, 73, 71, 72, 41, 61, 69, 89, 180, 40, 69, 73, 41, 61, 73, 89, 180, 32, 40, 69, 89, 69, 41, 61, 65, 89, 180,
40, 69, 89, 41, 61, 73, 217, 40, 69, 85, 41, 61, 89, 85, 87, 181, 40, 69, 81, 85, 65, 76, 41, 61, 73, 89, 52, 75, 87, 85, 204, 40,
69, 41, 61, 69, 200, 93, 198, 32, 40, 70, 41, 32, 61, 69, 72, 52, 198, 40, 70, 85, 76, 41, 61, 70, 85, 72, 204, 40, 70, 82, 73, 69,
78, 68, 41, 61, 70, 82, 69, 72, 53, 78, 196, 40, 70, 65, 84, 72, 69, 82, 41, 61, 70, 65, 65, 52, 68, 72, 69, 210, 40, 70, 41, 70,
189, 40, 70, 41, 61, 198, 93, 199, 32, 40, 71, 41, 32, 61, 74, 73, 89, 180, 40, 71, 73, 86, 41, 61, 71, 73, 72, 53, 214, 32, 40, 71,
41, 73, 94, 61, 199, 40, 71, 69, 41, 84, 61, 71, 69, 72, 181, 83, 85, 40, 71, 71, 69, 83, 41, 61, 71, 74, 69, 72, 52, 211, 40, 71,
71, 41, 61, 199, 32, 66, 35, 40, 71, 41, 61, 199, 40, 71, 41, 43, 61, 202, 40, 71, 82, 69, 65, 84, 41, 61, 71, 82, 69, 89, 52, 212,
40, 71, 79, 78, 41, 69, 61, 71, 65, 79, 53, 206, 35, 40, 71, 72, 41, 189, 32, 40, 71, 78, 41, 61, 206, 40, 71, 41, 61, 199, 93, 200,
32, 40, 72, 41, 32, 61, 69, 89, 52, 67, 200, 32, 40, 72, 65, 86, 41, 61, 47, 72, 65, 69, 54, 214, 32, 40, 72, 69, 82, 69, 41, 61,
47, 72, 73, 89, 210, 32, 40, 72, 79, 85, 82, 41, 61, 65, 87, 53, 69, 210, 40, 72, 79, 87, 41, 61, 47, 72, 65, 215, 40, 72, 41, 35,
61, 47, 200, 40, 72, 41, 189, 93, 201, 32, 40, 73, 78, 41, 61, 73, 72, 206, 32, 40, 73, 41, 32, 61, 65, 89, 180, 40, 73, 41, 32, 61,
65, 217, 40, 73, 78, 41, 68, 61, 65, 89, 53, 206, 83, 69, 77, 40, 73, 41, 61, 73, 217, 32, 65, 78, 84, 40, 73, 41, 61, 65, 217, 40,
73, 69, 82, 41, 61, 73, 89, 69, 210, 35, 58, 82, 40, 73, 69, 68, 41, 32, 61, 73, 89, 196, 40, 73, 69, 68, 41, 32, 61, 65, 89, 53,
196, 40, 73, 69, 78, 41, 61, 73, 89, 69, 72, 206, 40, 73, 69, 41, 84, 61, 65, 89, 52, 69, 200, 40, 73, 39, 41, 61, 65, 89, 181, 32,
58, 40, 73, 41, 94, 37, 61, 65, 89, 181, 32, 58, 40, 73, 69, 41, 32, 61, 65, 89, 180, 40, 73, 41, 37, 61, 73, 217, 40, 73, 69, 41,
61, 73, 89, 180, 32, 40, 73, 68, 69, 65, 41, 61, 65, 89, 68, 73, 89, 53, 65, 200, 40, 73, 41, 94, 43, 58, 35, 61, 73, 200, 40, 73,
82, 41, 35, 61, 65, 89, 210, 40, 73, 90, 41, 37, 61, 65, 89, 218, 40, 73, 83, 41, 37, 61, 65, 89, 218, 73, 94, 40, 73, 41, 94, 35,
61, 73, 200, 43, 94, 40, 73, 41, 94, 43, 61, 65, 217, 35, 58, 94, 40, 73, 41, 94, 43, 61, 73, 200, 40, 73, 41, 94, 43, 61, 65, 217,
40, 73, 82, 41, 61, 69, 210, 40, 73, 71, 72, 41, 61, 65, 89, 180, 40, 73, 76, 68, 41, 61, 65, 89, 53, 76, 196, 32, 40, 73, 71, 78,
41, 61, 73, 72, 71, 206, 40, 73, 71, 78, 41, 32, 61, 65, 89, 52, 206, 40, 73, 71, 78, 41, 94, 61, 65, 89, 52, 206, 40, 73, 71, 78,
41, 37, 61, 65, 89, 52, 206, 40, 73, 67, 82, 79, 41, 61, 65, 89, 52, 75, 82, 79, 200, 40, 73, 81, 85, 69, 41, 61, 73, 89, 52, 203,
40, 73, 41, 61, 73, 200, 93, 202, 32, 40, 74, 41, 32, 61, 74, 69, 89, 180, 40, 74, 41, 61, 202, 93, 203, 32, 40, 75, 41, 32, 61, 75,
69, 89, 180, 32, 40, 75, 41, 78, 189, 40, 75, 41, 61, 203, 93, 204, 32, 40, 76, 41, 32, 61, 69, 72, 52, 204, 40, 76, 79, 41, 67, 35,
61, 76, 79, 215, 76, 40, 76, 41, 189, 35, 58, 94, 40, 76, 41, 37, 61, 85, 204, 40, 76, 69, 65, 68, 41, 61, 76, 73, 89, 196, 32, 40,
76, 65, 85, 71, 72, 41, 61, 76, 65, 69, 52, 198, 40, 76, 41, 61, 204, 93, 205, 32, 40, 77, 41, 32, 61, 69, 72, 52, 205, 32, 40, 77,
82, 46, 41, 32, 61, 77, 73, 72, 52, 83, 84, 69, 210, 32, 40, 77, 83, 46, 41, 61, 77, 73, 72, 53, 218, 32, 40, 77, 82, 83, 46, 41,
32, 61, 77, 73, 72, 52, 83, 73, 88, 218, 40, 77, 79, 86, 41, 61, 77, 85, 87, 52, 214, 40, 77, 65, 67, 72, 73, 78, 41, 61, 77, 65,
72, 83, 72, 73, 89, 53, 206, 77, 40, 77, 41, 189, 40, 77, 41, 61, 205, 93, 206, 32, 40, 78, 41, 32, 61, 69, 72, 52, 206, 69, 40, 78,
71, 41, 43, 61, 78, 202, 40, 78, 71, 41, 82, 61, 78, 88, 199, 40, 78, 71, 41, 35, 61, 78, 88, 199, 40, 78, 71, 76, 41, 37, 61, 78,
88, 71, 85, 204, 40, 78, 71, 41, 61, 78, 216, 40, 78, 75, 41, 61, 78, 88, 203, 32, 40, 78, 79, 87, 41, 32, 61, 78, 65, 87, 180, 78,
40, 78, 41, 189, 40, 78, 79, 78, 41, 69, 61, 78, 65, 72, 52, 206, 40, 78, 41, 61, 206, 93, 207, 32, 40, 79, 41, 32, 61, 79, 72, 52,
215, 40, 79, 70, 41, 32, 61, 65, 72, 214, 32, 40, 79, 72, 41, 32, 61, 79, 87, 181, 40, 79, 82, 79, 85, 71, 72, 41, 61, 69, 82, 52,
79, 215, 35, 58, 40, 79, 82, 41, 32, 61, 69, 210, 35, 58, 40, 79, 82, 83, 41, 32, 61, 69, 82, 218, 40, 79, 82, 41, 61, 65, 79, 210,
32, 40, 79, 78, 69, 41, 61, 87, 65, 72, 206, 35, 40, 79, 78, 69, 41, 32, 61, 87, 65, 72, 206, 40, 79, 87, 41, 61, 79, 215, 32, 40,
79, 86, 69, 82, 41, 61, 79, 87, 53, 86, 69, 210, 80, 82, 40, 79, 41, 86, 61, 85, 87, 180, 40, 79, 86, 41, 61, 65, 72, 52, 214, 40,
79, 41, 94, 37, 61, 79, 87, 181, 40, 79, 41, 94, 69, 78, 61, 79, 215, 40, 79, 41, 94, 73, 35, 61, 79, 87, 181, 40, 79, 76, 41, 68,
61, 79, 87, 52, 204, 40, 79, 85, 71, 72, 84, 41, 61, 65, 79, 53, 212, 40, 79, 85, 71, 72, 41, 61, 65, 72, 53, 198, 32, 40, 79, 85,
41, 61, 65, 215, 72, 40, 79, 85, 41, 83, 35, 61, 65, 87, 180, 40, 79, 85, 83, 41, 61, 65, 88, 211, 40, 79, 85, 82, 41, 61, 79, 72,
210, 40, 79, 85, 76, 68, 41, 61, 85, 72, 53, 196, 40, 79, 85, 41, 94, 76, 61, 65, 72, 181, 40, 79, 85, 80, 41, 61, 85, 87, 53, 208,
40, 79, 85, 41, 61, 65, 215, 40, 79, 89, 41, 61, 79, 217, 40, 79, 73, 78, 71, 41, 61, 79, 87, 52, 73, 72, 78, 216, 40, 79, 73, 41,
61, 79, 89, 181, 40, 79, 79, 82, 41, 61, 79, 72, 53, 210, 40, 79, 79, 75, 41, 61, 85, 72, 53, 203, 70, 40, 79, 79, 68, 41, 61, 85,
87, 53, 196, 76, 40, 79, 79, 68, 41, 61, 65, 72, 53, 196, 77, 40, 79, 79, 68, 41, 61, 85, 87, 53, 196, 40, 79, 79, 68, 41, 61, 85,
72, 53, 196, 70, 40, 79, 79, 84, 41, 61, 85, 72, 53, 212, 40, 79, 79, 41, 61, 85, 87, 181, 40, 79, 39, 41, 61, 79, 200, 40, 79, 41,
69, 61, 79, 215, 40, 79, 41, 32, 61, 79, 215, 40, 79, 65, 41, 61, 79, 87, 180, 32, 40, 79, 78, 76, 89, 41, 61, 79, 87, 52, 78, 76,
73, 217, 32, 40, 79, 78, 67, 69, 41, 61, 87, 65, 72, 52, 78, 211, 40, 79, 78, 39, 84, 41, 61, 79, 87, 52, 78, 212, 67, 40, 79, 41,
78, 61, 65, 193, 40, 79, 41, 78, 71, 61, 65, 207, 32, 58, 94, 40, 79, 41, 78, 61, 65, 200, 73, 40, 79, 78, 41, 61, 85, 206, 35, 58,
40, 79, 78, 41, 61, 85, 206, 35, 94, 40, 79, 78, 41, 61, 85, 206, 40, 79, 41, 83, 84, 61, 79, 215, 40, 79, 70, 41, 94, 61, 65, 79,
52, 198, 40, 79, 84, 72, 69, 82, 41, 61, 65, 72, 53, 68, 72, 69, 210, 82, 40, 79, 41, 66, 61, 82, 65, 193, 94, 82, 40, 79, 41, 58,
35, 61, 79, 87, 181, 40, 79, 83, 83, 41, 32, 61, 65, 79, 53, 211, 35, 58, 94, 40, 79, 77, 41, 61, 65, 72, 205, 40, 79, 41, 61, 65,
193, 93, 208, 32, 40, 80, 41, 32, 61, 80, 73, 89, 180, 40, 80, 72, 41, 61, 198, 40, 80, 69, 79, 80, 76, 41, 61, 80, 73, 89, 53, 80,
85, 204, 40, 80, 79, 87, 41, 61, 80, 65, 87, 180, 40, 80, 85, 84, 41, 32, 61, 80, 85, 72, 212, 40, 80, 41, 80, 189, 40, 80, 41, 83,
189, 40, 80, 41, 78, 189, 40, 80, 82, 79, 70, 46, 41, 61, 80, 82, 79, 72, 70, 69, 72, 52, 83, 69, 210, 40, 80, 41, 61, 208, 93, 209,
32, 40, 81, 41, 32, 61, 75, 89, 85, 87, 180, 40, 81, 85, 65, 82, 41, 61, 75, 87, 79, 72, 53, 210, 40, 81, 85, 41, 61, 75, 215, 40,
81, 41, 61, 203, 93, 210, 32, 40, 82, 41, 32, 61, 65, 65, 53, 210, 32, 40, 82, 69, 41, 94, 35, 61, 82, 73, 217, 40, 82, 41, 82, 189,
40, 82, 41, 61, 210, 93, 211, 32, 40, 83, 41, 32, 61, 69, 72, 52, 211, 40, 83, 72, 41, 61, 83, 200, 35, 40, 83, 73, 79, 78, 41, 61,
90, 72, 85, 206, 40, 83, 79, 77, 69, 41, 61, 83, 65, 72, 205, 35, 40, 83, 85, 82, 41, 35, 61, 90, 72, 69, 210, 40, 83, 85, 82, 41,
35, 61, 83, 72, 69, 210, 35, 40, 83, 85, 41, 35, 61, 90, 72, 85, 215, 35, 40, 83, 83, 85, 41, 35, 61, 83, 72, 85, 215, 35, 40, 83,
69, 68, 41, 61, 90, 196, 35, 40, 83, 41, 35, 61, 218, 40, 83, 65, 73, 68, 41, 61, 83, 69, 72, 196, 94, 40, 83, 73, 79, 78, 41, 61,
83, 72, 85, 206, 40, 83, 41, 83, 189, 46, 40, 83, 41, 32, 61, 218, 35, 58, 46, 69, 40, 83, 41, 32, 61, 218, 35, 58, 94, 35, 40, 83,
41, 32, 61, 211, 85, 40, 83, 41, 32, 61, 211, 32, 58, 35, 40, 83, 41, 32, 61, 218, 35, 35, 40, 83, 41, 32, 61, 218, 32, 40, 83, 67,
72, 41, 61, 83, 203, 40, 83, 41, 67, 43, 189, 35, 40, 83, 77, 41, 61, 90, 85, 205, 35, 40, 83, 78, 41, 39, 61, 90, 85, 205, 40, 83,
84, 76, 69, 41, 61, 83, 85, 204, 40, 83, 41, 61, 211, 93, 212, 32, 40, 84, 41, 32, 61, 84, 73, 89, 180, 32, 40, 84, 72, 69, 41, 32,
35, 61, 68, 72, 73, 217, 32, 40, 84, 72, 69, 41, 32, 61, 68, 72, 65, 216, 40, 84, 79, 41, 32, 61, 84, 85, 216, 32, 40, 84, 72, 65,
84, 41, 61, 68, 72, 65, 69, 212, 32, 40, 84, 72, 73, 83, 41, 32, 61, 68, 72, 73, 72, 211, 32, 40, 84, 72, 69, 89, 41, 61, 68, 72,
69, 217, 32, 40, 84, 72, 69, 82, 69, 41, 61, 68, 72, 69, 72, 210, 40, 84, 72, 69, 82, 41, 61, 68, 72, 69, 210, 40, 84, 72, 69, 73,
82, 41, 61, 68, 72, 69, 72, 210, 32, 40, 84, 72, 65, 78, 41, 32, 61, 68, 72, 65, 69, 206, 32, 40, 84, 72, 69, 77, 41, 32, 61, 68,
72, 65, 69, 206, 40, 84, 72, 69, 83, 69, 41, 32, 61, 68, 72, 73, 89, 218, 32, 40, 84, 72, 69, 78, 41, 61, 68, 72, 69, 72, 206, 40,
84, 72, 82, 79, 85, 71, 72, 41, 61, 84, 72, 82, 85, 87, 180, 40, 84, 72, 79, 83, 69, 41, 61, 68, 72, 79, 72, 218, 40, 84, 72, 79,
85, 71, 72, 41, 32, 61, 68, 72, 79, 215, 40, 84, 79, 68, 65, 89, 41, 61, 84, 85, 88, 68, 69, 217, 40, 84, 79, 77, 79, 41, 82, 82,
79, 87, 61, 84, 85, 77, 65, 65, 181, 40, 84, 79, 41, 84, 65, 76, 61, 84, 79, 87, 181, 32, 40, 84, 72, 85, 83, 41, 61, 68, 72, 65,
72, 52, 211, 40, 84, 72, 41, 61, 84, 200, 35, 58, 40, 84, 69, 68, 41, 61, 84, 73, 88, 196, 83, 40, 84, 73, 41, 35, 78, 61, 67, 200,
40, 84, 73, 41, 79, 61, 83, 200, 40, 84, 73, 41, 65, 61, 83, 200, 40, 84, 73, 69, 78, 41, 61, 83, 72, 85, 206, 40, 84, 85, 82, 41,
35, 61, 67, 72, 69, 210, 40, 84, 85, 41, 65, 61, 67, 72, 85, 215, 32, 40, 84, 87, 79, 41, 61, 84, 85, 215, 38, 40, 84, 41, 69, 78,
32, 189, 40, 84, 41, 61, 212, 93, 213, 32, 40, 85, 41, 32, 61, 89, 85, 87, 180, 32, 40, 85, 78, 41, 73, 61, 89, 85, 87, 206, 32, 40,
85, 78, 41, 61, 65, 72, 206, 32, 40, 85, 80, 79, 78, 41, 61, 65, 88, 80, 65, 79, 206, 64, 40, 85, 82, 41, 35, 61, 85, 72, 52, 210,
40, 85, 82, 41, 35, 61, 89, 85, 72, 52, 210, 40, 85, 82, 41, 61, 69, 210, 40, 85, 41, 94, 32, 61, 65, 200, 40, 85, 41, 94, 94, 61,
65, 72, 181, 40, 85, 89, 41, 61, 65, 89, 181, 32, 71, 40, 85, 41, 35, 189, 71, 40, 85, 41, 37, 189, 71, 40, 85, 41, 35, 61, 215, 35,
78, 40, 85, 41, 61, 89, 85, 215, 64, 40, 85, 41, 61, 85, 215, 40, 85, 41, 61, 89, 85, 215, 93, 214, 32, 40, 86, 41, 32, 61, 86, 73,
89, 180, 40, 86, 73, 69, 87, 41, 61, 86, 89, 85, 87, 181, 40, 86, 41, 61, 214, 93, 215, 32, 40, 87, 41, 32, 61, 68, 65, 72, 52, 66,
85, 76, 89, 85, 215, 32, 40, 87, 69, 82, 69, 41, 61, 87, 69, 210, 40, 87, 65, 41, 83, 72, 61, 87, 65, 193, 40, 87, 65, 41, 83, 84,
61, 87, 69, 217, 40, 87, 65, 41, 83, 61, 87, 65, 200, 40, 87, 65, 41, 84, 61, 87, 65, 193, 40, 87, 72, 69, 82, 69, 41, 61, 87, 72,
69, 72, 210, 40, 87, 72, 65, 84, 41, 61, 87, 72, 65, 72, 212, 40, 87, 72, 79, 76, 41, 61, 47, 72, 79, 87, 204, 40, 87, 72, 79, 41,
61, 47, 72, 85, 215, 40, 87, 72, 41, 61, 87, 200, 40, 87, 65, 82, 41, 35, 61, 87, 69, 72, 210, 40, 87, 65, 82, 41, 61, 87, 65, 79,
210, 40, 87, 79, 82, 41, 94, 61, 87, 69, 210, 40, 87, 82, 41, 61, 210, 40, 87, 79, 77, 41, 65, 61, 87, 85, 72, 205, 40, 87, 79, 77,
41, 69, 61, 87, 73, 72, 205, 40, 87, 69, 65, 41, 82, 61, 87, 69, 200, 40, 87, 65, 78, 84, 41, 61, 87, 65, 65, 53, 78, 212, 65, 78,
83, 40, 87, 69, 82, 41, 61, 69, 210, 40, 87, 41, 61, 215, 93, 216, 32, 40, 88, 41, 32, 61, 69, 72, 52, 75, 210, 32, 40, 88, 41, 61,
218, 40, 88, 41, 61, 75, 211, 93, 217, 32, 40, 89, 41, 32, 61, 87, 65, 89, 180, 40, 89, 79, 85, 78, 71, 41, 61, 89, 65, 72, 78, 216,
32, 40, 89, 79, 85, 82, 41, 61, 89, 79, 72, 210, 32, 40, 89, 79, 85, 41, 61, 89, 85, 215, 32, 40, 89, 69, 83, 41, 61, 89, 69, 72,
211, 32, 40, 89, 41, 61, 217, 70, 40, 89, 41, 61, 65, 217, 80, 83, 40, 89, 67, 72, 41, 61, 65, 89, 203, 35, 58, 94, 40, 89, 41, 61,
73, 217, 35, 58, 94, 40, 89, 41, 73, 61, 73, 217, 32, 58, 40, 89, 41, 32, 61, 65, 217, 32, 58, 40, 89, 41, 35, 61, 65, 217, 32, 58,
40, 89, 41, 94, 43, 58, 35, 61, 73, 200, 32, 58, 40, 89, 41, 94, 35, 61, 65, 217, 40, 89, 41, 61, 73, 200, 93, 218, 32, 40, 90, 41,
32, 61, 90, 73, 89, 180, 40, 90, 41, 61, 218, 234, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 230,
32, 72, 69, 76, 76, 79, 27, 79, 87, 27, 72, 47, 72, 69, 72, 76, 79, 87, 27, 82, 82, 83, 72, 32, 83, 76, 65, 69, 32, 70, 79, 72,
52, 82, 83, 72, 32, 83, 76, 65, 69, 52, 83, 72, 47, 72, 69, 72, 76, 79, 87, 27, 89, 77, 27, 72, 79, 87, 54, 77, 63, 27, 32, 89,
73, 89, 52, 82, 46, 27, 27, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0,
95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0,
95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0,
95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0,
95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0,
95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 95, 0, 0, 95, 27,
67, 79, 80, 89, 82, 73, 71, 72, 84, 32, 49, 57, 56, 50, 32, 68, 79, 78, 39, 84, 32, 65, 83, 75, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 130,
0, 0, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 192, 168, 176, 172, 192, 160, 184,
160, 192, 188, 160, 172, 168, 172, 192, 160, 160, 172, 180, 164, 192, 168, 168, 176, 192, 188, 0, 0, 0, 2, 0, 32, 32, 155, 32, 192, 185, 32, 205,
163, 76, 138, 142, 96, 32, 155, 32, 192, 185, 169, 32, 141, 0, 141, 162, 1, 160, 0, 185, 21, 154, 41, 127, 201, 112, 144, 5, 41, 95, 76, 167,
142, 201, 96, 144, 2, 41, 79, 157, 0, 141, 232, 200, 192, 255, 208, 227, 162, 255, 169, 27, 157, 0, 141, 76, 194, 142, 32, 97, 155, 96, 32, 97,
155, 96, 169, 255, 133, 61, 169, 255, 133, 56, 230, 61, 166, 61, 189, 0, 141, 133, 64, 201, 27, 208, 12, 230, 56, 166, 56, 169, 155, 157, 21, 154,
76, 190, 142, 201, 46, 208, 24, 232, 189, 0, 141, 168, 185, 24, 142, 41, 1, 208, 12, 230, 56, 166, 56, 169, 46, 157, 21, 154, 76, 202, 142, 165,
64, 168, 185, 24, 142, 133, 57, 41, 2, 240, 11, 169, 165, 133, 62, 169, 146, 133, 63, 76, 92, 143, 165, 57, 208, 43, 169, 32, 157, 0, 141, 230,
56, 166, 56, 224, 120, 176, 7, 157, 21, 154, 76, 202, 142, 255, 169, 155, 157, 21, 154, 165, 61, 141, 45, 143, 133, 29, 32, 186, 142, 173, 45, 143,
133, 61, 76, 198, 142, 165, 57, 41, 128, 208, 1, 0, 165, 64, 56, 233, 65, 170, 189, 113, 146, 133, 62, 189, 139, 146, 133, 63, 160, 0, 24, 165,
62, 105, 1, 133, 62, 165, 63, 105, 0, 133, 63, 177, 62, 16, 239, 200, 177, 62, 201, 40, 240, 4, 200, 76, 112, 143, 132, 66, 200, 177, 62, 201,
41, 208, 249, 132, 65, 200, 177, 62, 41, 127, 201, 61, 208, 247, 132, 64, 166, 61, 134, 60, 164, 66, 200, 189, 0, 141, 133, 57, 177, 62, 197, 57,
240, 3, 76, 92, 143, 200, 196, 65, 208, 3, 76, 179, 143, 232, 134, 60, 76, 151, 143, 165, 61, 133, 59, 164, 66, 136, 132, 66, 177, 62, 133, 57,
16, 3, 76, 60, 145, 41, 127, 170, 189, 24, 142, 41, 128, 240, 18, 166, 59, 202, 189, 0, 141, 197, 57, 240, 3, 76, 92, 143, 134, 59, 76, 183,
143, 165, 57, 201, 32, 208, 3, 76, 31, 144, 201, 35, 208, 3, 76, 46, 144, 201, 46, 208, 3, 76, 56, 144, 201, 38, 208, 3, 76, 71, 144, 201,
64, 208, 3, 76, 103, 144, 201, 94, 208, 3, 76, 140, 144, 201, 43, 208, 3, 76, 155, 144, 201, 58, 208, 3, 76, 176, 144, 32, 57, 164, 0, 32,
191, 144, 41, 128, 240, 3, 76, 92, 143, 134, 59, 76, 183, 143, 32, 191, 144, 41, 64, 208, 244, 76, 92, 143, 32, 191, 144, 41, 8, 208, 3, 76,
92, 143, 134, 59, 76, 183, 143, 32, 191, 144, 41, 16, 208, 244, 189, 0, 141, 201, 72, 240, 3, 76, 92, 143, 202, 189, 0, 141, 201, 67, 240, 226,
201, 83, 240, 222, 76, 92, 143, 32, 191, 144, 41, 4, 208, 212, 189, 0, 141, 201, 72, 240, 3, 76, 92, 143, 201, 84, 240, 11, 201, 67, 240, 7,
201, 83, 240, 3, 76, 92, 143, 134, 59, 76, 183, 143, 32, 191, 144, 41, 32, 208, 3, 76, 92, 143, 134, 59, 76, 183, 143, 166, 59, 202, 189, 0,
141, 201, 69, 240, 241, 201, 73, 240, 237, 201, 89, 240, 233, 76, 92, 143, 32, 191, 144, 41, 32, 208, 3, 76, 183, 143, 134, 59, 76, 176, 144, 166,
59, 202, 189, 0, 141, 168, 185, 24, 142, 96, 166, 58, 232, 189, 0, 141, 168, 185, 24, 142, 96, 166, 58, 232, 189, 0, 141, 201, 69, 208, 70, 232,
189, 0, 141, 168, 202, 185, 24, 142, 41, 128, 240, 8, 232, 189, 0, 141, 201, 82, 208, 5, 134, 58, 76, 64, 145, 201, 83, 240, 247, 201, 68, 240,
243, 201, 76, 208, 10, 232, 189, 0, 141, 201, 89, 208, 44, 240, 229, 201, 70, 208, 38, 232, 189, 0, 141, 201, 85, 208, 30, 232, 189, 0, 141, 201,
76, 240, 209, 208, 20, 201, 73, 208, 16, 232, 189, 0, 141, 201, 78, 208, 8, 232, 189, 0, 141, 201, 71, 240, 187, 76, 92, 143, 165, 60, 133, 58,
164, 65, 200, 196, 64, 208, 3, 76, 79, 146, 132, 65, 177, 62, 133, 57, 170, 189, 24, 142, 41, 128, 240, 18, 166, 58, 232, 189, 0, 141, 197, 57,
240, 3, 76, 92, 143, 134, 58, 76, 64, 145, 165, 57, 201, 32, 208, 3, 76, 175, 145, 201, 35, 208, 3, 76, 190, 145, 201, 46, 208, 3, 76, 200,
145, 201, 38, 208, 3, 76, 215, 145, 201, 64, 208, 3, 76, 247, 145, 201, 94, 208, 3, 76, 28, 146, 201, 43, 208, 3, 76, 43, 146, 201, 58, 208,
3, 76, 64, 146, 201, 37, 208, 3, 76, 213, 144, 32, 57, 164, 0, 32, 202, 144, 41, 128, 240, 3, 76, 92, 143, 134, 58, 76, 64, 145, 32, 202,
144, 41, 64, 208, 244, 76, 92, 143, 32, 202, 144, 41, 8, 208, 3, 76, 92, 143, 134, 58, 76, 64, 145, 32, 202, 144, 41, 16, 208, 244, 189, 0,
141, 201, 72, 240, 3, 76, 92, 143, 232, 189, 0, 141, 201, 67, 240, 226, 201, 83, 240, 222, 76, 92, 143, 32, 202, 144, 41, 4, 208, 212, 189, 0,
141, 201, 72, 240, 3, 76, 92, 143, 201, 84, 240, 11, 201, 67, 240, 7, 201, 83, 240, 3, 76, 92, 143, 134, 58, 76, 64, 145, 32, 202, 144, 41,
32, 208, 3, 76, 92, 143, 134, 58, 76, 64, 145, 166, 58, 232, 189, 0, 141, 201, 69, 240, 241, 201, 73, 240, 237, 201, 89, 240, 233, 76, 92, 143,
32, 202, 144, 41, 32, 208, 3, 76, 64, 145, 134, 58, 76, 64, 146, 164, 64, 165, 60, 133, 61, 177, 62, 133, 57, 41, 127, 201, 61, 240, 7, 230,
56, 166, 56, 157, 21, 154, 36, 57, 16, 3, 76, 202, 142, 200, 76, 85, 146, 0, 149, 247, 162, 57, 197, 6, 126, 199, 38, 55, 78, 145, 241, 85,
161, 254, 36, 69, 45, 167, 54, 83, 46, 71, 218, 125, 126, 126, 127, 128, 129, 130, 130, 130, 132, 132, 132, 132, 132, 133, 135, 135, 136, 136, 137, 138,
139, 139, 140, 140, 140, 40, 65, 41, 189, 40, 33, 41, 61, 174, 40, 34, 41, 32, 61, 45, 65, 72, 53, 78, 75, 87, 79, 87, 84, 173, 40, 34,
41, 61, 75, 87, 79, 87, 52, 84, 173, 40, 35, 41, 61, 32, 78, 65, 72, 52, 77, 66, 69, 210, 40, 36, 41, 61, 32, 68, 65, 65, 52, 76,
69, 210, 40, 37, 41, 61, 32, 80, 69, 82, 83, 69, 72, 52, 78, 212, 40, 38, 41, 61, 32, 65, 69, 78, 196, 40, 39, 41, 189, 40, 42, 41,
61, 32, 65, 69, 52, 83, 84, 69, 82, 73, 72, 83, 203, 40, 43, 41, 61, 32, 80, 76, 65, 72, 52, 211, 40, 44, 41, 61, 172, 32, 40, 45,
41, 32, 61, 173, 40, 45, 41, 189, 40, 46, 41, 61, 32, 80, 79, 89, 78, 212, 40, 47, 41, 61, 32, 83, 76, 65, 69, 52, 83, 200, 40, 48,
41, 61, 32, 90, 73, 89, 52, 82, 79, 215, 32, 40, 49, 83, 84, 41, 61, 70, 69, 82, 52, 83, 212, 32, 40, 49, 48, 84, 72, 41, 61, 84,
69, 72, 52, 78, 84, 200, 40, 49, 41, 61, 32, 87, 65, 72, 52, 206, 32, 40, 50, 78, 68, 41, 61, 83, 69, 72, 52, 75, 85, 78, 196, 40,
50, 41, 61, 32, 84, 85, 87, 180, 32, 40, 51, 82, 68, 41, 61, 84, 72, 69, 82, 52, 196, 40, 51, 41, 61, 32, 84, 72, 82, 73, 89, 180,
40, 52, 41, 61, 32, 70, 79, 72, 52, 210, 32, 40, 53, 84, 72, 41, 61, 70, 73, 72, 52, 70, 84, 200, 40, 53, 41, 61, 32, 70, 65, 89,
52, 214, 32, 40, 54, 52, 41, 32, 61, 83, 73, 72, 52, 75, 83, 84, 73, 89, 32, 70, 79, 72, 210, 40, 54, 41, 61, 32, 83, 73, 72, 52,
75, 211, 40, 55, 41, 61, 32, 83, 69, 72, 52, 86, 85, 206, 32, 40, 56, 84, 72, 41, 61, 69, 89, 52, 84, 200, 40, 56, 41, 61, 32, 69,
89, 52, 212, 40, 57, 41, 61, 32, 78, 65, 89, 52, 206, 40, 58, 41, 61, 174, 40, 59, 41, 61, 174, 40, 60, 41, 61, 32, 76, 69, 72, 52,
83, 32, 68, 72, 65, 69, 206, 40, 61, 41, 61, 32, 73, 89, 52, 75, 87, 85, 76, 218, 40, 62, 41, 61, 32, 71, 82, 69, 89, 52, 84, 69,
82, 32, 68, 72, 65, 69, 206, 40, 63, 41, 61, 174, 40, 64, 41, 61, 32, 65, 69, 54, 212, 40, 94, 41, 61, 32, 75, 65, 69, 52, 82, 73,
88, 212, 93, 193, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};





//26 items. From 'A' to 'Z'
// positions for mem62 and mem63 for each character
unsigned char tab37489[] =
{
0, 149, 247, 162, 57, 197, 6, 126,
199, 38, 55, 78, 145, 241, 85, 161,
254, 36, 69, 45, 167, 54, 83, 46,
71, 218
};
unsigned char tab37515[] =
{
125, 126, 126, 127, 128, 129, 130, 130,
130, 132, 132, 132, 132, 132, 133, 135,
135, 136, 136, 137, 138, 139, 139, 140,
140, 140
};
#endif
