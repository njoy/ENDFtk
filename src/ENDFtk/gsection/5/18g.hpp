#ifndef NJOY_ENDFTK_GSECTION_5_18
#define NJOY_ENDFTK_GSECTION_5_18

// system includes
#include <numeric>

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/DataRecord.hpp"
#include "ENDFtk/section.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template <>
  class ENDFTK_PYTHON_EXPORT GType< 5, 18 > : protected BaseWithoutMT< GType< 5, 18 > > {

    friend BaseWithoutMT< GType< 5, 18 > >;

    /* fields */

    int lr_;
    double temp_;
    std::vector< double > chi_;
    // NOTE: NZ is always 1 for MF5

    /* auxiliary functions */

    static auto
    makeVectors( const DataRecord& record, int ngroups ) {

      if ( ngroups <= 0 ) {

        throw std::runtime_error( "Number of groups cannot be less than or equal to 0" );
      }
      std::size_t number_groups = ngroups;

      double temp;
      std::vector< double > chi( number_groups );

      if ( record.list().size() != 0 ) {

          temp = record.TEMP();

          for ( unsigned int g = 0; g < number_groups; ++g) {

              chi[g] = record.list()[ g ];
          } // groups
      } // endif

      return std::make_tuple( temp, std::move( chi ) );
    }

    static auto
    makeRecord( double temp,
                const std::vector< double >& chi ) {

      // int nz is always one for this section
      int ig2lo = 1;
      unsigned int ngroups = chi.size();

      std::vector< double > list( ngroups );
      list = std::move( chi );

      return DataRecord( temp, ngroups, ig2lo, ngroups, std::move ( list ) );
    }

    /* constructor */

    GType( int zaid, double awr, int lr,
           std::tuple< double,
           std::vector< double > >&& data ) :
        GType( zaid, awr, lr,
               std::move( std::get< 0 >( data ) ),        // temp
               std::move( std::get< 1 >( data ) ) ) {}    // chi

    GType( int zaid, double awr, int lr, int ngn,
           DataRecord&& record ) :
        GType( zaid, awr, lr,
               makeVectors( record, ngn ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Constructor from parameters for prompt fission spectrum
     *
     *  @param[in]  zaid        the ZAID identifier
     *  @param[in]  awr         the atomic weight ration
     *  @param[in]  lr          the break-up identifier flag
     *  @param[in]  temp        the temperature
     *  @param[in]  chi         the prompt neutron spectrum
     */
    GType( int zaid, double awr, int lr, double temp,
           std::vector< double > chi ) :
        BaseWithoutMT( zaid, awr ),
        lr_( lr ),
        temp_( temp ),
        chi_( std::move( chi ) ) {}

    /**
     *  @brief Constructor from buffer/string
     *
     *  @tparam Iterator        buffer iterator
     *
     *  @param[in] head         the head record of the section
     *  @param[in] begin        the start for the iterator
     *  @param[in] end          the end for the iterator
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     */
    template<typename Iterator>
    GType(const HEAD& head,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT)
      try: GType( head.ZA(), head.AWR(), head.N1(), head.N2(),
                  DataRecord( begin, end, lineNumber, head.MAT(), head.MF(), 18 ) ) {

        this->readSEND( begin, end, lineNumber, MAT, head.MF() );
      }
      catch(std::exception& e) {

        Log::info( "Encountered error while reading section {} of file {} fo material {}"
                   " in GENDF file.", 18, head.MF(), head.MAT() );
        throw e;
      }


    /* methods */

    /**
     *  @brief Return the number of dilutions
     */
    int NZ() const { return 1; }

    /**
     *  @brief Return the number of dilutions
     */
    int numberDilutions() const { return this->NZ(); }

    /**
     *  @brief Return the break up identifier flag
     */
    int LR() const { return this->lr_; }

    /**
     *  @brief Return the break up identifier flag
     */
    int breakUp() const { return this->LR(); }

    /**
     *  @brief Return the temperature
     */
    double TEMP() const { return this->temp_; }

    /**
     *  @brief Return the temperature
     */
    double temperature() const { return this->TEMP(); }

    /**
     *  @brief Return the number of neutron groups
     */
    int NGN() const { return this->chi_.size(); }

    /**
     *  @brief Return the number of neutron groups
     */
    int numberNeutronGroups() const { return this->NGN(); }

    /**
     *  @brief Return the prompt fission neutron spectra
     */
    const std::vector< double >& chi() const { return this->chi_; }

    template < typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = 18;
      ControlRecord( this->ZA(), this->AWR(), 1, this->NZ(),
                     this->LR(), this->NGN() ).print( it, MAT, MF, MT );
      auto record = makeRecord( this->temp_, this->chi_ );
      record.print( it, MAT, MF, MT );
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the section number
     */
    static constexpr int sectionNumber() { return 18; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section
} // ENDFtk
} // njoy

#endif