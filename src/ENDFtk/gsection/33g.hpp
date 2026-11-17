#ifndef NJOY_ENDFTK_GSECTION_33
#define NJOY_ENDFTK_GSECTION_33

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
  class ENDFTK_PYTHON_EXPORT GType< 33 > : protected Base {

    /* fields */

    int lmt_;
    int lr_;
    int ngn_;
    std::map< std::size_t, std::vector< std::vector< double > > > covariances_;
    std::vector< std::size_t > reactions_;

    /* auxiliary functions */

    static auto
    makeMatrices( const std::vector< std::pair< std::size_t, std::vector< DataRecord > > > records,
                  int ngroups ) {

      std::map< std::size_t, std::vector< std::vector< double > > > covr_matrices;

      if ( records.size() != 0 ) {

        for ( const auto& matrix : records ) {

          std::size_t sec_mt = matrix.first;

          if ( matrix.second.size() != 0 ) {

            covr_matrices[ sec_mt ]  = std::vector< std::vector< double > >
                                       ( ngroups, std::vector< double >( ngroups, 0.0 ) );
            for ( const auto& record : matrix.second ) {

              auto g_i = ( record.IG() - 1 );
              std::size_t idx = 0;
              std::size_t iglo = record.IG2LO();
              for ( std::size_t g_o = iglo - 1; g_o < iglo + record.NW() - 1; ++g_o ) {

                covr_matrices[ sec_mt ][g_i][g_o] = record.list()[ idx ];
                ++idx;
              } // outgoing energy
            } // records
          } // endif
        } // matrix
      } //endif

      return covr_matrices;
    }

    static auto
    makeRecords( const std::map< std::size_t, std::vector< std::vector< double > > >& covr ) {

      std::vector< DataRecord > records;
      for ( auto it = covr.begin(); it != covr.end(); ++it ) {

        std::size_t sec_mt = it->first;
        const auto& matrix = it->second;
        std::size_t ngn = matrix.size();
        // Each matrix is preceded with ControlRecord detailing the sec_rxn
        // Here we mimic the ControlRecord with a DataRecord
        records.emplace_back( 0.0, 0, sec_mt, ngn, std::vector<double>{} );
        for ( std::size_t g_i = 0; g_i < ngn; ++g_i ) {

          std::vector< double > list;

          auto it2 = std::find_if( matrix[g_i].begin(), matrix[g_i].end(),
                                   [] ( auto&& val ) { return val != 0.0; } );
          std::size_t ig2lo = std::distance( matrix[g_i].begin(), it2 ) + 1;

          for ( std::size_t g_o = 0; g_o < ngn; ++g_o ) {

              if ( ( matrix[g_i][g_o] != 0.0 ) ) {

                  list.emplace_back( matrix[g_i][g_o] );
              }
          } // secondary mt erg
          // check for zeros in last incident group
          if (  g_i == ngn - 1 ) {

              if ( std::all_of( matrix[g_i].begin(), matrix[g_i].end(),
                    []( double val ) { return val == 0.0; } ) ) {

                list.emplace_back( 0.0 );
                ig2lo = ngn;
              } // endif
          } // endif
          if ( list.size() != 0 ) {

              records.emplace_back( 0.0, list.size(), ig2lo, g_i + 1, std::move( list ) );
          } // endif
        } // primary mt erg
      } // matrix

      return records;
    }

    template< typename Iterator >
    static auto readRecords( Iterator& it, const Iterator& end, long& lineNumber,
                             int MAT, int MF, int MT, int num_matrices ) {

      std::vector< std::pair< std::size_t, std::vector< DataRecord > > > records;
      int ngn;
      for ( int m = 0; m < num_matrices; ++m ) {

        ControlRecord cont( it, end, lineNumber, MAT, MF, MT );
        std::size_t sec_rxn = cont.L2();
        records.emplace_back( sec_rxn, std::vector< DataRecord >{} );
        ngn = cont.N2();

        do {

            records.back().second.emplace_back( it, end, lineNumber, MAT, MF, MT );
        }
        while ( records.back().second.back().IG() < ngn );
      }

      return std::make_tuple( ngn, records );
    }

    void generateReactions() {

      this->reactions_.clear();
      this->reactions_.resize( this->covariances_.size() );
      std::transform( this->covariances_.begin(), this->covariances_.end(),
                      this->reactions_.begin(),
                      [] ( auto&& pair ) { return pair.first; } );
    }

    /* constructor */

    GType( int mt, int zaid, double awr, int lmt, int lr, int ngn,
           std::vector< std::pair< std::size_t, std::vector< DataRecord > > >&& records ) :
        GType( mt, zaid, awr, lmt, lr, ngn,
               makeMatrices( records, ngn ) ) {}

    GType( int mt, int zaid, double awr, int lmt, int lr, std::tuple< int,
           std::vector< std::pair< std::size_t, std::vector< DataRecord > > > >&& data ) :
        GType( mt, zaid, awr, lmt, lr,
               std::get<0>( data ),                     // ngn
               std::move( std::get<1>( data ) ) ) {}    // records

  public:

    /* constructor */

    /**
     *  @brief Constructor for covariance matrices
     *
     *  @param[in] mt           the section number
     *  @param[in] zaid         the ZAID identifier
     *  @param[in] awr          the atomic weight ratio
     *  @param[in] lmt          the lumped reaction number (0 is undefined)
     *  @param[in] lr           the break-up identifier flag
     *  @param[in] ngn          the number of neutron groups
     *  @param[in] covr         the covariance matrices
     */
    GType( int mt, int zaid, double awr, int lmt, int lr, int ngn,
           std::map< std::size_t, std::vector< std::vector< double > > > covr ) :
        Base( zaid, awr, mt ),
        lmt_( lmt ),
        lr_( lr ),
        ngn_( ngn ),
        covariances_( std::move( covr ) ) {

      this->generateReactions();
    }

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
    template< typename Iterator >
    GType( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
        try:
            GType( head.MT(), head.ZA(), head.AWR(), head.L2(), head.N1(),
                   readRecords( begin, end, lineNumber, head.MAT(), head.MF(),
                                head.MT(), head.N2() ) ) {
            this->readSEND(begin, end, lineNumber, MAT, head.MF() );
        }
        catch( std::exception& e ) {

            Log::info( "Encountered error while reading section {} of file {} for material {}"
                       " in GENDF file.", head.MT(), head.MF(), head.MAT());
            throw e;
        }

    /* methods */

    /**
     *  @brief Return the lumped covariance index (0 is not defined)
     */
    int MTL() const {

      return this->lmt_;
    }

    /**
     *  @brief Return the lumped covariance index (0 is not defined)
     */
    int lumpedCovarianceIndex() const {

      return this->MTL();
    }

    /**
     *  @brief Return the breakup flag.
     */
    int LRFLAG() const {

      return this->lr_;
    }

    /**
     *  @brief Return the breakup flag.
     */
    int breakUp() const {

      return this->LRFLAG();
    }

    /**
     *  @brief Return the number of neutron groups.
     */
    int NGN() const {

      return this->ngn_;
    }

    /**
     *  @brief Return the number of neutron groups.
     */
    int numberNeutronGroups() const {

      return this->NGN();
    }

    /**
     *  @brief Return the present secondary reactions.
     */
    auto secondaryReactions() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_ );
    }

    /**
     *  @brief Return the number of secondary reactions.
     */
    std::size_t NSMT() const {

      return this->covariances_.size();
    }

    /**
     *  @brief Return the number of secondary reactions.
     */
    std::size_t numberSecondaryReactions() const {

      return this->NSMT();
    }

    /**
     *  @brief Return the covariance matrix for a given secondary mt number
     *
     *  @param[in] mt   the requested secondary mt number
     */
    decltype(auto) covariance ( std::size_t mt ) const {

      auto iter = this->covariances_.find( mt );
      if ( iter != this->covariances_.end() ) {

        return iter->second;
      }
      else {

        throw std::runtime_error( "Requested secondary reaction is not present");
      }
    }

    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = this->MT();
      if ( this->covariances_.begin()->second.empty() ) {

          ControlRecord( this->ZA(), this->AWR(), 0, this->MTL(),
                         this->LRFLAG(), 0 ).print( it, MAT, MF, MT );
      } // endif
      else {

          ControlRecord( this->ZA(), this->AWR(), 0, 0, this->LRFLAG(),
                      this->NSMT() ).print( it, MAT, MF, MT );
          auto records = makeRecords( this->covariances_ );
          for ( const auto& record : records )       {

              record.print( it, MAT, MF, MT );
          }
      }
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

#endif // NJOY_ENDFTK_GSECTION_33
