#ifndef NJOY_ENDFTK_SECTION_10
#define NJOY_ENDFTK_SECTION_10

// system includes

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
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
  class ENDFTK_PYTHON_EXPORT Type< 10 > : protected Base {

  public:

    #include "ENDFtk/section/10/ReactionProduct.hpp"

  private:

    /* fields */

    int lis_;
    std::vector< ReactionProduct > products_;

  public:

    /* constructor */

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    Type() = default;
    #endif

    /**
     *  @brief Constructor
     *
     *  @param[in] mt     the MT number
     *  @param[in] zaid   the ZA  identifier
     *  @param[in] awr    the atomic mass ratio
     *  @param[in] lis    the target's excited level
     *  @param[in] products   the reaction products (at least 1)
     */
    Type( int mt, int zaid, double awr, long lis,
          std::vector< ReactionProduct >&& products ) :
      Base( zaid, awr, mt ), lis_( lis ), products_( std::move( products ) ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] head         the head record of the section
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     */
    template< typename Iterator >
    Type ( HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
      try: Type( head.MT(), head.ZA(), head.AWR(), head.L1(),
                 readSequence< ReactionProduct >( begin, end, lineNumber,
                                                         MAT, 10, head.MT(),
                                                         head.N1() ) ) {

        readSEND(begin, end, lineNumber, MAT, 10 );
      }
      catch( std::exception& e ) {

        Log::info
        ( "Encountered error while reading section {} of file 10 of material {}",
          head.MT(), MAT );
        throw e;
      }

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

      using namespace njoy::tools;
      return this->products_ | std20::views::all;
    }

    /**
     *  @brief Return the number of lines in this MF10 component
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->products_ ) {

        NC += entry.NC();
      }
      return NC;
    };

    /**
     *  @brief Print this MF10 component
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = this->MT();
      ControlRecord( this->ZA(), this->AWR(),
                     this->LIS(), 0,
                     this->products_.size(), 0 ).print( it, MAT, MF, MT );
      for ( const auto& entry : this->products_ ) {

        entry.print( it, MAT, MF, MT );
      }
      SEND( MAT, MF ).print( it );
    }

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
