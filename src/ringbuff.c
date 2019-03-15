/**
 * @file	ringbuff.c
 * @brief	RingBuffer
 * @author	AshGarden
 * @date	2019/03/11
 */
#include "ringbuff.h"

/*!
 * @fn		RINGMNG_T*	CreateRBMandRBD(uint32_t	max_index, uint32_t	max_len)
 * @brief	Create RingBufferManager & RingBufferData Area
 * @param [in] max_index	Max count write able to RingBuffer.
 * @param [in] max_len		Size that can be written to the ring buffer at once.
 * @return	RingBufferManager
 */
RINGMNG_T*	CreateRBMandRBD(	uint32_t	max_index, uint32_t	max_len)
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

/**
 * @fn		void	DelleteRBMandRBD(RINGMNG_T*	mng)
 * @brief	Dellete RingBufferManager & RingBufferData Area
 * @param [in] mng	RingBufferManager
 */
void	DelleteRBMandRBD(RINGMNG_T*	mng)
{
	free(mng->rbd);
	free(mng);
}

/**
 * @fn		void initRBM(	RINGMNG_T	*mng,	uint32_t	max_index,	uint32_t	max_len,	uint8_t*	rbd)
 * @brief	init RingBufferManager
 * @param [in] mng			RingBufferManager
 * @param [in] max_index	Max count write able to RingBuffer.
 * @param [in] max_len		Size that can be written to the ring buffer at once.
 * @param [in] data			RingBufferData Area
 * @details		If you prepare the memory of RingBufferManager and RingBufferDataArea yourself,
 * 				you can initialize with this function.
 */
void initRBM(	RINGMNG_T	*mng,
				uint32_t	max_index,
				uint32_t	max_len,
				uint8_t*	rbd)
{
	mng->write_index = 0;
	mng->read_index = 0;
	mng->max_index = max_index;
	mng->max_len = max_len;
	mng->rbd = rbd;
}

/**
 * @fn	void writeRB(	RINGMNG_T	*mng,	uint8_t*	data )
 * @brief		Write Data to RingBuff
 * @param [in] mng		RingBufferManager
 * @param [in] data		Data
 */
void writeRB(	RINGMNG_T	*mng,
				uint8_t*	data )
{
	memcpy(	&mng->rbd[mng->write_index*mng->max_len],
			data,
			mng->max_len);
	mng->write_index =
			(mng->write_index + 1) % mng->max_index;
}

/**
 * @fn		bool readRB(	RINGMNG_T	*mng,uint8_t*	data )
 * @brief	Read Data from RingBuffer
 * @param [in] mng			RingBufferManager
 * @param [out] data		Data
 * @return
 */
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

