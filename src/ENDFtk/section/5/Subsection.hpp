/**
 *  @class
 *  @brief A distribution subsection of an MF5 section
 */
class Subsection {

  PartialProbability probability_;
  PartialDistribution distribution_;

  /* auxiliary functions */
  #include "ENDFtk/section/5/Subsection/src/verifyLF.hpp"
  #include "ENDFtk/section/5/Subsection/src/readSubsection.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/5/Subsection/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the constant that defines the upper energy
   *         limit E - U for the secondary particle's energy E'
   */
  double U() const { return this->probability_.U(); }

  /**
   *  @brief Return the constant that defines the upper energy
   *         limit E - U for the secondary particle's energy E'
   */
  double energyLimitConstant() const { return this->U(); }

  /**
   *  @brief Return the probability
   */
  const auto& probability() const { return this->probability_; }

  /**
   *  @brief Return the distribution
   */
  const auto& distribution() const { return this->distribution_; }

  #include "ENDFtk/section/5/Subsection/src/NC.hpp"
  #include "ENDFtk/section/5/Subsection/src/print.hpp"
};
