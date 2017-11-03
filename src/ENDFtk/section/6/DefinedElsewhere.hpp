class DefinedElsewhere : protected NoLawDataGiven {

  int law_;

public:
  /* constructor */
#include "ENDFtk/section/6/DefinedElsewhere/src/ctor.hpp"

  /* get methods */
  int LAW() const { return this->law_; }

  using NoLawDataGiven::NC;
  using NoLawDataGiven::print;
};
