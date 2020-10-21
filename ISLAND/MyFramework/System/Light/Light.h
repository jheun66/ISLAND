#pragma once

// TODO : Light 분리하기

//#define MAX_LIGHT 10
//struct LightInfo
//{
//private:
//	enum Type
//	{
//		DIRECTION,
//		POINT,
//		SPOT,
//		CAPSULE
//	};
//
//	Float4 color;
//
//	Float3 position;
//	float range;
//
//	Float3 direction;
//	float outer;
//
//	float inner;
//	float length;
//	Type type;
//	int active;
//
//public:
//	LightInfo();
//	{
//		color = Float4(1, 1, 1, 1);
//		position = Float3(0, 0, 0);
//		range = 80.0f;
//		direction = Float3(0, -1, 0);
//		outer = 65.0f;
//		inner = 55.0f;
//		length = 50;
//		type = POINT;
//		active = 1;
//	}
//
//};