// validationReservoirInput.cpp -- validation of the selection symbol
#include <cctype>

#include "validationReservoirInput.h"

Validation validationReservoirInput(const int& input)
{
	if (input > 0 && input < 4)
	{
		return Validation::Success;
	}

	return Validation::Invalid;
}
