/*
 * HashMap.h
 *
 *  Created on: Jun 8, 2015
 *      Author: Raymond
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_
#include "Map.h"
#include "HashEntry.h"

class HashMap: public Map {
public:
	HashMap();
	virtual ~HashMap();
	void put(const string& key, const string& value);
	bool remove(const string& key);
	Vector *find(const string& key);
	const Vector *find(const string& key) const;
	int getSize() const;

private:
	static const int ARRAY_CAPACITY = 100;
	HashEntry **arr;
	int size;

	static int hashCode(const string& key);
};

#endif /* HASHMAP_H_ */
