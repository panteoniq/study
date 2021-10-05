/*
 * struct.h
 *
 *  Created on: 2021. 9. 25.
 *      Author: dhjeong
 */

#ifndef RAIIANDMEM_STRUCT_H_
#define RAIIANDMEM_STRUCT_H_

#include <boost/shared_ptr.hpp>
#include <iostream>

class DataInfo {
public:
	DataInfo() {
		size = 0;
		permission = 0;
	}

	DataInfo(const std::string &sName, size_t sSize, int sPermission) {
		name = sName;
		size = sSize;
		permission = sPermission;
	}

	~DataInfo() {
		std::cout << "Destroy " << name << std::endl;
	}

	std::string name;
	size_t size;
	int permission;
};

class A {
	int *data;
	std::shared_ptr<A> other;

public:
	A() {
		data = new int[100];
		std::cout << "자원을 획득함!" << std::endl;
	}

	~A() {
		std::cout << "소멸자 호출!" << std::endl;
		delete[] data;
	}

	void set_other(std::shared_ptr<A> o) {
		other = o;
	}

	int getCount() {
		return other.use_count();
	}
};

#endif /* RAIIANDMEM_STRUCT_H_ */
