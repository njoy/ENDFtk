class ThermalPoint : protected ListRecord {

public:
  /* constructor */
#include "ENDFtk/section/1/458/ThermalPoint/src/ctor.hpp"

  /* get methods */
  static constexpr int LFC() { return 0; }
  static constexpr int NPLY() { return 0; }
  static constexpr int NFC() { return 0; }

  double EFR() { return ListRecord::list()[0]; }
  double ENP() { return ListRecord::list()[2]; }
  double END() { return ListRecord::list()[4]; }
  double EGP() { return ListRecord::list()[6]; }
  double EGD() { return ListRecord::list()[8]; }
  double EB()  { return ListRecord::list()[10]; }
  double ENU() { return ListRecord::list()[12]; }
  double ER()  { return ListRecord::list()[14]; }
  double ET()  { return ListRecord::list()[16]; }

  double DEFR() { return ListRecord::list()[1]; }
  double DENP() { return ListRecord::list()[3]; }
  double DEND() { return ListRecord::list()[5]; }
  double DEGP() { return ListRecord::list()[7]; }
  double DEGD() { return ListRecord::list()[9]; }
  double DEB()  { return ListRecord::list()[11]; }
  double DENU() { return ListRecord::list()[13]; }
  double DER()  { return ListRecord::list()[15]; }
  double DET()  { return ListRecord::list()[17]; }

  using ListRecord::NC;
  using ListRecord::print;
};

