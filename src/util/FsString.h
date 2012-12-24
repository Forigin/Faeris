#ifndef _FS_REFCONT_STRING_H_
#define _FS_REFCONT_STRING_H_
#include <string>

#include "FsMacros.h"
#include "core/FsObject.h"

FAERIS_NAMESPACE_BEGIN
class FsString:public FsObject
{
	private:
		std::string m_string;
		FsLong m_hash_code;
	public:
		static FsBool checkType(FsObject* ob);

	public: 
		FsString();
		FsString(const FsChar* str);
		FsString(FsInt value);

	public:
		virtual FsLong getHashCode();
		virtual const FsChar* getName();
		virtual FsBool equal(FsObject* ob);
		virtual FsBool equal(const FsChar* str);
	public:
		FsString& append(const FsChar* str);
		FsString& append(const FsChar* str,FsLong n);
		FsString& append(const FsString& str);
		FsString& append(const FsString& str,FsLong n);

		FsString& assign(const FsString& str);
		FsString& assign(const FsString& str,FsLong n);
		FsString& assign(const FsChar* str);
		FsString& assign(const FsChar* str,FsLong n);

		void clear();
		int compare(const FsString& str) const;
		int compare(const FsChar* str)const;
		const FsChar* cstr()const;
		bool empty()const; 
		FsUlong length()const;
		FsString& erase(FsLong pos,FsLong num=1);
		FsChar operator[](FsUlong n)const ;
	private:
		inline void mCalHashCode();
};
FAERIS_NAMESPACE_END 

#include "FsString.inl"

#endif  /*_FS_REFCONT_STRING_H_*/
	





	
