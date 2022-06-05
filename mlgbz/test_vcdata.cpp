#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include "vcdata.h"
using namespace std;

int main() {
	VCData vcd(0);
	FILE *fp = fopen("test-vcdata.txt", "w");
	if (!fp) {
		cout << "error" << endl;
		return 1;
	}

	map<string, int> vars;

	vcd.add("0%");
	vcd.add("0,");
	vcd.add("1!");
	vcd.add("b011101001101 $");
	vars["%"] = 1;
	vars[","] = 1;
	vars["!"] = 1;
	vars["$"] = 12;
	vcd.out(fp);
	fclose(fp);

	ifstream ifs("test-vcdata.txt");
	vector<string> vcdata;
	vcd.parse(ifs, vars, vcdata);
	for (int i = 0; i < vcdata.size(); i++) {
		cout << vcdata[i] << endl;
	}
}
