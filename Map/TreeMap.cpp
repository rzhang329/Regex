/*
 * TreeMap.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: Raymond
 */

#include "TreeMap.h"

TreeMap::TreeMap() {
	root = NULL;
	size = 0;
}

TreeMap::~TreeMap() {
	destructorHelper(root);
}

void TreeMap::put(const string& key, const string& value) {
	if (root == NULL) {
		root = new TreeEntry(key, value);
		size += 1;
	} else {
		putHelper(key, value, root);
	}
}

bool TreeMap::remove(const string& key) {
	if (root == NULL) {
		return false;
	}
	if (key == root->getKey()) {
		size -= root->getValues().getSize();
		root = replace(root);
		return true;
	} else {
		return removeHelper(key, root);
	}
}

Vector *TreeMap::find(const string& key) {
	return findHelper(key, root);
}

const Vector *TreeMap::find(const string& key) const {
	return findHelper(key, root);
}

int TreeMap::getSize() const {
	return size;
}

void TreeMap::destructorHelper(TreeEntry *entry) {
	if (entry != NULL) {
		destructorHelper(entry->getLeft());
		destructorHelper(entry->getRight());
		delete entry;
	}
}

void TreeMap::putHelper(const string& key, const string& value,
		TreeEntry *entry) {
	int cmp = key.compare(entry->getKey());
	if (cmp == 0) {
		entry->getValues().push_back(value);
		size += 1;
	} else if (cmp < 0) {
		if (entry->getLeft() == NULL) {
			entry->setLeft(new TreeEntry(key, value));
			size += 1;
		} else {
			putHelper(key, value, entry->getLeft());
		}
	} else {
		if (entry->getRight() == NULL) {
			entry->setRight(new TreeEntry(key, value));
			size += 1;
		} else {
			putHelper(key, value, entry->getRight());
		}
	}
}

bool TreeMap::removeHelper(const string& key, TreeEntry *entry) {
	if (key.compare(entry->getKey()) < 0) {
		if (entry->getLeft() == NULL) {
			return false;
		}
		if (key == entry->getLeft()->getKey()) {
			size -= entry->getLeft()->getValues().getSize();
			entry->setLeft(replace(entry->getLeft()));
			return true;
		} else {
			removeHelper(key, entry->getLeft());
		}
	} else {
		if (entry->getRight() == NULL) {
			return false;
		}
		if (key == entry->getRight()->getKey()) {
			size -= entry->getRight()->getValues().getSize();
			entry->setRight(replace(entry->getRight()));
			return true;
		} else {
			removeHelper(key, entry->getRight());
		}
	}
	return false;
}

TreeEntry *TreeMap::replace(TreeEntry *entry) {
	if (entry->getLeft() == NULL) {
		TreeEntry *result = entry->getRight();
		delete entry;
		return result;
	}
	if (entry->getRight() == NULL) {
		TreeEntry *result = entry->getLeft();
		delete entry;
		return result;
	}
	if (entry->getRight()->getLeft() == NULL) {
		TreeEntry *result = entry->getRight();
		result->setLeft(entry->getLeft());
		delete entry;
		return result;
	}
	TreeEntry *result = successor(entry->getRight());
	result->setLeft(entry->getLeft());
	result->setRight(entry->getRight());
	delete entry;
	return result;
}

TreeEntry *TreeMap::successor(TreeEntry *entry) {
	if (entry->getLeft()->getLeft() == NULL) {
		TreeEntry *result = entry->getLeft();
		entry->setLeft(replace(entry->getLeft()));
		return result;
	}
	return successor(entry->getLeft());
}

Vector *TreeMap::findHelper(const string& key, TreeEntry *entry) {
	if (entry == NULL) {
		return NULL;
	}
	int cmp = key.compare(entry->getKey());
	if (cmp == 0) {
		return &entry->getValues();
	} else if (cmp < 0) {
		return findHelper(key, entry->getLeft());
	} else {
		return findHelper(key, entry->getRight());
	}
}

const Vector *TreeMap::findHelper(const string& key, TreeEntry *entry) const {
	if (entry == NULL) {
		return NULL;
	}
	int cmp = key.compare(entry->getKey());
	if (cmp == 0) {
		return &entry->getValues();
	} else if (cmp < 0) {
		return findHelper(key, entry->getLeft());
	} else {
		return findHelper(key, entry->getRight());
	}
}
