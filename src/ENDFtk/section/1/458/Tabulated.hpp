class Tabulated {

  /* fields */
  int nfc_;
  ThermalPoint values_;
  std::array< std::optional< EnergyReleaseComponent >, 9 > components_;

  /* auxiliary functions */
#include "ENDFtk/section/1/458/Tabulated/src/readTables.hpp"

public:
  /* constructor */
#include "ENDFtk/section/1/458/Tabulated/src/ctor.hpp"

  /* get methods */
  static constexpr int LFC() { return 1; }
  static constexpr int NPLY() { return 0; }
  int NFC() const { return this->nfc_; }

  double EFR() { return this->values_.EFR(); }
  double ENP() { return this->values_.ENP(); }
  double END() { return this->values_.END(); }
  double EGP() { return this->values_.EGP(); }
  double EGD() { return this->values_.EGD(); }
  double EB()  { return this->values_.EB(); }
  double ENU() { return this->values_.ENU(); }
  double ER()  { return this->values_.ER(); }
  double ET()  { return this->values_.ET(); }

  double DEFR() { return this->values_.DEFR(); }
  double DENP() { return this->values_.DENP(); }
  double DEND() { return this->values_.DEND(); }
  double DEGP() { return this->values_.DEGP(); }
  double DEGD() { return this->values_.DEGD(); }
  double DEB()  { return this->values_.DEB(); }
  double DENU() { return this->values_.DENU(); }
  double DER()  { return this->values_.DER(); }
  double DET()  { return this->values_.DET(); }

  const auto& tableEFR() { return std::get< 0 >( this->components_ ); }
  const auto& tableENP() { return std::get< 1 >( this->components_ ); }
  const auto& tableEND() { return std::get< 2 >( this->components_ ); }
  const auto& tableEGP() { return std::get< 3 >( this->components_ ); }
  const auto& tableEGD() { return std::get< 4 >( this->components_ ); }
  const auto& tableEB() { return std::get< 5 >( this->components_ ); }
  const auto& tableENU() { return std::get< 6 >( this->components_ ); }
  const auto& tableER() { return std::get< 7 >( this->components_ ); }
  const auto& tableET() { return std::get< 8 >( this->components_ ); }

#include "ENDFtk/section/1/458/Tabulated/src/NC.hpp"

#include "ENDFtk/section/1/458/Tabulated/src/print.hpp"

};

