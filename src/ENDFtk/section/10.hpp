#ifndef NJOY_ENDFTK_SECTION_10
#define NJOY_ENDFTK_SECTION_10

// system includes

// other includes
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF10 - cross sections for radioactive nuclide production
   *
   *  See ENDF102, section 10.2 for more information.
   */
  template<>
  class Type< 10 > : protected Base {

  public:

    #include "ENDFtk/section/10/ReactionProduct.hpp"

  private:

    /* fields */
    int lis_;
    std::vector< ReactionProduct > products_;

  public:

    /* constructor */
    #include "ENDFtk/section/10/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the excited level number of the target
     */
    int LIS() const { return this->lis_; }

    /**
     *  @brief Return the excited level number of the target
     */
    int excitedLevel() const { return this->LIS(); }

    /**
     *  @brief Return the number of excited states for the reaction product
     */
    int NS() const { return this->products_.size(); }

    /**
     *  @brief Return the number of excited states for the reaction product
     */
    int numberReactionProducts() const { return this->NS(); }

    /**
     *  @brief Return whether or not the excited state is present
     *
     *  @param[in] state    the excited state to retrieve
     */
    bool hasExcitedState( int state ) const {

      return std::find_if( this->products_.begin(), this->products_.end(),
                           [state] ( auto&& product )
                                   { return product.excitedLevel() == state; } )
             != this->products_.end();
    }

    /**
     *  @brief Return the reaction product for the requested excited state
     *
     *  @param[in] state    the excited state to retrieve
     */
    const ReactionProduct& reactionProduct( int state ) const {

      auto iter = std::find_if( this->products_.begin(), this->products_.end(),
                                [state] ( auto&& product )
                                        { return product.excitedLevel() == state; } );
      if ( this->products_.end() == iter ) {

        Log::error( "The requested excited state {} is not present in MF10",
                    state );
        throw std::exception();
      }
      else {

        return *iter;
      }
    }

    /**
     *  @brief Return the reaction product data
     */
    auto reactionProducts() const {

      return ranges::cpp20::views::all( this->products_ );
    }

    #include "ENDFtk/section/10/src/NC.hpp"
    #include "ENDFtk/section/10/src/print.hpp"

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
