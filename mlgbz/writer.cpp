#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stdlib.h>
#include "mlgbzwriter.h"
using namespace std;

void help()
{
	cout << "help" << endl;
}

int main(int argc, char **argv)
{
	if (argc <= 1) {
		help();
		return 1;
	}
	
	if (argc == 2) {
		cout << "all" << endl;

	// MlgbzWriter writer("../wavedata/test2.vcd.out", MlgbzWriter::ALL);
		MlgbzWriter writer(argv[1]);
		writer.writeHeader();
		writer.writeVCData();
		writer.writeEnd();
	}
	else if (argc == 3) {
		cout << "part" << endl;

		MlgbzWriter writer(argv[1]);
		ifstream ifs(argv[2]);
		map<string, int> varChosen;
		string line;
		while (!ifs.eof() && getline(ifs, line)) {
			varChosen[line] = 1;
			cout << line << endl;
		}

		writer.writeHeader(varChosen);
		writer.writeVCData();
		writer.writeEnd();
	}
	else help();
}
