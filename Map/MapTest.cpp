
#include "Map.h"
#include "HashMap.h"
#include "TreeMap.h"
#include <iostream>

string key[5];
string value[5];

void setStrings() {
	key[0] = "George";
	value[0] = "Washington";
	key[1] = "John";
	value[1] = "Adams";
	key[2] = "Thomas";
	value[2] = "Jefferson";
	key[3] = "James";
	value[3] = "Madison";
	key[4] = "James";
	value[4] = "Monroe";
}

void testPut(Map *map) {
	map->put(key[0], value[0]);
	map->put(key[1], value[1]);
	map->put(key[2], value[2]);
	map->put(key[3], value[3]);
	map->put(key[4], value[4]);
	cout << map->getSize() << endl;
}

void testFind(Map *map) {
	cout << map->find(key[0])->get(0) << endl;
	cout << map->find(key[1])->get(0) << endl;
	cout << map->find(key[2])->get(0) << endl;
	cout << map->find(key[3])->get(0) << endl;
	cout << map->find(key[4])->get(1) << endl;
	cout << map->getSize() << endl;
}

void testRemove(Map *map) {
	map->remove(key[0]);
	cout << map->getSize() << endl;
	map->remove(key[3]);
	cout << map->getSize() << endl;
	map->remove(key[1]);
	map->remove(key[2]);
	cout << map->getSize() << endl;
}

int main() {
	Map *hash = new HashMap();
	Map *tree = new TreeMap();
	setStrings();
	testPut(hash);
	testFind(hash);
	testRemove(hash);
	testPut(tree);
	testFind(tree);
	testRemove(tree);
	delete hash;
	delete tree;
}
