//v1.11 copyright Comine.com 20190829R0103
#include <new>
#include "MStdLib.h"
#include "MStringQueue.h"


//******************************************************
//**  Module Functions
//******************************************************
struct GNode
	{
	char *String;
	GNode *Next;
	};


///////////////////////////////////////////////////////
static bool GReleaseList(GNode *list)
	{
	GNode *p,*tmp;
	for(p=list;p!=NULL; )
		{
		tmp=p->Next;

		if(p->String!=NULL)
			{
			delete[] p->String;
			p->String=NULL;
			}

		delete p;
		p=tmp;
		}

	return true;
	}


//////////////////////////////////////////////////////
static GNode *GCreateNode(const char *string)
	{
	GNode *newnode;
	newnode=new(std::nothrow) GNode;
	if(newnode==NULL)
		{
		return NULL;
		}

	// Init all members 
	newnode->String=NULL;
	newnode->Next=NULL;

	if(string==NULL) { return newnode; }

	// Allocate space for string
	const int stringlength=MStdStrLen(string)+1;
	newnode->String=new(std::nothrow) char[stringlength];
	if(newnode->String==NULL)
		{
		delete newnode;
		return NULL;
		}


	// assign new string
	MStdStrCpy(newnode->String,string);
	newnode->Next=NULL;
	return newnode;
	}


//******************************************************
//**  MStringQueue class
//******************************************************
void MStringQueue::ClearObject(void)
	{
	mFirstNode=NULL;
	mLastNode=NULL;
	mQueueSize=0;
	}


/////////////////////////////////////////////////
MStringQueue::MStringQueue(void)
	{  ClearObject();  }


////////////////////////////////////////////////
MStringQueue::MStringQueue(bool create)
	{
	ClearObject();

	if(create==true && Create()==false)
		{
		return;
		}
	}


////////////////////////////////////////////////
MStringQueue::~MStringQueue(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MStringQueue::Create(void)
	{
	Destroy();

	mFirstNode=GCreateNode(NULL);
	if(mFirstNode==NULL)
		{
		Destroy();
		return false;
		}

	mLastNode=mFirstNode;
	mReadNode=mFirstNode;
	return true;
	}


////////////////////////////////////////////////
bool MStringQueue::Destroy(void)
	{
	GReleaseList(mFirstNode);
	ClearObject();
	return true;
	}


////////////////////////////////////////////////
bool MStringQueue::Enqueue(const char *string)
	{
	GNode *newnode=GCreateNode(string);
	if(newnode==NULL)
		{
		return false;
		}

	mLastNode->Next=newnode;
	mLastNode=newnode;
	mQueueSize = mQueueSize + 1;
	return true;
	}


////////////////////////////////////////////////
bool MStringQueue::Enqueue(const MStringQueue &queue)
	{
	GNode *start=queue.mFirstNode->Next;
	GNode *end=queue.mLastNode;
	
	GNode *p;
	for(p=start;p!=NULL;p=p->Next)
		{
		if(Enqueue(p->String)==false)
			{
			return false;
			}

		// If we have reached the end stop
		if(p==end) { break; }
		}

	return true;
	}


////////////////////////////////////////////////
bool MStringQueue::Dequeue(void)
	{
	if(mFirstNode->Next==NULL)
		{
		return false;
		}

	GNode *tmp;
	tmp=mFirstNode->Next;
	mFirstNode->Next=mFirstNode->Next->Next;

	if(tmp->String!=NULL)
		{
		delete [] tmp->String;
		tmp->String=NULL;
		}

	delete tmp;

	if(mFirstNode->Next==NULL)
		{  mLastNode=mFirstNode;  }
	
	mQueueSize=mQueueSize-1;
	return true;
	}


////////////////////////////////////////////////
int MStringQueue::GetQueueLength(void)
	{
	return mQueueSize;
	}


////////////////////////////////////////////////
const char *MStringQueue::GetFront(void)
	{
	if(mFirstNode->Next==NULL) { return NULL; }
	return mFirstNode->Next->String;
	}


//////////////////////////////////////////////
bool MStringQueue::Print(void)
	{
	MStdPrintf("MStringQueue: Queued Items=%d\n",mQueueSize) ;
	GNode *p;
	for(p=mFirstNode->Next;p!=NULL;p=p->Next)
		{
		if(p->String==NULL)
			{
			MStdPrintf("\t(NULL)\n");
			continue;
			}
	
		MStdPrintf("\t%s\n",p->String);
		}

	MStdPrintf("\n");
	return true;
	}


////////////////////////////////////////////////
bool MStringQueue::ReadReset(void)
	{
	mReadNode=mFirstNode;
	return true;
	}


////////////////////////////////////////////////
bool MStringQueue::Read(void)
	{
	if(mReadNode==NULL) { return false; }
	mReadNode=mReadNode->Next;
	if(mReadNode==NULL) { return false; }
	return true;
	}


////////////////////////////////////////////////
const char *MStringQueue::ReadGet(void)
	{
	if(mReadNode==NULL) { return NULL; }
	return mReadNode->String;
	}


////////////////////////////////////////////////
bool MStringQueue::Sort(void)
	{
	// Simple Sort Theta(n^2).  Quick, but not efficient.
	if(mFirstNode->Next==NULL) { return true; }

	GNode *p,*q;
	for(p=mFirstNode;p->Next->Next!=NULL;p=p->Next)
		{
		for(q=p->Next;q->Next!=NULL;q=q->Next)
			{
			MStdAssert(p->Next->String!=NULL);
			MStdAssert(q->Next->String!=NULL);

			if(MStdStrCmp(p->Next->String,q->Next->String)>0)
				{
				// Move the strings
				char *tmp=p->Next->String;
				p->Next->String = q->Next->String;
				q->Next->String = tmp;
				}
			}
		}
	
	// reset the current read positions
	ReadReset();
	return true;
	}


////////////////////////////////////////////////////
bool MStringQueue::IsMember(const char* str)
	{
	for (GNode* p = mFirstNode->Next; p != NULL; p = p->Next)
		{
		if(MStdStrCmp(p->String,str)==0) { return true; }
		}
	
	return false;
	}


//////////////////////////////////////////////////
bool MStringQueue::Reverse(void)
	{
	if(mLastNode==mFirstNode)
		{
		MStdAssert(mQueueSize==0);
		return true;
		}

	GNode* newlist = NULL;
	GNode* next;
	for (GNode* p = mFirstNode->Next; p != NULL; p = next)
		{
		next = p->Next;
		p->Next = newlist;
		newlist = p;
		}

	mLastNode = mFirstNode->Next;
	mFirstNode->Next= newlist;
	
	return true;
	}


