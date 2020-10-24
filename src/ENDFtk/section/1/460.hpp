#ifndef NJOY_ENDFTK_SECTION_1_460
#define NJOY_ENDFTK_SECTION_1_460

// system includes
#include <variant>

// other includes
#include "ENDFtk/types.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class Type< 1, 460 > : protected BaseWithoutMT< Type< 1, 460 > > {

    friend BaseWithoutMT< Type< 1, 460 > >;

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
    DelayedPhotonData data_;

    /* auxiliary functions */
  #include "ENDFtk/section/1/460/src/readPhotonData.hpp"
  #include "ENDFtk/section/1/460/src/readDiscretePhotons.hpp"

  public:

    /* constructor */
  #include "ENDFtk/section/1/460/src/ctor.hpp"

    /* set methods */

    /* get methods */

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 460; }

    int LO() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.LO(); },
                                        this->data_ ); }

    int NG() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.NG(); },
                                        this->data_ ); }

    const DelayedPhotonData& delayedPhotons() const { return this->data_; }

    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->data_ ); }

    #include "ENDFtk/section/1/460/src/print.hpp"

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
