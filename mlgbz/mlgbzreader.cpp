#include "mlgbzreader.h"
#include "bzutil.h"
#include "vcdata.h"
#include <map>
#include <DigitalType.h>

MlgbzReader::MlgbzReader(std::string infile)
	: _reader(infile)
{
	std::string outfile = infile + ".out";

	_fpout = fopen(outfile.data(), "w");
	bzzert(_fpout, "output out file open error");
}

void MlgbzReader::readHeader()
{
	_reader.readHeader();

	if (_fpout) {
    fprintf(_fpout, "$date\n %s\n$end\n", _reader.getDate().data());
    fprintf(_fpout, "$version\n %s\n$end\n", _reader.getVersion().data());
    fprintf(_fpout, "$timescale\n %s\n $end\n", _reader.getTimeScale().data());

    std::vector<Scope*> topscopes;
    _reader.topScopes(topscopes);
    for (unsigned i = 0; i < topscopes.size(); ++i) {
      dumpScopeInfo(topscopes[i]);
			fprintf(_fpout, "$upscope $end\n");
    }
    fprintf(_fpout, "$enddefinitions $end\n\n");
	}
}

void MlgbzReader::readVCData()
{
	_reader.beginReadTimeData();

  while (!_reader.isDataFinished()) {
    _reader.readNextPointData();

    long long time = _reader.getVCTime();
    const std::vector<std::string> &vcDatas = _reader.getVCValues();

		dumpTimeVCDatas(time, vcDatas);
  }
}

void MlgbzReader::readEnd()
{
	fclose(_fpout);
}

std::string MlgbzReader::varTypeToString(int type)
{
	switch (type) {
	case REG:				return "reg";

	case UWIRE:			return "uwire";
	case WIRE:			return "wire";

	case TRI:				return "tri";
	case TRI0:			return "tri0";
	case TRI1:			return "tri1";
	case TRIAND:		return "triand";
	case TRIOR:			return "trior";
	case TRIREG:		return "trireg";

	case SUPPLY0:		return "supply0";
	case SUPPLY1:		return "supply1";

	case WAND:			return "wand";
	case WOR:				return "wor";
	case INTEGER:		return "integer";
	case PARAMETER:	return "parameter";
	case REAL:			return "real";
	case TIME:			return "time";
	case EVENT:			return "event";
	
	default: bzzert(0, "varType error"); return "";
	}
}

void MlgbzReader::dumpScopeInfo(Scope *scope) {
	bzzert(scope, "scope empty");

	// output scope info
  fprintf(_fpout, "$scope %s %s $end\n", scope->type().c_str(), scope->name().c_str());

  const std::map<std::string, std::string>& vars = scope->getVars();
  std::map<std::string, std::string>::const_iterator it;

	// output vars info
  for (it = vars.cbegin(); it != vars.cend(); ++it) {
    std::string varName = (*it).first;
    std::string symbol = (*it).second;
    std::string type = varTypeToString(scope->getSignalType(varName));
    int width = scope->getSignalBus(varName);

    fprintf(_fpout, "$var %s %d %s %s $end\n", type.data(), width, symbol.data(), varName.data());

		_symbolWidthMap[symbol] = width;
  }

  // get sub socpes info
  const std::vector<Scope*> &subscopes = scope->getSubScopes();
  for (unsigned i = 0; i < subscopes.size(); ++i) {
    dumpScopeInfo(subscopes[i]);
		fprintf(_fpout, "$upscope $end\n");
  }
}

void MlgbzReader::dumpTimeVCDatas(long long time, const std::vector<std::string> &vcDatas)
{
	// fprintf(_fpout, "#%lld\n", time);
	std::vector<std::string> symbol;
	std::vector<std::string> value;

	VCData vcdata(time);
	for (unsigned i = 0; i < vcDatas.size(); i++) {
		// fprintf(stdout, "%s %lu\n", vcDatas[i].data(), vcDatas[i].size());
		vcdata.add(vcDatas[i]);
		// fprintf(_fpout, "%s\n", vcDatas[i].data());
	}
	vcdata.out(_fpout);
}
