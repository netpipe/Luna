Readme for Caswal "Zeussy" Parker's SQL Filesystem Extension for Irrlicht.

Copyright Caswal Parker 2007.

Free for Public and Commercial use. All I ask for is a simple credit somewhere,
even if it is just within a readme.txt.


This Package Includes:
------------------------------------------------------------------------------

Changed Include and source files, as well as patch files that can be applied to your svn checkout.
sqlite folder contains a prebuilt lib, and header file for sqlite3.
As you have to build these yourself. Irrlicht folder contains the changed and additional files. 
Check Changelog.txt for changes. Just incase you want to do a custom build if you cant use the patch files.


Description:
------------------------------------------------------------------------------

This is an SQL Filesystem extension for Irrlicht, to allow files to be packed easily
into an archive for efficient storage, but also some degree of protection.

The SQL database has single table, with the follow columns:

Key, Filename, Data, FileSize

All data within the database has been compressed with zlib. 
Currently no option is given over the compression. 
All files are compressed with the Z_BEST_COMPRESSION option.

Data can also be optionally encrypted, with the XTEA Algorithm.
The functions are straightly extracted from the Wikipedia article:
http://en.wikipedia.org/wiki/XTEA#Implementations 

My XTEA implementation uses an 128bit key, and 32 rounds.


How to Install:
------------------------------------------------------------------------------

Replace these files with mine, within your Irrlicht source code:
CFileSystem.cpp & CFileSystem.h as well as IFileSystem.h.

Or check Changelog.txt for the specific changes, if you want to add them yourself,
they are not many about 10.

Also add CSQLReader.h and CSQLReader.cpp to your source files.

You also need to add the sqlite3 header and library files.


Usage:
------------------------------------------------------------------------------


The usage is pretty simple. After you have built the new Irrlicht dll,
you can load a SQLite file archive with code similar too:


	irr::u32 Key[4] = { 0xFFEA3FA2, 0xDEADBEEF, 0x145AF48B, 0xDC4E2F63 };

	device->getFileSystem()->addSQLiteDatabase("./art.db", true, true, Key );
	

The key can either be a constant like so. Which is not very secure,
and can be retrived from the source.

Or you can pass a function reference into the function using the following syntax and example:

//Defined elsewhere in the program

const irr::f32 Gravity = 9.81f;

const irr::u32* GenKey(void)
{
	irr::u32 Seed = 0;

	memcpy( &Seed, &Gravity, 4 );

	u32 Key[4];

	Key[0] = Seed *= Seed >> 7;

	Key[1] = Seed *= Seed >> 9;

	Key[2] = Seed *= Seed >> 11;

	Key[3] = Seed *= Seed >> 13;

	return Key;
}

//Before you start your file loading
device->getFileSystem()->addSQLiteDatabase("./art.db", GenKey, true, true );



You will have to record the result of GenKey yourself using the debugger or
some kind of Debug output that you can use for passing into the Exporter.

The SQL FileSystem only creates a temporary copy of the key as it decrypts
the freshly loaded data, and immediately deletes the key when completed.

The Exporter has a full readme, just run it from command line
and follow its instructions. Im sorry that it is windows only atm. Source will come soon!


Known Issues/Bugs:
------------------------------------------------------------------------------

It currently does not ignore paths.
It currently stores all filenames in lower case.