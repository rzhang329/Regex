/*
 * MapEntry.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Raymond
 */

#ifndef MAPENTRY_H_
#define MAPENTRY_H_
#include "Vector.h"
#include <string>

class MapEntry {
public:
	MapEntry(const string& inKey, const string& value);
	virtual ~MapEntry();
	const string& getKey() const;
	Vector& getValues();
	const Vector& getValues() const;

private:
	string key;
	Vector values;
};

#endif /* MAPENTRY_H_ */
