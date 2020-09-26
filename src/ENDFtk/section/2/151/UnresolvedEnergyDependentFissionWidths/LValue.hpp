/**
 *  @class
 *  @brief The unresolved resonance parameters for a given l value in the SLBW
 *         representation for energy dependent fission widths (all other
 *         widths are energy independent).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class LValue : protected UnresolvedLValueBase< JValue > {

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/LValue/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/LValue/src/ctor.hpp"

  using UnresolvedLValueBase::AWRI;
  using UnresolvedLValueBase::atomicWeightRatio;
  using UnresolvedLValueBase::L;
  using UnresolvedLValueBase::orbitalMomentum;
  using UnresolvedLValueBase::NJS;
  using UnresolvedLValueBase::numberSpinValues;
  using UnresolvedLValueBase::jValues;

  using UnresolvedLValueBase::NE;

  using UnresolvedLValueBase::NC;
  using UnresolvedLValueBase::print;
};
