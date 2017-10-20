template<>
class Type< 1, 452 > : protected Base {
protected:

  /* fields */
  int lnu_;
  nubar::NubarData data_;

public:

  /* constructor */
#include "ENDFtk/section/1/452/src/ctor.hpp"

  /* set methods */

  /* get methods */
  virtual int MT() const { return 452; }

  int LNU() const { return this->lnu_; }
//! @todo use this as an alternative and do not store LNU in the section?
// NOTE: LNU is on the HEAD record of the section, not on the LIST or TAB1
//  int LNU() const { return std::visit( [] ( const auto& v ) -> long
//                                          { return v.LNU(); },
//                                       this->data_ ); }

  const nubar::NubarData& nubar() const { return this->data_; }

  long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->data_ ); }

#include "ENDFtk/section/1/452/src/print.hpp"

  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;
};

