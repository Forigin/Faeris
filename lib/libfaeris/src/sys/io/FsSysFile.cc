#include"FsSysFile.h"

#if FS_PLATFORM_OS(FS_OS_WIN32)|| FS_PLATFORM_OS(FS_OS_LINUX) ||FS_PLATFORM_OS(FS_OS_ANDROID)
	#include "platform/FsSysStdFile.cc"
#else
	#error "Error Platform For SysFile"
#endif 

NS_FS_BEGIN

const char* SysFile::getFileName()
{
	return FS_SYS_FILE_CLASS_NAME;
}

NS_FS_END
