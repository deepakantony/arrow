
#ifndef _PLANARMAPPING_H_
#define _PLANARMAPPING_H_

#include "Point.h"
#include "Vector.h"
#include "Mapping.h"

class PlanarMapping: public Mapping 
{
public:
  PlanarMapping();
	void map(const Point& hitPos, Vector& uvw) const;

protected:

private:

};

#endif // _PLANARMAPPING_H_
