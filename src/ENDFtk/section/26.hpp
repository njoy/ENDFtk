#ifndef NJOY_ENDFTK_SECTION_26
#define NJOY_ENDFTK_SECTION_26

// system includes

// other includes
#include "range/v3/algorithm/find_if_not.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/all.hpp"
#include "range/v3/view/chunk.hpp"
#include "range/v3/view/concat.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/join.hpp"
#include "range/v3/view/single.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/tail.hpp"
#include "range/v3/view/zip.hpp"
#include "range/v3/view/transform.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF26 - secondary distributions for photo- and electro-atomic
   *                interactions
   *
   *  See ENDF102, section 26.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 26 > : protected Base {

    #include "ENDFtk/section/6/src/verifySorted.hpp"

  public:

    #include "ENDFtk/section/26/Multiplicity.hpp"

    #include "ENDFtk/section/26/ContinuumEnergyAngle.hpp"      // LAW=1
    #include "ENDFtk/section/26/DiscreteTwoBodyScattering.hpp" // LAW=2
    #include "ENDFtk/section/26/EnergyTransfer.hpp"            // LAW=8

    using LAW1 = ContinuumEnergyAngle;
    using LAW2 = DiscreteTwoBodyScattering;
    using LAW8 = EnergyTransfer;

    using Distribution = std::variant< ContinuumEnergyAngle,      // LAW=1
                                       DiscreteTwoBodyScattering, // LAW=2
                                       EnergyTransfer >;          // LAW=8

    #include "ENDFtk/section/26/ReactionProduct.hpp"

  private:

    /* fields */
    std::vector< ReactionProduct > products_;

    /* auxiliary functions */

  public:

    /* constructor */
    #include "ENDFtk/section/26/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of reaction products
     */
    int NK() const { return this->products_.size(); }

    /**
     *  @brief Return the number of reaction products
     */
    int numberReactionProducts() const { return this->NK(); }

    /**
     *  @brief Return whether or not the reaction product is present
     *
     *  @param[in] zap    the reaction product to retrieve
     */
    bool hasReactionProduct( int zap ) const {

      return std::find_if( this->products_.begin(), this->products_.end(),
                           [zap] ( auto&& product )
                                 { return product.productIdentifier() == zap; } )
             != this->products_.end();
    }

    /**
     *  @brief Return the requested reaction product
     *
     *  @param[in] zap    the reaction product to retrieve
     */
    const ReactionProduct& reactionProduct( int zap ) const {

      auto iter = std::find_if( this->products_.begin(), this->products_.end(),
                                [zap] ( auto&& product )
                                      { return product.productIdentifier() == zap; } );
      if ( this->products_.end() == iter ) {

        Log::error( "The requested reaction product {} is not present in MF26", zap );
        throw std::exception();
      }
      else {

        return *iter;
      }
    }

    /**
     *  @brief Return the reaction products defined in this section
     */
    auto reactionProducts() const {

      return ranges::cpp20::views::all( this->products_ );
    }

    #include "ENDFtk/section/26/src/NC.hpp"
    #include "ENDFtk/section/26/src/print.hpp"

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::targetIdentifier;
    using Base::atomicWeightRatio;
    using Base::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
