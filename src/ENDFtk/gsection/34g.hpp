#ifndef NJOY_ENDFTK_GSECTION_34
#define NJOY_ENDFTK_GSECTION_34

// system includes
#include <numeric>
#include <map>
#include <algorithm>

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/DataRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "tools/Log.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template < >
  class ENDFTK_PYTHON_EXPORT GType< 34 > : protected Base {

    /* fields */

    int l_;
    int l1_;
    int irelco_;
    std::vector< std::vector< double > > ang_covr_;

    /* auxiliary functions */

    template<typename Iterator>
    static auto readRecords( Iterator& it, const Iterator& end, long& lineNumber,
                             int MAT, int MF, int MT ) {

      std::vector< DataRecord > records;
      int ngn;

      ControlRecord cont( it, end, lineNumber, MAT, MF, MT );
      ngn = cont.N2();

      do {

        records.emplace_back(it, end, lineNumber, MAT, MF, MT);
      }
      while ( records.back().IG() < ngn );

      return std::make_tuple( ngn, records );
    }

    static auto
    makeRecords( const std::vector <std::vector< double > >& ang_covr ) {

      std::vector< DataRecord > records;
      std::size_t ngn = ang_covr.size();

      for ( std::size_t g_i = 0; g_i < ngn; ++g_i ) {

        std::vector< double > list;

        auto it2 = std::find_if( ang_covr[g_i].begin(), ang_covr[g_i].end(),
                                 [] ( auto&& val ) {return val != 0.0; } );
        std::size_t ig2lo = std::distance( ang_covr[g_i].begin(), it2 ) + 1;

        for ( std::size_t g_o = 0; g_o < ngn; ++g_o ) {

            if ( ang_covr[g_i][g_o] != 0.0 ) {

                list.emplace_back( ang_covr[g_i][g_o] );
            } // endif
        } // sec. erg
        // check for zeros in last incident group

        if (  g_i == ngn - 1 ) {

            if ( std::all_of( ang_covr[g_i].begin(), ang_covr[g_i].end(),
                    []( double val ) { return val == 0.0; } ) ) {

                list.emplace_back( 0.0 );
                ig2lo = ngn;
            } // endif
        } // endif

        if ( list.size() != 0 ) {

            records.emplace_back( 0.0, list.size(), ig2lo, g_i + 1, std::move( list ) );
        } // endif
      } // inc. erg.

      return records;
    }

    static auto
    makeMatrices( const std::vector< DataRecord > records,
                  int ngroups) {

      std::size_t number_groups = ngroups;
      std::vector< std::vector< double > > ang_covr( number_groups, std::vector< double > ( number_groups, 0.0 ) );

      for ( const auto& record : records ) {

        std::size_t g_i = record.IG() - 1; // g_i = inc. erg
        std::size_t entry = 0;
        for ( std::size_t g_o = record.IG2LO() - 1; g_o < number_groups; ++g_o ) { // g_o = sec erg

          ang_covr[g_i][g_o] = record.list()[ entry ];
          ++entry;
        } // g_o
      } // records

      return ang_covr;
    }

    /* constructor */

    GType( int mt, int zaid, double awr, int irelco, int l, int l1, int ngn,
           std::vector< DataRecord >&& records ) :
        GType( mt, zaid, awr, irelco, l, l1,
               makeMatrices( records, ngn ) ) {}

    GType( int mt, int zaid, double awr, int irelco, int l, int l1,
           std::tuple< int, std::vector< DataRecord > >&& data ) :
        GType( mt, zaid, awr, irelco, l, l1,
               std::get<0>( data ),                     // ngn
               std::move( std::get<1>( data ) ) ) {}    // records

  public:

    /* constructor */

    /**
     *  @brief Constructor for angular covariance matrix
     *
     *  @param[in] mt           the section number
     *  @param[in] zaid         the ZAID identifier
     *  @param[in] awr          the atomic weight ratio
     *  @param[in] irelco       the covariance format
     *  @param[in] l            the legendre order
     *  @param[in] l1           the second legendre order
     *  @param[in] ngn          the number of neutron groups
     *  @param[in] ang_covr     the angular covariance matrix
     */
    GType( int mt, int zaid, double awr, int irelco, int l, int l1,
           std::vector< std::vector< double > > ang_covr ) :
        Base( zaid, awr, mt ),
        l_( l ),
        l1_( l1 ),
        irelco_( irelco ),
        ang_covr_( std::move( ang_covr ) ) {}

    /**
     *  @brief Constructor from buffer/string
     *
     *  @param[in] head         the head record of the section
     *  @param[in] begin        the start of the iterator
     *  @param[in] end          the end for the iterator
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     */
    template< typename Iterator >
    GType( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
        try:
            GType( head.MT(), head.ZA(), head.AWR(), head.L2(), head.N1(), head.N2(),
                   readRecords( begin, end, lineNumber, head.MAT(), head.MF(), head.MT() ) ) {

            this->readSEND(begin, end, lineNumber, MAT, head.MF() );
        }
        catch( std::exception& e ) {

            Log::info( "Encountered error while reading section {} of file {} for material {}"
                       " in GENDF file.", head.MT(), head.MF(), head.MAT());
            throw e;
        }

    /* methods */

    /**
     *  @brief Return the primary legendre order
     */
    int L() const {

      return this->l_;
    }

    /**
     *  @brief Return the primary legendre order
     */
    int primaryLegendre() const {

      return this->L();
    }

    /**
     *  @brief Return the secondary legendre order
     */
    int L1() const {

      return this->l1_;
    }

    /**
     *  @brief Return the secondary legendre order
     */
    int secondaryLegendre() const {

      return this->L1();
    }

    /**
     *  @brief Return the covariance format (0/1 -> abs./rel.)
     */
    int IRELCO() const {

      return this->irelco_;
    }

    /**
     *  @brief
     */
    int covarianceFormat() const {

      return this->IRELCO();
    }

    /**
     *  @brief Return the number of neutron groups.
     */
    int NGN() const {

      return this->ang_covr_.size();
    }

    /**
     *  @brief Return the number of neutron groups.
     */
    int numberNeutronGroups() const {

      return this->NGN();
    }

    /**
     * @brief Return the secondary angular distribution covariance matrix.
     */
    const std::vector< std::vector< double > >& angularCovariance() const{

      return this->ang_covr_;
    }

    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = this->MT();
      ControlRecord( this->ZA(), this->AWR(), 0, this->IRELCO(),
                     this->L() , this->L1() ).print( it, MAT, MF, MT );

      ControlRecord( 0.0, 0.0, MT, this->L(), this->L1(),
                     this->NGN() ).print(it, MAT, MF, MT);

      auto records = makeRecords( this->ang_covr_ );

      for ( const auto& record : records ) {
          record.print( it, MAT, MF, MT );
      } // record

      SEND( MAT, MF ).print( it );
    }

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::targetIdentifier;
    using Base::AWR;
    using Base::atomicWeightRatio;
  };

} // section
} // ENDFtk
} // njoy

#endif // NJOY_ENDFTK_GSECTION_34
