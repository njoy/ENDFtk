#ifndef NJOY_ENDFTK_SECTION_1_451
#define NJOY_ENDFTK_SECTION_1_451

// system includes

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/TextRecord.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/readSequence.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF1 MT451 - descriptive data and directory
   *
   *  See ENDF102, section 1.1 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 1, 451 > :
    protected BaseWithoutMT< Type< 1, 451 > > {

    friend BaseWithoutMT< Type< 1, 451 > >;

    /* fields */

    int lrp_;
    int lfi_;
    int nlib_;
    int nmod_;
    std::array< ControlRecord, 3 > parameters_;
    std::vector< TextRecord > description_;
    std::vector< DirectoryRecord > index_;

    /* auxiliary functions */

    static auto
    makeParameters( double elis, double sta, int lis, int liso, int nfor,
                    double awi, double emax, int lrel, int nsub, int nver,
                    double temp, double rtol, int ldrv, int nwd, int nxc ) {

      auto line0 = ControlRecord( elis, sta, lis, liso, 0, nfor );
      auto line1 = ControlRecord( awi, emax, lrel, 0, nsub, nver );
      auto line2 = ControlRecord( temp, rtol, ldrv, 0, nwd, nxc );
      return std::array< ControlRecord, 3 >{{ line0, line1, line2 }};
    }

    static
    std::vector< TextRecord >
    makeDescription( const std::string& description ) {

      std::vector< TextRecord > result;
      auto begin = description.begin();
      auto iter = std::find_if( begin, description.end(),
                                [] ( auto&& character ) { return character == '\n'; } );
      while ( begin != description.end() &&  iter != description.end() ) {

        result.emplace_back( std::string( begin, iter ) );
        begin = iter + 1;
        iter = std::find_if( begin, description.end(),
                             [] ( auto&& character ) { return character == '\n'; } );
      }

      if ( iter == description.end() && begin != description.end() ){
    	  result.emplace_back( std::string( begin, iter ) );
      }

      return result;
    }

    template< typename Iterator >
    static auto
    readParameters( Iterator& it, const Iterator& end, long& lineNumber, int MAT ) {

      auto line0 = ControlRecord( it, end, lineNumber, MAT, 1, 451 );
      auto line1 = ControlRecord( it, end, lineNumber, MAT, 1, 451 );
      auto line2 = ControlRecord( it, end, lineNumber, MAT, 1, 451 );
      if ( line2.N1() < 0 ){
        Log::error( "Number of descriptive records (NWD) must be greater than or equal to zero" );
        Log::info( "See line {}", lineNumber - 1 );
        throw std::runtime_error("Number of descriptive records (NWD) must be greater than or equal to zero");
      }
      if ( line2.N2() < 1 ){
        Log::error( "Number of index records (NXC) must be greater than or equal to one" );
        Log::info( "See line {}", lineNumber - 1 );
        throw std::runtime_error("Number of index records (NXC) must be greater than or equal to one");
      }
      return std::array< ControlRecord, 3 >{{ line0, line1, line2 }};
    }

    /* constructor */

    /**
     *  @brief Private constructor
     */
    Type( int zaid, double awr, int lrp, int lfi, int nlib, int nmod,
          std::array< ControlRecord, 3 >&& parameters,
          std::vector< TextRecord >&& description,
          std::vector< DirectoryRecord >&& index ) :
      BaseWithoutMT( zaid, awr ), lrp_( lrp ), lfi_( lfi ), nlib_( nlib ), nmod_( nmod ),
      parameters_( std::move( parameters ) ),
      description_( std::move( description ) ),
      index_( std::move( index ) ) {}

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
     *  @param[in] zaid          the ZA value of the material
     *  @param[in] awr           the atomic weight ratio
     *  @param[in] lrp           the resonance parameter flag
     *  @param[in] lfi           the fissile flag
     *  @param[in] nlib          the library type
     *  @param[in] nmod          the modification number
     *  @param[in] elis          the excitation energy
     *  @param[in] sta           the stability flag (whether or not the nuclide is unstable)
     *  @param[in] lis           the excited level number
     *  @param[in] liso          the isomeric state number
     *  @param[in] nfor          the library format version number
     *  @param[in] awi           the atomic weight ratio of the incident particle
     *  @param[in] emax          the maximum incident energy
     *  @param[in] lrel          the release number
     *  @param[in] nsub          the sublibrary number
     *  @param[in] nver          the version number
     *  @param[in] temp          the temperature
     *  @param[in] ldrv          the derived material flag
     *  @param[in] description   the descriptive information
     *  @param[in] index         the index
     *  @param[in] rtol          the reconstruction tolerance (internal NJOY value)
     */
    Type( int zaid, double awr, int lrp, int lfi, int nlib, int nmod,
          double elis, double sta, int lis, int liso, int nfor,
          double awi, double emax, int lrel, int nsub, int nver,
          double temp, int ldrv,
          const std::string& description,
          std::vector< DirectoryRecord >&& index,
          double rtol = 0. ) :
      BaseWithoutMT( zaid, awr ), lrp_( lrp ), lfi_( lfi ), nlib_( nlib ), nmod_( nmod ),
      parameters_( makeParameters( elis, sta, lis, liso, nfor,
                                   awi, emax, lrel, nsub, nver,
                                   temp, rtol, ldrv,
                                   njoy::tools::std20::distance( njoy::tools::std20::views::split( description, '\n' ) ),
                                   index.size() ) ),
      description_( makeDescription( description ) ),
      index_( std::move( index ) ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] head         the head record of the section
     *  @param[in] begin        the current position in the buffer
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
      try :

        BaseWithoutMT( head, MAT, 1 ), lrp_( head.L1() ), lfi_( head.L2() ),
        nlib_( head.N1() ), nmod_( head.N2() ),
        parameters_( readParameters( begin, end, lineNumber, MAT ) ),
        description_( readSequence< TextRecord >(
                          begin, end, lineNumber, MAT, 1, 451,
                          this->parameters_[2].N1() ) ),
        index_( readSequence< DirectoryRecord >(
                    begin, end, lineNumber, MAT, 1, 451,
                    this->parameters_[2].N2() ) ) {
        readSEND(begin, end, lineNumber, MAT, 1 );
      }
      catch( std::exception& e ) {

        Log::info( "Trouble while reading section 451 of File 1 of Material {}",
                   MAT );
        Log::info( "lineNumber: {}", lineNumber );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the resonance parameter flag
     */
    int LRP() const { return this->lrp_; }

    /**
     *  @brief Return the resonance parameter flag
     */
    int resonanceParameterFlag() const { return this->LRP(); }

    /**
     *  @brief Return the fissile flag
     */
    int LFI() const { return this->lfi_; }

    /**
     *  @brief Return the fissile flag
     */
    bool isFissile() const { return this->LFI(); }

    /**
     *  @brief Return the library type
     */
    int NLIB() const { return this->nlib_; }

    /**
     *  @brief Return the library type
     */
    int libraryType() const { return this->NLIB(); }

    /**
     *  @brief Return the modification number
     */
    int NMOD() const { return this->nmod_; }

    /**
     *  @brief Return the modification number
     */
    int modificationNumber() const { return this->NMOD(); }

    /**
     *  @brief Return the excitation energy
     */
    double ELIS() const { return std::get< 0 >( this->parameters_ ).C1(); }

    /**
     *  @brief Return the excitation energy
     */
    double excitationEnergy() const { return this->ELIS(); }

    /**
     *  @brief Return the stability flag
     */
    double STA() const { return std::get< 0 >( this->parameters_ ).C2(); }

    /**
     *  @brief Return whether or not the nuclide is unstable
     */
    bool isUnstable() const { return this->STA() == 1; }

    /**
     *  @brief Return whether or not the nuclide is stable
     */
    bool isStable() const { return ! this->isUnstable(); }

    /**
     *  @brief Return the excited level number
     */
    int LIS() const { return std::get< 0 >( this->parameters_ ).L1(); }

    /**
     *  @brief Return the excited level number
     */
    int excitedLevel() const { return this->LIS(); }

    /**
     *  @brief Return the isomeric state number
     */
    int LISO() const { return std::get< 0 >( this->parameters_ ).L2(); }

    /**
     *  @brief Return the isomeric state number
     */
    int isomericLevel() const { return this->LISO(); }

    /**
     *  @brief Return the library format version number
     */
    int NFOR() const { return std::get< 0 >( this->parameters_ ).N2(); }

    /**
     *  @brief Return the library format version number
     */
    int libraryFormat() const { return this->NFOR(); }

    /**
     *  @brief Return the atomic weight ratio of the incident particle
     */
    double AWI() const { return std::get< 1 >( this->parameters_ ).C1(); }

    /**
     *  @brief Return the atomic weight ratio of the incident particle
     */
    double projectileAtomicMassRatio() const { return this->AWI(); }

    /**
     *  @brief Return the maximum energy
     */
    double EMAX() const { return std::get< 1 >( this->parameters_ ).C2(); }

    /**
     *  @brief Return the maximum energy
     */
    double maximumEnergy() const { return this->EMAX(); }

    /**
     *  @brief Return the release number
     */
    int LREL() const { return std::get< 1 >( this->parameters_ ).L1(); }

    /**
     *  @brief Return the release number
     */
    int releaseNumber() const { return this->LREL(); }

    /**
     *  @brief Return the sublibrary number
     */
    int NSUB() const { return std::get< 1 >( this->parameters_ ).N1(); }

    /**
     *  @brief Return the sublibrary number
     */
    int subLibrary() const { return this->NSUB(); }

    /**
     *  @brief Return the version number
     */
    int NVER() const { return std::get< 1 >( this->parameters_ ).N2(); }

    /**
     *  @brief Return the version number
     */
    int versionNumber() const { return this->NVER(); }

    /**
     *  @brief Return the temperature
     */
    double TEMP() const { return std::get< 2 >( this->parameters_ ).C1(); }

    /**
     *  @brief Return the temperature
     */
    double temperature() const { return this->TEMP(); }

    /**
     *  @brief Return the reconstruction tolerance
     */
    double RTOL() const { return std::get< 2 >( this->parameters_ ).C2(); }

    /**
     *  @brief Return the reconstruction tolerance
     */
    double reconstructionTolerance() const { return this->RTOL(); }

    /**
     *  @brief Return the derived material flag
     */
    int LDRV() const { return std::get< 2 >( this->parameters_ ).L1(); }

    /**
     *  @brief Return the derived material flag
     */
    int derivedMaterial() const { return this->LDRV(); }

    /**
     *  @brief Return the number of lines of descriptive data
     */
    int NWD() const { return static_cast< int >( this->description_.size() ); }

    /**
     *  @brief Return the number of index entries
     */
    int NXC() const { return static_cast< int >( this->index_.size() ); }

    /**
     *  @brief Return the index of available files and sections
     */
    auto index() const {

      using namespace njoy::tools;
      return std20::views::all( this->index_ );
    }

    /**
     *  @brief Return the number of lines in this MF1/MT451 section
     */
    long NC() const { return 4 + this->NWD() + this->NXC(); }

    /**
     *  @brief Return the descriptive data
     */
    auto description() const {

      std::string description;
      description.reserve( this->description_.size() * 67 );
      for ( auto&& record : this->description_ ) {

        description += record.text();
        description += '\n';
      }
      return description;
    }

    /**
     *  @brief Print the MF1/MT451 section (includes SEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = 451;
      ControlRecord( this->ZA(), this->AWR(), this->LRP(),this->LFI(),
                     this->NLIB(), this->NMOD() ).print( it, MAT, MF, MT );
      for ( const auto& entry : this->parameters_ ) entry.print( it, MAT, MF, MT );
      for ( const auto& entry : this->description_ ) entry.print( it, MAT, MF, MT );
      for ( const auto& entry : this->index_ ) entry.print( it, MAT, MF, MT );
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 451; }

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
