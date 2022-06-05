#include <iostream>
#include "mlgbzreader.h"
using namespace std;

int main() {
	MlgbzReader bz("../wavedata/test2.vcd");
	bz.readHeader();
	bz.readVCData();
	bz.readEnd();
}
