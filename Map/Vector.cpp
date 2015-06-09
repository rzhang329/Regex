/*
 * Vector.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Raymond
 */

#include "Vector.h"
#include <stdexcept>

Vector::Vector() {
	arr = &initData[0];
	size = 0;
	capacity = INITIAL_CAPACITY;
}

Vector::Vector(const Vector& src):Vector() {
	for (int i = 0; i < src.getSize(); i += 1) {
		push_back(src.get(i));
	}
}

Vector::~Vector() {
	if (capacity > INITIAL_CAPACITY) {
		delete []arr;
	}
}

void Vector::push_back(const string& data) {
	if (size <= capacity) {
		string *temp = new string[capacity * 2];
		for (int i = 0; i < size; i += 1) {
			temp[i] = arr[i];
		}
		if (capacity > INITIAL_CAPACITY) {
			delete []arr;
		}
		arr = temp;
		capacity *= 2;
	}
	arr[size++] = data;
}

const string& Vector::get(int index) const {
	if (index < 0 || index >= size) {
		throw invalid_argument("Error. Index out of bounds.");
	}
	return arr[index];
}

int Vector::getSize() const {
	return size;
}

const string& Vector::toString() const {
	string rep = "";
	for (int i = 0; i < size; i += 1) {
		rep += arr[i] + "\n";
	}
	return rep;
}
