/**
 *  @class
 *  @brief Thermal point evaluation for fission energy release components
 *
 *  The thermal point evaluation for fission energy release components uses
 *  analytical functions to model dependence on incident neutron energy.
 *
 *  See ENDF102, section 1.5 for more information.
 */
class ThermalPointComponents : protected ListRecord {

public:

  /* constructor */
  #include "ENDFtk/section/1/458/ThermalPointComponents/src/ctor.hpp"

  /* methods */
  static constexpr int LFC() { return 0; }
  static constexpr int NPLY() { return 0; }
  static constexpr int NFC() { return 0; }

  double EFR() const { return ListRecord::list()[0]; }
  double ENP() const { return ListRecord::list()[2]; }
  double END() const { return ListRecord::list()[4]; }
  double EGP() const { return ListRecord::list()[6]; }
  double EGD() const { return ListRecord::list()[8]; }
  double EB() const { return ListRecord::list()[10]; }
  double ENU() const { return ListRecord::list()[12]; }
  double ER() const { return ListRecord::list()[14]; }
  double ET() const { return ListRecord::list()[16]; }

  double DEFR() const { return ListRecord::list()[1]; }
  double DENP() const { return ListRecord::list()[3]; }
  double DEND() const { return ListRecord::list()[5]; }
  double DEGP() const { return ListRecord::list()[7]; }
  double DEGD() const { return ListRecord::list()[9]; }
  double DEB() const { return ListRecord::list()[11]; }
  double DENU() const { return ListRecord::list()[13]; }
  double DER() const { return ListRecord::list()[15]; }
  double DET() const  { return ListRecord::list()[17]; }

  using ListRecord::NC;
  using ListRecord::print;
};
