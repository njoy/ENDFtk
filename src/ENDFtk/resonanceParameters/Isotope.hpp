class Isotope {
  double zai;
  double abn;
  int lfw;
  std::vector< EnergyRange > ranges;

  #include "ENDFtk/resonanceParameters/Isotope/src/readRanges.hpp"
  
public:
  #include "ENDFtk/resonanceParameters/Isotope/src/ctor.hpp"

  double ZAI() const { return this->zai; }
  double ABN() const { return this->abn; }
  int LFW() const { return this->lfw; }
  int NER() const { return this->ranges.size(); }

  auto energyRanges() const {
    return ranges::make_iterator_range( this->ranges.begin(),
                                        this->ranges.end() );
  }
};
