/*
 * Vector.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Raymond
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include <string>
using namespace std;

class Vector {
public:
	Vector();
	Vector(const Vector& src);
	virtual ~Vector();
	void push_back(const string& data);
	const string& get(int index) const;
	int getSize() const;
	const string& toString() const;

private:
	static const int INITIAL_CAPACITY = 10;
	string *arr;
	string initData[INITIAL_CAPACITY];
	int size;
	int capacity;
};

#endif /* VECTOR_H_ */
