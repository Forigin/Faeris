#ifndef _FAERY_TIMER_H_
#define _FAERY_TIMER_H_ 
#include "FsMacros.h"
#include "FsConfig.h"

#if FS_PLATFORM_OS(FS_OS_LINUX)
	#include <sys/time.h>
	typedef struct timeval PlatformTimeVal;
#elif FS_PLATFORM_OS(FS_OS_WIN32)
	#include <Windows.h>
	typedef DWORD  PlatformTimeVal;
#else 
	#error "Unsupport Platform OS"
#endif 

NS_FS_BEGIN


class Timer
{
	public:
		Timer();
		void reset();
		FsLong now() const ;
	private:
		PlatformTimeVal m_begin;
};

NS_FS_END

#endif /*_FAERY_TIMER_H_*/
