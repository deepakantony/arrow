

#ifndef _SPHERICALMAPPING_H_
#define _SPHERICALMAPPING_H_

#include "Mapping.h"

class SphericalMapping: public Mapping 
{
public:
	SphericalMapping();
		
	void map(const Point& hitPos, Vector& uvw) const;

protected:

private:

};

#endif // _SPHERICALMAPPING_H_
