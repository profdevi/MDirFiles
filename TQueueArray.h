//v1.2 copyright Comine.com 20170625U1013
#ifndef TQueueArray_h
#define TQueueArray_h

////////////////////////////////////////////
#include "MStdLib.h"
#include "TVector.h"
#include "TAutoPtr.h"

/*
	Class implements a  queue of references pointers implemented in a fixed
	size array.
*/
////////////////////////////////////////////
template <class ItemClass>
class TQueueArray
	{
	TVector<TAutoPtr<ItemClass> > mArray;					
	int mFrontIndex;							// Current Index of the front
	int mLength;								// Length of Queue

	/////////////////////////////////////////
	void ClearObject(void)
		{
		mFrontIndex=0;
		mLength=0;
		}

	public:
	/////////////////////////////////////////
	TQueueArray(void)
		{  ClearObject();  }


	/////////////////////////////////////////
	explicit TQueueArray(int count)
		{
		ClearObject();
		if(Create(count)==false)
			{
			return;
			}
		}


	/////////////////////////////////////////
	~TQueueArray(void)
		{  Destroy();  }


	///////////////////////////////////////
	bool Create(int count)
		{
		Destroy();

		if(mArray.Create(count)==false)
			{
			Destroy();
			return false;
			}

		mFrontIndex=0;
		mLength=0;

		return true;
		}


	////////////////////////////////////////
	bool Destroy(void)
		{
		mArray.Destroy();
		ClearObject();
		return true;
		}


	///////////////////////////////////////
	int GetMaxCapacity(void) 
		{
		return mArray.GetCount();
		}


	///////////////////////////////////////
	int GetLength(void)
		{
		return mLength;
		}


	//////////////////////////////////////////////
	ItemClass *Get(int index)
		{
		MStdAssert(index>=0 && index<mLength );
		const int arraylength=mArray.GetCount();
		return mArray[(mFrontIndex+index)%arraylength].Get();
		}


	////////////////////////////////////////////////
	// Add item to end at mArray[mcCount]
	ItemClass *EnqueueBack(void)
		{
		const int arraylength=mArray.GetCount();
		if(mLength>=arraylength)
			{
			return NULL;
			}

		const int backindex=(mFrontIndex+mLength)%arraylength;

		if(mArray[backindex].Create()==false)
			{
			return NULL;
			}

		ItemClass *newitem=mArray[backindex].Get();
		MStdAssert(newitem!=NULL);

		mLength=mLength+1;
		return newitem;
		}


	////////////////////////////////////////////////
	// Add item to front of Queue
	ItemClass *EnqueueFront(void)
		{
		const int arraylength=mArray.GetCount();
		if(mLength>=arraylength)
			{
			return NULL;
			}

		mFrontIndex=(mFrontIndex+arraylength-1) % arraylength;
		mLength=mLength+1;

		if(mArray[mFrontIndex].Create()==false)
			{
			mFrontIndex=(mFrontIndex+1) % arraylength;
			return NULL;
			}

		ItemClass *newitem=mArray[mFrontIndex].Get();
		MStdAssert(newitem!=NULL);

		return newitem;
		}


	////////////////////////////////////////////////
	// Add item to end at mArray[mcCount]
	bool DequeueBack(void)
		{
		if(mLength<=0)
			{
			return false;
			}

		const int arraylength=mArray.GetCount();
		
		mLength=mLength-1;
		const int backindex=(mFrontIndex+mLength)%arraylength;

		mArray[backindex].Destroy();

		MStdAssert(mArray[backindex].Get()==NULL);
		
		return true;
		}


	////////////////////////////////////////////////
	bool DequeueFront(void)
		{
		if(mLength<=0)
			{
			return false;
			}

		const int arraylength=mArray.GetCount();
		mArray[mFrontIndex].Destroy();
		MStdAssert(mArray[mFrontIndex].Get()==NULL);

		mFrontIndex = (mFrontIndex + 1) % arraylength;
		mLength=mLength-1;
		return true;
		}

	};

#endif //TQueueArray_h

