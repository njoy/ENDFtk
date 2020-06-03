class GendfDataRecord : protected ListRecord {

protected:

  int num_legendre_;
  int num_sigma0_;
  
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

  auto flux() const { 
    return this->list()
      | ranges::view::take_exactly( num_legendre_ * num_sigma0_ );
  }
  auto values() const {
    return this->list()
      | ranges::view::drop_exactly( num_legendre_ * num_sigma0_ );
  }

};
