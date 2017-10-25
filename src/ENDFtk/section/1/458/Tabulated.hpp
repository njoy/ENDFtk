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

  double EFR() const { return this->values_.EFR(); }
  double ENP() const { return this->values_.ENP(); }
  double END() const { return this->values_.END(); }
  double EGP() const { return this->values_.EGP(); }
  double EGD() const { return this->values_.EGD(); }
  double EB() const { return this->values_.EB(); }
  double ENU() const { return this->values_.ENU(); }
  double ER() const  { return this->values_.ER(); }
  double ET() const  { return this->values_.ET(); }

  double DEFR() const { return this->values_.DEFR(); }
  double DENP() const { return this->values_.DENP(); }
  double DEND() const { return this->values_.DEND(); }
  double DEGP() const { return this->values_.DEGP(); }
  double DEGD() const { return this->values_.DEGD(); }
  double DEB() const { return this->values_.DEB(); }
  double DENU() const { return this->values_.DENU(); }
  double DER() const { return this->values_.DER(); }
  double DET() const { return this->values_.DET(); }

  const auto& tableEFR() const { return std::get< 0 >( this->components_ ); }
  const auto& tableENP() const { return std::get< 1 >( this->components_ ); }
  const auto& tableEND() const { return std::get< 2 >( this->components_ ); }
  const auto& tableEGP() const { return std::get< 3 >( this->components_ ); }
  const auto& tableEGD() const { return std::get< 4 >( this->components_ ); }
  const auto& tableEB() const { return std::get< 5 >( this->components_ ); }
  const auto& tableENU() const { return std::get< 6 >( this->components_ ); }
  const auto& tableER() const { return std::get< 7 >( this->components_ ); }
  const auto& tableET() const { return std::get< 8 >( this->components_ ); }

#include "ENDFtk/section/1/458/Tabulated/src/NC.hpp"

#include "ENDFtk/section/1/458/Tabulated/src/print.hpp"

};

