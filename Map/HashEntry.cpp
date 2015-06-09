/*
 * HashEntry.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: Raymond
 */

#include "HashEntry.h"

HashEntry::HashEntry(const string& inKey, const string& value):
		MapEntry(inKey, value) {
	next = NULL;
}

HashEntry::~HashEntry() {
}

HashEntry *HashEntry::getNext() {
	return next;
}

void HashEntry::setNext(HashEntry *inNext) {
	next = inNext;
}
