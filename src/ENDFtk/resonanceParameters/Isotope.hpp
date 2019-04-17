class Isotope {
  std::vector< EnergyRange > ranges;
  double zai;
  double abn;
  int lfw;

  #include "ENDFtk/resonanceParameters/Isotope/src/readRanges.hpp"
  #include "ENDFtk/resonanceParameters/Isotope/src/ctor.hpp"

public:
  double ZAI() const { return this->zai; }
  double ABN() const { return this->abn; }
  int LFW() const { return this->lfw; }
  int NER() const { return this->ranges.size(); }

  auto energyRanges() const {
    return ranges::make_iterator_range( this->ranges.begin(),
                                        this->ranges.end() );
  }

  #include "ENDFtk/resonanceParameters/Isotope/src/print.hpp"
  #include "ENDFtk/resonanceParameters/Isotope/src/NC.hpp"
};
