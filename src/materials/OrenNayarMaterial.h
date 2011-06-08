
#ifndef _ORENNAYARMATERIAL_H_
#define _ORENNAYARMATERIAL_H_

#include "Material.h"

class OrenNayarMaterial: public Material 
{
public:

protected:

private:
	double A,B;
	double Ka, Kd;
	Color color;
};

#endif // _ORENNAYARMATERIAL_H_
