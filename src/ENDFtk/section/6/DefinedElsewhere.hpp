class DefinedElsewhere : protected NoLawDataGiven {

  /* fields */
  int law_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/DefinedElsewhere/src/checkLAW.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/DefinedElsewhere/src/ctor.hpp"

  /* get methods */
  int LAW() const { return this->law_; }

  using NoLawDataGiven::NC;
  using NoLawDataGiven::print;
};
