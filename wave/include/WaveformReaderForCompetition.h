#ifndef LIBREADER_WAVEFORMREADERFORCOMPETITION_H_
#define LIBREADER_WAVEFORMREADERFORCOMPETITION_H_

#include <string>
#include <map>
#include <set>

typedef std::set<std::string> SignalSymbolSet;

class DigitalWaveForm;
class Scope;
class TimeValue;

class WaveformReaderForCompetition {
 public:
  WaveformReaderForCompetition(const std::string& fileName);   

  ~WaveformReaderForCompetition();

  void read();

  void getAllTranValues(std::vector<TimeValue*>& tranTimes);

  void topScopes(std::vector<Scope*> &scopes); 

  void getSignalName(std::string symbol,
      std::vector<std::string> &sigNames);
  
  void readAllSignalDatas(std::map<long long, std::vector<std::string> > &sigDatas);

  void readSignalDatas(const std::set<std::string> &selectedSignal,
      long long startTime, long long endTime,
      std::map<long long, std::vector<std::string> > &sigDatas);

  void dumpVCDFile(const std::string &outfile);

 private:
  DigitalWaveForm * _wavePtr;
};


#endif  /// LIBREADER_WAVEFORMREADERFORCOMPETITION_H_
