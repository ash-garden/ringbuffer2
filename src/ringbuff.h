/*
 * ringbuff.h
 *
 *  Created on: 2019/03/11
 *      Author: AshGarden
 */

#ifndef RINGBUFF_H_
#define RINGBUFF_H_
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
				uint8_t*	data);

void writeRB(	RINGMNG_T	*mng,
				uint8_t*	data );

bool readRB(	RINGMNG_T	*mng,
				uint8_t*	data );


#endif /* RINGBUFF_H_ */
