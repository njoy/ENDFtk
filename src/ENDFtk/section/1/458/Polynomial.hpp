class Polynomial : protected ListRecord {

  /* auxiliary functions */
#include "ENDFtk/section/1/458/Polynomial/src/createRangeFromIndex.hpp"

public:
  /* constructor */
#include "ENDFtk/section/1/458/Polynomial/src/ctor.hpp"

  /* get methods */
  static constexpr int LFC() { return 0; }
  int NPLY() const { return ListRecord::L2(); }
  static constexpr int NFC() { return 0; }

  auto EFR() const { return this->createRangeFromIndex( 0 ); }
  auto ENP() const { return this->createRangeFromIndex( 2 ); }
  auto END() const { return this->createRangeFromIndex( 4 ); }
  auto EGP() const { return this->createRangeFromIndex( 6 ); }
  auto EGD() const { return this->createRangeFromIndex( 8 ); }
  auto EB() const { return this->createRangeFromIndex( 10 ); }
  auto ENU() const { return this->createRangeFromIndex( 12 ); }
  auto ER() const { return this->createRangeFromIndex( 14 ); }
  auto ET() const  { return this->createRangeFromIndex( 16 ); }

  auto DEFR() const { return this->createRangeFromIndex( 1 ); }
  auto DENP() const { return this->createRangeFromIndex( 3 ); }
  auto DEND() const { return this->createRangeFromIndex( 5 ); }
  auto DEGP() const { return this->createRangeFromIndex( 7 ); }
  auto DEGD() const { return this->createRangeFromIndex( 9 ); }
  auto DEB() const { return this->createRangeFromIndex( 11 ); }
  auto DENU() const { return this->createRangeFromIndex( 13 ); }
  auto DER() const { return this->createRangeFromIndex( 15 ); }
  auto DET() const  { return this->createRangeFromIndex( 17 ); }

  using ListRecord::NC;
  using ListRecord::print;
};

