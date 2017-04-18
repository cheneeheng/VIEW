/*
 * util.h
 *
 *  Created on: Jan 6, 2017
 *      Author: chen
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "dataDeclaration.h"
#include "algo.h"
#include "vtkExtra.h"

void parseData2Point(
	vector<vector<string> > data_full,
	vector<point_t> &points);

int fileSelect(
	const struct dirent *entry);

void readFile(
	const char *name,
	vector<vector<string> > &data_full,
	char delimiter);


#endif /* UTIL_H_ */
