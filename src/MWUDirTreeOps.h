//v1.0 copyright Comine.com 20190829R1117
#ifndef MWUDirTreeOps_h
#define MWUDirTreeOps_h

/////////////////////////////////////////////////
#include "MStdLib.h"
#include "MStringQueue.h"

//******************************************************
//**  MWUDirTreeOps class
//******************************************************
class MWUDirTreeOps
	{
	////////////////////////////////////////////////
	
	////////////////////////////////////////////////
	void ClearObject(void);
	
	////////////////////////////////////////////////
	public:
	MWUDirTreeOps(bool create=false);
	~MWUDirTreeOps(void);
	bool Create(void);
	bool Destroy(void);
	bool GetPath(const char* dir, const char* subdir,MStdArray<char> &fullpath);
	bool GetPath(const char *dir,const char *subdir,const char *filename,MStdArray<char> &fullpath);
	bool GetFilePath(const char* dir,const char* filename, MStdArray<char>& fullpath);
	bool GetDirs(const char *dir,MStringQueue &dirlist);
	bool GetDirsRelative(const char* dir, const char *relativedir,MStringQueue& dirs,MStringQueue& reldirs);
	bool GetDirsRecursivesly(const char *dir,MStringQueue &dirlist);
	bool GetDirsRecursiveslyRelative(const char* dir,const char* relativedir, MStringQueue& dirs,MStringQueue& dirlist);
	bool GetFiles(const char* dir, MStringQueue& filelist);
	bool GetFilesRelative(const char* dir, const char *relativedir,MStringQueue &files,MStringQueue &filesrel);
	bool GetFilesRecursively(const char *dir,MStringQueue &filelist);
	bool GetFilesRecursivelyRelative(const char* dir, const char *dirrel,MStringQueue& files,MStringQueue &filesrel);
	bool CopyDirTree(const char *srcdir,const char *dstdir);		// Copy source files and directories to destination
	bool DeleteDirTree(const char* dir);							// Delete all files and subdirectories in  directory
	bool MakeDirs(const char *dir,const char *dirlist[]);			// make directories in folder. Order is important
	bool DirsExists(const char *dir,const char *dirlist[]);			// Check if all the subdirectories exists
	bool FileWriteText(const char *dir,const char *subdir,const char *filename,const char *txt);		// Write text to file in directory
	bool FileWriteText(const char* dir,const char* filename, const char*txt);		// Write text to file in directory
	bool FileWriteBinary(const char *dir,const char *subdir,const char *filename,const char *buffer,int elementsize,int elementcount);
	bool FileReadText(const char *dir,const char *subdir,const char *filename,MStdArray<char> &textcontent);	// Read text of file
	bool FileReadBinary(const char* dir,const char* subdir,const char* filename,MStdArray<char>& textcontent);	// Read text of file
	};

#endif // MWUDirTreeOps_h

