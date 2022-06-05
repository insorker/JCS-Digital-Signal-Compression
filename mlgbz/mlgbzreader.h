#ifndef MlgbzReader_H
#define MlgbzReader_H

#include <string>
#include <vector>
#include <map>
#include <WaveformReaderForCompetition.h>

class MlgbzReader {
public:
	MlgbzReader(std::string infile);

	void readHeader();
	void readVCData();
	void readEnd();

private:
	std::string varTypeToString(int type);
	void dumpScopeInfo(Scope* scope);
	void dumpTimeVCDatas(long long time, const std::vector<std::string> &vsDatas);

private:
	FILE *_fpout;

	WaveformReaderForCompetition _reader;
	std::map<std::string, int> _symbolWidthMap;
};

#endif
