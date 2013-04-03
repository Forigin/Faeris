#ifndef _FS_PACKAGE_H_
#define _FS_PACKAGE_H_ 

#include "core/FsObject.h"

NS_FS_BEGIN

class FsFile;
class Package:public FsObject
{
	public:
		enum 
		{
			PACKAGE_UNKOWN=0,
			PACKAGE_ZIP,
			PACKAGE_RES,
		};
	public:
		static  Package* create(const char* filename,int type=PACKAGE_UNKOWN);
	public:
		virtual FsFile* getBlock(const char* file)=0;
		virtual ~Package();
	public:
		virtual const char* className();
};
NS_FS_END

#endif /*_FS_PACKAGE_H_*/

