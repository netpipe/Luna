//-----------------------------------------------------------------------------
// 	File: CSQLReader.cpp
// 	Author: Caswal Parker
// 	Copyright 2007
//		Description: Adds an SQLite Filesystem to Irrlicht. 
//							Using zlib compression and XTEA encryption.
//-----------------------------------------------------------------------------


#include "CSQLReader.h"
#include "os.h"
#include "CMemoryReadFile.h"

#include "IrrCompileConfig.h"
#ifdef _IRR_COMPILE_WITH_ZLIB_
    #ifndef _IRR_USE_NON_SYSTEM_ZLIB_
    #include <zlib.h> // use system lib
    #else // _IRR_USE_NON_SYSTEM_ZLIB_
    #include "zlib/zlib.h" 
    #endif // _IRR_USE_NON_SYSTEM_ZLIB_
#endif // _IRR_COMPILE_WITH_ZLIB_

namespace irr
{
namespace io
{



void decipher(unsigned int num_rounds, unsigned long* v, unsigned long* k)
{
    unsigned long v0=v[0], v1=v[1], i;
    unsigned long delta=0x9E3779B9, sum=delta*num_rounds;

    for(i=0; i<num_rounds; i++)
	{
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
        sum -= delta;
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
    }

    v[0]=v0; v[1]=v1;
}

char* Decrypt( char* Data, unsigned int Size, unsigned long* Key )
{
	for (int i = 0; i < Size-8; i+=8 )
	{
		decipher( 32, (unsigned long*)&Data[i], Key );
	}

	return Data;
}



CSQLReader::CSQLReader(const c8* filename, const u32* key)
{
	mRC = sqlite3_open(filename, &mDB);

	mHasKey = false;

	mKeyGenFunc = 0;

	if ( key )
	{
		memcpy( mKey, key, 16 );
		mHasKey = true;
	}

	if( mRC )
	{
		os::Printer::log( "Can't open database: ", filename, ELL_ERROR );

		sqlite3_close(mDB);
	}

}

CSQLReader::CSQLReader(const c8* filename, const u32* (*KeyGenFunc)(void))
{
	mRC = sqlite3_open(filename, &mDB);

	mKeyGenFunc = KeyGenFunc;
	mHasKey = true;


	if( mRC )
	{
		os::Printer::log( "Can't open database: ", filename, ELL_ERROR );

		sqlite3_close(mDB);
	}

}

CSQLReader::~CSQLReader(void)
{
	if (mDB)
	{
		sqlite3_close( mDB );
	}
}


bool CSQLReader::CheckForError()
{
	if( mRC != SQLITE_OK )
	{
		os::Printer::log( "SQL error: ", mErrMsg, ELL_ERROR );

		sqlite3_free(mErrMsg);

		return true;
	}

	return false;
}

IReadFile* CSQLReader::openFile(const c8* filename)
{
	if (!mDB)
		return 0;

	//Do we have a file? if So what is its decompressed size?
	u32 FileSize = GetFileSize( filename );

	if ( FileSize == 0 )
		return 0;

	//Lets read some data out
	const c8 *SELECTBLOB = "SELECT Data FROM Files WHERE Filename = ?";
	sqlite3_stmt *pStmt = 0;

	mRC = sqlite3_prepare(mDB, SELECTBLOB, -1, &pStmt, 0);

	c8 *Data = 0;
	
	
	c8 filenamelwr[255];

	strcpy( filenamelwr, filename );

	strlwr( filenamelwr );

	u32 SizeInBytes = 0;

	do
	{
		
		if( mRC != SQLITE_OK )
		{
		  return 0;
		}

		sqlite3_bind_text( pStmt, 1, filenamelwr, strlen(filenamelwr), SQLITE_STATIC  );

		mRC = sqlite3_step(pStmt);

		if( mRC == SQLITE_ROW )
		{
			SizeInBytes = sqlite3_column_bytes( pStmt, 0);
			
			Data = new c8[SizeInBytes];

			memcpy( Data, sqlite3_column_blob(pStmt, 0), SizeInBytes );
		}
	} while ( mRC == SQLITE_SCHEMA );

	if ( Data != 0 ) //We have the data, time for some decompression
	{

		//Well the data is encrypted
		if ( mHasKey )
		{
			if ( mKeyGenFunc )
			{
				//Create some memory to store the key
				unsigned long *Key = new unsigned long[4];

				//As soon as the function gets popped off the stack
				//Its memory is disallocated
				memcpy( Key, (*mKeyGenFunc)(), 16 );

				//Decrypt the file using the Key
				Decrypt( Data, SizeInBytes, Key );

				//Delete it NOW
				delete[] Key;
			}
			else
				Decrypt( Data, SizeInBytes, (unsigned long*)mKey );
		}

		c8* UncompressedData = new c8[FileSize];

		uncompress( (Bytef*)UncompressedData, (uLongf*)&FileSize, (const Bytef*)Data, SizeInBytes );

		//Delete the compressed data buffer now that we are done with it.
		delete[] Data;

		return new CMemoryReadFile( UncompressedData, FileSize, filename, true );
	}

	else return 0;
}

u32 CSQLReader::GetFileSize( const c8* filename )
{
	if (!mDB)
		return 0;
	//Lets read some data out
	const c8 *FINDFILE = "SELECT FileSize FROM Files WHERE FileName = ?";
	sqlite3_stmt *pStmt = 0;

	mRC = sqlite3_prepare(mDB, FINDFILE, -1, &pStmt, 0);

	c8 filenamelwr[255];

	strcpy( filenamelwr, filename );

	strlwr( filenamelwr );

	do
	{
		
		if( mRC != SQLITE_OK )
		{
		  return 0;
		}

		sqlite3_bind_text( pStmt, 1, filenamelwr, strlen(filenamelwr), SQLITE_STATIC  );

		mRC = sqlite3_step(pStmt);

		if( mRC == SQLITE_ROW )
		{
			return sqlite3_column_int(pStmt, 0 );

		}
	} while ( mRC == SQLITE_SCHEMA );


	return 0;
}

s32 CSQLReader::findFile(const c8* filename)
{
	if (!mDB)
		return -1;
	//Lets read some data out
	const c8 *FINDFILE = "SELECT Key FROM Files WHERE FileName = ?";
	sqlite3_stmt *pStmt = 0;

	mRC = sqlite3_prepare(mDB, FINDFILE, -1, &pStmt, 0);

	do
	{
		
		if( mRC != SQLITE_OK )
		{
		  return -1;
		}

		sqlite3_bind_text( pStmt, 1, filename, strlen(filename), SQLITE_STATIC  );

		mRC = sqlite3_step(pStmt);

		if( mRC == SQLITE_ROW )
		{
			return sqlite3_column_int(pStmt, 0 );

		}
	} while ( mRC == SQLITE_SCHEMA );


	return -1;
}

} //namespace io
} //namespace irr