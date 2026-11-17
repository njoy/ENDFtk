#ifndef NJOY_ENDFTK_GSECTION_5_455
#define NJOY_ENDFTK_GSECTION_5_455

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
  class ENDFTK_PYTHON_EXPORT GType< 5, 455 > : protected BaseWithoutMT< GType< 5, 455 > > {

    friend BaseWithoutMT< GType< 5, 455 > >;

    /* fields */

    int lr_;
    double temp_;
    int ng2_;
    // for the delayed time constants (lambda) the size is nl which is the time index
    std::vector< double > lambda_;
    // for the neutron spectra, the size is ( nl, ng2 - 1 )
    std::vector< std::vector< double > > chi_;
    // NOTE: NZ is always 1 for MF5

    /* auxiliary functions */

    static auto
    makeVectors( const DataRecord& record,
                 int ntimes, int ngroups ) {

      std::vector< double > lambda;
      std::vector< std::vector< double > > chi;
      double temp;

      if ( ntimes <= 0 || ngroups <= 0 ) {

        throw std::runtime_error( "Number of times and groups cannot be "
                                  "less than or equal to 0" );
      }
      std::size_t number_times = ntimes;
      std::size_t number_groups = ngroups;
      std::size_t ng2 = record.NG2();

      if ( record.list().size() != 0 ) {

        chi.resize( number_times );
        temp = record.TEMP();

        lambda.resize( number_times );
        for ( std::size_t t = 0; t < number_times; ++t ) {

          lambda[t] = record.list()[ t ];

          for ( std::size_t g = 0; g < ( ng2 - 1 ); ++g ) {

            if ( chi[t].size() == 0 ) {

                chi[t] = std::vector< double > (number_groups, 0. );
            } // endif
            chi[t][g] = record.list()[ number_times * ( g + 1 ) + t ];
          } // groups
        } // times
      } // endif


      return std::make_tuple(temp, ng2, std::move( chi ), std::move( lambda ) );
    }

    static auto
    makeRecord( double temp,
                int ng2,
                const std::vector< double >& lambda,
                const std::vector< std::vector< double > >& chi ) {

      if ( ng2 <= 0 ) {

        throw std::runtime_error( "Number of outgoing groups cannot be "
                                  "less than or equal to 0" );
      }
      std::size_t number_groups = ng2;

      int ig2lo = 1;
      auto ntimes = lambda.size();
      std::size_t ngroups = chi.front().size();

      std::vector < double > list;
      list = std::move( lambda );
      for  ( std::size_t g = 0; g < ( number_groups - 1 ); ++g ) {

          for ( std::size_t t = 0; t < ntimes; ++t ) {

              list.emplace_back( chi[t][g] );
          }
      }

      return DataRecord( temp, ng2, ig2lo, ngroups, std::move ( list ) );
    }

    /* constructor */

    GType( int zaid, double awr, int lr,
           std::tuple< double,
                       int,
                       std::vector< std::vector< double > >,
                       std::vector< double > >&& data ) :
        GType( zaid, awr, lr,
               std::move( std::get<0>( data ) ),        // temp
               std::move( std::get<1>( data ) ),        // ng2
               std::move( std::get<2>( data ) ),        // chi
               std::move( std::get<3>( data ) ) ) {}    // lambda

    GType( int zaid, double awr, int nt, int lr, int ngn,
           DataRecord&& record ) :
        GType( zaid, awr, lr,
               makeVectors( record, nt, ngn ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Constructor from parameters for delayed fission spectrum
     *
     *  @param[in]  zaid        the ZAID identifier
     *  @param[in]  awr         the atomic weight ration
     *  @param[in]  lr          the break-up identifier flag
     *  @param[in]  temp        the temperature
     *  @param[in]  ng2         number of secondary positions (needed for clipped records)
     *  @param[in]  chi         the delayed neutron spectrum
     *  @param[in]  lambda      the time constants
     */
    GType( int zaid, double awr, int lr, double temp, int ng2,
           std::vector< std::vector< double > > chi,
           std::vector< double > lambda ) :
        BaseWithoutMT( zaid, awr ),
        lr_( lr ),
        temp_( temp ),
        ng2_( ng2 ),
        lambda_( std::move( lambda ) ),
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
      try:
            GType( head.ZA(), head.AWR(), head.L1(),
                   head.N1(), head.N2(),
            DataRecord( begin, end, lineNumber, head.MAT(), head.MF(), 455 ) ) {

        this->readSEND( begin, end, lineNumber, MAT, head.MF() );
      }
      catch(std::exception& e) {

        Log::info( "Encountered error while reading section {} of file {} fo material {}"
                   " in GENDF file.", 455, head.MF(), head.MAT());
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the number of time constants
     */
    int NT() const { return this->chi_.size(); }

    /**
     *  @brief Return the number of time constants
     */
    int numberTimeConstants() const { return this->NT(); }

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
    int NGN() const { return this->chi_.front().size(); }

    /**
     *  @brief Return the number of neutron groups
     */
    int numberNeutronGroups() const { return this->NGN(); }

    /**
     *  @brief Return the delayed neutron time constants
     */
    const std::vector< double >& lambda() const { return this->lambda_;}

    /**
     *  @brief Return the delayed neutron spectra for a given time constant
     */
    const std::vector< double >& chi( int timeConstant ) const {
        return this->chi_[timeConstant];
    }

    template < typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = 455;
      ControlRecord( this->ZA(), this->AWR(), this->NT(), this->NZ(),
                     this->LR(), this->NGN() ).print( it, MAT, MF, MT );
      auto record = makeRecord( this->temp_, this->ng2_, this->lambda_, this->chi_ );
      record.print( it, MAT, MF, MT );
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the section number
     */
    static constexpr int sectionNumber() { return 455; }

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