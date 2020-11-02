#pragma once

#define MAX_LIGHT 10
class Light
{
private:
	friend class Environment;
	friend class Scattering;
	enum Type
	{
		DIRECTION,
		POINT,
		SPOT,
		CAPSULE
	};

	Float4 color;

	Float3 position;
	float range;

	Float3 direction;
	float outer;

	float inner;
	float length;
	Type type;
	int active;

public:
	Light();
	~Light() = default;
};