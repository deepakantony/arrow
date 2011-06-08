
#include "Filter.h"

Filter::Filter() {
	support = 1;
}

Filter::Filter(int support)
:support(support)
{
}

int Filter::getSupport() {
	return support;
}
