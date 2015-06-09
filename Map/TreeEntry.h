/*
 * TreeEntry.h
 *
 *  Created on: Jun 8, 2015
 *      Author: Raymond
 */

#ifndef TREEENTRY_H_
#define TREEENTRY_H_
#include "MapEntry.h"
#include <string>

class TreeEntry: public MapEntry {
public:
	TreeEntry(const string& inKey, const string& value);
	virtual ~TreeEntry();
	TreeEntry *getLeft();
	TreeEntry *getRight();
	void setLeft(TreeEntry *inLeft);
	void setRight(TreeEntry *inRight);

private:
	TreeEntry *left;
	TreeEntry *right;
};

#endif /* TREEENTRY_H_ */
