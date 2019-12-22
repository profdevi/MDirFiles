//v1.0 copyright Comine.com 20190829R1117
#include "MStdLib.h"
#include "MStringQueue.h"
#include "MWUDirReader.h"
#include "MFilePathBuilder.h"
#include "MWUDirTreeOps.h"


//******************************************************
//**  Module Elements
//******************************************************


//******************************************************
//**  MWUDirTreeOps class
//******************************************************
void MWUDirTreeOps::ClearObject(void)
	{
	}



////////////////////////////////////////////////
MWUDirTreeOps::MWUDirTreeOps(bool create)
	{
	ClearObject();
	if (create == true && Create() == false)
		{
		return;
		}
	}


////////////////////////////////////////////////
MWUDirTreeOps::~MWUDirTreeOps(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MWUDirTreeOps::Create(void)
	{
	Destroy();
	return true;
	}


////////////////////////////////////////////////
bool MWUDirTreeOps::Destroy(void)
	{
	ClearObject();
	return true;
	}


/////////////////////////////////////////////////
bool MWUDirTreeOps::GetPath(const char* dir, const char* subdir, MStdArray<char> &fullpath)
	{
	MStdArray<char> path;
	if (MStdPathGetAbsolute(dir, path) == false)
		{
		return false;
		}

	MFilePathBuilder builder;
	if (builder.Create(path.Get()) == false)
		{
		return false;
		}

	// Push Subdirectory
	if (builder.Push(subdir) == false)
		{
		return false;
		}

	MBuffer buffullpath;	
	if (builder.GetFullPath(buffullpath) == false)
		{
		return false;
		}

	if (fullpath.Create(buffullpath.GetStringLength() + 2) == false)
		{
		return false;
		}

	MStdStrCpy(fullpath.Get(),fullpath.GetLength(),buffullpath.GetBuffer());

	return true;
	}


/////////////////////////////////////////////////
bool MWUDirTreeOps::GetPath(const char* dir, const char* subdir, const char* filename, MStdArray<char> &fullpath)
	{
	MStdArray<char> path;
	if (MStdPathGetAbsolute(dir, path) == false)
		{
		return false;
		}

	MFilePathBuilder builder;
	if (builder.Create(path.Get()) == false)
		{
		return false;
		}

	// Push subdirectory
	if (builder.Push(subdir) == false)
		{
		return false;
		}

	// Push filename
	if (builder.Push(filename) == false)
		{
		return false;
		}

	MBuffer buffullpath;
	if (builder.GetFullPath(buffullpath) == false)
		{
		return false;
		}

	if (fullpath.Create(buffullpath.GetStringLength() + 2) == false)
		{
		return false;
		}

	MStdStrCpy(fullpath.Get(), fullpath.GetLength(), buffullpath.GetBuffer());

	return true;
	}


////////////////////////////////////////////////
bool MWUDirTreeOps::GetFilePath(const char* dir, const char* filename, MStdArray<char>& fullpath)
	{
	MStdArray<char> path;
	if (MStdPathGetAbsolute(dir, path) == false)
		{
		return false;
		}

	MFilePathBuilder builder;
	if (builder.Create(path.Get()) == false)
		{
		return false;
		}

	// Push filename
	if (builder.Push(filename) == false)
		{
		return false;
		}

	MBuffer buffullpath;
	if (builder.GetFullPath(buffullpath) == false)
		{
		return false;
		}

	if (fullpath.Create(buffullpath.GetStringLength() + 2) == false)
		{
		return false;
		}

	MStdStrCpy(fullpath.Get(), fullpath.GetLength(), buffullpath.GetBuffer());

	return true;
	}


////////////////////////////////////////////////
bool MWUDirTreeOps::GetDirs(const char* dir, MStringQueue& dirlist)
	{
	MWUDirReader reader;
	if (reader.Create(dir) == false)
		{
		return false;
		}

	if (dirlist.Create() == false)
		{
		return false;
		}

	while (reader.Read() == true)
		{
		if(reader.IsDirectory()==false) { continue; }
		if (dirlist.Enqueue(reader.GetFullFilePath()) == false)
			{
			return false;
			}
		}

	return true;
	}


///////////////////////////////////////////////
bool MWUDirTreeOps::GetDirsRelative(const char* dir,const char *relativedir
		,MStringQueue &dirs,MStringQueue& reldirs)
	{
	if (GetDirs(dir, dirs) == false)
		{
		return false;
		}

	MStdArray<char> dirfullpath;
	if (MStdPathGetAbsolute(dir, dirfullpath) == false)
		{
		return false;
		}

	if (reldirs.Create() == false)
		{
		return false;
		}

	// Get Absolute path to relativedir
	MStdArray<char> relativeabspath;
	if (MStdPathGetAbsolute(relativedir, relativeabspath) == false)
		{
		}

	dirs.ReadReset();
	while (dirs.Read() == true)
		{
		const char *partialpath=MStdPathDiff(dirs.ReadGet(),dirfullpath.Get());
		if (partialpath == NULL)
			{
			return false;
			}

		MFilePathBuilder pathbuilder;
		if (pathbuilder.Create(relativeabspath.Get()) == false)
			{
			return false;
			}

		if (pathbuilder.Push(partialpath) == false)
			{
			return false;
			}

		MBuffer fullpathfinal;
		if (pathbuilder.GetFullPath(fullpathfinal) == false)
			{
			return false;
			}

		if (reldirs.Enqueue(fullpathfinal.GetBuffer() ) == false)
			{
			return false;
			}
		}

	return true;
	}


///////////////////////////////////////////////
bool MWUDirTreeOps::GetDirsRecursivesly(const char* dir, MStringQueue& dirlist)
	{
	// Get Full path 
	MStdArray<char> fullpath;
	if (MStdPathGetAbsolute(dir, fullpath) == false)
		{
		return false;
		}

	// init openlist and closed list(dirlist)
	MStringQueue openlist;
	if (openlist.Create() == false || dirlist.Create() == false)
		{
		return false;
		}

	if (openlist.Enqueue(fullpath.Get()) == false)
		{
		return false;
		}

	// openlist.Print();

	while (openlist.GetQueueLength() > 0)
		{
		const char *firstdir=openlist.GetFront();
		MStdAssert(firstdir!=NULL && *firstdir!=0);
		
		MStringQueue subdirlist;
		if (GetDirs(firstdir, subdirlist) == false)
			{
			return false;
			}

		if (openlist.Enqueue(subdirlist) == false)
			{
			return false;
			}

		// Remove the first item in open list and add to closed list
		dirlist.Enqueue(firstdir);
		openlist.Dequeue();
		}

	// Remove the first directory
	dirlist.Dequeue();

	return true;
	}


/////////////////////////////////////////////////
bool MWUDirTreeOps::GetDirsRecursiveslyRelative(const char* dir, const char* relativedir,MStringQueue& dirs,MStringQueue& dirlist)
	{
	// Get All sub directories from dir
	if (GetDirsRecursivesly(dir, dirs) == false)
		{
		return false;
		}

	MStdArray<char> dirpath;
	if (MStdPathGetAbsolute(dir, dirpath) == false)
		{
		return false;
		}

	MStdArray<char> relativedirpath;
	if (MStdPathGetAbsolute(relativedir, relativedirpath) == false)
		{
		return false;
		}

	dirs.ReadReset();
	if (dirlist.Create() == false)
		{
		return false;
		}

	while (dirs.Read() == true)
		{
		const char *dirfilename=dirs.ReadGet();
		
		const char *pathdiff=MStdPathDiff(dirfilename,dirpath.Get());
		if (pathdiff == 0)
			{
			return false;
			}

		MFilePathBuilder builder;
		if (builder.Create(relativedirpath.Get()) == false)
			{
			return false;
			}

		if (builder.Push(pathdiff) == false)
			{
			return false;
			}

		MBuffer fullpath;
		if (builder.GetFullPath(fullpath) == false)
			{
			return false;
			}

		if (dirlist.Enqueue(fullpath.GetBuffer()) == false)
			{
			return false;
			}
		}
	
	return true;
	}


////////////////////////////////////////////////
bool MWUDirTreeOps::GetFiles(const char* dir, MStringQueue& filelist)
	{
	MWUDirReader reader;
	if (reader.Create(dir) == false)
		{
		return false;
		}

	if (filelist.Create() == false)
		{
		return false;
		}

	while (reader.Read() == true)
		{
		if (reader.IsDirectory() == true) { continue; }
		if (filelist.Enqueue(reader.GetFullFilePath()) == false)
			{
			return false;
			}
		}

	return true;
	}


////////////////////////////////////////////////////
bool MWUDirTreeOps::GetFilesRelative(const char* dir, const char* relativedir, MStringQueue& files, MStringQueue& filesrel)
	{
	if (GetFiles(dir, files) == false)
		{
		return false;
		}
	
	MStdArray<char> dirabs;
	if (MStdPathGetAbsolute(dir, dirabs) == false)
		{
		return false;
		}

	MStdArray<char> dirrelabs;
	if (MStdPathGetAbsolute(relativedir, dirrelabs) == false)
		{
		return false;
		}

	// Init filesrel
	if (filesrel.Create() == false)
		{
		return false;
		}

	files.ReadReset();
	while (files.Read() == true)
		{
		const char *filepath=files.ReadGet();
		const char *relativepath=MStdPathDiff(filepath,dirabs.Get());
		
		MFilePathBuilder builder;
		if (builder.Create(dirrelabs.Get()) == false)
			{
			return false;
			}
		
		if(builder.Push(relativepath)==false)
			{
			return false;
			}

		MBuffer fullpath;
		if (builder.GetFullPath(fullpath) == false)
			{
			return false;
			}

		if (filesrel.Enqueue(fullpath.GetBuffer()) == false)
			{
			return false;
			}
		}

	return true;
	}


///////////////////////////////////////////////////
bool MWUDirTreeOps::GetFilesRecursively(const char* dir, MStringQueue& filelist)
	{
	MStringQueue dirlist;
	if (GetDirsRecursivesly(dir, dirlist) == false)
		{
		return false;
		}

	if (filelist.Create() == false)
		{
		return false;
		}

	dirlist.ReadReset();
	while (dirlist.Read()==true)
		{
		const char *dirname=dirlist.ReadGet();
		MStdAssert(dirname!=0);

		MStringQueue files;
		if (GetFiles(dirname,files) == false)
			{
			return false;
			}

		if (filelist.Enqueue(files) == false)
			{
			return false;
			}
		}

	return true;
	}


//////////////////////////////////////////////////////////////////
bool MWUDirTreeOps::GetFilesRecursivelyRelative(const char* dir, const char* dirrel
		, MStringQueue& files, MStringQueue& filesrel)
	{
	if(GetFilesRecursively(dir,files)==false)
		{
		return false;
		}

	MStdArray<char> dirpath;
	if (MStdPathGetAbsolute(dir, dirpath) == false)
		{
		return false;
		}
		
	MStdArray<char> dirrelpath;
	if (MStdPathGetAbsolute(dirrel, dirrelpath) == false)
		{
		return false;
		}

	if (filesrel.Create() == false)
		{
		return false;
		}

	files.ReadReset();
	while (files.Read() == true)
		{
		const char *filepath=files.ReadGet();
		const char *relativepath=MStdPathDiff(filepath,dirpath.Get());
		
		MFilePathBuilder filepathbuilder;
		if (filepathbuilder.Create(dirrelpath.Get()) == false)
			{
			return false;
			}

		if (filepathbuilder.Push(relativepath) == false)
			{
			return false;
			}

		MBuffer fullpath;
		if (filepathbuilder.GetFullPath(fullpath) == false)
			{
			return false;
			}

		if (filesrel.Enqueue(fullpath.GetBuffer()) == false)
			{
			return false;
			}
		}

	return true;
	}


//////////////////////////////////////////////////////////////
bool MWUDirTreeOps::CopyDirTree(const char* srcdir, const char* dstdir)
	{
	MStringQueue srcdirs;
	MStringQueue dstdirs;
	if (GetDirsRecursiveslyRelative(srcdir, dstdir, srcdirs, dstdirs) == false)
		{
		return false;
		}

	MStdAssert(srcdirs.GetQueueLength() == dstdirs.GetQueueLength());

	srcdirs.ReadReset();
	dstdirs.ReadReset();
	while (srcdirs.Read() == true)
		{
		if (dstdirs.Read() == false)
			{
			return false;
			}

		const char *sourcedir=srcdirs.ReadGet();
		const char *targetdir=dstdirs.ReadGet();
		MStdAssert(MStdDirExists(sourcedir)==true);

		// If Target dir does not exist,create it.
		if (MStdDirExists(targetdir) == false)
			{
			if (MStdDirCreate(targetdir) == false)
				{
				return false;
				}
			}
		}

	//=We not have identical directory structure.

	//**Copy files over
	MStringQueue srcfiles;
	MStringQueue dstfiles;
	if (GetFilesRecursivelyRelative(srcdir, dstdir, srcfiles, dstfiles) == false)
		{
		return false;
		}

	srcfiles.ReadReset();
	dstfiles.ReadReset();
	while (srcfiles.Read() == true)
		{
		if (dstfiles.Read() == false)
			{
			return false;
			}

		const char *srcfilename=srcfiles.ReadGet();
		const char *dstfilename=dstfiles.ReadGet();

		// Delete destination file, if it exists.
		if(MStdFileExists(dstfilename)==true)
			{
			MStdFileRemove(dstfilename);
			}

		// Copy file
		if (MStdFileCopy(srcfilename, dstfilename) == false)
			{
			return false;
			}
		}

	return true;
	}


//////////////////////////////////////////////////////
bool MWUDirTreeOps::DeleteDirTree(const char *dir)
	{
	MStringQueue files;	
	if (GetFilesRecursively(dir, files) == false)
		{
		return false;
		}

	// Delete all the files
	files.ReadReset();
	while(files.Read() == true)
		{
		const char *filepath=files.ReadGet();
		if (MStdFileRemove(filepath) == false)
			{
			return false;
			}
		}

	//  Now  Get directories 
	MStringQueue dirs;
	if (GetDirsRecursivesly(dir, dirs) == false)
		{
		return false;
		}

	// Reverse the dirs queue
	if (dirs.Reverse() == false)
		{
		return false;
		}

	dirs.ReadReset();

	while (dirs.Read() == true)
		{
		const char *dirpath=dirs.ReadGet();
		
		if (MStdDirDestroy(dirpath) == false)
			{
			return false;
			}
		}

	return true;
	}


////////////////////////////////////////////////////////
bool MWUDirTreeOps::MakeDirs(const char* dir, const char* dirlist[])
	{
	MStdAssert(dir!=0 && dirlist!=0);

	MStdArray<char> dirpath;
	if (MStdPathGetAbsolute(dir, dirpath) == false)
		{
		return false;
		}
	
	for (int i = 0; dirlist[i] != 0; ++i)
		{
		MFilePathBuilder builder;
		if (builder.Create(dirpath.Get()) == false)
			{
			return false;
			}

		const char *newsubdir=dirlist[i];
		if (builder.Push(newsubdir) == false)
			{
			return false;
			}

		MBuffer fullpath;
		if (builder.GetFullPath(fullpath) == false)
			{
			return false;
			}

		if (MStdDirExists(fullpath.GetBuffer()) == false)
			{
			if(MStdDirCreate(fullpath.GetBuffer())==false)
				{
				return false;
				}
			}
		}

	return true;
	}


//////////////////////////////////////////////////////////////
bool MWUDirTreeOps::DirsExists(const char* dir, const char* dirlist[])
	{
	MStdAssert(dir != 0 && dirlist != 0);

	MStdArray<char> dirpath;
	if (MStdPathGetAbsolute(dir, dirpath) == false)
		{
		return false;
		}

	for (int i = 0; dirlist[i] != 0; ++i)
		{
		MFilePathBuilder builder;
		if (builder.Create(dirpath.Get()) == false)
			{
			return false;
			}

		const char* newsubdir = dirlist[i];
		if (builder.Push(newsubdir) == false)
			{
			return false;
			}

		MBuffer fullpath;
		if (builder.GetFullPath(fullpath) == false)
			{
			return false;
			}

		if (MStdDirExists(fullpath.GetBuffer()) == false) { return false; }
		}

	return true;
	}


//////////////////////////////////////////////////////////
bool MWUDirTreeOps::FileWriteText(const char* dir, const char* subdir, const char *filename,const char* txt)
	{
	MStdArray<char> fullpath;
	if (GetPath(dir,subdir,filename,fullpath)== false)
		{
		return false;
		}

	// Write to file
	if (MStdFileWriteText(fullpath.Get(), txt) == false)
		{
		return false;
		}
	
	return true;
	}


///////////////////////////////////////////////////////
bool MWUDirTreeOps::FileWriteText(const char* dir, const char* filename, const char* txt)
	{
	MStdArray<char> fullpath;
	if (GetFilePath(dir,filename,fullpath)== false)
		{
		return false;
		}

	// Write to file
	if (MStdFileWriteText(fullpath.Get(), txt) == false)
		{
		return false;
		}
	
	return true;
	}


//////////////////////////////////////////////////////
bool MWUDirTreeOps::FileWriteBinary(const char* dir, const char* subdir,const char *filename,const char* buffer, int elementsize, int elementcount)
	{
	MStdArray<char> fullpath;
	if (GetPath(dir, subdir,filename,fullpath) == false)
		{
		return false;
		}

	// Write to file
	if (MStdFileWrite(fullpath.Get(), buffer,elementsize,elementcount) == false)
		{
		return false;
		}

	return true;
	}


//////////////////////////////////////////////////////
bool MWUDirTreeOps::FileReadText(const char* dir, const char* subdir,const char *filename,MStdArray<char>& textcontent)
	{
	MStdArray<char> fullpath;
	if (GetPath(dir, subdir,filename,fullpath) == false)
		{
		return false;
		}

	// Write to file
	if (MStdFileReadText(fullpath.Get(),textcontent) == false)
		{
		return false;
		}

	return true;
	}


//////////////////////////////////////////////////////////
bool MWUDirTreeOps::FileReadBinary(const char* dir, const char* subdir, const char *filename,MStdArray<char>& bindata)
	{
	MStdArray<char> fullpath;
	if (GetPath(dir, subdir,filename, fullpath) == false)
		{
		return false;
		}

	// Write to file
	if (MStdFileReadBinary(fullpath.Get(), bindata) == false)
		{
		return false;
		}

	return true;
	}


