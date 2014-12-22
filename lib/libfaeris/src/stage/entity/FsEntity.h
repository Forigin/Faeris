#ifndef _FAERIS_ENTITY_H_
#define _FAERIS_ENTITY_H_
#include <functional>


#include "FsMacros.h"
#include "stage/FsActionTarget.h"
#include "math/FsVector3.h"
#include "math/FsMatrix4.h"
#include "transform/FsITransform.h"
#include "math/FsRect2D.h"
#include "support/util/FsString.h"
#include "support/util/FsSlowArray.h"

NS_FS_BEGIN
class RenderDevice;
class Layer;
class Scene;
class Entity :public ActionTarget
{
	public:
		FS_CLASS_DECLARE(Entity);

	public:
		static Entity* create();

	public:

		/* visible */
		void setVisible(bool visible){m_visible=visible;}
		bool getVisible(){return m_visible&&m_visibles;}
		void setVisibles(bool visible){m_visibles=visible;}
		bool getVisibles(){return m_visibles;}
		void setChildVisible(bool visiable,bool rec);


	public:
		virtual void update(float dt);
		virtual void draw(RenderDevice* r,bool updateMatrix=true);

		virtual void updates(float dt);
		virtual void draws(RenderDevice* r,bool updateMatrix=true);

		/* relation ship*/
		virtual int getChildNu();
		virtual void addChild(Entity* n);
		virtual void removeChild(Entity* n);
		virtual void clearChild();
		virtual void detach();


		virtual Matrix4* getWorldMatrix();
		virtual Matrix4* getLocalMatrix();


	public:
		std::function<void(Entity*,float)> onUpdate;
		std::function<void(Entity*,RenderDevice*,bool)> onDraw;



	public:

		Vector3 localToWorld(const Vector3& v);
		Vector3 worldToLocal(const Vector3& v);


		FS_FEATURE_NEW_OBJECT(FsArray*) takeAllChild(bool visible);
		void getAllChild(FsArray* array,bool visible);


		bool updateWorldMatrix();
		void updateAllWorldMatrix();
		void setChildWorldMatrixDirty();


	public: /* zorlder */
		float getZorder();
		void setZorder(float z);
		Layer* getLayer();

		/* please don't call setLayer directly */
		void setLayer(Layer* layer);
		
		Entity* getParent();
		Scene* getScene();

		/* used for layer to sort */
		uint32_t getAddOlder(){return m_addOlder;}
		void  setAddOlder(uint32_t older){ m_addOlder=older;}

	public:

		/* transform  */
		virtual void setPosition(const Vector3& pos);
		virtual Vector3 getPosition();

		virtual void setRotate(const Vector3& r);
		virtual Vector3 getRotate();

		virtual void setScale(const Vector3& s);
		virtual Vector3 getScale();

		void setTransform(ITransform* tf);
		ITransform* getTransform();


	public: /* get transform info */
		void getPosition(float* x,float* y,float* z);
		float getPositionX();
		float getPositionY();
		float getPositionZ();

		/*  scale information */
		float getScaleX();
		float getScaleY();
		float getScaleZ();


		/* rotate information */
		float getRotateX();
		float getRotateY();
		float getRotateZ();

	public: /* transform */
		void rotate(float rx,float ry,float rz);
		void rotateX(float r);
		void rotateY(float r);
		void rotateZ(float r);

		void scale(float sx,float sy,float sz);
		void scaleX(float s);
		void scaleY(float s);
		void scaleZ(float s);

		void move(float tx,float ty,float tz);
		void moveX(float t);
		void moveY(float t);
		void moveZ(float t);

	public:/* set transform */
		void setRotate(float rx,float ry,float rz);
		void setRotateX(float r);
		void setRotateY(float r);
		void setRotateZ(float r);

		void setScale(float sx,float sy,float sz);
		void setScaleX(float s);
		void setScaleY(float s);
		void setScaleZ(float s);

		void setPosition(float tx,float ty,float tz = 0.0f);
		void setPositionX(float t);
		void setPositionY(float t);
		void setPositionZ(float t);

	public: /* world transform */
		void setPositionInWorld(float tx,float ty,float tz);
		void setPositionInWorld(const Vector3& v);

		Vector3 getPositionInWorld();
		void getPositionInWorld(float* x,float* y,float* z);

	public:
		void setDispatchTouchEnabled(bool enabled);
		bool getDispatchTouchEnabled();
		void setDispatchTouchesEnabled(bool enabled);
		bool getDispatchTouchesEnabled();


	protected:
		Entity();
		virtual ~Entity();

		void init();
		void destruct();
		void updateChildWorldMatrix(bool force);
	
		void setParent(Entity* parent);

		void sortChildren();

	protected:  
		/* flags */
		union 
		{
			struct{
				ulong m_localMatrixDirty:1;
				ulong m_worldMatrixDirty:1;
				ulong m_visible:1;
				ulong m_visibles:1;
				ulong m_zorderDirty:1;
			};
			ulong m_flags;
		};

		/* matrix */
		Matrix4 m_worldMatrix;
		ITransform* m_transform;


		/* zorlder */
		float m_zorlder;
		uint32_t m_addOlder;


		/* relation ship*/
		Layer* m_layer;
		Entity* m_parent;
		FsSlowArray* m_chirdren;


		friend class Layer;

	/* class attribute */
	private:
		static uint32_t ms_olderCount;
};


#include "stage/entity/FsEntity.inl"
NS_FS_END

#endif 




