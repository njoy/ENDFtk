#ifndef NJOY_ENDFTK_SECTION_8_454
#define NJOY_ENDFTK_SECTION_8_454

// system includes

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/section/8/FissionYieldData.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template<>
  class ENDFTK_PYTHON_EXPORT Type< 8, 454 > :
    protected BaseWithoutMT< Type< 8, 454 > > {

    friend BaseWithoutMT< Type< 8, 454 > >;

    /* fields */

    std::vector< FissionYieldData > data_;

    /* auxiliary functions */

    static std::vector< FissionYieldData >
    generateFissionYields( std::vector< unsigned int >&& identifiers,
                           std::vector< unsigned int >&& states,
                           std::vector< double >&& energies,
                           std::vector< unsigned int >&& interpolants,
                           std::vector< std::vector< std::array< double, 2 > > >&& yields ) {

      std::vector< FissionYieldData > sequence;
      unsigned int size = energies.size();
      sequence.reserve( size );

      if ( size != interpolants.size() + 1 ) {

        Log::error( "Encountered inconsistent number of energy values and "
                    "interpolation flags" );
        Log::info( "Number of I values must be equal to NE - 1" );
        Log::info( "Number of I values: {}", interpolants.size() );
        Log::info( "NE value: {}", size );
        throw std::exception();
      }

      unsigned int nfp = identifiers.size();
      if ( ( nfp != states.size() ) || ( nfp != yields.size() ) ) {

        Log::error( "Encountered inconsistent number of identifiers, isomeric states "
                    "and yield data" );
        Log::info( "Number of identifiers, isomeric states and yield sets must be the same" );
        Log::info( "Number of identifiers: {}", identifiers.size() );
        Log::info( "Number of isomeric states: {}", states.size() );
        Log::info( "Number of yield sets: {}", yields.size() );
        throw std::exception();
      }

      for ( unsigned int i = 0; i < nfp; ++i ) {

        if ( yields[i].size() != size ) {

          Log::error( "The number of fission yield values for the fission product "
                     "with index {} is not equal to the expected value", i );
          Log::info( "NE value: {}", size );
          Log::info( "yields[i].size(): {}", yields[i].size() );
          throw std::exception();
        }
      }

      for ( unsigned int i = 0; i < size; ++i ) {

        using namespace njoy::tools;
        auto data = yields | std20::views::transform( [i] ( auto&& values )
                                                          { return values[i]; });
        sequence.emplace_back( std::vector< unsigned int >( identifiers ),
                               std::vector< unsigned int >( states ),
                               std::vector< std::array< double, 2 > >{ data.begin(), data.end() },
                               energies[i],
                               i == 0 ? energies.size() - 1 : interpolants[i-1] );
      }

      return sequence;
    }

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
     *  @param[in] zaid      the material ZAID value
     *  @param[in] awr       the atomic weight ratio
     *  @param[in] yields    the fission yield data
     */
    Type( int zaid, double awr, std::vector< FissionYieldData >&& yields ) :
      BaseWithoutMT( zaid, awr ),
      data_( std::move( yields ) ) {}

    /**
     *  @brief Constructor for energy independent yields
     *
     *  @param[in] zaid           the material ZAID value
     *  @param[in] awr            the atomic weight ratio
     *  @param[in] identifiers    the fission product identifiers (NFP values)
     *  @param[in] states         the isomeric states (NFP values)
     *  @param[in] yields         the fission yield values and uncertainties
     *                            (NFP pairs)
     */
    Type( int zaid, double awr,
          std::vector< unsigned int >&& identifiers,
          std::vector< unsigned int >&& states,
          std::vector< std::array< double, 2 > >&& yields )
      try : Type( zaid, awr,
                  std::vector< FissionYieldData >{
                    FissionYieldData( std::move( identifiers ), std::move( states ),
                                      std::move( yields ) ) } ) {}
      catch ( std::exception& e ) {

        Log::info( "Trouble while constructing section 454 of File 8" );
        throw;
      }

    /**
     *  @brief Constructor for energy dependent yields where each energy has the
     *         same fission products
     *
     *  @param[in] zaid           the material ZAID value
     *  @param[in] awr            the atomic weight ratio
     *  @param[in] identifiers    the fission product identifiers (NFP values)
     *  @param[in] states         the isomeric states (NFP values)
     *  @param[in] energies       the incident neutron energies (NE values)
     *  @param[in] interpolants   the interpolation types (NE-1 values)
     *  @param[in] yields         the fission yield values and uncertainties
     *                            (NFP arrays of NE pairs)
     */
    Type( int zaid, double awr,
          std::vector< unsigned int >&& identifiers,
          std::vector< unsigned int >&& states,
          std::vector< double >&& energies,
          std::vector< unsigned int >&& interpolants,
          std::vector< std::vector< std::array< double, 2 > > >&& yields )
      try : Type( zaid, awr,
                  generateFissionYields( std::move( identifiers ),
                                         std::move( states ),
                                         std::move( energies ),
                                         std::move( interpolants ),
                                         std::move( yields ) ) ) {}
      catch ( std::exception& e ) {

        Log::info( "Trouble while constructing section 454 of File 8" );
        throw;
      }

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
      try : Type( head.ZA(), head.AWR(),
                  readSequence< FissionYieldData >( begin, end, lineNumber,
                                                    MAT, 8, 454, head.L1() ) ) {
        readSEND(begin, end, lineNumber, MAT, 8 );
      } catch ( std::exception& e ) {
        Log::info( "Trouble while reading section 454 of File 8 of Material {}",
                   MAT );
        throw e;
      }

    /* get methods */

    /**
     *  @brief Return whether or not the fission yield data is energy independent
     */
    bool LE() const { return this->data_.size() == 1; }

    /**
     *  @brief Return whether or not the fission yield data is energy independent
     */
    bool isEnergyIndependent() const { return this->LE(); }

    /**
     *  @brief Return the fission yield data, one for each incident energy
     */
    auto yields() const {

      using namespace njoy::tools;
      return std20::views::all( this->data_ );
    }

    /**
     *  @brief Return the number of incident energy values
     */
    long NE() const { return this->data_.size(); }

    /**
     *  @brief Return the number of incident energy values
     */
    long numberIncidentEnergies() const { return this->NE(); }

    /**
     *  @brief Return the incident energy values
     */
    auto E() const {

      using namespace njoy::tools;
      return this->yields()
                 | std20::views::transform( [] ( const auto& entry )
                                               { return entry.E(); } );
    }

    /**
    *  @brief Return the incident energy values
     */
    auto incidentEnergies() const { return this->E(); }

    /**
     *  @brief Return the number of lines in this MF87/MT454 or MF8/MT459 section
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->data_ ) { NC += entry.NC(); }
      return NC;
    };

    /**
     *  @brief Print the MF8/MT454 section (includes SEND record)
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
                     this->data_.size() == 1 ? 1 : this->data_.size(),
                     0, 0, 0 ).print( it, MAT, MF, MT );
      for ( const auto& entry : this->data_ ) { entry.print( it, MAT, MF, MT ); }
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 454; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
