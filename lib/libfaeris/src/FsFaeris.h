/*************************************************************************/
/*  FsFaeris.h                                                           */
/*************************************************************************/
/* Copyright (C) 2012-2014 nosiclin@foxmail.com                          */
/* Copyright (C) 2014-2015 www.fsource.cn                                */
/*                                                                       */
/* http://www.fsource.cn                                                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/


#ifndef _FS_FAERIS_H_
#define _FS_FAERIS_H_

#include "FsConfig.h"
#include "FsMacros.h"
#include "extends/FsScriptEngine.h"
#include "FsClass.h"
#include "FsEnums.h"
#include "FsFaerisModule.h"
#include "FsGlobal.h"
#include "FsObject.h"
#include "FsTypes.h"
#include "FsVariant.h"
#include "graphics/FsColor.h"
#include "graphics/FsFontBitmap.h"
#include "graphics/FsFontTTF.h"
#include "graphics/FsFrameBuffer.h"
#include "graphics/FsImage2D.h"
#include "graphics/FsRenderDevice.h"
#include "graphics/FsRenderTarget.h"
#include "graphics/FsTexture2D.h"
#include "graphics/FsTypoPage.h"
#include "graphics/FsVertexBuffer.h"
#include "graphics/material/FsMaterial.h"
#include "graphics/material/FsMaterial2D.h"
#include "graphics/shader/FsProgram.h"
#include "graphics/shader/FsProgramFeatureDesc.h"
#include "graphics/shader/FsProgramSource.h"
#include "graphics/shader/FsStreamMap.h"
#include "graphics/shader/FsUniformMap.h"
#include "graphics/shader/FsUniformValue.h"
#include "math/curve/FsCatmullRomCurve.h"
#include "math/curve/FsCubicBezierCurve.h"
#include "math/curve/FsCurve.h"
#include "math/curve/FsLinearCurve.h"
#include "math/easing/FsBackEase.h"
#include "math/easing/FsBezierEase.h"
#include "math/easing/FsBounceEase.h"
#include "math/easing/FsCircleEase.h"
#include "math/easing/FsCubicEase.h"
#include "math/easing/FsEaseExpr.h"
#include "math/easing/FsEasingUtil.h"
#include "math/easing/FsElasticEase.h"
#include "math/easing/FsExponentialEase.h"
#include "math/easing/FsLinearEase.h"
#include "math/easing/FsPowerEase.h"
#include "math/easing/FsQuadEase.h"
#include "math/easing/FsQuartEase.h"
#include "math/easing/FsQuintEase.h"
#include "math/easing/FsSineEase.h"
#include "math/FsBox3D.h"
#include "math/FsCamera.h"
#include "math/FsFace3.h"
#include "math/FsMath.h"
#include "math/FsMathUtil.h"
#include "math/FsMatrix4.h"
#include "math/FsQuaternion.h"
#include "math/FsRect2D.h"
#include "math/FsTexCoord2.h"
#include "math/FsVector2.h"
#include "math/FsVector3.h"
#include "math/FsVector4.h"
#include "math/FsVertices.h"
#include "media/FsAudioEngine.h"
#include "media/FsAudioPlayer.h"
#include "mgr/FsClassMgr.h"
#include "mgr/FsFelisScriptMgr.h"
#include "mgr/FsFontBitmapMgr.h"
#include "mgr/FsFontTTFMgr.h"
#include "mgr/FsMaterial3DMgr.h"
#include "mgr/FsMeshMgr.h"
#include "mgr/FsProgramSourceMgr.h"
#include "mgr/FsResource.h"
#include "mgr/FsResourceMgr.h"
#include "mgr/FsSprite2DDataMgr.h"
#include "mgr/FsTextureMgr.h"
#include "scheduler/FsScheduler.h"
#include "scheduler/FsSchedulerTarget.h"
#include "scheduler/FsTask.h"
#include "stage/action/FsAction.h"
#include "stage/action/FsCurve3Action.h"
#include "stage/action/FsFixTimeAction.h"
#include "stage/action/FsLoopAction.h"
#include "stage/action/FsMoveAction.h"
#include "stage/action/FsPauseAction.h"
#include "stage/action/FsRotateAction.h"
#include "stage/action/FsScaleAction.h"
#include "stage/action/FsSeqAction.h"
#include "stage/entity/FsEntity.h"
#include "stage/entity/FsEntity2D.h"
#include "stage/entity/FsLabelBitmap.h"
#include "stage/entity/FsLabelTTF.h"
#include "stage/entity/FsParticle2DEffect.h"
#include "stage/entity/FsParticle2DEmitter.h"
#include "stage/entity/FsQuad2D.h"
#include "stage/entity/FsSprite2D.h"
#include "stage/entity/FsSprite2DData.h"
#include "stage/entity/FsVertexPolygon.h"
#include "stage/entity/transform/FsEulerTransform.h"
#include "stage/entity/transform/FsITransform.h"
#include "stage/entity/transform/FsQuaternionTransform.h"
#include "stage/filter/FsBlurFilter.h"
#include "stage/filter/FsBrightnessFilter.h"
#include "stage/filter/FsColorMatrixFilter.h"
#include "stage/filter/FsFilter.h"
#include "stage/filter/FsGrayFilter.h"
#include "stage/filter/FsOpacityFilter.h"
#include "stage/FsActionTarget.h"
#include "stage/FsDirector.h"
#include "stage/FsScene.h"
#include "stage/layer/FsColorLayer.h"
#include "stage/layer/FsLayer.h"
#include "stage/layer/FsLayer2D.h"
#include "stage/ui/FsDialog.h"
#include "stage/ui/FsDynamicView.h"
#include "stage/ui/FsListView.h"
#include "stage/ui/FsPageView.h"
#include "stage/ui/FsPressButton.h"
#include "stage/ui/FsProcessBar.h"
#include "stage/ui/FsScroller.h"
#include "stage/ui/FsScrollView.h"
#include "stage/ui/FsScrollWidget.h"
#include "stage/ui/FsStateButton.h"
#include "stage/ui/FsToggleButton.h"
#include "stage/ui/FsUiWidget.h"
#include "stage/ui/FsVelocityTracker.h"
#include "support/data/FsBase64.h"
#include "support/data/FsDeflate.h"
#include "support/data/FsEncrypt.h"
#include "support/data/FsFgzReader.h"
#include "support/data/FsHash.h"
#include "support/data/FsIconv.h"
#include "support/data/FsJson.h"
#include "support/data/FsMd5.h"
#include "support/data/FsUnicode.h"
#include "support/data/FsZipReader.h"
#include "support/felis/sl_state.h"
#include "support/felis/xir_file.h"
#include "support/felis/xir_parser.h"
#include "support/felis/xir_scanner.h"
#include "support/felis/xir_state.h"
#include "support/felis/xir_token.h"
#include "support/image/FsImageDecoder.h"
#include "support/image/FsImageFaw.h"
#include "support/image/FsImageJpeg.h"
#include "support/image/FsImagePng.h"
#include "support/image/FsImageTga.h"
#include "support/loader/FsShaderLoader.h"
#include "support/util/FsArray.h"
#include "support/util/FsDict.h"
#include "support/util/FsInteger.h"
#include "support/util/FsLog.h"
#include "support/util/FsPathUtil.h"
#include "support/util/FsScriptUtil.h"
#include "support/util/FsSlowArray.h"
#include "support/util/FsSlowDict.h"
#include "support/util/FsString.h"
#include "sys/event/FsInputTextDispatcher.h"
#include "sys/event/FsKeypadDispatcher.h"
#include "sys/event/FsSysDispatcher.h"
#include "sys/event/FsTEventDispatcher.h"
#include "sys/event/FsTouchDispatcher.h"
#include "sys/FsKeyCode.h"
#include "sys/FsSys.h"
#include "sys/FsTimer.h"
#include "sys/FsWindow.h"
#include "sys/io/FsFgzPackage.h"
#include "sys/io/FsFile.h"
#include "sys/io/FsMemFile.h"
#include "sys/io/FsPackage.h"
#include "sys/io/FsSegFile.h"
#include "sys/io/FsSysFile.h"
#include "sys/io/FsVFS.h"
#include "sys/io/FsZipPackage.h"
#include "sys/network/FsHttpEngine.h"
#include "sys/network/FsHttpReponse.h"
#include "sys/network/FsHttpRequest.h"
#include "sys/thread/FsConditionVariable.h"
#include "sys/thread/FsMutex.h"
#include "sys/thread/FsSemaphore.h"
#include "sys/thread/FsThread.h"


#endif /*_FS_FAERIS_H_*/


