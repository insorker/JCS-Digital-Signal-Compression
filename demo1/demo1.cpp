#include "DigitalType.h"
#include "WaveformOutputterForCompetition.h"
#include "WaveformReaderForCompetition.h"

#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void dumpScopeInfo(Scope &scope) {
	const map<string, string> &vars = scope.getVars();
	map<string, string>::const_iterator varit;

	for (varit = vars.begin(); varit != vars.end(); ++varit) {
		string varName = (*varit).first;
		string symbol  = (*varit).second;
		int type  = scope.getSignalType(varName);
		int width = scope.getSignalBus(varName);

		cout << "varName: " << varName << endl;
		cout << "symbol:  " << symbol << endl;
		cout << "type:    " << type << endl;
		cout << "width:   " << width << endl;
		cout << endl;
	}
}

int main(int argc, char** argv) {
	int opt, dump = 0;
	string file;

	while ((opt = getopt(argc, argv, "df:")) != -1) {
		switch (opt) {
		case 'd':
			dump = 1;
			break;
		case 'f':
			file = optarg;
			break;
		}
	}

	WaveformReaderForCompetition reader(file);
	reader.read();

	if (dump) {
		vector<Scope *> scopes;
		reader.topScopes(scopes);

		for (int i = 0; i < scopes.size(); i ++ ) {
			dumpScopeInfo(*scopes[i]);
		}
	}
	
	vector<TimeValue *> tranTimes;
	reader.getAllTranValues(tranTimes);

	for (unsigned i = 0; i < 1; i ++ ) {
		long long t = tranTimes[i]->time();
		const vector<Signal *> &sigValues = tranTimes[i]->allSignals();

		for (unsigned j = 0; j < sigValues.size(); j ++ ) {
			string valStr = sigValues[j]->_valStr;

			cout << valStr << endl;
		}
	}
}
