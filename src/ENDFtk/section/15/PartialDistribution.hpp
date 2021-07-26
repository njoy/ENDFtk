/**
 *  @class
 *  @brief A distribution subsection of an MF15 section
 */
class PartialDistribution {

  Probability probability_;
  Distribution distribution_;

  /* auxiliary functions */
  #include "ENDFtk/section/15/PartialDistribution/src/verifyLF.hpp"
  #include "ENDFtk/section/15/PartialDistribution/src/readPartialDistribution.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/15/PartialDistribution/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the probability
   */
  const Probability& probability() const { return this->probability_; }

  /**
   *  @brief Return the distribution
   */
  const Distribution& distribution() const { return this->distribution_; }

  #include "ENDFtk/section/15/PartialDistribution/src/NC.hpp"
  #include "ENDFtk/section/15/PartialDistribution/src/print.hpp"
};
