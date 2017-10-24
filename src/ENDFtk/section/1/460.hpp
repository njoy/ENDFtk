template<>
class Type< 1, 460 > : protected Base {
public:

#include "ENDFtk/section/1/460/DiscretePhoton.hpp"
#include "ENDFtk/section/1/460/Discrete.hpp"
#include "ENDFtk/section/1/460/Continuous.hpp"

  using DelayedPhotonData = std::variant< // LO=1
                                          Discrete,
                                          // LO=2
                                          Continuous >;

protected:

  /* fields */
  int lo_;
  int ng_;
  DelayedPhotonData data_;

  /* auxiliary functions */
#include "ENDFtk/section/1/460/src/readPhotonData.hpp"
#include "ENDFtk/section/1/460/src/readDiscretePhotons.hpp"

public:

  /* constructor */
#include "ENDFtk/section/1/460/src/ctor.hpp"

  /* set methods */

  /* get methods */
  virtual int MT() const { return 460; }

  int LO() const { return this->lo_; }
//! @todo use this as an alternative and do not store LO in the section?
// NOTE: LO is on the HEAD record of the section, not on the TAB1s or LIST
//  int LO() const { return std::visit( [] ( const auto& v ) -> long
//                                         { return v.LO(); },
//                                      this->data_ ); }
  int NG() const { return this->ng_; }
//! @todo use this as an alternative and do not store NG in the section?
// NOTE: NG is on the HEAD record of the section, not on the TAB1s or LIST
//  int NG() const { return std::visit( [] ( const auto& v ) -> long
//                                         { return v.NG(); },
//                                      this->data_ ); }

  const DelayedPhotonData& delayedPhotons() const { return this->data_; }

  long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->data_ ); }

#include "ENDFtk/section/1/460/src/print.hpp"

  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;
};

