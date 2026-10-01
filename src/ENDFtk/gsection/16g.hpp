#ifndef NJOY_ENDFTK_GSECTION_16
#define NJOY_ENDFTK_GSECTION_16

// system includes
#include <numeric>
#include <algorithm>

// other includes
#include "ENDFtk/macros.hpp"
#include "tools/std20/views.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/DataRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "tools/Log.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template < >
  class ENDFTK_PYTHON_EXPORT GType< 16 > : protected Base {

    /* fields */

    int lr_;
    int ngn_;
    double temp_;
    std::vector< std::vector< std::vector< double > > > flux_;
    std::vector< std::vector< std::vector< std::vector< double > > > > matrix_;

    /* auxiliary functions */

    static void
    verifySize( const std::vector< std::vector< std::vector< double > > >& flux,
                const std::vector< std::vector< std::vector< std::vector< double > > > >& matrix ) {

        auto ngroups = flux.size() > 0 ? flux.front().size() > 0
                                         ? flux.front().front().size()
                                         : 0
                                       : 0;
        auto ogroups = matrix.size() > 0 ? matrix.front().size() > 0
                                           ? matrix.front().front().size() > 0
                                             ? matrix.front().front().front().size()
                                             : 0
                                           : 0
                                         : 0;

        if (ngroups == 0) {

            Log::error( "The number of groups cannot be zero" );
            throw std::exception();
        }

        auto nmoments = matrix.size();
        if (nmoments == 0) {

            Log::error( "The number of moments cannot be zero" );
            throw std::exception();
        }

        if ( ( nmoments != matrix.size() ) || ( nmoments != flux.size() ) ) {

            Log::error( "The number of moments is not consistent across the flux and matrix" );
            Log::info( "flux.size() = {}", flux.size() );
            Log::info( "matrix.size() = {}", matrix.size() );

            Log::info( "expected {}", nmoments );
            throw std::exception();
        }

        auto ndilutions = matrix.front().size();
        if ( ndilutions == 0 ) {

            Log::error( "The number of dilutions cannot be zero" );
            throw std::exception();
        }
        for ( size_t l = 0; l < nmoments; ++l  ) {

            if ( ( ndilutions != flux[l].size() ) || ( ndilutions != matrix[l].size() ) ) {

                Log::error( "The number of dilutions is not consistent across the flux and matrix at moment {}", l );
                Log::info( "flux[l].size() = {}", flux[l].size() );
                Log::info( "matrix[l].size() = {}", matrix[l].size() );

                Log::info( "expected {}", ndilutions );
                throw std::exception();
            }

            for ( size_t z = 0; z < ndilutions; ++z ) {

                if ( ( ngroups != flux[l][z].size() ) || ( ngroups != matrix[l][z].size() ) ) {

                    Log::error( "The number of groups is not consistent across the flux and matrix at moment {} "
                                "and dilution {}", l, z);
                    Log::info( "flux[l][z].size() = {}", flux[l][z].size() );
                    Log::info( "matrix[l][z].size() = {}", matrix[l][z].size() );

                    Log::info( "expected {}", ngroups );
                    throw std::exception();
                }
                for ( size_t g_i = 0; g_i < ngroups; ++g_i ) {
                    if ( ogroups != matrix[l][z][g_i].size() ) {
                        Log::error( "The number of outgoing groups is not consistent across the matrix at "
                                    " moment {}, dilution {}, and incident energy {}", l, z, g_i);
                        Log::info( "matrix[l][z][g_i].size() = {}", matrix[l][z][g_i].size() );
                        Log::info( "expected {}", ogroups );
                        throw std::exception();

                    }
                } // incident erg
            } // dilutions
        } // moments
    }

    static auto
    makeMatrices( const std::vector< DataRecord > records,
                  int nmoments, int ndilutions, int ngroups, int max_gg ) {

      std::vector< std::vector< std::vector< double > > > flux( nmoments );
      std::vector< std::vector< std::vector < std::vector< double > > > > matrix( nmoments );

      if ( nmoments <= 0 || ndilutions <= 0 || ngroups <= 0 || max_gg <= 0 ) {

        throw std::runtime_error( "Number of moments, dilutions and groups cannot be "
                                  "less than or equal to 0" );
      }
      std::size_t number_moments = nmoments;
      std::size_t number_dilutions = ndilutions;
      std::size_t number_groups = ngroups;
      std::size_t number_max_gg = max_gg;

      double temp;
      if ( records.size() != 0 ) {

        temp = records.front().TEMP();
      }
      else {

        throw std::runtime_error( "Vector of DataRecord is empty!" );
      }

      for ( const auto& record : records ) {

        int g_i = record.IG() - 1;
        int group_block = 1;
        std::size_t iglo = record.IG2LO();
        for ( std::size_t g_o = iglo - 1; g_o < number_max_gg; ++g_o ) {

          for ( std::size_t l = 0; l < number_moments; ++l ) {

              if ( flux[l].size() == 0 ) {

                flux[l].resize( number_dilutions );
                matrix[l].resize( number_dilutions );
              } // endif
              for ( std::size_t z = 0; z < number_dilutions; ++z ) {

                if ( flux[l][z].size() == 0 ) {

                  flux[l][z] = std::vector< double >( number_groups,  0. );
                  matrix[l][z] = std::vector< std::vector< double > >
                              ( number_groups, std::vector< double >( number_max_gg, 0. ) );
                }
                if ( g_o == iglo - 1 ) {

                  flux[l][z][g_i] = record.list()[ z * number_moments + l ];
                }
                if ( g_o >= ( iglo - 1 ) && g_o < ( iglo + record.NG2() - 2 ) ) {

                  matrix[l][z][g_i][g_o] = record.list()[ group_block * number_dilutions * number_moments + z * number_moments + l ];
                }
              } // dilutions
          } // moments
          group_block += 1;
        } // outgoing erg
      } // records

      return std::make_tuple( temp, flux, matrix );
    }

    static auto
    makeRecords( double temp,
                 const std::vector< std::vector< std::vector< double > > >& flux,
                 const std::vector< std::vector< std::vector< std::vector< double > > > >& matrix ) {

      std::size_t nmoments = flux.size();
      std::size_t ndilutions = 0;
      std::size_t ngroups = 0;
      std::size_t max_gg = 0;
      bool last_record_not_zero = true;
      if ( nmoments > 0 ) {

        ndilutions = flux.front().size();
        if ( flux.front().size() > 0 ) {

          ngroups = flux.front().front().size();

          if ( matrix.front().front().front().size() > 0 ) {

            max_gg = matrix.front().front().front().size();
          }
        }
      }


      std::vector< DataRecord > records;
      for ( std::size_t g_i = 0; g_i < ngroups; ++g_i ) {

        std::vector< double > list;
        std::vector< double > yield;
        auto it = std::find_if( matrix[0][0][g_i].begin(), matrix[0][0][g_i].end(),
                        [] (auto && val ) { return val != 0.0; } );
        std::size_t ig2lo = std::distance( matrix[0][0][g_i].begin(), it );
        for ( std::size_t g_o = 0; g_o < max_gg; ++g_o ) {

          for ( std::size_t l = 0; l < nmoments; ++l ) {

            for ( std::size_t z = 0; z < ndilutions; ++z ) {

              if ( g_o == 0 && flux[l][z][g_i] != 0.0 ) {

                list.emplace_back( flux[l][z][g_i] );
              }

              if ( ( g_o >= ig2lo && matrix[l][z][g_i][g_o] != 0.0 ) ||
                   ( g_i == (ngroups - 1) && g_o == 0 ) ) {

                yield.emplace_back( matrix[l][z][g_i][g_o] );
              }
            } // dilutions
          } // moments
        } // g_o

        // check last record contains zero yields
        if ( g_i == ngroups - 1 ) {

          for ( std::size_t l = 0; l < nmoments; ++ l ) {

            for ( std::size_t z = 0; z < ndilutions; ++ z ) {

              last_record_not_zero = std::all_of( matrix[l][z][ngroups - 1].begin(), matrix[l][z][ngroups - 1].end(),
                                                  [](double val) { return val > 0.; } );
            }
          }
        }

        list.insert( list.end(), yield.begin(), yield.end() );
        if ( last_record_not_zero ) {

          ig2lo += 1;
        }
        else {

          ig2lo = 1;
        }
        int ng2 = list.size() / ( nmoments * ndilutions );

        if ( list.size() > 0 ) {

          records.emplace_back( temp, ng2, ig2lo, g_i + 1, std::move( list ) );
        }
      } // g_i
      return records;
    }

    template< typename Iterator >
    static auto readRecords( Iterator& it, const Iterator& end, long& lineNumber,
                             int MAT, int MF, int MT, int NGN ) {

      std::vector< DataRecord > records;

      // need to find max nonzero gamma group index
      int max_gg = 0;
      do {

        records.emplace_back(it, end, lineNumber, MAT, MF, MT);
        if ( max_gg < ( (records.back().NG2() - 1 ) + records.back().IG2LO() ) ) {

          max_gg = (records.back().NG2() - 1 ) + records.back().IG2LO();
        }
      }
      while ( records.back().IG() < NGN);

      return std::make_tuple( records, max_gg );
    }

    // taken from MF6

    void verifyIndex( std::size_t moment, std::size_t dilution ) const {

      auto nmoments = this->matrix_.size();
      auto ndilutions = this->matrix_.front().size();

      if ( ( nmoments <= moment ) || ( ndilutions <= dilution ) ) {

        Log::error( "The moment and/or dilution index are out of range" );
        Log::info( "Total number of moments: {}, requested index: {}", nmoments, moment );
        Log::info( "Total number of dilutions: {}, requested index: {}", ndilutions, dilution );
        throw std::exception();
      }
    }

    void verifyIndex( std::size_t dilution ) const {

      auto ndilutions = this->matrix_.front().size();

      if ( ndilutions <= dilution ) {

        Log::error( "The dilution index is out of range" );
        Log::info( "Total number of dilutions: {}, requested index: {}", ndilutions, dilution );
        throw std::exception();
      }
    }

    /* constructor */

      GType( int mt, int zaid, double awr, int lr, int ngn,
             std::tuple< double,
                         std::vector< std::vector< std::vector< double > > >,
                         std::vector< std::vector< std::vector< std::vector< double > > > > >&& data ) :
          GType( mt, zaid, awr, lr, ngn,
                 std::move( std::get<0>( data ) ),        // temp
                 std::move( std::get<1>( data ) ),        // flux
                 std::move( std::get<2>( data ) ) ) {}    // matrix

      GType( int mt, int zaid, double awr, int nl, int nz,  int lr, int ngn,
             std::tuple< std::vector< DataRecord >, int >&& record_data ) :
          GType( mt, zaid, awr, lr, ngn,
                 makeMatrices( std::move( std::get<0>( record_data ) ), nl, nz, ngn,
                               std::move( std::get<1>( record_data ) ) ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Constructor from parameters with probabilities (Note: IG = 0)
     *
     *  @param[in]  mt              the section number
     *  @param[in]  zaid            the ZAID identifier
     *  @param[in]  awr             the atomic weight ratio
     *  @param[in]  lr              the break-up identifier flag
     *  @param[in]  ngn             the number of neutron energy groups
     *  @param[in]  temp            the temperature
     *  @param[in]  groups          the group index
     *  @param[in]  flux            the group-wise flux
     *  @param[in]  matrix          the transfer matrices
     */
    GType( int mt, int zaid, double awr, int lr, int ngn, double temp,
           std::vector < std::vector< std::vector< double > > > flux,
           std::vector < std::vector< std::vector< std::vector< double > > > > matrix ) :
        Base(zaid, awr, mt),
        lr_(lr),
        ngn_(ngn),
        temp_(temp),
        flux_( std::move(flux) ),
        matrix_( std::move(matrix ) ) {

      verifySize( this->flux_, this->matrix_ );
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
      try : GType( head.MT(), head.ZA(), head.AWR(), head.L1(),
                   head.L2(), head.N1(), head.N2(),
                   readRecords( begin, end, lineNumber, head.MAT(), head.MF(),
                                head.MT(), head.N2() ) ) {

              this->readSEND(begin, end, lineNumber, MAT, head.MF());
            }
      catch( std::exception& e ) {

        Log::info( "Encountered error while reading section {} of file {} fo material {}"
                   " in GENDF file.", head.MT(), head.MF(), head.MAT() );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the number of legendre moments.
     */
    int NL() const { return this->flux_.size(); }

    /**
     *  @brief Return the number of legendre moments.
     */
    int numberMoments() const { return this->NL(); }

    /**
     *  @brief Return the number of dilution values.
     */
    int NZ() const { return this->flux_.front().size(); }

    /**
     *  @brief Return the number of dilution values
     */
    int numberDilutions() const { return this->NZ(); }

    /**
     *  @brief Return the break up identifier flag.
     */
    int LRFLAG() const { return this->lr_; }

    /**
     *  @brief Return the break up identifier flag.
     */
    int breakUpID() const { return this->LRFLAG(); }

    /**
     *  @brief Return the number of neutron energy bins
     */
    int NGN() const { return this->ngn_; }

    /**
     *  @brief Return the number of neutron energy bins
     */
    int numberNeutronGroups() const { return this->NGN(); }

    /**
     *  @brief Return the temperature
     */
    double TEMP() const { return this->temp_; }

    /**
     *  @brief Return the temperature
     */
    double temperature() const { return this->TEMP(); }

    /**
     *  @brief Return the matrix for a given moment and dilution
     *
     *  @param[in] moment   the legendre moment requested
     *  @param[in] diltuion the dilution index requested
     */
    decltype(auto) matrix( int moment, int dilution ) const {

      this->verifyIndex( moment, dilution );
      return this->matrix_[ moment ][ dilution ];
    }

    /**
     *  @brief Return the flux
     *
     *  @param[in] moment   the legendre moment requested
     *  @param[in] dilution the dilution index requested
     */
    decltype(auto) flux( int moment, int dilution ) const {

      this->verifyIndex( moment, dilution );
      return this->flux_[ moment ][ dilution ];
    }

    template < typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = this->MT();
      ControlRecord( this->ZA(), this->AWR(), this->NL(), this->NZ(),
                     this->LRFLAG(), this->NGN() ).print( it, MAT, MF, MT );
      auto records = makeRecords( this->temp_, this->flux_, this->matrix_ );
      for ( const auto& record : records) { record.print( it, MAT, MF, MT ); }
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

#endif // NJOY_ENDFTK_GSECTION_16