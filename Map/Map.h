/*
 * Map.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Raymond
 */

#ifndef MAP_H_
#define MAP_H_
#include "Vector.h"
#include <string>

class Map {
public:
	virtual ~Map() {
	}
	virtual void put(const string& key, const string& value) = 0;
	virtual bool remove(const string& key) = 0;
	virtual Vector *find(const string& key) = 0;
	virtual const Vector *find(const string& key) const = 0;
	virtual int getSize() const = 0;
};

#endif /* MAP_H_ */
