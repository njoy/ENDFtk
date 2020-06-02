class GendfDataRecord : protected ListRecord {

public:

  /* constructor */
  #include "ENDFtk/GendfDataRecord/src/ctor.hpp"

  /* getters */
  double temperature() const { return this->C1(); };
  int NG2() const { return this->L1(); }
  int numSecondaryPositions() const { return NG2(); }
  int IG2LO() const { return this->L2(); }
  int lowestGroup() const { return IG2LO(); };
  int IG() const { return this->N2(); }
  int group() const { return IG(); }

  using ListRecord::list;

};
