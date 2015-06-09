/*
 * HashMap.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: Raymond
 */

#include "HashMap.h"
#include <string.h>

HashMap::HashMap() {
	arr = new HashEntry *[ARRAY_CAPACITY];
	memset(arr, 0, sizeof(HashEntry *) * ARRAY_CAPACITY);
	size = 0;
}

HashMap::~HashMap() {
	delete []arr;
}

void HashMap::put(const string& key, const string& value) {
	int index = hashCode(key) % ARRAY_CAPACITY;
	HashEntry *entry = arr[index];
	while (entry != NULL) {
		if (key == entry->getKey()) {
			entry->getValues().push_back(value);
			size += 1;
			return;
		}
		entry = entry->getNext();
	}
	entry = new HashEntry(key, value);
	entry->setNext(arr[index]);
	arr[index] = entry;
	size += 1;
}

bool HashMap::remove(const string& key) {
	int index = hashCode(key) % ARRAY_CAPACITY;
	HashEntry *entry = arr[index];
	if (entry == NULL) {
		return false;
	}
	if (key == entry->getKey()) {
		size -= entry->getValues().getSize();
		arr[index] = NULL;
		delete entry;
		return true;
	}
	while (entry->getNext() != NULL) {
		if (key == entry->getNext()->getKey()) {
			HashEntry *temp = entry->getNext();
			entry->setNext(temp->getNext());
			size -= temp->getValues().getSize();
			delete temp;
			return true;
		}
		entry = entry->getNext();
	}
	return false;
}

Vector *HashMap::find(const string& key) {
	int index = hashCode(key) % ARRAY_CAPACITY;
	HashEntry *entry = arr[index];
	while (entry != NULL) {
		if (key == entry->getKey()) {
			return &entry->getValues();
		}
		entry = entry->getNext();
	}
	return NULL;
}

const Vector *HashMap::find(const string& key) const {
	int index = hashCode(key) % ARRAY_CAPACITY;
	HashEntry *entry = arr[index];
	while (entry != NULL) {
		if (key == entry->getKey()) {
			return &entry->getValues();
		}
		entry = entry->getNext();
	}
	return NULL;
}

int HashMap::hashCode(const string& data) {
	int result = 17;
	for (unsigned int i = 0; i < data.length(); i += 1) {
		result = result * 31 + data[i];
	}
	return result;
}

int HashMap::getSize() const {
	return size;
}
