#include "BigQ.h"

void *workerThread(void *temp);
BigQ::BigQ() {
}
BigQ :: BigQ (Pipe &in, Pipe &out, OrderMaker &sortorder, int runlen) {
	runLen = runlen;
	inPipe = &in;
	outPipe = &out;
	sortOrder = &sortorder;
	pthread_create(&wthread, NULL, &workerThread, (void *)this);
cout<< "Pradeep: " << __func__ << ":" <<__LINE__;
}

BigQ::~BigQ () {
	pthread_join (wthread, NULL);
}

void BigQ :: StartProcessing(void)
{
cout<< "Pradeep: " << __func__ << ":" <<__LINE__;
	Record *currRecord;
	priority_queue<Record*, vector<Record*>, BigQ> sortedRecsPQ;
	while (true) {
		cout<< "Pradeep: " << __func__ << ":" <<__LINE__;
		currRecord = new Record();
		if (!(inPipe->Remove(currRecord))) {
			break;
		}
		sortedRecsPQ.push(currRecord);
	}

	while (!sortedRecsPQ.empty()) {
cout<< "Pradeep: " << __func__ << ":" <<__LINE__;
		currRecord = sortedRecsPQ.top();
		outPipe->Insert (currRecord);
	}
cout<< "Pradeep: " << __func__ << ":" <<__LINE__;
	outPipe->ShutDown ();
}

void *workerThread(void *temp)
{
cout<< "Pradeep: " << __func__ << ":" <<__LINE__;
	BigQ *bigQ= (BigQ *)temp;
	bigQ->StartProcessing();
}
