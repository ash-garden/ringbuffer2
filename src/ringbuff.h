/**
 * @file	ringbuff.h
 * @brief	RingBuffer
 * @author	AshGarden
 * @date	2019/03/11
 */

#ifndef RINGBUFF_H_
#define RINGBUFF_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct{
	uint32_t	write_index;
	uint32_t	read_index;
	uint32_t	max_index;
	uint32_t	max_len;
	uint8_t*	rbd;
}RINGMNG_T;

RINGMNG_T*	CreateRBMandRBD(	uint32_t	max_index,
								uint32_t	max_len);
void	DelleteRBMandRBD(RINGMNG_T*	mng);

void initRBM(	RINGMNG_T	*mng,
				uint32_t	max_index,
				uint32_t	max_len,
				uint8_t*	rbd);

void writeRB(	RINGMNG_T	*mng,
				uint8_t*	data );

bool readRB(	RINGMNG_T	*mng,
				uint8_t*	data );

#define WriteRB(x,y) writeRB(x,(uint8_t*)y)
#define ReadRB(x,y) readRB(x,(uint8_t*)y)


#endif /* RINGBUFF_H_ */
