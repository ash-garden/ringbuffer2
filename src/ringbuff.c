/*
 * ringbuff.c
 *
 *  Created on: 2019/03/11
 *      Author: AshGarden
 */


#include "ringbuff.h"


RINGMNG_T*	CreateRBMandRBD(	uint32_t	max_index,
								uint32_t	max_len)
{
	RINGMNG_T* mng;
	uint8_t*	rbd;

	mng = malloc(sizeof(RINGMNG_T));
	if( mng != 0)
	{
		rbd = malloc(max_index * max_len);
		if( rbd == 0)
		{
			free(mng);
			mng = 0;
		}
		else{
			initRBM(mng,max_index,max_len,rbd);
		}
	}
	return mng;
}


void	DelleteRBMandRBD(RINGMNG_T*	mng)
{
	free(mng->rbd);
	free(mng);
}


void initRBM(	RINGMNG_T	*mng,
				uint32_t	max_index,
				uint32_t	max_len,
				uint8_t*	data)
{
	mng->write_index = 0;
	mng->read_index = 0;
	mng->max_index = max_index;
	mng->max_len = max_len;
	mng->rbd = data;
}

void writeRB(	RINGMNG_T	*mng,
				uint8_t*	data )
{
	memcpy(	&mng->rbd[mng->write_index*mng->max_len],
			data,
			mng->max_len);
	mng->write_index =
			(mng->write_index + 1) % mng->max_index;
}


bool readRB(	RINGMNG_T	*mng,
				uint8_t*	data )
{
	if(mng->write_index != mng->read_index){
		memcpy(	data,
				&mng->rbd[mng->read_index * mng->max_len],
				mng->max_len );
		mng->read_index =
				(mng->read_index + 1) % mng->max_index;
		return true;
	}
	else{
		return false;
	}
}

