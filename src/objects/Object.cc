
#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::preprocess()
{
}

void Object::setInstance(const bool isInstanced)
{
	this->isInstanced = isInstanced;
}

void Object::setInvTransMatrix(const Matrix invTransMatrix)
{
	this->invTransMatrix = invTransMatrix;
}

void Object::setTransMatrix(const Matrix transMatrix)
{
	this->transMatrix = transMatrix;
}
