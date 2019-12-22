//v1.19 copyright Comine.com 20180626T1146
#ifndef MStringList_h
#define MStringList_h

///////////////////////////////////////////////////
class MStringList
	{
	/////////////////////////////////////////////
	struct GNode *mFirstNode;
	struct GNode *mLastNode;
	struct GNode *mCurrent;
	int mCount;

	//////////////////////////////////////////////
	void ClearObject(void);

	//////////////////////////////////////////////
	public:
	MStringList(void);
	MStringList(bool create);
	MStringList(MStringList &reflist);	// Initialize from another list
	~MStringList(void);
	bool Create(void);
	bool Create(MStringList &reflist);	// Initialize from another list
	bool Destroy(void);
	bool AddString(const char *string); // Add to the end of the list
	bool AddList(MStringList &list);	// Add existing list
	bool ReadReset(void);				// Will Reset to the first item again
	const char *ReadString(void);		// Read a string untill NULL
	bool IsMember(const char *string,bool casematch=true);	// Check if string is a member
	int GetCount(void);					// Get Count of strings
	bool Remove(const char *string);	// Remove the string from list
	bool Swap(MStringList &list);		// Swap Two Lists
	bool Print(void);					// Print out strings
	};

#endif // MStringList_h

