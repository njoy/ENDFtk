class ReichMoore : public BreitWigner {
  int lad;
  int nlsc;

#include "ENDFtk/ResonanceParameters/Resolved/ReichMoore/src/validate.hpp"

public:
#include "ENDFtk/ResonanceParameters/Resolved/ReichMoore/src/ctor.hpp"
  
  int LAD() const { return this->lad; }
  int NLSC() const { return this->nlsc; }
};
