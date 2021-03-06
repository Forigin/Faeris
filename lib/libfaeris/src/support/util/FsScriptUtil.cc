#include <string.h>
#include <stdlib.h>

#include "support/util/FsScriptUtil.h"
#include "support/util/FsArray.h"
#include "support/util/FsDict.h"
#include "support/util/FsString.h"
#include "support/felis/xir_parser.h"
#include "support/data/FsJson.h"

NS_FS_BEGIN
static bool s_ObjectWrite(FsObject* ob,FsFile* file,int indent);
static void s_IndentWrite(FsFile* file,int indent);
static bool s_ArrayWrite(FsArray* ay,FsFile* file);
static bool s_DictWrite(FsDict* dt,FsFile* file,int indent);
static bool s_StringWrite(FsString* str,FsFile* file);


static bool s_ObjectWrite(FsObject* ob,FsFile* file,int indent)
{
	if(FsString::checkType(ob))
	{
		s_StringWrite((FsString*)ob,file);
	}
	else if(FsDict::checkType(ob))
	{
		s_DictWrite((FsDict*)ob,file,indent);
	}
	else if(FsArray::checkType(ob))
	{
		s_ArrayWrite((FsArray*)ob,file);
	}
	else 
	{
		file->writeStr("%s(%ld)",ob->className(),(long)ob);
	}
	return true;
}
static void s_IndentWrite(FsFile* file,int indent)
{
	for(int i=0;i<indent;++i)
	{
		file->writeStr("\t");
	}
}
static bool s_ArrayWrite(FsArray* ay,FsFile* file)
{
	FsArray::Iterator iter(ay);
	file->writeStr("[");
	while(!iter.done())
	{
		FsObject* ob=iter.getValue();
		if(ob!=NULL)
		{
			s_ObjectWrite(ob,file,-1);
			ob->decRef();
		}
		file->writeStr(",");
		iter.next();
	}
	file->writeStr("]");
	return true;
}
static bool s_DictWrite(FsDict* dt,FsFile* file,int indent)
{
	FsDict::Iterator iter(dt);
	file->writeStr("{");
	if(indent!=-1)
	{
		file->writeStr("\n");
	}
	while(!iter.done())
	{
		FsObject* key=iter.getKey();
		FsObject* value=iter.getValue();
		if(indent!=-1)
		{
			s_IndentWrite(file,indent+1);
			s_ObjectWrite(key,file,-1);
			file->writeStr(":");
			s_ObjectWrite(value,file,indent+1);
			file->writeStr("\n");
		}
		else 
		{
			s_ObjectWrite(key,file,-1);
			file->writeStr(":");
			s_ObjectWrite(value,file,-1);
			file->writeStr(",");
		}
		key->decRef();
		value->decRef();
		iter.next();
	}
	if(indent!=-1)
	{
		s_IndentWrite(file,indent);
	}
	file->writeStr("}");
	return true;
}

static inline bool s_SpecialChar(char ch)
{
	switch(ch)
	{
		/* Specifal char */
		case '{':
		case '}':
		case '[':
		case ']':
		case ':':
		case ',':
		case '\'':
		case '\"':
		case '#':
			return true;

		/* reverse */
		case '$':
		case '%':
		case '&':
		case '(':
		case ')':
		case '*':
		case '/':
		case ';':
		case '<':
		case '=':
		case '>':
		case '?':
		case '@':
		case '^':
		case '`':
		case '|':
		case '~':
			return true;



	}
	return false;
}
static inline bool s_EscapeChar(char ch)
{
	switch(ch)
	{
		case '\t':
		case '\n':
		case '\\':
		case '\"':
			return true;
	}
	return false;
}

static inline char  s_EscapeCharToOrign(char ch)
{
	switch(ch)
	{
		case 't':
			return '\t';
		case 'n':
			return '\n';
		case '\\':
			return '\\';
		case '\"':
			return '\"';
	}
	return ch;
}

static bool s_StringWrite(FsString* str,FsFile* file)
{

	bool need_quote=false;
	const char* chs=str->cstr();
	for(uint i=0;i<str->length();++i)
	{
		if(s_SpecialChar(chs[i])||s_EscapeChar(chs[i]))
		{
			need_quote=true;
			break;
		}
	}

	if(need_quote)
	{
		file->writeStr("\"");
		for(uint i=0;i<str->length();++i)
		{
			switch(chs[i])
			{
				case '\t':
					file->writeStr("\\t");
					break;
				case '\n':
					file->writeStr("\\n");
					break;
				case '\"':
					file->writeStr("\\\"");
					break;
				case '\\':
					file->writeStr("\\");
					break;
				default:
					file->writeStr("%c",chs[i]);
					break;
			}
		}
		file->writeStr("\"");
	}
	else 
	{
		file->writeStr("%s",chs);
	}
	return true;
}

FsDict* ScriptUtil::parseJson(const char* json)
{
	return FsJson_Decode(json);
}

FsDict* ScriptUtil::parseScript(FsFile* file)
{
	return XirParser::create(file);
}



bool ScriptUtil::saveScript(FsFile* file,FsDict* dict,int indent)
{
	FsDict::Iterator iter(dict);
	while(!iter.done())
	{
		FsObject* key=iter.getKey();
		FsObject* value=iter.getValue();
		if(indent!=-1)
		{
			s_IndentWrite(file,indent);
			s_ObjectWrite(key,file,-1);
			file->writeStr(":");
			s_ObjectWrite(value,file,indent);
			file->writeStr("\n");
		}
		else 
		{
			s_ObjectWrite(key,file,-1);
			file->writeStr(":");
			s_ObjectWrite(value,file,-1);
			file->writeStr(",");
		}
		key->decRef();
		value->decRef();
		iter.next();
	}
	return true;
}	

char* ScriptUtil::escapeStringToOrign(const char* src)
{
	char* buffer=NULL;
	long src_len=0;
	long dst_len=0;

	if(src[0]!='\''&&src[0]!='\"')
	{
		return NULL;
	}

	src_len=strlen(src);

	FS_TRACE_ERROR_ON(src_len<2,"Some Error Must Happen");

	buffer=new char[src_len+1];

	long i=1;
	while(i<src_len-1)
	{
		if(src[i]=='\\')
		{
			i++;
			buffer[dst_len++]=s_EscapeCharToOrign(src[i]);
		}
		else 
		{
			buffer[dst_len++]=src[i];
		}
		i++;
	}
	buffer[dst_len]='\0';
	return buffer;
}


FsArray* ScriptUtil::getArray(FsDict* dict,const char* key)
{
	FsObject* ob=dict->lookup(key);
	if(ob==NULL)
	{
		return NULL;
	}

	if(FsArray::checkType(ob))
	{
		return (FsArray*)ob;
	}
	else 
	{
		return NULL;
	}
}

FsDict* ScriptUtil::getDict(FsDict* dict,const char* key)
{
	FsObject* ob=dict->lookup(key);
	if(ob==NULL)
	{
		return NULL;
	}

	if(FsDict::checkType(ob))
	{
		return (FsDict*)ob;
	}
	else 
	{
		return NULL;
	}
}
FsString* ScriptUtil::getString(FsDict* dict,const char* key)
{
	FsObject* ob=dict->lookup(key);
	if(ob==NULL)
	{
		return NULL;
	}

	if(FsString::checkType(ob))
	{
		return (FsString*)ob;
	}
	else 
	{
		return NULL;
	}
}

bool ScriptUtil::getInteger(FsDict* dict,const char* key,int* value)
{
	FsString* str=getString(dict,key);
	if(str==NULL)
	{
		return false;
	}
	*value=parseInteger(str);
	return true;

}

bool ScriptUtil::getFloat(FsDict* dict,const char* key,float* value)
{
	FsString* str=getString(dict,key);
	if(str==NULL)
	{
		return false;
	}
	*value=parseFloat(str);
	return true;
}
/* aux for quick get object in array */
FsArray* ScriptUtil::getArray(FsArray* array,uint index)
{
	FsObject* ob=array->get(index);
	if(ob==NULL)
	{
		return NULL;
	}
	if(FsArray::checkType(ob))
	{
		return (FsArray*) ob;
	}
	else 
	{
		return NULL;
	}
}


FsDict* ScriptUtil::getDict(FsArray* array,uint index)
{
	FsObject* ob=array->get(index);
	if(ob==NULL)
	{
		return NULL;
	}
	if(FsDict::checkType(ob))
	{
		return (FsDict*) ob;
	}
	else 
	{
		return NULL;
	}
}

FsString* ScriptUtil::getString(FsArray* array,uint index)
{
	FsObject* ob=array->get(index);
	if(ob==NULL)
	{
		return NULL;
	}
	if(FsString::checkType(ob))
	{
		return (FsString*) ob;
	}
	else 
	{
		return NULL;
	}
}

bool ScriptUtil::getInteger(FsArray* array,uint index,int* v)
{
	FsString* str=ScriptUtil::getString(array,index);
	if(str==NULL)
	{
		return false;
	}

	*v=parseInteger(str);
	return true;
}
bool ScriptUtil::getFloat(FsArray* array,uint index,float* v)
{
	FsString* str=ScriptUtil::getString(array,index);
	if(str==NULL)
	{
		return false ;
	}
	*v=parseFloat(str);
	return true;
}

bool ScriptUtil::getBoolean(FsDict* dict,const char* name,bool* value)
{
	FsString* str=ScriptUtil::getString(dict,name);
	if(str==NULL)
	{
		return false;
	}
	*value=parseBoolean(str);
	return true;
}
bool ScriptUtil::getBoolean(FsArray* array,uint index,bool* value)
{
	FsString* str=ScriptUtil::getString(array,index);
	if(str==NULL)
	{
		return false;
	}
	*value=parseBoolean(str);
	return true;
}
	


float ScriptUtil::parseFloat(const char* str)
{
	return (float)atof(str);
}
int ScriptUtil::parseInteger(const char* str)
{
	return atoi(str);
}

bool ScriptUtil::parseBoolean(const char* str)
{
	if(strcmp(str,"false")==0)
	{
		return false;
	}
	return true;
}




NS_FS_END 



































