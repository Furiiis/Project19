#include "figure.h"

namespace Figure_2D {

	const Coordinate Get_Displace_Vector(const Coordinate& from, const Coordinate& to)
	{
		return { to.first - from.first, to.second - from.second };
	}

}