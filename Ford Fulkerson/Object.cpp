#include "Object.h"

Object::Object(int loo)
{
	labelOfObject = loo;
	isObjectSet = false;
}

bool Object::GetIsObjectSet(){return isObjectSet;}
int Object::GetLabelOfObject(){return labelOfObject;}
