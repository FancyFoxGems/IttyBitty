#ifndef _ITTYBITTY_GPIO_H
#define _ITTYBITTY_GPIO_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IttyBitty_bits.h"

namespace GPIO
{
	class IttyBitty_GPIO
	{
	 protected:


	 public:
		void init();
	};

	extern const IttyBitty_GPIO gp;
}

#endif
