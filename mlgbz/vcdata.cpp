#include "vcdata.h"
#include "bzutil.h"
#include <cstdlib>
#include <sstream>
#include <iterator>

#define TESTVCData 0
#if TESTVCData
#include <iostream>
#endif

void VCData::add(std::string vcdata)
{
	bzzert(vcdata.size() > 0, "vcdata empty");

	// array
	if (vcdata[0] == 'b') {
		int pos = vcdata.find(" ");

#if TESTVCData && 1
		std::cout << vcdata.substr(pos + 1) << std::endl;
		std::cout << vcdata.substr(1, pos - 1) << std::endl;
#endif

		addSymbol(vcdata.substr(pos + 1));
		addValue(vcdata.substr(1, pos - 1));
	}
	// single digit
	else {
#if TESTVCData && 1
		std::cout << vcdata.substr(1) << std::endl;
		std::cout << vcdata.substr(0, 1) << std::endl;
#endif
		
		addSymbol(vcdata.substr(1));
		addValue(vcdata.substr(0, 1));
	}
#if TESTVCData && 1
	std::cout << _value.data() << std::endl;
#endif
}

void VCData::out(FILE *fpout)
{
	fprintf(fpout, "#%lld\n", _time);
	for (unsigned i = 0; i < _symbol.size(); i++) {
		fprintf(fpout, "%s ", _symbol[i].data());
	}
	fprintf(fpout, "\n%s\n", _value.data());
}

void VCData::parse(std::ifstream &fpin,
		std::map<std::string, int> &vars, std::vector<std::string> &vcdata)
{
	// std::string time;
	std::string symbolline;
	std::string dataline;
	// std::getline(fpin, time);
	std::getline(fpin, symbolline);
	std::getline(fpin, dataline);

#if TESTVCData && 0
	// std::cout << time << std::endl;
	std::cout << symbolline << std::endl;
	std::cout << dataline.size() << std::endl;
#endif

	// _time = strtoll(time.substr(1).data(), NULL, 10);
	// vcdata.push_back("#" + std::to_string(_time));

	std::stringstream symbolss(symbolline);
	std::istream_iterator<std::string> begin(symbolss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> symbolvec(begin, end);

	long long datapos = 0;
	unsigned dataidx = datapos / _gmod;
	unsigned databias = datapos % _gmod * _gbias;

	for (unsigned i = 0; i < symbolvec.size(); i++) {
		int width = vars[symbolvec[i]];
		// bzzert(width > 0, "data width error");
		if (width <= 0) continue;

		bool isend = false;
		if (width == 1) {
			vcdata.push_back(
					std::string(
						1, binary2value(
							dataline[dataidx] >> databias & ((1 << _gbias) - 1), isend
							)
						) + symbolvec[i]
					);

			datapos++;
			dataidx = datapos / _gmod;
			databias = datapos % _gmod * _gbias;
		}
		else {
			std::string data;
			for (unsigned j = 0; j < width; j++) {
				data += binary2value(dataline[dataidx] >> databias & ((1 << _gbias) - 1), isend);

				datapos++;
				dataidx = datapos / _gmod;
				databias = datapos % _gmod * _gbias;

				if (isend) break;
			}

			vcdata.push_back("b" + data + " " + symbolvec[i]);
		}
	}
}

void VCData::addSymbol(std::string symbol)
{
	_symbol.push_back(symbol);
}

void VCData::addValue(std::string value)
{
	for (unsigned i = 0; i < value.size(); i++) {
		long long bias = _vlength++ % _gmod * _gbias;
		if (bias == 0)
			_value.push_back(64);

		std::string::iterator it = _value.end() - 1;
		if (i == value.size() - 1)
			*it += (value2binary(value[i]) + 0x04) << bias;
		else
			*it += value2binary(value[i]) << bias;
	}
}

char VCData::value2binary(char v)
{
	switch (v) {
	case '0': return 0;
	case '1': return 1;
	case 'x': return 2;
	case 'z': return 3;

	default:
		printf("%d %c\n", v, v);
		bzzert(0, "vcdata value error"); return 4;
	}
}

char VCData::binary2value(char v, bool &isend)
{
	isend = (v >> 2) & 1 ? true : false;

	switch (v) {
	case 0: return '0';
	case 1: return '1';
	case 2: return 'x';
	case 3: return 'z';

	case 4: return '0';
	case 5: return '1';
	case 6: return 'x';
	case 7: return 'z';

	default: bzzert(0, "vcdata value error"); return 0;
	}
}
