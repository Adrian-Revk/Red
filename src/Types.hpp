#ifndef TYPES
#define TYPES


namespace blue {

#ifdef _MSC_VER
	typedef unsigned __int8		u8;
#else
	typedef unsigned char		u8;
#endif


#ifdef _MSC_VER
	typedef unsigned __int16	u16;
#else
	typedef unsigned short		u16;
#endif


#ifdef _MSC_VER
	typedef unsigned __int32	u32;
#else
	typedef unsigned int			u32;
#endif


	typedef float f32;
	typedef double f64;

}

#endif
