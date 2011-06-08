#ifndef WORLD_H_
#define WORLD_H_

#include <Scene.h>

public class World {
public:
	World();
	
private:
	virtual void build() const = 0;
}

#endif /*WORLD_H_*/
