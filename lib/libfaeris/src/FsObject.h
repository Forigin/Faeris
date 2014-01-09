#ifndef FAERIS_OBJECT_H_ 
#define FAERIS_OBJECT_H_

#include "FsMacros.h"

#define FS_INVALID_HASH_CODE (-1)

NS_FS_BEGIN

class ObjectMgr;
class FsObject 
{
	/* class attribute */
	private:
		static int m_objectNu;
	public:
		static int getObjectNu(){return FsObject::m_objectNu;}


	/* object attribute */
	private:
		bool m_autoDelete;
		int m_refNu;
		ObjectMgr* m_objectMgr;

	public:
		int refCnt(){return m_refNu;}
		void addRef(){m_refNu++;}
		void decRef()
		{
			m_refNu--;
			if((m_refNu<=0)&&m_autoDelete)
			{
				delete this;
			}
		}

		void destory(){
			FS_TRACE_WARN_ON(m_refNu>0,"Object(%s) Is Owner By Other %d Object",className(),m_refNu);
			delete this;
		}

	public:
		FsObject()
			:m_autoDelete(true),
			:m_refNu(0),
			m_objectMgr(NULL),
#if FS_CONFIG(FS_SCRIPT_SUPPORT)
			m_scriptData(-1)
#endif 
		{ 
			FsObject::m_objectNu++;
		}

		virtual ~FsObject();
		virtual const char* className()=0;
		virtual long getHashCode();
		virtual bool equal(FsObject* ob); 

		virtual void destruct();


		void setObjectMgr(ObjectMgr* ob);
		ObjectMgr* getObjectMgr();


#if FS_CONFIG(FS_SCRIPT_SUPPORT)
	public:
		int m_scriptData; /* script data */

	public:
		virtual void dropScriptData();
#endif 

};
NS_FS_END

#endif 




