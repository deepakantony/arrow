
#include "PlanarMapping.h"

PlanarMapping::PlanarMapping()
{
}

void PlanarMapping::map(const Point& hitPos, Vector& uvw) const
{
	// Something I don't understand!
	//uvw = Vector((hitPos.x()+1.0)/2.0, (hitPos.y()+1.0)/2.0, (hitPos.z()+1.0)/2.0);
}
