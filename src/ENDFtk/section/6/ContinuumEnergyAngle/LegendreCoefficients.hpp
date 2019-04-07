class LegendreCoefficients : protected Base {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients/src/generateList.hpp"
    
public:
  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients/src/ctor.hpp"

  /* get methods */
  static constexpr int LANG() { return 1; }

  using Base::energy;
  using Base::ND;
  using Base::numberDiscreteEnergies;
  using Base::NA;
  using Base::numberAngularParameters;
  using Base::NW;
  using Base::NEP;
  using Base::numberSecondaryEnergies;

  using Base::energies;
  using Base::totalEmissionProbabilities;
  auto coefficients() const { return Base::data(); }

  using Base::NC;
  using Base::print;
};
