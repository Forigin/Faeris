#ifndef _FS_FRAME_BUFFER_H_
#define _FS_FRAME_BUFFER_H_

#include "FsMacros.h"

#include "FsRenderTarget.h"

#if FS_CONFIG(FS_GL_RENDER) || FS_CONFIG(FS_GLES_RENDER) 
	#include "platform/FsGLFrameBuffer.h"
#else 
	#error "Unsupport PlatformTexture" 
#endif 


#endif /*_FS_FRAME_BUFFER_H_*/

