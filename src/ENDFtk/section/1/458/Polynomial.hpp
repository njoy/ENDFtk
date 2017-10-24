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

  using ListRecord::NC;
  using ListRecord::print;
};

