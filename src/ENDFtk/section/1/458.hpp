template<>
class Type< 1, 458 > : protected Base {
public:

#include "ENDFtk/section/1/458/ThermalPoint.hpp"
#include "ENDFtk/section/1/458/Polynomial.hpp"
#include "ENDFtk/section/1/458/EnergyReleaseComponent.hpp"
#include "ENDFtk/section/1/458/Tabulated.hpp"

  using FissionEnergyReleaseData = std::variant< // LFC=0 NPLY=0
                                                 ThermalPoint,
                                                 // LFC=0 NPLY!=0
                                                 Polynomial,
                                                 // LFC=1 NPLY=0
                                                 Tabulated >;

protected:

  /* fields */
  int lfc_;
  int nfc_;
  FissionEnergyReleaseData data_;

  /* auxiliary functions */
#include "ENDFtk/section/1/458/src/readFissionEnergyReleaseData.hpp"

public:

  /* constructor */
#include "ENDFtk/section/1/458/src/ctor.hpp"

  /* set methods */

  /* get methods */
  static constexpr int MT() { return 458; }

  int LFC() const { return this->lfc_; }
//! @todo use this as an alternative and do not store LFC in the section?
// NOTE: LFC is on the HEAD record of the section
//  int LFC() const { return std::visit( [] ( const auto& v ) -> long
//                                          { return v.LO(); },
//                                       this->data_ ); }
  int NFC() const { return this->nfc_; }
//! @todo use this as an alternative and do not store NFC in the section?
// NOTE: NFC is on the HEAD record of the section
//  int NFC() const { return std::visit( [] ( const auto& v ) -> long
//                                          { return v.NG(); },
//                                       this->data_ ); }
  int NPLY() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.NPLY(); },
                                        this->data_ ); }

  const FissionEnergyReleaseData& energyRelease() const { return this->data_; }

  long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->data_ ); }

#include "ENDFtk/section/1/458/src/print.hpp"

  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;
};

