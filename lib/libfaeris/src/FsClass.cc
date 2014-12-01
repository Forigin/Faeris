#include "FsClass.h"

#include "support/util/FsDict.h"
#include "support/util/FsString.h"

NS_FS_BEGIN

FsClass::FsAttribute::FsAttribute(FsClass::FsAttributeDeclare* desc)
{
	m_subAttributes=NULL;
	m_name=FsString::create(desc->name);
	m_name->addRef();

	m_attrType = desc->attrType;

	if(desc->subAttributeDeclare!=NULL)
	{
		FsClass::FsAttributeDeclare* dsc= desc->subAttributeDeclare;
		m_subAttributes=FsDict::create();
		m_subAttributes->addRef();

		while(dsc->name!=NULL)
		{
			FsAttribute* attr=FsAttribute::create(dsc);
			m_subAttributes->insert(attr->m_name,attr);
			dsc++;
		}
	}

	m_setFunc=desc->setFunc;
	m_getFunc=desc->getFunc;
}


FsClass::FsAttribute::~FsAttribute()
{
	FS_SAFE_DEC_REF(m_name);
	FS_SAFE_DEC_REF(m_subAttributes);
}



FsClass* FsClass::create(const char* name,NewInstanceFunc new_func, FsAttributeDeclare* mb)
{
	FsClass* ret=new FsClass();
	ret->init(NULL,name,new_func,mb);
	return ret;
}

FsClass* FsClass::create(FsClass* base,const char* name,NewInstanceFunc new_func,FsAttributeDeclare* mb)
{
	FsClass* ret=new FsClass();
	ret->init(base,name,new_func,mb);
	return ret;
}

FsClass ::FsClass()
{
	m_name=NULL;
	m_newFunc=0;
	m_baseClass=NULL;
	m_attribute = NULL;
}

FsClass::~FsClass()
{
	FS_SAFE_DEC_REF(m_name);
	FS_SAFE_DEC_REF(m_baseClass);
	FS_SAFE_DEC_REF(m_attribute);
}


void FsClass::init(FsClass* base,const char* name,NewInstanceFunc new_func,FsAttributeDeclare* mb)
{
	FS_SAFE_ASSIGN(m_baseClass,base);
	m_name=FsString::create(name);
	m_name->addRef();
	m_newFunc=new_func;
	m_attribute=FsDict::create();

	while(mb&&(mb->name!=NULL))
	{
		FsAttribute* attr=FsAttribute::create(mb);
		m_attribute->insert(attr->getName(),attr);
		mb++;
	}
}

FsObject* FsClass::newInstance()
{
	return this->m_newFunc(this);
}

FsClass::FsAttribute* FsClass::getAttribute(const char* name)
{
	FsAttribute* attr=(FsAttribute*)m_attribute->lookup(name); 
	if(attr!=NULL)
	{
		return attr;
	}

	if(m_baseClass)
	{
		return m_baseClass->getAttribute(name);
	}

	return NULL;

}

bool FsClass::FsAttribute::callSet(FsObject* ob,const FsVariant& v)
{
	if(m_setFunc)
	{
		if(v.getType()==m_attrType)
		{
			m_setFunc(ob,v.getValue());
			return true;
		}


		FsVariant q=v.getCast(m_attrType);
		if(q.isValid())
		{
			m_setFunc(ob,v.getValue());
			return true; 
		}
	}

	if (v.getType()== FsType::FT_DICT) 
	{
		if(m_subAttributes)
		{
			FsDict::Iterator* iter=m_subAttributes->takeIterator();
			while(!iter->done())
			{
				FsString* name=(FsString*)iter->getKey();
				FsObject* value=iter->getValue();

				FsAttribute* attr=(FsAttribute*)m_subAttributes->lookup(name);
				if(attr)
				{
					attr->callSet(ob,FsVariant(value));
				}
				iter->next();
			}
			delete iter;
			return true;
		}
	}
	return false;
}

FsVariant FsClass::FsAttribute::callGet(FsObject* ob)
{
	if(m_getFunc)
	{
		return FsVariant(m_attrType,m_getFunc(ob));
	}
	return FsVariant();
}




bool FsClass::callSet(FsObject* ob,const char* name,const FsVariant& v)
{
	FsAttribute* attr=getAttribute(name);
	if(!attr)
	{
		return false;
	}

	return attr->callSet(ob,v);
}



FsVariant FsClass::callGet(FsObject* ob,const char* name)
{
	FsAttribute* attr=getAttribute(name);
	if(!attr)
	{
		return FsVariant();
	}
	return attr->callGet(ob);

}



NS_FS_END 



