// Copyright (C) 2008 Christian Stehno
// Heavily based on the OpenGL driver implemented by Nikolaus Gebhardt
// 2017 modified by Michael Zeilfelder (unifying extension handlers)
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in Irrlicht.h

#include "COGLESExtensionHandler.h"

#ifdef _IRR_COMPILE_WITH_OGLES1_

#include "irrString.h"
#include "SMaterial.h"
#include "fast_atof.h"

namespace irr
{
namespace video
{

	COGLES1ExtensionHandler::COGLES1ExtensionHandler(IContextManager* contextManager) : COGLESCoreExtensionHandler(this),
		COGLES1BaseFunctionsHandler(contextManager), ContextManager(contextManager), MaxUserClipPlanes(0), MaxLights(0)
#if defined(_IRR_OGLES1_USE_EXTPOINTER_)
		, pGlBlendEquationOES(0), pGlBlendFuncSeparateOES(0),
		pGlBindFramebufferOES(0), pGlDeleteFramebuffersOES(0),
		pGlGenFramebuffersOES(0), pGlCheckFramebufferStatusOES(0),
		pGlFramebufferTexture2DOES(0), pGlGenerateMipmapOES(0)
#endif
	{
	}

	void COGLES1ExtensionHandler::initExtensions()
	{
		getGLVersion();

		if (Version >= 100)
			os::Printer::log("OpenGL ES driver version is 1.1.", ELL_INFORMATION);
		else
			os::Printer::log("OpenGL ES driver version is 1.0.", ELL_WARNING);

		getGLExtensions();

		GLint val = 0;

		if (Version > 100 || FeatureAvailable[IRR_GL_IMG_user_clip_plane])
		{
			pglGetIntegerv(GL_MAX_CLIP_PLANES, &val);
			MaxUserClipPlanes = static_cast<u8>(val);
		}

		pglGetIntegerv(GL_MAX_LIGHTS, &val);
		MaxLights = static_cast<u8>(val);

		pglGetIntegerv(GL_MAX_TEXTURE_UNITS, &val);
		Feature.MaxTextureUnits = static_cast<u8>(val);

#ifdef GL_EXT_texture_filter_anisotropic
		if (FeatureAvailable[IRR_GL_EXT_texture_filter_anisotropic])
		{
			pglGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &val);
			MaxAnisotropy = static_cast<u8>(val);
		}
#endif
#ifdef GL_MAX_ELEMENTS_INDICES
		pglGetIntegerv(GL_MAX_ELEMENTS_INDICES, &val);
		MaxIndices = val;
#endif
		pglGetIntegerv(GL_MAX_TEXTURE_SIZE, &val);
		MaxTextureSize = static_cast<u32>(val);
#ifdef GL_EXT_texture_lod_bias
		if (FeatureAvailable[IRR_GL_EXT_texture_lod_bias])
			pglGetFloatv(GL_MAX_TEXTURE_LOD_BIAS_EXT, &MaxTextureLODBias);
#endif
		pglGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, DimAliasedLine);
		pglGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, DimAliasedPoint);

		Feature.MaxTextureUnits = core::min_(Feature.MaxTextureUnits, static_cast<u8>(MATERIAL_MAX_TEXTURES));
		Feature.MaxTextureUnits = core::min_(Feature.MaxTextureUnits, static_cast<u8>(MATERIAL_MAX_TEXTURES_USED));
		Feature.ColorAttachment = 1;

#if defined(_IRR_OGLES1_USE_EXTPOINTER_)
		pGlBlendEquationOES = (PFNGLBLENDEQUATIONOESPROC)ContextManager->loadFunction("glBlendEquationOES");
		pGlBlendFuncSeparateOES = (PFNGLBLENDFUNCSEPARATEOESPROC)ContextManager->loadFunction("glBlendFuncSeparateOES");
		pGlBindFramebufferOES = (PFNGLBINDFRAMEBUFFEROESPROC)ContextManager->loadFunction("glBindFramebufferOES");
		pGlDeleteFramebuffersOES = (PFNGLDELETEFRAMEBUFFERSOESPROC)ContextManager->loadFunction("glDeleteFramebuffersOES");
		pGlGenFramebuffersOES = (PFNGLGENFRAMEBUFFERSOESPROC)ContextManager->loadFunction("glGenFramebuffersOES");
		pGlCheckFramebufferStatusOES = (PFNGLCHECKFRAMEBUFFERSTATUSOESPROC)ContextManager->loadFunction("glCheckFramebufferStatusOES");
		pGlFramebufferTexture2DOES = (PFNGLFRAMEBUFFERTEXTURE2DOESPROC)ContextManager->loadFunction("glFramebufferTexture2DOES");
		pGlGenerateMipmapOES = (PFNGLGENERATEMIPMAPOESPROC)ContextManager->loadFunction("glGenerateMipmapOES");
#endif
	}

} // end namespace video
} // end namespace irr


#endif // _IRR_COMPILE_WITH_OGLES2_
