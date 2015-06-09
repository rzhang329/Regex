/*
 * TreeEntry.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: Raymond
 */

#include "TreeEntry.h"

TreeEntry::TreeEntry(const string& inKey, const string& value):
		MapEntry(inKey, value) {
	left = NULL;
	right = NULL;
}

TreeEntry::~TreeEntry() {
}

TreeEntry *TreeEntry::getLeft() {
	return left;
}

TreeEntry *TreeEntry::getRight() {
	return right;
}

void TreeEntry::setLeft(TreeEntry *inLeft) {
	left = inLeft;
}

void TreeEntry::setRight(TreeEntry *inRight) {
	right = inRight;
}
