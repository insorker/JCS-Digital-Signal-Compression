#ifndef VCDATA_H
#define VCDATA_H

#include <vector>
#include <string>
#include <map>
#include <fstream>

class VCData {
public:
	VCData(long long time)
		: _time(time), _vlength(0) { };

	void add(std::string vcdata);
	void out(FILE *fpout);
	void parse(std::ifstream &fpin, 
			std::map<std::string, int> &vars, std::vector<std::string> &vcdata);

private:
	void addSymbol(std::string symbol);
	void addValue(std::string value);
	char value2binary(char v);
	char binary2value(char v, bool &isend);

	long long _time;
	long long _vlength;
	std::vector<std::string> _symbol;
	std::string _value;

	static const int _gmod = 2;
	static const int _gbias = 3;
};

#endif
