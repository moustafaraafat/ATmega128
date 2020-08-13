/*
 * bit_handle.h
 *
 * Created: 5/20/2020 11:10:47 AM
 *  Author: Raafat
 */ 


#ifndef BIT_HANDLE_H_
#define BIT_HANDLE_H_

/*Set, Clear, Toggle, and read a bit*/
#define setBit(R,N)				(R |=  (1<<(N)))
#define clearBit(R,N)			(R &= ~(1<<(N)))
#define toggleBit(R,N)			(R ^=  (1<<(N)))

#define readBit(R,N)			((R>>(N)) & 0x01)

/*Set, Clear, Toggle, and read a group of bits*/
#define setBits(R,M)			(R |=  M)
#define clearBits(R,M)			(R &=  ~M)
#define toggleBits(R,M)			(R ^=  M)

/*Set, Clear, Toggle, and read all bits*/
#define setAllBits(R)			(R =  (0xFF))
#define clearAllBits(R)			(R =  (0x00))
#define toggleAllBits(R)		(R ^= (0xFF))

#endif /* BIT_HANDLE_H_ */