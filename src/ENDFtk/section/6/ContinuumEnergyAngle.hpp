class ContinuumEnergyAngle {
public:

  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Tabulated.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/SubSection.hpp"

private:
  InterpolationSequenceRecord< SubSection > data_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/checkLANG.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/readInterpolationRecord.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/readSequence.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/ctor.hpp"

  /* get methods */
  static constexpr int LAW() { return 1; }
  int LANG() const { return this->data_.tab2().L1(); }
  int LEP() const { return this->data_.tab2().L2(); }

  auto energies() const { return this->data_.records(); }

  auto interpolants() const { return this->data_.tab2().interpolants(); }
  auto boundaries() const { return this->data_.tab2().boundaries(); }

  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/print.hpp"
};
