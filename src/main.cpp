/*
 * main.cpp
 *
 *  Created on: Dec 6, 2010
 *      Author: papazov
 */


#include "dataDeclaration.h"
#include "algo.h"
#include "util.h"
#include "vtkExtra.h"

string DATADIR = "../../KINECT/recording/";

// ============================================================================
// >>>>> MAIN <<<<<
// ============================================================================
int main(int argc, char *argv[])
{

	vector<int> 				file_eof;
	vector<point_t> 			points;
	vector<vector<string> > 	data_full;

	// [READ FILE]*************************************************************
	struct dirent **namelist;
	string name;
	string dir_name;
	dir_name = DATADIR;
	int n = scandir(dir_name.c_str(), &namelist, fileSelect, alphasort);
	//for(int i=0;i<n;i++)
	{
		name = dir_name + namelist[n-1]->d_name;
		readFile(name.c_str(), data_full , ',');
		file_eof.push_back(data_full.size());

		//table
		vector<string> last_line = data_full[data_full.size()-1];
	}
	printf("Reading data......Complete\n");
	// *************************************************************[READ FILE]
	// [PARSE DATA]************************************************************
	int num_points = data_full.size();
	reshapeVector(points, num_points);
	parseData2Point(data_full, points);
	for(int i=0;i<num_points;i++)
		if(atoi(data_full[i][1].c_str())==1)
			points[i].cluster_id=0;			
	printf("Parsing training data......Complete\n");
	// ************************************************************[PARSE DATA]

	vector<unsigned char*> color_code(12);
	for(int j=0;j<12;j++) color_code[j] = Calloc(unsigned char,3);
	colorCode(color_code);
	vector<string>  label_; label_.resize(2);
	showData(points, label_, color_code, true, false);

	return 0;
}
