/**
 *  @class
 *  @brief A distribution subsection of an MF5 section
 */
class SubSection {

  PartialProbability probability_;
  PartialDistribution distribution_;

  /* auxiliary functions */
  #include "ENDFtk/section/5/SubSection/src/verifyLF.hpp"
  #include "ENDFtk/section/5/SubSection/src/readSubSection.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/5/SubSection/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the probability
   */
  const auto& probability() const { return this->probability_; }

  /**
   *  @brief Return the distribution
   */
  const auto& distribution() const { return this->distribution_; }

  #include "ENDFtk/section/5/SubSection/src/NC.hpp"
  #include "ENDFtk/section/5/SubSection/src/print.hpp"
};
