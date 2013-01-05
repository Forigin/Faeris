#ifndef _FS_MESH_H_
#define _FS_MESH_H_
#include "FsMacros.h"
#include "util/FsResource.h"
#include "model/FsSubMesh.h"

NS_FS_BEGIN 
class Animation;
class Mesh:public Resource
{
	public:
		enum 
		{
			TYPE_STATIC,
			TYPE_SHAPE,
			TYPE_SKELETON,
		};
	public:
		FsUint subMeshNu()const{return m_submesh.size();}
		SubMesh* getSubMesh(FsUint index)const;
		FsInt  getType()const{return m_type;} 

		/* animation */
		void addAnimation(const FsChar* name,Animation* ani);
		void removeAnimation(const FsChar* name);
		void removeAnimation(Animation* ani);
		Animation* getAnimation(const FsChar* name);

		/* render */
		void draw(Render* r);
	public:
		Mesh(FsUint submesh_nu,int type);
		virtual const FsChar* getName();
		virtual ~Mesh();
	private:
		std::vector<SubMesh*> m_submesh;
		std::map<std::string,Animation*> m_animations;
		FsInt m_type;
};

NS_FS_END 

#endif /*_FS_MESH_H_*/