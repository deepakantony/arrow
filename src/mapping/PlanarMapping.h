
#ifndef _PLANARMAPPING_H_
#define _PLANARMAPPING_H_

class PlanarMapping: public Mapping 
{
public:
	void map(const Point& hitPos, Vector& uvw) const;

protected:

private:

};

#endif // _PLANARMAPPING_H_
