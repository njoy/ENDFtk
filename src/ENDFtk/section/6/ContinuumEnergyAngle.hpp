class ContinuumEnergyAngle {
public:

  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/EqualProbabilityBins.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Tabulated.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/SubSection.hpp"

private:
  InterpolationSequenceRecord< SubSection > data_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/readSequence.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/verifyLANG.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/ctor.hpp"

  /* get methods */
  static constexpr int LAW() { return 1; }
  int LANG() const { return this->data_.tab2().L1(); }
  int LEP() const { return this->data_.tab2().L2(); }
  int interpolationScheme() const { return this->LEP(); }
  long NR() const { return this->data_.tab2().NR(); }
  long NE() const { return this->data_.tab2().NZ(); }

  auto subsections() const { return this->data_.records(); }

  auto interpolants() const { return this->data_.tab2().interpolants(); }
  auto boundaries() const { return this->data_.tab2().boundaries(); }

  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/print.hpp"
};
