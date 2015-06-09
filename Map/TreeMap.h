/*
 * TreeMap.h
 *
 *  Created on: Jun 8, 2015
 *      Author: Raymond
 */

#ifndef TREEMAP_H_
#define TREEMAP_H_
#include "Map.h"
#include "TreeEntry.h"

class TreeMap: public Map {
public:
	TreeMap();
	virtual ~TreeMap();
	void put(const string& key, const string& value);
	bool remove(const string& key);
	Vector *find(const string& key);
	const Vector *find(const string& key) const;
	int getSize() const;

private:
	TreeEntry *root;
	int size;

	void destructorHelper(TreeEntry *entry);
	void putHelper(const string& key, const string& value, TreeEntry *entry);
	bool removeHelper(const string& key, TreeEntry *entry);
	TreeEntry *replace(TreeEntry *entry);
	TreeEntry *successor(TreeEntry *entry);
	Vector *findHelper(const string& key, TreeEntry *entry);
	const Vector *findHelper(const string& key, TreeEntry *entry) const;
};

#endif /* TREEMAP_H_ */
