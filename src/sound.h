/*
 * sound.h
 *
 *  Created on: 7 déc. 2017
 *      Author: Willliam
 */

#ifndef SOUND_H_
#define SOUND_H_

void initCodec();
Int16 AIC3204_rset( Uint16 regnum, Uint16 regval);
void generateSound(Uint16 freq, Uint16 duration, float volume);


#endif /* SOUND_H_ */
