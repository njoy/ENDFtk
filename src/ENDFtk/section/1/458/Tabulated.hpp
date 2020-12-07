class Tabulated {

  /* fields */
  int nfc_;
  ThermalPointComponents values_;
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

  auto EFR() const { return this->values_.EFR(); }
  auto ENP() const { return this->values_.ENP(); }
  auto END() const { return this->values_.END(); }
  auto EGP() const { return this->values_.EGP(); }
  auto EGD() const { return this->values_.EGD(); }
  auto EB() const { return this->values_.EB(); }
  auto ENU() const { return this->values_.ENU(); }
  auto ER() const  { return this->values_.ER(); }
  auto ET() const  { return this->values_.ET(); }

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
