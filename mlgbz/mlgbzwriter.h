#ifndef MLGBZWRITER_H
#define MLGBZWRITER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

class MlgbzWriter
{
public:
	MlgbzWriter(std::string infile);

	void add();
	void writeHeader();
	void writeVCData();
	void writeHeader(std::map<std::string, int> varChosen);
	void writeEnd();
	
private:
	std::ifstream _fpvcd;
	std::ofstream _fpout;
	std::map<std::string, int> _vars;
};

#endif
