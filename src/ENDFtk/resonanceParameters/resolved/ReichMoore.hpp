class ReichMoore : public BreitWigner {
  int lad;
  int nlsc;

#include "ENDFtk/resonanceParameters/resolved/ReichMoore/src/validate.hpp"

public:
#include "ENDFtk/resonanceParameters/resolved/ReichMoore/src/ctor.hpp"
  
  int LAD() const { return this->lad; }
  int NLSC() const { return this->nlsc; }

  static constexpr int LRF() { return 3; }

#include "ENDFtk/resonanceParameters/resolved/ReichMoore/src/print.hpp"
};
