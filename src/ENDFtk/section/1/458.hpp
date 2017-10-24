template<>
class Type< 1, 458 > : protected Base {
protected:

  /* fields */
  int lfc_;
  ListRecord components_;

  //! @todo use optionals instead?
  std::vector< TabulationRecord > tables_;

  /* auxiliary functions */
#include "ENDFtk/section/1/458/src/readTables.hpp"
#include "ENDFtk/section/1/458/src/verifyLFC.hpp"
#include "ENDFtk/section/1/458/src/verifyNFC.hpp"
#include "ENDFtk/section/1/458/src/verifyNPLY.hpp"
#include "ENDFtk/section/1/458/src/createRangeFromIndex.hpp"

public:

  /* constructor */
#include "ENDFtk/section/1/458/src/ctor.hpp"

  /* set methods */

  /* get methods */
  static constexpr int MT() { return 458; }

  int LFC() const { return this->lfc_; }
  int NPLY() const { return this->components_.L2(); }
  int NFC() const { return this->tables_.size(); }

  auto EFR() { return this->createRangeFromIndex( 0 ); }
  auto ENP() { return this->createRangeFromIndex( 2 ); }
  auto END() { return this->createRangeFromIndex( 4 ); }
  auto EGP() { return this->createRangeFromIndex( 6 ); }
  auto EGD() { return this->createRangeFromIndex( 8 ); }
  auto EB()  { return this->createRangeFromIndex( 10 ); }
  auto ENU() { return this->createRangeFromIndex( 12 ); }
  auto ER()  { return this->createRangeFromIndex( 14 ); }
  auto ET()  { return this->createRangeFromIndex( 16 ); }

  auto DEFR() { return this->createRangeFromIndex( 1 ); }
  auto DENP() { return this->createRangeFromIndex( 3 ); }
  auto DEND() { return this->createRangeFromIndex( 5 ); }
  auto DEGP() { return this->createRangeFromIndex( 7 ); }
  auto DEGD() { return this->createRangeFromIndex( 9 ); }
  auto DEB()  { return this->createRangeFromIndex( 11 ); }
  auto DENU() { return this->createRangeFromIndex( 13 ); }
  auto DER()  { return this->createRangeFromIndex( 15 ); }
  auto DET()  { return this->createRangeFromIndex( 17 ); }

  long NC() const {
    long NC = 1 + this->components_.NC();
    for ( auto& entry : this->tables_ ) { NC += entry.NC(); }
    return NC;
  }

#include "ENDFtk/section/1/458/src/print.hpp"

  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;
};

