/*
 * HashEntry.h
 *
 *  Created on: Jun 8, 2015
 *      Author: Raymond
 */

#ifndef HASHENTRY_H_
#define HASHENTRY_H_
#include "MapEntry.h"
#include <string>

class HashEntry: public MapEntry {

public:
	HashEntry(const string& inKey, const string& value);
	virtual ~HashEntry();
	HashEntry *getNext();
	void setNext(HashEntry *inNext);

private:
	HashEntry *next;
};

#endif /* HASHENTRY_H_ */
