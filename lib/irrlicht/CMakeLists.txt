#Mostly copied from STK
if(NOT SERVER_ONLY)
    find_package(PNG REQUIRED)
    find_package(JPEG REQUIRED)

    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/"
                        "${JPEG_INCLUDE_DIR}"
                        "${PNG_INCLUDE_DIRS}"
                        "${ZLIB_INCLUDE_DIR}")

    if(MSVC)
        include_directories("${CMAKE_CURRENT_BINARY_DIR}/../zlib/") # For zconf.h on WIN32
    endif()

    if(MSVC OR APPLE)
        include_directories("${CMAKE_CURRENT_BINARY_DIR}/../libpng/")
    endif()

    if(NOT USE_GLES2)
        find_package(OpenGL REQUIRED)
        include_directories(${OPENGL_INCLUDE_DIR})
    endif()
        
    if(UNIX AND NOT APPLE)
        find_package(X11 REQUIRED)
        include_directories(${X11_INCLUDE_DIR})
        
        if(NOT X11_FOUND)
            message(FATAL_ERROR "X11 not found.")
        endif()
        
        if(NOT X11_Xrandr_FOUND)
            message(FATAL_ERROR "XRANDR not found.")
        endif()
    endif()

    if(USE_GLES2 OR ENABLE_WAYLAND_DEVICE)
        find_package(EGL)
        
        if(EGL_FOUND)
            include_directories(${EGL_INCLUDE_DIR})
        else()
            if(USE_GLES2)
                message(FATAL_ERROR "EGL not found.")
            elseif(ENABLE_WAYLAND_DEVICE)
                message(WARNING "EGL not found. Disable wayland support.")
                set(ENABLE_WAYLAND_DEVICE OFF)
            endif()
        endif()
    endif()

    if(ENABLE_WAYLAND_DEVICE)
        find_package(Wayland)
        
        if(WAYLAND_FOUND AND NOT (WAYLAND_VERSION VERSION_LESS "1.14"))
            include_directories(${WAYLAND_INCLUDE_DIR})
            add_definitions(-D_IRR_COMPILE_WITH_WAYLAND_DEVICE_)
        else()
            message(WARNING "Wayland not found. Disable wayland support.")
            set(ENABLE_WAYLAND_DEVICE OFF)
        endif()        
    endif()
else()
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")
    if(MSVC)
        include_directories("${CMAKE_CURRENT_BINARY_DIR}/../zlib/")
    else()
        find_package(ZLIB REQUIRED)
        include_directories("${ZLIB_INCLUDE_DIR}")
    endif()
    add_definitions(-DNO_IRR_COMPILE_WITH_LIBPNG_)
    add_definitions(-DNO_IRR_COMPILE_WITH_LIBJPEG_)
    add_definitions(-DNO_IRR_COMPILE_WITH_BMP_LOADER_)
    add_definitions(-DNO_IRR_COMPILE_WITH_PNG_LOADER_)
    add_definitions(-DNO_IRR_COMPILE_WITH_JPG_LOADER_)
    add_definitions(-DNO_IRR_COMPILE_WITH_BMP_WRITER_)
    add_definitions(-DNO_IRR_COMPILE_WITH_PNG_WRITER_)
    add_definitions(-DNO_IRR_COMPILE_WITH_JPG_WRITER_)
    add_definitions(-DNO_IRR_COMPILE_WITH_OPENGL_)
    add_definitions(-DNO_IRR_COMPILE_WITH_X11_)
    add_definitions(-DNO_IRR_COMPILE_WITH_WAYLAND_DEVICE_)
endif()

if(APPLE)
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht/MacOSX" "${CMAKE_CURRENT_SOURCE_DIR}/source/Irrlicht")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch x86_64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch x86_64 -F/Library/Frameworks")
endif()

add_definitions(-DNDEBUG=1 -DIRRLICHT_EXPORTS=1 -DPNG_THREAD_UNSAFE_OK -DPNG_NO_MMX_CODE -DPNG_NO_MNG_FEATURES)

if(UNIX OR MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif()

if(WIN32)
    add_definitions(-D_IRR_STATIC_LIB_)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS) # Shut up about unsafe stuff
else()
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wall -pipe -O3  -fno-exceptions  -fstrict-aliasing")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pipe -O3  -fno-exceptions  -fstrict-aliasing")
    if(CMAKE_COMPILER_IS_GNUCC)
        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -fexpensive-optimizations")
    endif()
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -fexpensive-optimizations")
    endif()
endif()

if(USE_GLES2)
    add_definitions(-D_IRR_COMPILE_WITH_OGLES2_ -DNO_IRR_COMPILE_WITH_OPENGL_)
endif()

if(CYGWIN)
    add_definitions(-DNO_IRR_COMPILE_WITH_JOYSTICK_EVENTS_)
endif()


set(IRRLICHT_SOURCES
#The sources are the only part I changed.
source/Irrlicht/CGUIComboBox.cpp
source/Irrlicht/COSOperator.cpp
source/Irrlicht/CTRStencilShadow.cpp
source/Irrlicht/CB3DMeshWriter.cpp
source/Irrlicht/CTextSceneNode.cpp
source/Irrlicht/CTRGouraud.cpp
source/Irrlicht/CIrrDeviceLinux.cpp
source/Irrlicht/CNPKReader.cpp
source/Irrlicht/CGUIMeshViewer.cpp
source/Irrlicht/COpenGLNormalMapRenderer.cpp
source/Irrlicht/CParticleCylinderEmitter.cpp
source/Irrlicht/CImageLoaderJPG.cpp
source/Irrlicht/CSoftwareDriver.cpp
source/Irrlicht/CWaterSurfaceSceneNode.cpp
source/Irrlicht/CTRTextureGouraud.cpp
source/Irrlicht/CSceneNodeAnimatorFlyCircle.cpp
source/Irrlicht/CVideoModeList.cpp
source/Irrlicht/COctreeTriangleSelector.cpp
source/Irrlicht/CAnimatedMeshMD2.cpp
source/Irrlicht/CGUIMenu.cpp
source/Irrlicht/CParticleRingEmitter.cpp
source/Irrlicht/CPakReader.cpp
source/Irrlicht/CVolumeLightSceneNode.cpp
source/Irrlicht/CImageWriterBMP.cpp
source/Irrlicht/CBillboardSceneNode.cpp
source/Irrlicht/CTRTextureLightMap2_M1.cpp
source/Irrlicht/CLogger.cpp
source/Irrlicht/CColladaMeshWriter.cpp
source/Irrlicht/utf8.cpp
source/Irrlicht/CWADReader.cpp
source/Irrlicht/CGUIStaticText.cpp
source/Irrlicht/CSceneNodeAnimatorDelete.cpp
source/Irrlicht/CImageLoaderDDS.cpp
source/Irrlicht/CImageWriterTGA.cpp
source/Irrlicht/CGUIFont.cpp
source/Irrlicht/COBJMeshFileLoader.cpp
source/Irrlicht/CBurningShader_Raster_Reference.cpp
source/Irrlicht/CD3D9HLSLMaterialRenderer.cpp
source/Irrlicht/CCSMLoader.cpp
source/Irrlicht/Irrlicht.cpp
source/Irrlicht/CDummyTransformationSceneNode.cpp
source/Irrlicht/CSphereSceneNode.cpp
source/Irrlicht/CTRTextureLightMapGouraud2_M4.cpp
source/Irrlicht/CNullDriver.cpp
source/Irrlicht/CGeometryCreator.cpp
source/Irrlicht/CGUISpinBox.cpp
source/Irrlicht/CSceneCollisionManager.cpp
source/Irrlicht/CTRTextureDetailMap2.cpp
source/Irrlicht/CImageWriterPNG.cpp
source/Irrlicht/CParticlePointEmitter.cpp
source/Irrlicht/CSTLMeshWriter.cpp
source/Irrlicht/CGUITabControl.cpp
source/Irrlicht/CFileSystem.cpp
source/Irrlicht/COpenGLParallaxMapRenderer.cpp
source/Irrlicht/CParticleScaleAffector.cpp
source/Irrlicht/CD3D9Driver.cpp
source/Irrlicht/leakHunter.cpp
source/Irrlicht/CParticleBoxEmitter.cpp
source/Irrlicht/COCTLoader.cpp
source/Irrlicht/CAnimatedMeshSceneNode.cpp
source/Irrlicht/irrXML.cpp
source/Irrlicht/CColladaFileLoader.cpp
source/Irrlicht/CD3D9ShaderMaterialRenderer.cpp
source/Irrlicht/CZBuffer.cpp
source/Irrlicht/CImage.cpp
source/Irrlicht/COpenGLCacheHandler.cpp
source/Irrlicht/CTRTextureLightMap2_Add.cpp
source/Irrlicht/CGUIMessageBox.cpp
source/Irrlicht/CTRTextureGouraudAdd2.cpp
source/Irrlicht/CImageWriterPCX.cpp
source/Irrlicht/CDefaultSceneNodeFactory.cpp
source/Irrlicht/CGUIImageList.cpp
source/Irrlicht/CMeshManipulator.cpp
source/Irrlicht/CTRTextureGouraudNoZ2.cpp
source/Irrlicht/CWGLManager.cpp
source/Irrlicht/CParticleSystemSceneNode.cpp
source/Irrlicht/CImageLoaderPVR.cpp
source/Irrlicht/CMS3DMeshFileLoader.cpp
source/Irrlicht/CTRTextureBlend.cpp
source/Irrlicht/CImageWriterPSD.cpp
source/Irrlicht/CEmptySceneNode.cpp
source/Irrlicht/CSceneNodeAnimatorFollowSpline.cpp
source/Irrlicht/CColorConverter.cpp
source/Irrlicht/CSceneManager.cpp
source/Irrlicht/CSceneNodeAnimatorFlyStraight.cpp
source/Irrlicht/CTRTextureGouraudAlpha.cpp
source/Irrlicht/aesGladman/pwd2key.cpp
source/Irrlicht/aesGladman/sha1.cpp
source/Irrlicht/aesGladman/aestab.cpp
source/Irrlicht/aesGladman/aeskey.cpp
source/Irrlicht/aesGladman/prng.cpp
source/Irrlicht/aesGladman/sha2.cpp
source/Irrlicht/aesGladman/hmac.cpp
source/Irrlicht/aesGladman/fileenc.cpp
source/Irrlicht/aesGladman/aescrypt.cpp
source/Irrlicht/CSoftwareTexture2.cpp
source/Irrlicht/CGUIToolBar.cpp
source/Irrlicht/CSceneLoaderIrr.cpp
source/Irrlicht/CIrrMeshWriter.cpp
source/Irrlicht/CGUIInOutFader.cpp
source/Irrlicht/CBoneSceneNode.cpp
source/Irrlicht/COBJMeshWriter.cpp
source/Irrlicht/CIrrDeviceFB.cpp
source/Irrlicht/CParticleAttractionAffector.cpp
source/Irrlicht/CXMLWriter.cpp
source/Irrlicht/CGUICheckBox.cpp
source/Irrlicht/CGUIContextMenu.cpp
source/Irrlicht/CImageLoaderPNG.cpp
source/Irrlicht/CParticleRotationAffector.cpp
source/Irrlicht/CTRTextureFlatWire.cpp
source/Irrlicht/CTriangleSelector.cpp
source/Irrlicht/CLMTSMeshFileLoader.cpp
source/Irrlicht/IBurningShader.cpp
source/Irrlicht/CMetaTriangleSelector.cpp
source/Irrlicht/CSTLMeshFileLoader.cpp
source/Irrlicht/C3DSMeshFileLoader.cpp
source/Irrlicht/CTRFlatWire.cpp
source/Irrlicht/CProfiler.cpp
source/Irrlicht/CIrrDeviceSDL.cpp
source/Irrlicht/CImageWriterPPM.cpp
source/Irrlicht/CGUIColorSelectDialog.cpp
source/Irrlicht/CSceneNodeAnimatorCameraMaya.cpp
source/Irrlicht/CGUIButton.cpp
source/Irrlicht/CTRTextureGouraud2.cpp
source/Irrlicht/CParticleFadeOutAffector.cpp
source/Irrlicht/CMD2MeshFileLoader.cpp
source/Irrlicht/CD3D9NormalMapRenderer.cpp
source/Irrlicht/CImageWriterJPG.cpp
source/Irrlicht/CWriteFile.cpp
source/Irrlicht/CGUIEnvironment.cpp
source/Irrlicht/CLightSceneNode.cpp
source/Irrlicht/CTRTextureLightMap2_M2.cpp
source/Irrlicht/CShadowVolumeSceneNode.cpp
source/Irrlicht/CImageLoaderPSD.cpp
source/Irrlicht/CD3D9Texture.cpp
source/Irrlicht/CPLYMeshFileLoader.cpp
source/Irrlicht/CTRGouraudAlpha2.cpp
source/Irrlicht/CIrrDeviceWin32.cpp
source/Irrlicht/CGLXManager.cpp
source/Irrlicht/CTRTextureGouraudAddNoZ2.cpp
source/Irrlicht/CAnimatedMeshMD3.cpp
source/Irrlicht/CCubeSceneNode.cpp
source/Irrlicht/CTRTextureFlat.cpp
source/Irrlicht/CGUISkin.cpp
source/Irrlicht/CTRTextureLightMap2_M4.cpp
source/Irrlicht/CGUITreeView.cpp
source/Irrlicht/CZipReader.cpp
source/Irrlicht/CBSPMeshFileLoader.cpp
source/Irrlicht/CSceneNodeAnimatorCollisionResponse.cpp
source/Irrlicht/CParticleGravityAffector.cpp
source/Irrlicht/CTRTextureGouraudAlphaNoZ.cpp
source/Irrlicht/CFileList.cpp
source/Irrlicht/CMountPointReader.cpp
source/Irrlicht/CImageLoaderPPM.cpp
source/Irrlicht/CSoftwareDriver2.cpp
source/Irrlicht/CTRTextureGouraudAdd.cpp
source/Irrlicht/CQ3LevelMesh.cpp
source/Irrlicht/CTRTextureGouraudNoZ.cpp
source/Irrlicht/CLWOMeshFileLoader.cpp
source/Irrlicht/CAnimatedMeshHalfLife.cpp
source/Irrlicht/CSceneNodeAnimatorCameraFPS.cpp
source/Irrlicht/CGUIEditBox.cpp
source/Irrlicht/CParticleSphereEmitter.cpp
source/Irrlicht/CXMLReader.cpp
source/Irrlicht/CParticleAnimatedMeshSceneNodeEmitter.cpp
source/Irrlicht/CTarReader.cpp
source/Irrlicht/CD3D9ParallaxMapRenderer.cpp
source/Irrlicht/CSkyBoxSceneNode.cpp
source/Irrlicht/COctreeSceneNode.cpp
source/Irrlicht/CCameraSceneNode.cpp
source/Irrlicht/CTRTextureGouraudWire.cpp
source/Irrlicht/CQuake3ShaderSceneNode.cpp
source/Irrlicht/CSMFMeshFileLoader.cpp
source/Irrlicht/CXMeshFileLoader.cpp
source/Irrlicht/CDefaultSceneNodeAnimatorFactory.cpp
source/Irrlicht/CTRNormalMap.cpp
source/Irrlicht/CLimitReadFile.cpp
source/Irrlicht/CDMFLoader.cpp
source/Irrlicht/CImageLoaderTGA.cpp
source/Irrlicht/CGUIListBox.cpp
source/Irrlicht/CMemoryFile.cpp
source/Irrlicht/CGUIFileOpenDialog.cpp
source/Irrlicht/CD3D9RenderTarget.cpp
source/Irrlicht/CDefaultGUIElementFactory.cpp
source/Irrlicht/CTerrainSceneNode.cpp
source/Irrlicht/os.cpp
source/Irrlicht/CGUIProfiler.cpp
source/Irrlicht/CTRTextureGouraudVertexAlpha2.cpp
source/Irrlicht/CIrrDeviceConsole.cpp
source/Irrlicht/CMD3MeshFileLoader.cpp
source/Irrlicht/CB3DMeshFileLoader.cpp
source/Irrlicht/CTerrainTriangleSelector.cpp
source/Irrlicht/CImageLoaderRGB.cpp
source/Irrlicht/CIrrMeshFileLoader.cpp
source/Irrlicht/CMeshCache.cpp
source/Irrlicht/CMY3DMeshFileLoader.cpp
source/Irrlicht/CMeshSceneNode.cpp
source/Irrlicht/COpenGLDriver.cpp
source/Irrlicht/COgreMeshFileLoader.cpp
source/Irrlicht/CTRFlat.cpp
source/Irrlicht/CAttributes.cpp
source/Irrlicht/CGUIImage.cpp
source/Irrlicht/CIrrDeviceStub.cpp
source/Irrlicht/CGUIWindow.cpp
source/Irrlicht/COpenGLSLMaterialRenderer.cpp
source/Irrlicht/COpenGLShaderMaterialRenderer.cpp
source/Irrlicht/CTriangleBBSelector.cpp
source/Irrlicht/CImageLoaderBMP.cpp
source/Irrlicht/CSceneNodeAnimatorRotation.cpp
source/Irrlicht/CParticleMeshEmitter.cpp
source/Irrlicht/CFPSCounter.cpp
source/Irrlicht/CReadFile.cpp
source/Irrlicht/COpenGLExtensionHandler.cpp
source/Irrlicht/CSoftwareTexture.cpp
source/Irrlicht/CTRGouraudWire.cpp
source/Irrlicht/CSkyDomeSceneNode.cpp
source/Irrlicht/CGUIScrollBar.cpp
source/Irrlicht/CMeshTextureLoader.cpp
source/Irrlicht/CImageLoaderWAL.cpp
source/Irrlicht/CTRGouraudAlphaNoZ2.cpp
source/Irrlicht/CTRGouraud2.cpp
source/Irrlicht/CSkinnedMesh.cpp
source/Irrlicht/CGUIModalScreen.cpp
source/Irrlicht/CTRTextureWire2.cpp
source/Irrlicht/CDepthBuffer.cpp
source/Irrlicht/CGUISpriteBank.cpp
source/Irrlicht/CSceneNodeAnimatorTexture.cpp
source/Irrlicht/CImageLoaderPCX.cpp
source/Irrlicht/CGUITable.cpp
source/Irrlicht/CPLYMeshWriter.cpp

include/driverChoice.h
include/IParticleFadeOutAffector.h
include/irrAllocator.h
include/IGUIFont.h
include/ISceneUserDataSerializer.h
include/EShaderTypes.h
include/EPrimitiveTypes.h
include/IMeshWriter.h
include/IGUIMeshViewer.h
include/irrList.h
include/IEventReceiver.h
include/IParticleSphereEmitter.h
include/SIrrCreationParameters.h
include/SOverrideMaterial.h
include/coreutil.h
include/SMaterial.h
include/IDynamicMeshBuffer.h
include/EMaterialFlags.h
include/IParticleBoxEmitter.h
include/EReadFileType.h
include/EDriverFeatures.h
include/IGUIEnvironment.h
include/IParticleCylinderEmitter.h
include/ISceneNodeAnimatorCameraMaya.h
include/IMeshSceneNode.h
include/IMeshLoader.h
include/IAnimatedMesh.h
include/IGUITable.h
include/IQ3LevelMesh.h
include/IOctreeSceneNode.h
include/IMemoryReadFile.h
include/IGeometryCreator.h
include/ITextSceneNode.h
include/irrTypes.h
include/ILightManager.h
include/ILightSceneNode.h
include/heapsort.h
include/path.h
include/IGUITreeView.h
include/plane3d.h
include/IMeshBuffer.h
include/ISceneLoader.h
include/IImage.h
include/EDebugSceneTypes.h
include/irrXML.h
include/IMeshCache.h
include/IParticleRingEmitter.h
include/IGUIFileOpenDialog.h
include/IVertexBuffer.h
include/Keycodes.h
include/ISceneNodeAnimatorFactory.h
include/SExposedVideoData.h
include/IMaterialRendererServices.h
include/CMeshBuffer.h
include/ISceneNodeFactory.h
include/ISceneCollisionManager.h
include/IParticleGravityAffector.h
include/ETerrainElements.h
include/SVertexIndex.h
include/CIndexBuffer.h
include/IAttributeExchangingObject.h
include/IVolumeLightSceneNode.h
include/IGUIToolbar.h
include/SMeshBufferLightMap.h
include/triangle3d.h
include/SVertexManipulator.h
include/IGUIImage.h
include/IGUIColorSelectDialog.h
include/IParticleMeshEmitter.h
include/exampleHelper.h
include/ITimer.h
include/IMetaTriangleSelector.h
include/IGUISpriteBank.h
include/ISceneManager.h
include/IGUISkin.h
include/IrrlichtDevice.h
include/IVideoModeList.h
include/EMessageBoxFlags.h
include/EHardwareBufferFlags.h
include/SSharedMeshBuffer.h
include/IImageWriter.h
include/IParticleAnimatedMeshSceneNodeEmitter.h
include/quaternion.h
include/SMeshBuffer.h
include/aabbox3d.h
include/IGUIFontBitmap.h
include/IMeshManipulator.h
include/IRenderTarget.h
include/IFileSystem.h
include/fast_atof.h
include/position2d.h
include/IGUIListBox.h
include/IGUIProfiler.h
include/IParticleEmitter.h
include/vector3d.h
include/ISceneNodeAnimator.h
include/ESceneNodeAnimatorTypes.h
include/IVideoDriver.h
include/IGUIContextMenu.h
include/IGUIEditBox.h
include/IIndexBuffer.h
include/IAnimatedMeshSceneNode.h
include/IGUITabControl.h
include/IImageLoader.h
include/EMaterialTypes.h
include/ISceneNodeAnimatorCameraFPS.h
include/IGPUProgrammingServices.h
include/IShaderConstantSetCallBack.h
include/ECullingTypes.h
include/EDriverTypes.h
include/IGUIElement.h
include/IColladaMeshWriter.h
include/irrMap.h
include/IParticleRotationAffector.h
include/IAnimatedMeshMD2.h
include/SKeyMap.h
include/ISceneNode.h
include/line2d.h
include/CDynamicMeshBuffer.h
include/IDummyTransformationSceneNode.h
include/IFileList.h
include/irrMath.h
include/IGUIButton.h
include/IBillboardSceneNode.h
include/IGUIImageList.h
include/IGUISpinBox.h
include/IGUIComboBox.h
include/IMesh.h
include/IReadFile.h
include/SMesh.h
include/rect.h
include/EDeviceTypes.h
include/irrpack.h
include/vector2d.h
include/leakHunter.h
include/IBoneSceneNode.h
include/IGUIElementFactory.h
include/IGUIScrollBar.h
include/matrix4.h
include/IParticleAttractionAffector.h
include/SMaterialLayer.h
include/SceneParameters.h
include/IOSOperator.h
include/SLight.h
include/ICameraSceneNode.h
include/IGUICheckBox.h
include/ICursorControl.h
include/IGUIWindow.h
include/IWriteFile.h
include/IRandomizer.h
include/IrrCompileConfig.h
include/IMeshTextureLoader.h
include/ISkinnedMesh.h
include/ITriangleSelector.h
include/IParticleSystemSceneNode.h
include/ITexture.h
include/line3d.h
include/SParticle.h
include/IQ3Shader.h
include/SMeshBufferTangents.h
include/IAttributes.h
include/IParticleAffector.h
include/IXMLReader.h
include/dimension2d.h
include/IShadowVolumeSceneNode.h
include/ISceneNodeAnimatorCollisionResponse.h
include/irrlicht.h
include/ILogger.h
include/IContextManager.h
include/ITerrainSceneNode.h
include/IMaterialRenderer.h
include/EMeshWriterEnums.h
include/S3DVertex.h
include/EFocusFlags.h
include/IGUIStaticText.h
include/EAttributes.h
include/irrunpack.h
include/CVertexBuffer.h
include/IProfiler.h
include/SColor.h
include/EGUIAlignment.h
include/SSkinMeshBuffer.h
include/IBillboardTextSceneNode.h
include/ESceneNodeTypes.h
include/IGUIInOutFader.h
include/IFileArchive.h
include/IXMLWriter.h
include/irrArray.h
include/SAnimatedMesh.h
include/SViewFrustum.h
include/EGUIElementTypes.h
include/IReferenceCounted.h
include/irrString.h
include/IAnimatedMeshMD3.h

)

if(NOT SERVER_ONLY AND ENABLE_WAYLAND_DEVICE)
    set(IRRLICHT_SOURCES 
        ${IRRLICHT_SOURCES}
        source/Irrlicht/xdg_decoration_unstable_v1_protocol.c
        source/Irrlicht/xdg_shell_protocol.c)
endif()


if(APPLE)
    set(IRRLICHT_SOURCES
        ${IRRLICHT_SOURCES}
        source/Irrlicht/MacOSX/AppDelegate.mm
        source/Irrlicht/MacOSX/CIrrDeviceMacOSX.mm
        source/Irrlicht/MacOSX/OSXClipboard.mm)

    #list(APPEND CMAKE_C_SOURCE_FILE_EXTENSIONS mm)
    #set(CMAKE_CXX_SOURCE_FILE_EXTENSIONS cpp)

    set_source_files_properties(source/Irrlicht/MacOSX/AppDelegate.mm PROPERTIES COMPILE_FLAGS "-x objective-c++ -O3  -fno-rtti")
    set_source_files_properties(source/Irrlicht/MacOSX/AppDelegate.mm PROPERTIES LANGUAGE C)

    set_source_files_properties(source/Irrlicht/MacOSX/CIrrDeviceMacOSX.mm PROPERTIES COMPILE_FLAGS "-x objective-c++ -O3  -fno-rtti")
    set_source_files_properties(source/Irrlicht/MacOSX/CIrrDeviceMacOSX.mm PROPERTIES LANGUAGE C)

    set_source_files_properties(source/Irrlicht/MacOSX/OSXClipboard.mm PROPERTIES COMPILE_FLAGS "-x objective-c++ -O3 -fno-rtti")
    set_source_files_properties(source/Irrlicht/MacOSX/OSXClipboard.mm PROPERTIES LANGUAGE C)
endif()

add_library(stkirrlicht STATIC ${IRRLICHT_SOURCES})

target_link_libraries(stkirrlicht ${ZLIB_LIBRARY})

if(NOT SERVER_ONLY)
    target_link_libraries(stkirrlicht ${PNG_LIBRARY} ${JPEG_LIBRARY})
    if(UNIX AND NOT APPLE)
        target_link_libraries(stkirrlicht ${X11_X11_LIB} ${X11_Xrandr_LIB})
    endif()
        
    if(USE_GLES2 OR ENABLE_WAYLAND_DEVICE)
        target_link_libraries(stkirrlicht ${EGL_LIBRARY})
    endif()
    
    if(ENABLE_WAYLAND_DEVICE)
        target_link_libraries(stkirrlicht ${WAYLAND_LIBRARIES})
    endif()
endif()

if(WIN32)
    target_link_libraries(stkirrlicht imm32 xinput9_1_0)
endif()
