#ifndef NJOY_ENDFTK_SECTION_1_455
#define NJOY_ENDFTK_SECTION_1_455

// system includes
#include <variant>

// other includes
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/InterpolationRecord.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/section.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/drop_exactly.hpp"

#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"
#include "ENDFtk/section/1/readNubarData.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class Type< 1, 455 > : protected BaseWithoutMT< Type< 1, 455 > > {

    friend BaseWithoutMT< Type< 1, 455 > >;

  public:

    #include "ENDFtk/section/1/455/Constant.hpp"
    #include "ENDFtk/section/1/455/DecayConstant.hpp"
    #include "ENDFtk/section/1/455/EnergyDependent.hpp"

    using DecayConstantData = std::variant< // LDG=0
                                            Constant,
                                            // LDG=1
                                            EnergyDependent >;

    using NubarData = std::variant< // LNU=1
                                    Polynomial,
                                    // LNU=2
                                    Tabulated >;

  private:

    /* fields */
    DecayConstantData lambda_;
    NubarData nubar_;

    /* auxiliary functions */
    #include "ENDFtk/section/1/455/src/readDecayConstantData.hpp"

  public:

    /* constructor */
  #include "ENDFtk/section/1/455/src/ctor.hpp"

    /* set methods */

    /* get methods */

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 455; }

    int LNU() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.LNU(); },
                                         this->nubar_ ); }

    int LDG() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.LDG(); },
                                         this->lambda_ ); }

    const DecayConstantData& lambda() const { return this->lambda_; }

    const NubarData& nubar() const { return this->nubar_; }

    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->lambda_ )
                               + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->nubar_ ); }

    #include "ENDFtk/section/1/455/src/print.hpp"

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
