#include <iostream>
#include "mlgbzreader.h"
using namespace std;

void help()
{
	cout << "请输入.vcd文件名" << endl;
}

int main(int argc, char **argv)
{
	if (argc == 1) {
		help();
		return 1;
	}

	MlgbzReader bz(argv[1]);
	bz.readHeader();
	bz.readVCData();
	bz.readEnd();
}
