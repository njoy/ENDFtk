/**
 *  @class
 *  @brief The unresolved resonance parameters for a given l value in the SLBW
 *         representation for energy dependent fission widths (all other
 *         widths are energy independent).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT LValue : protected UnresolvedLValueBase< JValue > {

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/LValue/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/LValue/src/ctor.hpp"

  using UnresolvedLValueBase< JValue >::AWRI;
  using UnresolvedLValueBase< JValue >::atomicWeightRatio;
  using UnresolvedLValueBase< JValue >::L;
  using UnresolvedLValueBase< JValue >::orbitalMomentum;
  using UnresolvedLValueBase< JValue >::NJS;
  using UnresolvedLValueBase< JValue >::numberSpinValues;
  using UnresolvedLValueBase< JValue >::jValues;

  using UnresolvedLValueBase< JValue >::NE;

  using UnresolvedLValueBase< JValue >::NC;
  using UnresolvedLValueBase< JValue >::print;
};
