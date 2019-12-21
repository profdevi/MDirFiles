//v1.0 copyright Comine.com 20191220F2209
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MDirFiles.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MDirFiles";	// Used in Help
static const char *GApplicationVersion="1.0";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);
static bool GListFiles(MCommandArg &args);
static bool GDelFiles(MCommandArg& args);
static bool GKeepFiles(MCommandArg& args);
static bool GCatFiles(MCommandArg& args);
static bool GCatFilesWithHeader(MCommandArg& args);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	///////////////////////////////////////////////
	if(args.GetArgCount()<2)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveArg("-list")==true)
		{
		if(GListFiles(args)==false)
			{
			MStdPrintf("**Unable to list files\n");
			return 1;
			}

		return 0;
		}
	else if(args.CheckRemoveArg("-del")==true)
		{
		if(GDelFiles(args)==false)
			{
			MStdPrintf("**Unable to delete files with extensions\n");
			return 2;
			}

		MStdPrintf("done...\n");
		return 0;
		}
	else if(args.CheckRemoveArg("-keep")==true)
		{
		if(GKeepFiles(args)==false)
			{
			MStdPrintf("**Unable to keep files with extensions\n");
			return 3;
			}

		MStdPrintf("done...\n");
		return 0;
		}
	else if(args.CheckRemoveArg("-cat")==true)
		{
		if(GCatFiles(args)==false)
			{
			MStdPrintf("**Unable to cat files with extensions\n");
			return 4;
			}

		return 0;
		}
	else if(args.CheckRemoveArg("-cathead")==true)
		{
		if(GCatFilesWithHeader(args)==false)
			{
			MStdPrintf("**Unable to cat files with extensions\n");
			return 4;
			}

		return 0;
		}


	else
		{
		GDisplayHelp();
		return 1;
		}

	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s [-?][-list][-del|[-keep] <extensions>*\n"
				"           v%s copyright Comine.com\n"
				"\n"				
				"      -list     :  list files with extensions\n"
				"      -del      :  delete files with extensions\n"
				"      -keep     :  delete all files except those with extensions\n"
				"      -cat      :  print out contents all files with extensions\n"
				"      -cathead  :  print out contents all files with extensions with header\n"
				"\n"
				"   examples:\n"
				"       1)   List all .h .cpp files\n"
				"            C:> %s -list .h .cpp\n"
				"\n"
				"       2)   Delete all .h .cpp files\n"
				"            C:> %s -del .h .cpp\n"
				"\n"
				"       3)   Kepp only .h .cpp files.  Delete all others\n"
				"            C:> %s -keep .h .cpp\n"
				"\n"
				,GApplicationName,GApplicationVersion
				,GApplicationName, GApplicationName, GApplicationName);
	}


/////////////////////////////////////////////////////////
static bool GListFiles(MCommandArg& args)
	{
	// Get Current Directory
	MStdArray<char> currentdir;
	if(MStdDirGet(currentdir)==false)
		{
		return false;
		}

	MDirFiles dirfiles;
	if(dirfiles.Create(currentdir.Get())==false)
		{
		return false;
		}
	
	if(args.GetArgCount()<=1)
		{
		dirfiles.PrintFileNames();
		return true;
		}

	// Add extensions
	const int argcount=args.GetArgCount();
	for(int i=1;i<argcount;++i)
		{
		if(dirfiles.AddExtension(args.GetArg(i))==false)
			{
			return false;
			}
		}

	if(dirfiles.PrintFileNamesWithExtensions()==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////////////////
static bool GDelFiles(MCommandArg& args)
	{
	// Get Current Directory
	MStdArray<char> currentdir;
	if(MStdDirGet(currentdir)==false)
		{
		return false;
		}

	MDirFiles dirfiles;
	if(dirfiles.Create(currentdir.Get())==false)
		{
		return false;
		}
	
	if(args.GetArgCount()<=1)
		{
		return true;
		}

	// Add extensions
	const int argcount=args.GetArgCount();
	for(int i=1;i<argcount;++i)
		{
		if(dirfiles.AddExtension(args.GetArg(i))==false)
			{
			return false;
			}
		}

	if(dirfiles.DeleteFilesWithExtensions()==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////////////////
static bool GKeepFiles(MCommandArg& args)
	{
	// Get Current Directory
	MStdArray<char> currentdir;
	if(MStdDirGet(currentdir)==false)
		{
		return false;
		}

	MDirFiles dirfiles;
	if(dirfiles.Create(currentdir.Get())==false)
		{
		return false;
		}
	
	if(args.GetArgCount()<=1)
		{
		return true;
		}

	// Add extensions
	const int argcount=args.GetArgCount();
	for(int i=1;i<argcount;++i)
		{
		if(dirfiles.AddExtension(args.GetArg(i))==false)
			{
			return false;
			}
		}

	if(dirfiles.DeleteFilesWithOutExtensions()==false)
		{
		return false;
		}

	return true;
	}


/////////////////////////////////////////////////////////////
static bool GCatFiles(MCommandArg& args)
	{
	// Get Current Directory
	MStdArray<char> currentdir;
	if(MStdDirGet(currentdir)==false)
		{
		return false;
		}

	MDirFiles dirfiles;
	if(dirfiles.Create(currentdir.Get())==false)
		{
		return false;
		}
	
	if(args.GetArgCount()<=1)
		{
		return true;
		}

	// Add extensions
	const int argcount=args.GetArgCount();
	for(int i=1;i<argcount;++i)
		{
		if(dirfiles.AddExtension(args.GetArg(i))==false)
			{
			return false;
			}
		}

	if(dirfiles.PrintFilesWithExtensions()==false)
		{
		return false;
		}

	return true;
	}


////////////////////////////////////////////////////	
static bool GCatFilesWithHeader(MCommandArg& args)
	{
	// Get Current Directory
	MStdArray<char> currentdir;
	if(MStdDirGet(currentdir)==false)
		{
		return false;
		}

	MDirFiles dirfiles;
	if(dirfiles.Create(currentdir.Get())==false)
		{
		return false;
		}
	
	if(args.GetArgCount()<=1)
		{
		return true;
		}

	// Add extensions
	const int argcount=args.GetArgCount();
	for(int i=1;i<argcount;++i)
		{
		if(dirfiles.AddExtension(args.GetArg(i))==false)
			{
			return false;
			}
		}

	if(dirfiles.PrintFilesWithExtensions(true)==false)
		{
		return false;
		}

	return true;
	}


