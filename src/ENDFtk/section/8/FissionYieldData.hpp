#ifndef NJOY_ENDFTK_SECTION_8_FISSIONYIELDDATA
#define NJOY_ENDFTK_SECTION_8_FISSIONYIELDDATA

// system includes

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief Fission yield data for a specific incident energy (or energy
   *         independent yields)
   *
   *  This class is defined outside of any of the fission yield
   *  section::Type instances since this component is common to all of them.
   *
   *  See ENDF102, section 8.3 for more information.
   */
  class ENDFTK_PYTHON_EXPORT FissionYieldData : protected ListRecord {

    /* auxiliary functions */

    static void
    verifySize( int NPL, int NFP ) {

      if ( NPL != NFP * 4 ) {

        Log::error( "Encountered illegal NPL and NFP values " );
        Log::info( "NPL must be equal to 4*NFP for fission yield data" );
        Log::info( "NPL value: {}", NPL );
        Log::info( "NFP value: {}", NFP );
        throw std::exception();
      }
    }

    static std::vector< double >
    generateList( std::vector< unsigned int >&& identifiers,
                  std::vector< unsigned int >&& states,
                  std::vector< std::array< double, 2 > >&& yields ) {

      unsigned int nfp = identifiers.size();
      if ( ( states.size() != nfp ) or ( yields.size() != nfp ) ) {

        Log::info( "The number of fission products and the fission product data "
                   "are not consistent" );
        Log::info( "NFP value: {}", nfp );
        Log::info( "identifiers.size(): {}", identifiers.size() );
        Log::info( "states.size(): {}", states.size() );
        Log::info( "yields.size(): {}", yields.size() );
        throw std::exception();
      }

      std::vector< double > list;
      for ( unsigned int i = 0; i < nfp; ++i ) {

        list.push_back( identifiers[i] );
        list.push_back( states[i] );
        list.push_back( yields[i][0] );
        list.push_back( yields[i][1] );
      }
      return list;
    }

    auto column( unsigned int i ) const {

      using namespace njoy::tools;
      return ListRecord::list() | std20::views::drop( i )
                                | std23::views::stride( 4 );
    }

    /* constructor */

    /**
     *  @brief Private constructor
     */
    FissionYieldData( ListRecord&& list ) :
      ListRecord( std::move( list ) ) {

      verifySize( ListRecord::NPL(), this->NFP() );
    };

  public:

    #include "ENDFtk/section/8/FissionYieldData/FissionProduct.hpp"

    /* constructors */

    /**
     *  @brief Constructor
     *
     *  @param[in] identifiers     the fission product identifiers (ZA identifier)
     *  @param[in] states          the isomeric state for each fission product
     *  @param[in] yields          the fission yield values and uncertainties
     *  @param[in] energy          the incident neutron energy (equal to zero for
     *                             energy independent yields)
     *  @param[in] interpolation   the interpolation type (equal to zero for
     *                             energy independent yields)
     */
    FissionYieldData( std::vector< unsigned int >&& identifiers,
                      std::vector< unsigned int >&& states,
                      std::vector< std::array< double, 2 > >&& yields,
                      double energy = 0.0, int interpolation = 0 )
      try : FissionYieldData(
                ListRecord( energy, 0.0,
                            interpolation, 0, identifiers.size(),
                            generateList( std::move( identifiers ),
                                          std::move( states ),
                                          std::move( yields ) ) ) ) {}
      catch ( std::exception& e ) {

        Log::info( "Encountered error while constructing fission yields" );
        throw;
      }

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     *  @param[in] MF           the expected MF number
     *  @param[in] MT           the expected MT number
     */
    template< typename Iterator >
    FissionYieldData( Iterator& begin, const Iterator& end,
                      long& lineNumber, int MAT, int MF, int MT )
      try : FissionYieldData( ListRecord( begin, end, lineNumber, MAT, MF, MT ) ) {}
      catch ( std::exception& e ) {

        Log::info( "Encountered error while constructing fission yields" );
        throw;
      }

    /* methods */

    /**
     *  @brief Return the interpolation type (or LE value)
     */
    int I() const { return ListRecord::L1(); }

    /**
     *  @brief Return the interpolation type (or LE value)
     */
    int interpolationType() const { return this->I(); }

    /**
     *  @brief Return whether or not the fission yields are energy dependent
     *         or not
     */
    bool LE() const { return this->I() == 0; }

    /**
     *  @brief Return whether or not the fission yield data is energy independent
     */
    bool isEnergyIndependent() const { return this->LE(); }

    /**
     *  @brief Return the incident energy for which the fission yields are given
     */
    double E() const { return ListRecord::C1(); }

    /**
     *  @brief Return the incident energy for which the fission yields are given
     */
    double incidentEnergy() const { return this->E(); }

    /**
     *  @brief Return the number of fission products
     */
    int NFP() const { return ListRecord::N2(); }

    /**
     *  @brief Return the number of fission products
     */
    int numberFissionProducts() const { return this->NFP(); }

    /**
     *  @brief Return the fission product ZA identifiers
     */
    auto ZAFP() const { return this->column( 0 ); }

    /**
     *  @brief Return the fission product ZA identifiers
     */
    auto fissionProductIdentifiers() const { return this->ZAFP(); }

    /**
     *  @brief Return the fission product isomeric states
     */
    auto FPS() const { return this->column( 1 ); }

    /**
     *  @brief Return the fission product isomeric states
     */
    auto isomericStates() const { return this->FPS(); }

    /**
     *  @brief Return the fission yield values
     */
    auto FY() const { return this->column( 2 ); }

    /**
     *  @brief Return the fission yield values
     */
    auto fissionYieldValues() const { return this->FY(); }

    /**
     *  @brief Return the fission yield uncertainties
     */
    auto DFY() const { return this->column( 3 ); }

    /**
     *  @brief Return the fission yield values
     */
    auto fissionYieldUncertainties() const { return this->DFY(); }

    /**
     *  @brief Return the fission yield values and uncertainties
     */
    auto Y() const {

      using namespace njoy::tools;
      return ListRecord::list() | std20::views::drop( 2 )
                                | std23::views::chunk( 2 )
                                | std23::views::stride( 2 );
    }

    /**
     *  @brief Return the fission yield values and uncertainties
     */
    auto fissionYields() const { return this->Y(); }

    /**
     *  @brief Return the fission products
     */
    auto fissionProducts() const {

      using namespace njoy::tools;
      using Chunk = decltype( ( ListRecord::list()
                                  | std23::views::chunk( 4 ) )[0] );
      return ListRecord::list() | std23::views::chunk( 4 )
               | std20::views::transform(
                   [] ( Chunk&& chunk ) -> FissionProduct< Chunk >
                      { return { std::move( chunk ) }; } );
    }

    using ListRecord::NC;
    using ListRecord::print;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
