//v1.11 copyright Comine.com 20190829R0103
#ifndef MStringQueue_h
#define MStringQueue_h

//******************************************************
//**  MStringQueue class
//******************************************************
class MStringQueue
	{
	////////////////////////////////////////////////
	int mQueueSize;							// Number of Queued Items
	struct GNode *mFirstNode;				// Always points to a dummy node
	struct GNode *mLastNode;				// Last Node in list
	struct GNode *mReadNode;				// Current Read Node

	////////////////////////////////////////////////
	void ClearObject(void);
	
	////////////////////////////////////////////////
	public:
	MStringQueue(void);
	explicit MStringQueue(bool create);
	~MStringQueue(void);
	bool Create(void);
	bool Destroy(void);
	bool Enqueue(const char *string);
	bool Enqueue(const MStringQueue &queue);
	bool Dequeue(void);
	int GetQueueLength(void);
	const char *GetFront(void);					// Returns first item in List
	bool Print(void);							// Print out the Queue

	// Reader Code
	bool ReadReset(void);
	bool Read(void);
	const char *ReadGet(void);

	// Extra Operations
	bool Sort(void);							// Sort in Alphabetical Order + Will Reset the read
	bool IsMember(const char *str);				// Check if queue contains member
	bool Reverse(void);							// Reverse the queue
	};

#endif // MStringQueue_h

