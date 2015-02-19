#ifndef BIGQ_H
#define BIGQ_H
#include <pthread.h>
#include <iostream>
#include "Pipe.h"
#include "File.h"
#include "Record.h"
#include <queue>
#include <iomanip>

using namespace std;

class BigQ {
	int runLen;
	Pipe *inPipe, *outPipe;
	OrderMaker *sortOrder;
	pthread_t wthread;
	ComparisonEngine ceng;
public:
	BigQ();
	BigQ (Pipe &in, Pipe &out, OrderMaker &sortorder, int runlen);
	~BigQ ();
	bool operator()(void *firstRec, void *secRec)
	{
		Record *r1 = (Record *) firstRec;
		Record *r2 = (Record *) secRec;
		if (ceng.Compare(r1, r2, sortOrder) == 1)
			return true;
		return false;
    	}
	void StartProcessing(void);
};

#endif
