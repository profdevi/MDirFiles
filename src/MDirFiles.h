//v0.0 copyright Comine.com 20150816U1847
#ifndef MDirFiles_h
#define MDirFiles_h

/////////////////////////////////////////////////
#include "MStdLib.h"
#include "MString.h"
#include "MStringList.h"
#include "MStringQueue.h"

/*
		MDirFiles Processes All the files 
*/

//******************************************************
//**  MDirFiles class
//******************************************************
class MDirFiles
	{
	////////////////////////////////////////////////
	MString mBaseDir;
	MStringList mExtList;
	
	////////////////////////////////////////////////
	void ClearObject(void);
	bool GetAllFiles(MStringQueue& allfiles);
	bool IsExtensionInList(const char *extension);

	////////////////////////////////////////////////
	public:
	MDirFiles(void);
	~MDirFiles(void);
	bool Create(const char *basedir);
	bool Destroy(void);
	bool ClearExtensions(void);
	bool AddExtension(const char *extension);
	bool PrintExtension(void);
	bool PrintFileNames(void);
	bool PrintFileNamesWithExtensions(void);
	bool PrintFileNamesWithOutExtensions(void);
	bool DeleteFilesWithExtensions(void);
	bool DeleteFilesWithOutExtensions(void);	
	bool PrintFilesWithExtensions(bool printseperator=false);
	};

#endif // MDirFiles_h

