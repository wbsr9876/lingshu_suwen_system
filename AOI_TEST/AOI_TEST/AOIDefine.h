#ifndef _AOI_DEFINE_
#define _AOI_DEFINE_

#define FLOAT_DELTA 0.001f

enum AOI_STEP
{
	AOI_STEP_INIT = 0x1,
	AOI_STEP_CEHCK = 0x2,
	AOI_STEP_OUTPUT = 0x4,

};

enum COORDINATE_NAME
{
	X_COORDINATE,
	Y_COORDINATE,
	Z_COORDINATE
};
enum BLOCK_TYPE
{
	INVAILD_BLOCK = 0x1,
	PARENT_BLOCK = 0x2,
};

inline bool Less(float a, float b)
{
	return a + FLOAT_DELTA < b;
}
inline bool More(float a, float b)
{
	return a - FLOAT_DELTA > b;
}
inline bool Equal(float a, float b)
{
	return a - FLOAT_DELTA < b && a + FLOAT_DELTA > b;
}
#endif
