/**
 *  @class
 *  @brief The unresolved resonance parameters for a given l value in the SLBW
 *         representation for energy dependent fission widths (all other
 *         widths are energy independent).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class LValue : protected LValueBase< JValue > {

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/LValue/src/ctor.hpp"

  using LValueBase::AWRI;
  using LValueBase::atomicWeightRatio;
  using LValueBase::L;
  using LValueBase::orbitalMomentum;
  using LValueBase::NJS;
  using LValueBase::numberSpinValues;
  using LValueBase::jValues;
  using LValueBase::NE;

  using LValueBase::NC;
  using LValueBase::print;
};
