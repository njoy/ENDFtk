/**
 *  @class
 *  @brief The distributions are defined elsewhere and no data is given
 *
 *  See ENDF102, section 6.2.4 for more information.
 */
class DefinedElsewhere : protected NoLawDataGiven {

  /* fields */
  int law_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/DefinedElsewhere/src/checkLAW.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/DefinedElsewhere/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  int LAW() const { return this->law_; }

  using NoLawDataGiven::NC;
  using NoLawDataGiven::print;
};
