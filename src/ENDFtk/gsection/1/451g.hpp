#ifndef NJOY_ENDFTK_GSECTION_1_451
#define NJOY_ENDFTK_GSECTION_1_451

// system includes

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template <>
  class ENDFTK_PYTHON_EXPORT GType< 1, 451 > : protected BaseWithoutMT< GType< 1, 451 > > {

    friend BaseWithoutMT< GType< 1, 451 > >;

    /* fields */

    int nwt_;
    int ngt_;
    int nz_;
    ListRecord parameters_;

    /* auxiliary functions */

    static auto
    makeParameters( double temp,  std::vector< double > sigz,
                    std::vector< double > egn, std::vector< double > egg ) {

      std::vector< double > data = {};
      data.reserve( sigz.size() + egn.size() + egg.size() );

      auto ngn = egn.size() - 1;
      auto ngg = egg.size() - 1;

      data.insert( data.end(), sigz.begin(), sigz.end() );
      data.insert( data.end(), egn.begin(), egn.end() );
      data.insert( data.end(), egg.begin(), egg.end() );
      return ListRecord( temp, 0, ngn, ngg, 0, std::move( data ) );
    }

    static auto
    makeParameters( double temp, std::vector< double > egn ) {

      return ListRecord( temp, 0, egn.size() - 1, 0, 0, std::move( egn ) );
    }

    /* constructor */

    /**
     *  @brief Intermediate private constructor
     */
    GType( int zaid, double awr, int nz, int ngt, int nwt, ListRecord&& list ) :
        BaseWithoutMT(zaid, awr),
        nwt_( nwt ),
        ngt_( ngt ),
        nz_( nz ),
        parameters_( std::move( list ) ) {}

    /**
     *  @brief Intermediate private constructor
     */
    GType( int zaid, double awr, std::size_t nz, double temp,
           std::vector< double >&& sigz,
           std::vector< double >&& egn,
           std::vector< double >&& egg ) :
        GType( zaid, awr, nz, -1, 0,
               makeParameters( temp, std::move( sigz ),
                               std::move( egn ), std::move( egg ) ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Constructor for an ERRORR style MF1 MT451 section
     *
     *  @param[in] zaid   the ZA value of the material
     *  @param[in] awr    the atomic weight ratio
     *  @param[in] egn    the neutron group structure
     */
    GType( int zaid, double awr, double temp,
           std::vector< double > egn ) :
      GType( zaid, awr, 0, -11, 0,
             makeParameters( temp, std::move( egn ) ) ) {}

    /**
     *  @brief Constructor for a GROUPR style MF1 MT451 section
     *
     *  @param[in] zaid   the ZA value of the material
     *  @param[in] awr    the atomic weight ratio
     *  @param[in] temp   the temperature evaluated
     *  @param[in] sigz   the dilution values
     *  @param[in] egn    the neutron group structure
     *  @param[in] egg    the photon group structure
     */
    GType( int zaid, double awr, double temp,
           std::vector< double > sigz,
           std::vector< double > egn,
           std::vector< double > egg ) :
      GType( zaid, awr, sigz.size(), temp,
             std::move( sigz ), std::move( egn ), std::move( egg ) ) {}

    /**
     *  @brief Constructor (from buffer)
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
    GType( HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
      try : GType( head.ZA(), head.AWR(), head.L2(), head.N1(), head.N2(),
                   ListRecord( begin, end, lineNumber, MAT, 1, 451 ) ) {

        readFendOrSend(begin, end, lineNumber, MAT, 1 );
      }
      catch( std::exception& e ) {

        Log::info( "Trouble reading gsection 451 of File 1 of Material {}", MAT );
        Log::info( "lineNumber: {}", lineNumber );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the GENDF file type (-1 for GROUPR and -11 for ERRORR)
     */
    int NGT() const { return this->ngt_; }

    /**
     *  @brief Return the GENDF file type (-1 for GROUPR and -11 for ERRORR)
     */
    int type() const { return this->NGT(); }

    /**
     *  @brief Return the number of title words
     */
    int NWT() const { return this->nwt_; }

    /**
     *  @brief Return the number of title words (obsolete)
     */
    int numberTitleWords() const { return this->NWT(); }

    /**
     *  @brief Return the number of dilution values
     */
    int NZ() const { return this->nz_; }

    /**
     *  @brief Return the number of dilution values
     */
    int numberDilutions() const { return this->NZ(); }

    /**
     *  @brief Return the temperature
     */
    double TEMP() const { return this->parameters_.C1(); }

    /**
     *  @brief Return the temperature
     */
    double temperature() const {return this->TEMP();}

    /**
     *  @brief Return the number of neutron groups
     */
    int NGN() const { return this->parameters_.L1(); }

    /**
     *  @brief Return the number of neutron groups
     */
    int numberNeutronGroups() const { return this->NGN(); }

    /**
     *  @brief Return the number of photon groups
     */
    int NGG() const { return this->parameters_.L2(); }

    /**
     *  @brief Return the number of photon groups
     */
    int numberPhotonGroups() const { return this->NGG(); }

    /**
     *  @brief Return the dilution values
     */
    auto SIGZ() const {

      using namespace njoy::tools;
      return this->parameters_.list() | std20::views::drop( this->NWT() )
                                      | std20::views::take( this->NZ() );
    }

    /**
     *  @brief Return the dilution values
     */
    auto dilutions() const { return this->SIGZ(); }

    /**
     *  @brief Return the neutron group structure
     */
    auto EGN() const {

      using namespace njoy::tools;
      return this->parameters_.list() | std20::views::drop( this->NWT() + this->NZ() )
                                      | std20::views::take( this->NGN() + 1 );
    }

    /**
     *  @brief Return the neutron group structure
     */
    auto neutronStructure() const { return this->EGN(); }

    /**
     *  @brief Return the photon group structure
     */
    auto EGG() const {

      using namespace njoy::tools;
      return this->parameters_.list() | std20::views::drop( this->NWT() + this->NZ() + this->NGN() + 1 )
                                      | std20::views::take( this->NGG() + 1 );
    }

    /**
     *  @brief Return the photon group structure
     */
    auto photonStructure() const { return this->EGG(); }

    template <typename OutputIterator>
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT=451;
      ControlRecord( this->ZA(), this->AWR(), 0, this->NZ(),
                     this->NGT(), this->NWT() ).print(it, MAT, MF, MT );
      parameters_.print(it, MAT, MF, MT);
      FEND(MAT).print(it);
    }

    /**
     *  @brief Return the section number
     */
    static constexpr int sectionNumber() { return 451; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // gsection namespace
} // ENDFtk namespace
} // njoy namespace

#endif