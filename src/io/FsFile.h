#ifndef _FAERY_IO_FSFILE_H_
#define _FAERY_IO_FSFILE_H_

#include "FsMacros.h"
#include "core/FsObject.h"
NS_FS_BEGIN

class FsFile:public FsObject
{
	public:
		enum
		{
			FS_SEEK_SET,
			FS_SEEK_CUR,
			FS_SEEK_END,
		};
		enum
		{
			FS_IO_RDONLY=0x1,
			FS_IO_WRONLY=0x2,
			FS_IO_RDWR=0x4,
			FS_IO_APPEND=0x8,
			FS_IO_CREATE=0x16,
			FS_IO_TRUNC=0x32
		};
	public:
		virtual FsLong read(FsVoid* buf,FsLong length)=0;
		virtual FsLong write(const FsVoid* buf,FsLong length)=0;
		virtual FsLong seek(FsLong offset,FsInt where)=0;
		virtual FsInt  close()=0;
		virtual FsLong tell()=0;
		virtual FsLong getLength();
		virtual ~FsFile(){}
		virtual const FsChar* getName();
	public:
		FsLong writeStr(const char* fmt,...);
};

NS_FS_END

#endif  /*_FAERY_IO_FSFILE_H_*/
