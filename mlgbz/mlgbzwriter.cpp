#include "mlgbzwriter.h"
#include "bzutil.h"
#include "vcdata.h"
#include <sstream>
#include <iostream>

MlgbzWriter::MlgbzWriter(std::string infile)
	: _fpvcd(infile), _fpout(infile + ".cp", std::ios::out)
{
}

void MlgbzWriter::writeHeader()
{
	std::string line;

	while (1) {
		std::getline(_fpvcd, line);
		_fpout << line << "\n";

		if (line == "$enddefinitions $end") {
			break;
		}
		else if (line.size() > 4 && line.substr(0, 4) == "$var") {
			std::istringstream iss(line);
			std::string s;
			std::string symbol;
			int width;

			for (int i = 0; iss >> s && i < 4; i++) {
				if (i == 2) width = atoi(s.data());
				if (i == 3) symbol = s;
			}
			
			_vars[symbol] = width;
		}
	}
}

void MlgbzWriter::writeHeader(std::map<std::string, int> varChosen)
{
	std::string line;

	while (1) {
		std::getline(_fpvcd, line);
		_fpout << line << "\n";

		if (line == "$enddefinitions $end") {
			break;
		}
		else if (line.size() > 4 && line.substr(0, 4) == "$var") {
			std::istringstream iss(line);
			std::string s;
			std::string symbol;
			int width;

			for (int i = 0; iss >> s && i < 4; i++) {
				if (i == 2) width = atoi(s.data());
				if (i == 3) symbol = s;
			}
			
			if (varChosen[symbol])
				_vars[symbol] = width;
		}
	}
}

void MlgbzWriter::writeVCData()
{
	std::string line;

	while (std::getline(_fpvcd, line), line[0] != '#');

	while (!_fpvcd.eof()) {
		bzzert(line[0] == '#', "vcdata time error");
		_fpout << line << "\n";

		VCData vcdata(0);
		std::vector<std::string> vcdatavec;
		vcdata.parse(_fpvcd, _vars, vcdatavec);
		for (unsigned i = 0; i < vcdatavec.size(); i++) {
			_fpout << vcdatavec[i] << "\n";
		}

		while (std::getline(_fpvcd, line), line[0] != '#') {
			writeEnd();
			bzzert(0, "time error");
		}
	}
}

void MlgbzWriter::writeEnd()
{
	_fpvcd.close();
	_fpout.close();
}
