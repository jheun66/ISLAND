#include "Framework.h"

Light::Light()
{
	color = Float4(1, 1, 1, 1);
	position = Float3(0, 0, 0);
	range = 80.0f;
	direction = Float3(0, -1, 0);
	outer = 65.0f;
	inner = 55.0f;
	length = 50;
	type = POINT;
	active = 1;
}
