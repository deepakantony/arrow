
#ifndef _MAPPING_H_
#define _MAPPING_H_

#include "utils/Point.h"

class Mapping
{
public:
	virtual void map(const Point& hitPos, Vector& uvw) const = 0;

protected:

private:

};

#endif // _MAPPING_H_
