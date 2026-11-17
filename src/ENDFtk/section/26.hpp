#ifndef NJOY_ENDFTK_SECTION_26
#define NJOY_ENDFTK_SECTION_26

// system includes

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
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

    template < typename Range, typename String >
    static void
    verifySorted( const Range& values, const String& name ){

      auto iter = std::is_sorted_until( values.begin(), values.end(),
                                        [] ( auto&& left, auto&& right )
                                           { return left < right; } );
      const bool valuesAreSorted = ( iter == values.end() );

      if ( not valuesAreSorted ){

        Log::error( "{} values are not sorted", name );
        const auto position = iter - values.begin();
        Log::info( "{} value [{}]: {}", name, (position - 1), iter[-1] );
        Log::info( "{} value [{}]: {}", name, position, iter[0] );
        throw std::exception();
      }
    }

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
     *  @param[in] mt            the MT number of the section
     *  @param[in] zaid          the material ZAID value
     *  @param[in] awr           the atomic weight ratio
     *  @param[in] products      the reaction products (at least 1)
     */
    Type( int MT, int zaid, double awr,
          std::vector< ReactionProduct >&& products ) :
      Base( zaid, awr, MT ),
      products_( std::move( products ) ) {}

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
    Type( HEAD& head,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT )
      try:
        Base( head, MAT, 26 ),
        products_(
          readSequence< ReactionProduct >( begin, end, lineNumber,
                                           MAT, 26, head.MT(), head.N1() ) ) {
        readSEND(begin, end, lineNumber, MAT, 26 );
      } catch( std::exception& e ) {

        Log::info( "Trouble while reading section {} of File 26 of Material {}",
                   head.MT(), MAT );
        throw e;
      }

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

      using namespace njoy::tools;
      return std20::views::all( this->products_ );
    }

    /**
     *  @brief Return the number of lines in this MF26 section
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->products_ ) { NC += entry.NC(); }
      return NC;
    };

    /**
     *  @brief Print the MF26 section (includes SEND record)
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
      ControlRecord( this->ZA(), this->AWR(), 0, 0,
                     this->NK(), 0 ).print( it, MAT, MF, MT );
      for ( auto& entry : this->products_ ) { entry.print( it, MAT, MF, MT ); }
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
