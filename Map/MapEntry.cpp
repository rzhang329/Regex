/*
 * MapEntry.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Raymond
 */

#include "Vector.h"
#include "MapEntry.h"

MapEntry::MapEntry(const string& inKey, const string& value) {
	key = inKey;
	values.push_back(value);
}

MapEntry::~MapEntry() {
}

const string& MapEntry::getKey() const {
	return key;
}

Vector& MapEntry::getValues() {
	return values;
}

const Vector& MapEntry::getValues() const {
	return values;
}
