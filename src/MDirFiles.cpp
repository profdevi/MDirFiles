//v0.0 copyright Comine.com 20150220F0758
#include "MStdLib.h"
#include "MString.h"
#include "MWUDirTreeOps.h"
#include "MStringQueue.h"
#include "MStringList.h"
#include "MFileOps.h"
#include "MBuffer.h"
#include "MDirFiles.h"


//******************************************************
//**  Module Elements
//******************************************************
static bool GPrintFile(const char *filename)
	{
	MFileOps fileops(true);
	MBuffer buffer;
	if(fileops.ReadBinaryFile(filename,buffer)==false)
		{
		return false;
		}

	const int length=buffer.GetSize();
	const char *bufferptr=buffer.GetBuffer();
	for(int i=0;i<length;++i)
		{
		const char data=bufferptr[i];
		if(MStdIsPrintable(data)==true || data=='\n' || data=='\t')
			{
			MStdPrintf("%c",data);
			}
		}

	return true;
	}


////////////////////////////////////////////////////////
bool GPrintHeader(const char *filename)
	{
	MStdAssert(filename!=0);
	const int length=MStdStrLen(filename);

	
	if(length>=60)
		{
		MStdPrintf("\n");
		for(int i=0;i<60;++i) {  MStdPrintf("#"); }
		MStdPrintf("\n");
		MStdPrintf("##  %s\n",filename);
		for (int i = 0; i < 60; ++i) { MStdPrintf("#"); }
		MStdPrintf("\n");
		return true;
		}

	//=File Name is shorter

	MStdPrintf("\n");
	const int spaces=(70-length)/2-2;
	for(int i = 0; i < 70; ++i) { MStdPrintf("#"); }
	MStdPrintf("\n");

	MStdPrintf("##");
	for(int i=0;i<spaces;++i){ MStdPrintf(" "); }
	MStdPrintf("%s",filename);
	
	for(int i=0;i<70-length-spaces-4;++i){ MStdPrintf(" "); }
	MStdPrintf("##\n");
	
	for (int i = 0; i < 70; ++i) { MStdPrintf("#"); }
	MStdPrintf("\n");
	return true;
	}


//******************************************************
//**  MDirFiles class
//******************************************************
void MDirFiles::ClearObject(void)
	{
	}


////////////////////////////////////////////////
bool MDirFiles::GetAllFiles(MStringQueue &allfiles)
	{
	MWUDirTreeOps treeops(true);
	if(treeops.GetFiles(mBaseDir.Get(),allfiles)==false)
		{
		return false;
		}

	MStringQueue subdirfiles;
	if(treeops.GetFilesRecursively(mBaseDir.Get(),subdirfiles)==false)
		{
		return false;
		}

	if(allfiles.Enqueue(subdirfiles)==false)
		{
		return false;
		}
	
	return true;
	}


/////////////////////////////////////////////////
bool MDirFiles::IsExtensionInList(const char* extension)
	{
	mExtList.ReadReset();
	const char *listext;
	while((listext=mExtList.ReadString())!=0)
		{
		if(MStdStrICmp(extension,listext)==0) { return true; }
		}

	return false;
	}


////////////////////////////////////////////////
MDirFiles::MDirFiles(void)
	{  ClearObject();  }


////////////////////////////////////////////////
MDirFiles::~MDirFiles(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MDirFiles::Create(const char* basedir)
	{
	Destroy();
	if(MStdDirExists(basedir)==false)
		{
		return false;
		}

	if(mBaseDir.Create(basedir)==false)
		{
		Destroy();
		return false;
		}

	if(mExtList.Create()==false)
		{
		Destroy();
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MDirFiles::Destroy(void)
	{
	mBaseDir.Destroy();
	mExtList.Destroy();
	ClearObject();
	return true;
	}


///////////////////////////////////////////////
bool MDirFiles::ClearExtensions(void)
	{
	if(mExtList.Create()==false)
		{
		return false;
		}

	return true;
	}


//////////////////////////////////////////////
bool MDirFiles::AddExtension(const char* extension)
	{
	if(mExtList.AddString(extension)==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MDirFiles::PrintExtension(void)
	{
	mExtList.Print();
	return true;
	}


//////////////////////////////////////////////
bool MDirFiles::PrintFileNames(void)
	{
	MStringQueue files;
	if(GetAllFiles(files)==false)
		{
		return false;
		}

	files.ReadReset();
	while(files.Read()==true)
		{
		MStdPrintf("%s\n",files.ReadGet());
		}

	return true;	
	}


////////////////////////////////////////////////////////////
bool MDirFiles::PrintFileNamesWithExtensions(void)
	{
	if(mExtList.GetCount()==0)
		{
		return false;
		}

	// Get All Files
	MStringQueue files;
	if(GetAllFiles(files)==false)
		{
		return false;
		}

	files.ReadReset();
	while(files.Read()==true)
		{
		const char *filename=files.ReadGet();
		const char *extension=MStdPathGetExtension(filename);
		if(extension==0 || *extension==0) { continue; }
		if(IsExtensionInList(extension)==false) { continue; }

		MStdPrintf("%s\n",filename);
		}

	return true;	
	}


////////////////////////////////////////////////////////////
bool MDirFiles::PrintFileNamesWithOutExtensions(void)
	{
	if(mExtList.GetCount()==0)
		{
		return false;
		}

	// Get All Files
	MStringQueue files;
	if(GetAllFiles(files)==false)
		{
		return false;
		}

	files.ReadReset();
	while(files.Read()==true)
		{
		const char *filename=files.ReadGet();
		const char *extension=MStdPathGetExtension(filename);
		if(extension==0 || *extension==0) { continue; }
		if(IsExtensionInList(extension)==true) { continue; }

		MStdPrintf("%s\n",filename);
		}

	return true;	
	}


////////////////////////////////////////////////////////////
bool MDirFiles::DeleteFilesWithExtensions(void)	
	{
	if(mExtList.GetCount()==0)
		{
		return false;
		}

	// Get All Files
	MStringQueue files;
	if(GetAllFiles(files)==false)
		{
		return false;
		}

	files.ReadReset();
	while(files.Read()==true)
		{
		const char *filename=files.ReadGet();
		const char *extension=MStdPathGetExtension(filename);
		if(extension==0 || *extension==0) { continue; }
		if(IsExtensionInList(extension)==false) { continue; }

		if(MStdFileRemove(filename)==false)
			{
			//=continue anyway
			}
		}

	return true;
	}


////////////////////////////////////////////////////////////
bool MDirFiles::DeleteFilesWithOutExtensions(void)
	{
	if(mExtList.GetCount()==0)
		{
		return false;
		}

	// Get All Files
	MStringQueue files;
	if(GetAllFiles(files)==false)
		{
		return false;
		}

	files.ReadReset();
	while(files.Read()==true)
		{
		const char *filename=files.ReadGet();
		const char *extension=MStdPathGetExtension(filename);
		if(extension==0 || *extension==0) { continue; }
		if(IsExtensionInList(extension)==true) { continue; }

		if(MStdFileRemove(filename)==false)
			{
			//=continue anyway
			}
		}

	return true;
	}


////////////////////////////////////////////////////////
bool MDirFiles::PrintFilesWithExtensions(bool printseperator)
	{
	if(mExtList.GetCount()==0)
		{
		return false;
		}

	// Get All Files
	MStringQueue files;
	if(GetAllFiles(files)==false)
		{
		return false;
		}

	files.ReadReset();
	while(files.Read()==true)
		{
		const char *filename=files.ReadGet();
		const char *extension=MStdPathGetExtension(filename);
		if(extension==0 || *extension==0) { continue; }
		if(IsExtensionInList(extension)==false) { continue; }

		// Print out the file
		if(printseperator==true) {  GPrintHeader(filename);  }

		GPrintFile(filename);
		}

	return true;
	}


