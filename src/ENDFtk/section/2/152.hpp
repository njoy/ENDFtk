#ifndef NJOY_ENDFTK_SECTION_2_152
#define NJOY_ENDFTK_SECTION_2_152

// system includes
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF2 MT152 - internal NJOY section
   *
   *  See the NJOY manual, RECONR and UNRESR for more information.
   */
  template<>
  class Type< 2, 152 > : protected BaseWithoutMT< Type< 2, 152 > > {

    friend BaseWithoutMT< Type< 2, 152 > >;

    /* fields */

    bool lssf_;
    int interpolation_;
    ListRecord data_;

    /* workaround for the removal of range-v3 */

    // using transform with more ranges operations in the transform causes issues
    // on the Python side. we just generate the underlying array at construction
    // time to solve it.
    using Iterator = njoy::tools::std20::ranges::iterator_t< decltype( data_.list() ) >;
    using Array = njoy::tools::std20::subrange< Iterator, Iterator >;
    std::vector< std::vector< Array > > reactions_;

    void  generateArrays() {

      this->reactions_.clear();

      using namespace njoy::tools;

      unsigned int nreac = this->data_.L1();
      unsigned int nsigz = this->data_.L2();
      this->reactions_ = std::vector< std::vector< Array > >( nreac );
      auto chunks = this->data_.list()
                      | std20::views::drop( nsigz )
                      | std23::views::chunk( 1 + nsigz * nreac );

      for ( auto&& chunk : chunks ) {

        auto begin = chunk.begin();
        for ( std::size_t i = 0; i < nreac; ++i ) {

          this->reactions_[i].emplace_back( begin + 1 + i * nsigz,
                                            begin + 1 + ( i + 1 ) * nsigz );
        }
      }
    }

    /* auxiliary functions */

    static std::vector< double >
    generateList( std::vector< double >&& dilutions,
                  std::vector< double >&& energies,
                  std::vector< std::vector< double > >&& total,
                  std::vector< std::vector< double > >&& elastic,
                  std::vector< std::vector< double > >&& fission,
                  std::vector< std::vector< double > >&& capture,
                  std::vector< std::vector< double > >&& cwTotal ) {

      unsigned int nsigz = dilutions.size();
      unsigned int nunr = energies.size();
      if ( ( total.size() != nunr ) or
           ( elastic.size() != nunr ) or ( fission.size() != nunr ) or
           ( capture.size() != nunr ) or ( cwTotal.size() != nunr ) ) {

        Log::error( "The number of energies and sets of cross section values is "
                    "not consistent" );
        Log::info( "NUNR value: {}", nunr );
        Log::info( "total.size(): {}", total.size() );
        Log::info( "elastic.size(): {}", elastic.size() );
        Log::info( "fission.size(): {}", fission.size() );
        Log::info( "capture.size(): {}", capture.size() );
        Log::info( "cwTotal.size(): {}", cwTotal.size() );
        throw std::exception();
      }

      std::vector< double > list( dilutions );
      for ( unsigned int i = 0; i < nunr; ++i ) {

        list.push_back( energies[i] );
        if ( ( total[i].size() != nsigz ) or
             ( elastic[i].size() != nsigz ) or ( fission[i].size() != nsigz ) or
             ( capture[i].size() != nsigz ) or ( cwTotal[i].size() != nsigz ) ) {

          Log::error( "The number of cross section values and dilutions is not "
                      "consistent for the energy with index {}", i );
          Log::info( "NSIGZ value: {}", nsigz );
          Log::info( "total[i].size(): {}", total[i].size() );
          Log::info( "elastic[i].size(): {}", elastic[i].size() );
          Log::info( "fission[i].size(): {}", fission[i].size() );
          Log::info( "capture[i].size(): {}", capture[i].size() );
          Log::info( "cwTotal[i].size(): {}", cwTotal[i].size() );
          throw std::exception();
        }

        list.insert( list.end(), total[i].begin(), total[i].end() );
        list.insert( list.end(), elastic[i].begin(), elastic[i].end() );
        list.insert( list.end(), fission[i].begin(), fission[i].end() );
        list.insert( list.end(), capture[i].begin(), capture[i].end() );
        list.insert( list.end(), cwTotal[i].begin(), cwTotal[i].end() );
      }

      return list;
    }

    static std::vector< double >
    generateList( std::vector< double >&& energies,
                  std::vector< double >&& total,
                  std::vector< double >&& elastic,
                  std::vector< double >&& fission,
                  std::vector< double >&& capture,
                  std::vector< double >&& cwTotal ) {

      unsigned int nunr = energies.size();
      if ( ( total.size() != nunr ) or
           ( elastic.size() != nunr ) or ( fission.size() != nunr ) or
           ( capture.size() != nunr ) or ( cwTotal.size() != nunr ) ) {

        Log::error( "The number of energies and sets of cross section values is "
                    "not consistent" );
        Log::info( "NUNR value: {}", nunr );
        Log::info( "total.size(): {}", total.size() );
        Log::info( "elastic.size(): {}", elastic.size() );
        Log::info( "fission.size(): {}", fission.size() );
        Log::info( "capture.size(): {}", capture.size() );
        Log::info( "cwTotal.size(): {}", cwTotal.size() );
        throw std::exception();
      }

      std::vector< double > list = { 1e+10 };
      for ( unsigned int i = 0; i < nunr; ++i ) {

        list.push_back( energies[i] );
        list.push_back( total[i] );
        list.push_back( elastic[i] );
        list.push_back( fission[i] );
        list.push_back( capture[i] );
        list.push_back( cwTotal[i] );
      }
      return list;
    }

    static void
    verifySize( int NREAC, int NSIGZ, int NUNR, int NW ) {

      if ( NW != ( NREAC * NSIGZ + 1 ) * NUNR + NSIGZ )  {

        Log::error( "Inconsistent data size" );
        Log::info( "Expected NW = ( NREAC * NSIGZ + 1 ) * NUNR + NSIGZ" );
        Log::info( "NW value: {}", NW );
        Log::info( "NREAC value: {}", NREAC );
        Log::info( "NSIGZ value: {}", NSIGZ );
        Log::info( "NUNR value: {}", NUNR );
        throw std::exception();
      }
    }

    /* constructor */

    /**
     *  @brief Intermediate private constructor
     */
    Type( int zaid, double awr, bool lssf, int interpolation,
          ListRecord&& list ) :
      BaseWithoutMT( zaid, awr ), lssf_( lssf ), interpolation_( interpolation ),
      data_( std::move( list ) ) {

        verifySize( this->NREAC(), this->NSIGZ(), this->NUNR(), this->NW() );
        this->generateArrays();
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
     *  @brief General constructor
     *
     *  @param[in] zaid            the material ZAID value
     *  @param[in] awr             the atomic weight ratio
     *  @param[in] lssf            the lssf flag
     *  @param[in] interpolation   the interpolation scheme
     *  @param[in] temperature     the temperature
     *  @param[in] dilutions       the dilution values (nsigz values)
     *  @param[in] energies        the energy values (nunr values)
     *  @param[in] total           the total cross section values (nunr values of
     *                             nsigz values)
     *  @param[in] elastic         the elastic cross section values (nunr values of
     *                             nsigz values)
     *  @param[in] fission         the fission cross section values (nunr values of
     *                             nsigz values)
     *  @param[in] capture         the capture cross section values (nunr values of
     *                             nsigz values)
     *  @param[in] cwTotal         the current weighted total cross section values
     *                             (nunr values of nsigz values)
     */
    Type( int zaid, double awr, bool lssf, int interpolation, double temperature,
          std::vector< double >&& dilutions, std::vector< double >&& energies,
          std::vector< std::vector< double > >&& total,
          std::vector< std::vector< double > >&& elastic,
          std::vector< std::vector< double > >&& fission,
          std::vector< std::vector< double > >&& capture,
          std::vector< std::vector< double > >&& cwTotal )
      try : Type( zaid, awr, lssf, interpolation,
                  ListRecord( temperature, 0., 5, dilutions.size(), energies.size(),
                              generateList( std::move( dilutions ),
                                            std::move( energies ),
                                            std::move( total ),
                                            std::move( elastic ),
                                            std::move( fission ),
                                            std::move( capture ),
                                            std::move( cwTotal ) ) ) ) {}
      catch ( std::exception& e ) {

        Log::info( "Trouble while constructing section 152 of File 2" );
        throw e;
      }

    /**
     *  @brief Constructor for infinite dilution only
     *
     *  @param[in] zaid            the material ZAID value
     *  @param[in] awr             the atomic weight ratio
     *  @param[in] lssf            the lssf flag
     *  @param[in] interpolation   the interpolation scheme
     *  @param[in] temperature     the temperature
     *  @param[in] energies        the energy values (nunr values)
     *  @param[in] total           the total cross section values (nunr values)
     *  @param[in] elastic         the elastic cross section values (nunr values)
     *  @param[in] fission         the fission cross section values (nunr values)
     *  @param[in] capture         the capture cross section values (nunr values)
     *  @param[in] cwTotal         the current weighted total cross section values
     *                             (nunr values)
     */
    Type( int zaid, double awr, bool lssf, int interpolation, double temperature,
          std::vector< double >&& energies, std::vector< double >&& total,
          std::vector< double >&& elastic, std::vector< double >&& fission,
          std::vector< double >&& capture, std::vector< double >&& cwTotal )
      try : Type( zaid, awr, lssf, interpolation,
                  ListRecord( temperature, 0., 5, 1, energies.size(),
                              generateList( std::move( energies ),
                                            std::move( total ),
                                            std::move( elastic ),
                                            std::move( fission ),
                                            std::move( capture ),
                                            std::move( cwTotal ) ) ) ) {}
      catch ( std::exception& e ) {

        Log::info( "Trouble while constructing section 152 of File 2" );
        throw e;
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
    Type ( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
      try:
        Type( head.ZA(), head.AWR(), head.L1(), head.N2(),
              ListRecord( begin, end, lineNumber, head.MAT(), 2, 152 ) ) {

          readSEND( begin, end, lineNumber, MAT, 2 );
      } catch( std::exception& e ){
        Log::info( "Trouble while reading section 152 of File 2 of Material {}",
                   MAT );
        throw e;
      }

    Type( const Type& base ) :
      BaseWithoutMT( base.ZA(), base.AWR() ),
      lssf_( base.lssf_ ), interpolation_( base.interpolation_ ),
      data_( base.data_ ) {

      this->generateArrays();
    }

    Type( Type&& base ) :
      BaseWithoutMT( base.ZA(), base.AWR() ),
      lssf_( base.lssf_ ), interpolation_( base.interpolation_ ),
      data_( std::move( base.data_ ) ) {

      this->generateArrays();
    }

    Type& operator=( const Type& base ) {

      if ( this != &base ) {

        BaseWithoutMT::operator=( base );
        this->lssf_ = base.lssf_;
        this->interpolation_ = base.interpolation_;
        this->data_ = base.data_;
        this->generateArrays();
      }
      return *this;
    }

    Type& operator=( Type&& base ) {

      if ( this != &base ) {

        BaseWithoutMT::operator=( std::move( base ) );
        this->lssf_ = base.lssf_;
        this->interpolation_ = base.interpolation_;
        this->data_ = std::move( base.data_ );
        this->generateArrays();
      }
      return *this;
    }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 152; }

    /**
     *  @brief Return the self-shielding only flag
     */
    bool LSSF() const { return this->lssf_; }

    /**
     *  @brief Return the self-shielding only flag
     */
    bool selfShieldingOnly() const { return this->LSSF(); }

    /**
     *  @brief Return the interpolation flag
     */
    int interpolation() const { return this->interpolation_; }

    /**
     *  @brief Return the temperature
     */
    double TEMZ() const { return this->data_.C1(); }

    /**
     *  @brief Return the temperature
     */
    double temperature() const { return this->TEMZ(); }

    /**
     *  @brief Return the number of data values
     */
    int NW() const { return this->data_.NPL(); }

    /**
     *  @brief Return the number of data values
     */
    int numberValues() const { return this->NW(); }

    /**
     *  @brief Return the number of reactions (normally 5)
     */
    int NREAC() const { return this->data_.L1(); }

    /**
     *  @brief Return the number of reactions (normally 5)
     */
    int numberReactions() const { return this->NREAC(); }

    /**
     *  @brief Return the number of dilution or sigma zero values
     */
    int NSIGZ() const { return this->data_.L2(); }

    /**
     *  @brief Return the number of dilution or sigma zero values
     */
    int numberDilutions() const { return this->NSIGZ(); }

    /**
     *  @brief Return the dilution or sigma zero values
     */
    auto SIGZ() const {

      using namespace njoy::tools;
      return this->data_.list() | std20::views::take( this->NSIGZ() );
    }

    /**
     *  @brief Return the dilution or sigma zero values
     */
    auto dilutions() const { return this->SIGZ(); }

    /**
     *  @brief Return the number of energy values
     */
    int NUNR() const { return this->data_.N2(); }

    /**
     *  @brief Return the number of energy values
     */
    int numberEnergies() const { return this->NUNR(); }

    /**
     *  @brief Return the unresolved resonance energies
     */
    auto EUNR() const {

      using namespace njoy::tools;
      return this->data_.list()
               | std20::views::drop( this->NSIGZ() )
               | std23::views::stride( 1 + this->NSIGZ() * 5 );
    }

    /**
     *  @brief Return the unresolved resonance energies
     */
    auto energies() const {

      return this->EUNR();
    }

    /**
     *  @brief Return the total cross section values for each energy and dilution
     */
    auto total() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_[0] );
    }

    /**
     *  @brief Return the elastic cross section values for each energy and dilution
     */
    auto elastic() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_[1] );
    }

    /**
     *  @brief Return the fission cross section values for each energy and dilution
     */
    auto fission() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_[2] );
    }

    /**
     *  @brief Return the capture cross section values for each energy and dilution
     */
    auto capture() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_[3] );
    }

    /**
     *  @brief Return the current weighted cross section values for each
     *         energy and dilution
     */
    auto currentWeightedTotal() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_[4] );
    }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::AWR;

    /**
     *  @brief Print the MF2/MT152 section (includes SEND record)
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
                     this->LSSF(), 0,
                     0, this->interpolation() ).print( it, MAT, MF, MT );
      this->data_.print( it, MAT, MF, MT );
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the number of lines in this MF2/MT152 section
     */
    long NC() const {

      return 1 + this->data_.NC();
    }
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
