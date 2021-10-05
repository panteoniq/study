/*
 * WeakPtr.h
 *
 *  Created on: 2021. 9. 25.
 *      Author: dhjeong
 */

#ifndef RAIIANDMEM_WEAKPTR_H_
#define RAIIANDMEM_WEAKPTR_H_

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "struct.h"


class WeakPtr {
public:
	WeakPtr();
	virtual ~WeakPtr();

	void run();
	void inside(boost::shared_ptr<DataInfo> &sharedPtr, boost::weak_ptr<DataInfo> weakPtr);
};

#endif /* RAIIANDMEM_WEAKPTR_H_ */
