#pragma once
#include "PositionedObject.h"

class Entity : public PositionedObject
{
public:
	bool BeenHit = false;
	bool EntityOnly = false;

	virtual bool Initialize(Utilities* utilities);
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

	bool CirclesIntersect(Entity& target);
	bool CirclesIntersectBullet(Entity& target);

private:
	Ray TheRay = { 0 };
	RayCollision TheRayCollision = { 0 };
};

