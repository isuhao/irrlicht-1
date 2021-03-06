// Copyright (C) 2002-2006 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h
// 
// This file was originally written by ZDimitor.
// I (Nikolaus Gebhardt) did some few changes to this:
// - replaced logging calls to their os:: counterparts
// - removed some logging calls
// - enabled image dropping of CImage again, because that bug has been fixed now
// - removed setTexture path and replaced it with the directory of the mesh
// - added EAMT_MY3D file type
// - fixed a memory leak when decompressing RLE data.
// - cleaned multi character constant problems with gcc
// - removed octree child scene node generation because irrlicht is now able to draw 
//   scene nodes with transparent and sold materials in them at the same time. (see changes.txt)
// Thanks a lot to ZDimitor for his work on this and that he gave me
// his permission to add it into Irrlicht. 

//--------------------------------------------------------------------------------
// This tool created by ZDimitor everyone can use it as wants
//--------------------------------------------------------------------------------

#ifndef __CMY3D_MESH_FILE_LOADER_H_INCLUDED__
#define __CMY3D_MESH_FILE_LOADER_H_INCLUDED__


#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif


#include "IMeshLoader.h"
#include "SMesh.h"
#include "SMeshBufferLightMap.h"
#include "IFileSystem.h"
#include "IVideoDriver.h"
#include "irrString.h"
#include "ISceneManager.h"

#include "CMY3DStuff.h"

namespace irr 
{
namespace scene 
{



class CMY3DMeshFileLoader : public IMeshLoader
{
public:
	CMY3DMeshFileLoader(
        io::IFileSystem* fs, video::IVideoDriver* driver, ISceneManager *scmgr);
	virtual ~CMY3DMeshFileLoader();

	virtual bool isALoadableFileExtension(const c8* fileName);

	virtual IAnimatedMesh* createMesh(io::IReadFile* file);

	//! getting access to the nodes (with transparent material), creating 
    //! while loading .my3d file 
	core::array<ISceneNode*>& getChildNodes();
	
private:
	
	scene::SMesh* Mesh;

	video::IVideoDriver* Driver;
	io::IFileSystem* FileSystem;
	ISceneManager *SceneManager;

	video::SColor SceneBackgrColor;
	video::SColor SceneAmbientColor;

	struct SMyMaterialEntry
	{
		SMyMaterialEntry ()
            : Texture1FileName("null"), Texture2FileName("null"),
            Texture1(0), Texture2(0), MaterialType(video::EMT_SOLID) {;}
		SMyMaterialHeader Header;
		core::stringc Texture1FileName;
		core::stringc Texture2FileName;
		video::ITexture *Texture1;
		video::ITexture *Texture2;
		video::E_MATERIAL_TYPE MaterialType;
	};

	struct SMyMeshBufferEntry
	{
		SMyMeshBufferEntry() : MaterialIndex(-1), MeshBuffer(0) {}
		SMyMeshBufferEntry(s32 mi, SMeshBufferLightMap* mb)
			: MaterialIndex(mi), MeshBuffer(mb) {;}

		s32 MaterialIndex;
		SMeshBufferLightMap* MeshBuffer;
	};

	core::array<SMyMaterialEntry>   MaterialEntry;
	core::array<SMyMeshBufferEntry> MeshBufferEntry;

	SMyMaterialEntry*    getMaterialEntryByIndex     (u32 matInd);
	SMeshBufferLightMap* getMeshBufferByMaterialIndex(u32 matInd);

	core::array<ISceneNode*> ChildNodes;
};


} // end namespace scene
} // end namespace irr


#endif // __CMY3D_MESH_FILE_LOADER_H_INCLUDED__
