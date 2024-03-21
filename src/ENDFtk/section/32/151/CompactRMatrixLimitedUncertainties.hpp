/**
 *  @class
 *  @brief The resonance parameters and uncertainties in the R-matrix limited
 *         representation (LCOMP = 2)
 *
 *  See ENDF102, section 32.2.3.3 for more information - if you don't value
 *  your sanity.
 */
class ENDFTK_PYTHON_EXPORT CompactRMatrixLimitedUncertainties {

public:

  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/ParticlePairs.hpp"
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/ResonanceChannels.hpp"
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/ResonanceParameters.hpp"
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/SpinGroup.hpp"

private:

  /* fields */
  ParticlePairs particle_pairs_;
  std::vector< SpinGroup > spin_groups_;

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int NJSX() const { return this->spin_groups_.size(); }

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int numberSpinGroups() const { return this->NJSX(); }

  /**
   *  @brief Return the particle pair information
   */
  const ParticlePairs& particlePairs() const { return this->particle_pairs_; }

  /**
   *  @brief Return the spin groups
   */
  auto spinGroups() const {

    return ranges::cpp20::views::all( this->spin_groups_ );
  }

  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/src/NC.hpp"
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/src/print.hpp"
};
