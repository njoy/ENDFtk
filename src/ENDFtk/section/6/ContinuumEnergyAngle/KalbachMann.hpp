class KalbachMann : protected Base {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/src/verifyNA.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/src/generateList.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/src/ctor.hpp"

  /* get methods */
  static constexpr int LANG() { return 2; }

  using Base::E;
  using Base::incidentEnergy;
  using Base::ND;
  using Base::numberDiscreteEnergies;
  using Base::NA;
  using Base::numberAngularParameters;
  using Base::NW;
  using Base::NEP;
  using Base::numberSecondaryEnergies;

  using Base::energies;
  using Base::totalEmissionProbabilities;
  auto parameters() const { return Base::data(); }

  using Base::NC;
  using Base::print;
};
