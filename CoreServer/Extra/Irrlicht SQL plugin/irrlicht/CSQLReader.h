//-----------------------------------------------------------------------------
// 	File: CSQLReader.h
// 	Author: Caswal Parker
// 	Copyright 2007
//		Description: Adds an SQLite Filesystem to Irrlicht. 
//							Using zlib compression and XTEA encryption.
//-----------------------------------------------------------------------------


#ifndef _C_SQLREADER_H_H
#define _C_SQLREADER_H_H

#include "IReadFile.h"
#include "irrArray.h"
#include "irrString.h"
#include "IFileSystem.h"

#include "./sqlite/sqlite3.h"

#ifdef _WINDOWS
#pragma comment(lib, "./sqlite/SQLBuild.lib")
#else
#error Non Windows Not Supported yet
#endif

namespace irr
{
	namespace io
	{

		class CSQLReader :public virtual IReferenceCounted
		{
		public:
			CSQLReader(const c8* filename, const u32* key);
			CSQLReader(const c8* filename, const u32* (*KeyGenFunc)(void));
			virtual ~CSQLReader(void);

			//! opens a file by file name
			virtual IReadFile* openFile(const c8* filename);

			//! returns fileindex
			s32 findFile(const c8* filename);
		private:
			sqlite3 *mDB;

			char *mErrMsg;
			int mRC;

			u32 GetFileSize( const c8* filename );

			const u32* (*mKeyGenFunc)(void);

			u32 mKey[4];

			bool mHasKey;

			bool CheckForError();
		};



	} //Namepace IO
}// Namespace irr


#endif _C_SQLREADER_H_H
