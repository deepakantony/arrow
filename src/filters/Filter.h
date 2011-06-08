

#ifndef _FILTER_H_
#define _FILTER_H_

class Filter
{
public:
	Filter(void);
	Filter(int support);
	virtual double evaluate(double x, double y) const = 0;
	int getSupport();
	
protected:
	int support;
private:

};

#endif // _FILTER_H_
