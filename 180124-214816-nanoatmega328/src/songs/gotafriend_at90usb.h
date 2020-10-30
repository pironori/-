#ifndef gotafriend
#define gotafriend
#include <stdint.h>
#include <avr/pgmspace.h>

#define PART0 256,p0_notes,p0_delays,sizeof(p0_notes)/sizeof(*(p0_notes)),sizeof(p0_delays)/sizeof(*(p0_delays))
#define PART1 256,p1_notes,p1_delays,sizeof(p1_notes)/sizeof(*(p1_notes)),sizeof(p1_delays)/sizeof(*(p1_delays))
/*

    Part: 0
    Freq: 8000000
    Number of voices: 1
    Note length: 319
    Delay length: 319

    Part: 1
    Freq: 8000000
    Number of voices: 1
    Note length: 165
    Delay length: 165

*/
const uint8_t p0_notes[] PROGMEM = {
0,79,66,49,44,41,39,49,59,41,44,49,66,70,74,0,79,99,83,105,88,112,83,105,83,0,79,66,79,79,59,66,79,88,99,112,0,0,59,49,59,49,83,79,79,83,79,0,99,59,74,66,99,0,0,62,62,59,59,66,59,59,66,79,79,99,88,88,99,79,79,99,59,88,79,66,79,99,83,79,118,59,49,59,66,105,99,99,99,66,66,49,49,59,66,49,59,59,0,79,66,49,44,41,39,49,59,41,44,49,66,70,74,0,79,66,79,79,59,66,79,88,99,112,0,0,59,49,59,49,83,79,79,83,79,0,99,59,74,66,99,0,0,62,62,59,59,66,59,59,66,79,79,99,88,88,99,79,79,99,59,88,79,66,79,99,83,79,118,59,49,59,66,105,99,99,99,66,66,49,49,59,66,49,59,59,79,79,79,0,74,74,74,74,74,74,74,74,59,59,52,70,70,70,70,70,70,70,70,52,0,79,59,83,59,79,59,59,83,52,52,52,52,79,52,52,52,52,52,52,59,66,66,0,79,74,79,88,79,0,0,79,79,79,59,66,99,88,99,112,99,0,59,49,59,49,83,79,79,83,79,0,74,59,49,59,70,70,59,66,49,79,70,49,59,66,105,105,99,99,66,66,0,70,49,59,66,105,105,99,49,52,66,0,70,49,59,66,49,59,59,79,66,49,44,41,39,49,59,41,44,49,66,70,74,0,99,0,0
};
const uint8_t p0_delays[] PROGMEM = {
2,2,1,2,1,2,4,4,4,4,4,4,4,4,5,1,4,4,4,4,4,4,4,2,1,1,2,2,2,2,4,2,6,2,4,5,1,2,2,2,2,4,2,6,4,2,5,1,2,2,2,4,5,1,2,2,2,4,2,2,4,2,2,4,2,2,4,4,4,2,4,2,2,4,2,2,2,2,2,4,4,4,6,2,2,2,4,4,2,2,6,2,6,2,2,4,2,2,2,2,1,2,1,2,4,4,4,4,4,4,4,4,5,1,2,2,2,2,4,2,6,2,4,5,1,2,2,2,2,4,2,6,4,2,5,1,2,2,2,4,5,1,2,2,2,4,2,2,4,2,2,4,2,2,4,4,4,2,4,2,2,4,2,2,2,2,2,4,4,4,6,2,2,2,4,4,2,2,6,2,6,2,2,4,2,6,2,4,4,2,2,2,1,2,1,2,1,2,2,1,1,2,1,1,2,1,2,2,1,2,1,7,1,7,9,2,4,2,2,2,2,2,4,2,2,4,2,4,2,2,4,4,6,2,2,4,2,4,5,1,2,2,2,2,4,2,6,2,4,4,2,2,2,2,2,4,2,6,4,2,5,1,2,2,2,2,4,3,1,4,4,8,2,2,2,2,2,4,4,2,2,9,1,2,2,2,2,2,4,4,2,2,9,1,2,2,2,2,4,2,4,2,1,2,1,2,4,4,4,4,4,4,4,4,5,1,45,1,2
};

const uint8_t p1_notes[] PROGMEM = {
49,52,59,62,66,66,49,0,66,0,66,66,49,66,49,66,49,44,39,37,0,34,33,24,29,33,39,49,37,39,39,29,37,39,39,29,37,34,33,31,29,37,39,59,29,44,33,24,29,44,33,49,52,59,62,66,66,49,66,49,66,49,44,39,37,0,34,33,24,29,33,39,49,37,39,39,29,37,39,39,29,37,34,33,31,29,37,39,59,29,44,33,24,29,44,33,24,49,44,39,37,49,52,52,49,52,49,66,49,52,0,46,0,44,0,41,41,39,39,59,59,44,44,66,66,49,66,49,66,49,44,39,37,0,34,33,24,29,33,39,49,37,34,33,31,29,44,33,24,29,44,33,24,29,44,33,49,52,59,62,66,66,24,0,0
};
const uint8_t p1_delays[] PROGMEM = {
8,8,8,8,8,8,7,1,4,4,8,8,8,8,8,4,1,2,1,7,1,8,4,4,2,2,2,2,8,8,8,8,8,8,8,8,4,4,4,2,2,2,4,6,4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,1,2,1,7,1,8,4,4,2,2,2,2,8,8,8,8,8,8,8,8,4,4,4,2,2,2,4,6,4,8,8,8,8,8,8,4,4,4,4,8,8,8,8,8,8,4,4,8,7,1,7,1,7,1,4,4,4,4,4,4,4,4,4,4,8,8,8,4,1,2,1,7,1,8,4,4,2,2,2,2,8,8,4,4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,45,1,2
};

#endif
