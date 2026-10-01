#ifndef NJOY_ENDFTK_GSECTION_6
#define NJOY_ENDFTK_GSECTION_6

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
  class ENDFTK_PYTHON_EXPORT GType< 6 > : protected Base {

    /* fields */

    int lr_;
    int ngn_;
    double temp_;
    int cutoff_ig_;
    std::vector< std::vector< std::vector< double > > > flux_;
    std::vector< std::vector< std::vector< std::vector< double > > > > matrix_;
    std::vector< std::vector< double > > chi_;

    /* auxiliary functions */

    static auto
    makeMatrices( const std::vector< DataRecord > records,
                  int nmoments, int ndilutions, int ngroups ) {

      if ( nmoments <= 0 || ndilutions <= 0 || ngroups <= 0 ) {

        throw std::runtime_error( "Number of moments, dilutions and groups cannot be "
                                  "less than or equal to 0" );
      }
      std::size_t number_moments = nmoments;
      std::size_t number_dilutions = ndilutions;
      std::size_t number_groups = ngroups;

      std::vector< std::vector < std::vector< double > > > flux( number_moments );
      std::vector< std::vector< std::vector < std::vector< double > > > > matrix( number_moments );
      std::vector< std::vector < double > > chi;

      double temp;
      int cutoff_ig;
      bool is_fission = records.front().IG() == 0 ? true : false;
      if ( records.size() != 0 ) {

        temp = records.front().TEMP();
      }
      else {

        throw std::runtime_error( "Vector of DataRecords is empty!" );
      }

      if ( is_fission ) {

        for ( const auto& record : records) {

          // prompt fission ( MT18 )
          if ( record.IG() == 0 ) {

            chi.resize( number_dilutions );
            for ( std::size_t z = 0; z < number_dilutions; ++z ) {

              if ( chi[z].size() == 0 ) {

                  chi[z] = std::vector< double >( number_groups, 0. );
              }
              for ( std::size_t g = 0; g < number_groups; ++g ) {

                  chi[z][g] = record.list()[ g * number_dilutions + z];
              }
            }
          } // prompt fission ( MT18 )
          else {

            // entering compressed format
            if ( record.IG2LO() == 0 ) {

              // nl is 1 for MT 18
              flux[0].resize( number_dilutions );
              matrix[0].resize( number_dilutions );
              auto g_i = record.IG() - 1;
              cutoff_ig = record.IG();
              for ( std::size_t z = 0; z < number_dilutions; ++z ) {

                if ( flux[0][z].size() == 0) {

                    flux[0][z] = std::vector< double >( number_groups, 0. );
                    matrix[0][z] = std::vector< std::vector< double > >
                                   ( number_groups, std::vector< double >( number_groups, 0. ) );
                }
                flux[0][z][g_i] = record.list()[ z ];
                for ( std::size_t g_o = 0; g_o < number_groups; ++g_o ) {

                  matrix[0][z][g_i][g_o] = record.list()[ number_dilutions + z ] * chi[z][g_o];
                } // outgoing erg
              } // dilutions
            } // compressed format

            // uncompressed format of fission matrix
            else {

              std::size_t g_i = record.IG() - 1; // g_i = incident_erg
              int group_block = 1;
              for ( std::size_t g_o = 0; g_o < number_groups; ++g_o ) { // g_o = outgoing_erg

                for ( std::size_t z = 0; z < number_dilutions; ++z ) {

                  if ( g_i == g_o ) {

                      flux[0][z][g_i] = record.list()[ z * number_moments];
                  }

                  matrix[0][z][g_i][g_o] = record.list()[group_block  * number_dilutions * number_moments + z * number_moments ];
                } // dilutions
                ++group_block;
              } // outgoing erg
            } // uncompressed format
          }
        } // records
      } // is_fission

      // standard MF6 matrix
      else {

        for ( const auto& record : records ) {

          std::size_t g_i = record.IG() - 1; // g_i = incident_erg
          int group_block = 1;
          for ( std::size_t g_o = record.IG2LO() - 1; g_o <= g_i; ++g_o ) { // g_o = outgoing_erg

            for ( std::size_t l = 0; l < number_moments; ++l ) {

              if ( flux[l].size() == 0 ) {

                  flux[l].resize( number_dilutions );
                  matrix[l].resize( number_dilutions );
              } // endif
              for ( std::size_t z = 0; z < number_dilutions; ++z ) {

                if ( flux[l][z].size() == 0 ) {

                  flux[l][z] = std::vector< double > (number_groups, 0. );
                  matrix[l][z] = std::vector< std::vector< double > >
                  (number_groups, std::vector< double >(number_groups, 0.));
                } // endif
                if ( g_i == g_o ) {

                  flux[l][z][g_i] = record.list()[ z * number_moments + l];
                }
                matrix[l][z][g_i][g_o] = record.list()[group_block  * number_dilutions * number_moments + z * number_moments + l];
              } // dilutions
            } // moments
            ++group_block;
          } // outgoing erg
        } // records
      } // standard matrix

      return std::make_tuple(temp, flux, matrix, cutoff_ig, chi);
    }

    static auto
    makeRecords( double temp,
                 std::size_t cutoff_ig,
                 const std::vector< std::vector< std::vector< double > > >& flux,
                 const std::vector< std::vector< std::vector< std::vector< double > > > >& matrix,
                 const std::vector< std::vector< double > >& chi ) {

      std::size_t nmoments = flux.size();
      std::size_t ndilutions = 0;
      std::size_t ngroups = 0;
      if ( nmoments > 0 ) {

        ndilutions = flux.front().size();
        if ( flux.front().size() > 0 ) {

          ngroups = flux.front().front().size();
        }
      }
      bool is_fission = chi.size() > 0 ? true: false;

      // search and find what gets written
      std::vector< DataRecord > records;
      if ( is_fission ) {

        // write the chi record
        std::vector< double > list;
        list.reserve( ndilutions * ngroups );
        for ( std::size_t g_o = 0; g_o < ngroups; ++ g_o ) {
            for ( std::size_t z = 0; z < ndilutions; ++z ) {
                list.push_back( chi[z][g_o] );
            }
        }
        records.emplace_back( temp, ngroups, 1, 0, std::move( list ) );

        // write the compressed low energy format
        for ( std::size_t g_i = 0; g_i < cutoff_ig; ++g_i ) {

          std::vector< double > list(  ndilutions );
          std::vector< double > xs ( ndilutions );
          for ( std::size_t z = 0; z < ndilutions; ++z ) {

            list[z] = ( flux[0][z][g_i] );
            xs[z] = ( matrix[0][z][g_i][g_i] / chi[z][g_i] );
          }
          list.insert( list.end(), xs.begin(), xs.end() );
          if ( list.size() != 0 ) {

            records.emplace_back( temp, 2, 0, ( g_i + 1 ), std::move( list ) );
          }
        } // compressed ig

        // write the uncompressed format
        for ( std::size_t g_i = cutoff_ig; g_i < ngroups; ++g_i ) {

          std::vector< double > list;
          std::vector< double > xs;

          auto it = std::find_if( matrix[0][0][g_i].begin(), matrix[0][0][g_i].end(),
                                  [] ( auto&& val ) { return val != 0.0; } );

          int ig2lo = std::distance( matrix[0][0][g_i].begin(), it );
          int ng2 = 1;
          for ( std::size_t g_o = 0; g_o < ngroups; ++g_o ) {

            for ( std::size_t z = 0; z < ndilutions; ++z ) {

              for ( std::size_t l = 0; l < nmoments; ++l ) {


                if ( flux[l][z][g_i] != 0.0 && g_o == g_i ) {

                  list.emplace_back( flux[l][z][g_i] );
                } // endif
                if ( matrix[l][z][g_i][g_o] != 0.0 || ( g_i == ngroups - 1 && g_o == 0 ) ) {

                  xs.emplace_back( matrix[l][z][g_i][g_o] );
                  if ( z == 0 ) {

                      ++ng2;
                  }
                }
              } // moments
            } // dilutions
          } // outgoing erg
          ++ig2lo; // need to correct from array index to GENDF index value.
          list.insert( list.end(), xs.begin(), xs.end() );
          if (list.size() != 0 ) {

            records.emplace_back( temp, ng2, ig2lo, g_i + 1, std::move( list ));
          }
        } // incident erg
      }
      else {

        for ( std::size_t g_i = 0; g_i < ngroups; ++g_i ) {

          std::vector< double > list;
          std::vector< double > xs;

          auto it = std::find_if( matrix[0][0][g_i].begin(), matrix[0][0][g_i].end(),
                                  [] ( auto&& val ) { return val != 0.0; } );

          std::size_t ig2lo = std::distance( matrix[0][0][g_i].begin(), it );
          std::size_t ng2 = 1;
          for ( std::size_t g_o = 0; g_o < ngroups; ++g_o ) {

            for ( std::size_t z = 0; z < ndilutions; ++z ) {

              for ( std::size_t l = 0; l < nmoments; ++l ) {

                if ( flux[l][z][g_i] != 0.0 && g_o == g_i ) {

                  list.emplace_back( flux[l][z][g_i] );
                } // endif

                if ( g_o <= g_i && g_o >= ig2lo ) {

                  xs.emplace_back( matrix[l][z][g_i][g_o] );
                } // endif
              } // moments
            } // dilutions
          } // outgoing erg
          ng2 += ( (g_i + 1) - ig2lo );
          ig2lo += 1; // need to correct from array index to GENDF index value.
          list.insert( list.end(), xs.begin(), xs.end() );
          if (list.size() != 0 ) {

            records.emplace_back( temp, ng2, ig2lo, g_i + 1, std::move( list ));
          }
        } // incident erg
      }

      return records;
    }

    template<typename Iterator>
    static auto readRecords( Iterator& it, const Iterator& end, long& lineNumber,
                             int MAT, int MF, int MT, int NGN ) {

      std::vector< DataRecord > records;
      do {

        records.emplace_back(it, end, lineNumber, MAT, MF, MT);
      }
      while ( records.back().IG() < NGN );

      return records;
    }

    static void
    verifySize( const std::vector< std::vector< std::vector< double > > >& flux,
                const std::vector< std::vector< std::vector< std::vector< double > > > >& matrix,
                const std::vector< std::vector< double > >& chi ) {

      auto ngroups = flux.size() > 0 ? flux.front().size() > 0
                                      ? flux.front().front().size()
                                      : 0
                                      : 0;

      if (ngroups == 0) {

        Log::error( "The number of groups cannot be zero" );
        throw std::exception();
      }

      auto nmoments = matrix.size();
      if ( nmoments == 0 ) {

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

        if ( ( ndilutions != flux[l].size() ) || ( ndilutions != matrix[l].size() ) ||
             ( chi.size() != 0 && ndilutions != chi.size() ) ) {

          Log::error( "The number of dilutions is not consistent across the flux, matrix and chi at moment {}", l );
          Log::info( "flux[l].size() = {}", flux[l].size() );
          Log::info( "matrix[l].size() = {}", matrix[l].size() );
          if ( chi.size() > 0 ) {

              Log::info( "chi.size() = {}", chi.size() );
          }
          Log::info( "expected {}", ndilutions );
          throw std::exception();
        }

        for ( size_t z = 0; z < ndilutions; ++z ) {

          if ( ( ngroups != flux[l][z].size() ) || ( ngroups != matrix[l][z].size() ) ||
               ( chi.size() != 0 && ngroups != chi[z].size() ) ) {

            Log::error( " The number of groups is not consistent across the flux, matrix and chi at moment {} "
                        "and dilution {}", l, z);
            Log::info( "flux[l][z].size() = {}", flux[l][z].size() );
            Log::info( "matrix[l][z].size() = {}", matrix[l][z].size() );
            if( chi.size() > 0 ) {

              Log::info( "chi[z].size() = {}", chi[z].size() );
            }

            Log::info( "expected {}", ngroups );
            throw std::exception();
          }
          for ( size_t g_i = 0; g_i < ngroups; ++g_i ) {

            if ( ngroups != matrix[l][z][g_i].size() ) {

              Log::error( "The dimensionality of the matrix is not square. Dimensionality issue at "
                          " moment {}, dilution {}, and incident energy {}", l, z, g_i);
              Log::info( "matrix[l][z][g_i].size() = {}", matrix[l][z][g_i].size() );
              Log::info( "expected {}", ngroups );
              throw std::exception();
            }
          } // incident erg
        } // dilutions
      } // moments
    }

    static void
    verifySize( const std::vector< std::vector< std::vector< double > > >& flux,
                const std::vector< std::vector< std::vector< std::vector< double > > > >& matrix ) {

        auto ngroups = flux.size() > 0 ? flux.front().size() > 0
                                        ? flux.front().front().size()
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
                Log::error( "The number of dilutions is not consistent across the flux, matrix and chi at moment {}", l );
                Log::info( "flux[l].size() = {}", flux[l].size() );
                Log::info( "matrix[l].size() = {}", matrix[l].size() );

                Log::info( "expected {}", ndilutions );
                throw std::exception();
            }

            for ( size_t z = 0; z < ndilutions; ++z ) {
                if ( ( ngroups != flux[l][z].size() ) || ( ngroups != matrix[l][z].size() ) ) {
                    Log::error( " The number of groups is not consistent across the flux, matrix and chi at moment {} "
                                "and dilution {}", l, z);
                    Log::info( "flux[l][z].size() = {}", flux[l][z].size() );
                    Log::info( "matrix[l][z].size() = {}", matrix[l][z].size() );

                    Log::info( "expected {}", ngroups );
                    throw std::exception();
                }
                for ( size_t g_i = 0; g_i < ngroups; ++g_i ) {
                    if ( ngroups != matrix[l][z][g_i].size() ) {
                        Log::error( "The dimensionality of the matrix is not square. Dimensionality issue at "
                                    " moment {}, dilution {}, and incident energy {}", l, z, g_i);
                        Log::info( "matrix[l][z][g_i].size() = {}", matrix[l][z][g_i].size() );
                        Log::info( "expected {}", ngroups );
                        throw std::exception();

                    }
                } // incident erg
            } // dilutions
        } // moments
    }

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
                       std::vector< std::vector< std::vector< std::vector< double > > > >,
                       int,
                       std::vector< std::vector< double > > >&& data ) :
        GType( mt, zaid, awr, lr, ngn,
               std::move( std::get<0>( data ) ),        // temp
               std::move( std::get<1>( data ) ),        // flux
               std::move( std::get<2>( data ) ),        // matrix
               std::move( std::get<3>( data ) ),        // cutoff_ig
               std::move( std::get<4>( data ) ) ) {}    // chi

    GType( int mt, int zaid, double awr, int nl, int nz,  int lr, int ngn,
           std::vector< DataRecord >&& records ) :

        GType( mt, zaid, awr, lr, ngn,
               makeMatrices(records, nl, nz, ngn)) {}

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
     *  @param[in]  flux            the group-wise flux
     *  @param[in]  matrix          the transfer matrices
     *  @param[in]  cutoff_ig       the cuttoff group index for compressed fission matrix
     *  @param[in]  chi             the fission spectrum
     */
    GType( int mt, int zaid, double awr, int lr, int ngn, double temp,
           std::vector < std::vector< std::vector< double > > > flux,
           std::vector < std::vector< std::vector< std::vector< double > > > > matrix,
           int cutoff_ig,
           std::vector < std::vector< double > > chi ) :
        Base(zaid, awr, mt),
        lr_(lr),
        ngn_(ngn),
        temp_(temp),
        cutoff_ig_(cutoff_ig),
        flux_( std::move(flux) ),
        matrix_( std::move(matrix ) ),
        chi_( std::move( chi ) ) {

      verifySize( this->flux_, this->matrix_, this->chi_ );
    }

    //! @todo check sizes for this last one, and use delegation with the next one?

    /**
     *  @brief Constructor from parameters without probabilities.
     *
     *  @param[in]  mt       the section number
     *  @param[in]  zaid     the ZAID identifier
     *  @param[in]  awr      the atomic weight ratio
     *  @param[in]  nl       the number of legendre moments
     *  @param[in]  nz       the number of dilution values
     *  @param[in]  lr       the break-up identifier flag
     *  @param[in]  ngn      the number of neutron energy groups
     *  @param[in]  temp     the temperature
     *  @param[in]  flux     the group-wise flux
     *  @param[in]  matrix   the transfer matrices
     */
    GType( int mt, int zaid, double awr, int lr,
           int ngn, double temp,
           std::vector < std::vector < std::vector < double > > > flux,
           std::vector < std::vector< std::vector< std::vector< double > > > > matrix ) :
        Base( zaid, awr, mt ),
        lr_( lr ),
        ngn_( ngn ),
        temp_( temp ),
        flux_( std::move( flux ) ) ,
        matrix_(std::move ( matrix ) )  {

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
      try:
          GType( head.MT(), head.ZA(), head.AWR(), head.L1(),
                 head.L2(), head.N1(), head.N2(),
                 readRecords( begin, end, lineNumber, head.MAT(), head.MF(),
                            head.MT(), head.N2() ) ) {

        this->readSEND(begin, end, lineNumber, MAT, head.MF());
      }
      catch(std::exception& e) {

        Log::info( "Encountered error while reading section {} of file {} fo material {}"
                   " in GENDF file.", head.MT(), head.MF(), head.MAT());
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
     *  @brief Return the number of dilution values.
     */
    int numberDilutions() const { return this->NZ(); }

    /**
     *  @brief Return the break up flag.
     */
    int LRFLAG() const { return this->lr_; }

    /**
     *  @brief Return the break up flag.
     */
    int breakUp() const { return this->LRFLAG(); }

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
     *  @param[in] moment     the legendre moment requested
     *  @param[in] dilution   the dilution index requested
     */
    decltype(auto) matrix( std::size_t moment, std::size_t dilution ) const {

      this->verifyIndex( moment, dilution );
      return this->matrix_[moment][dilution];
    }

    /**
     *  @brief Return the flux
     *
     *  @param[in] moment     the legendre moment requested
     *  @param[in] dilution   the dilution index requested
     */
    decltype(auto) flux( std::size_t moment, std::size_t dilution ) const {

      this->verifyIndex( moment, dilution );
      return this->flux_[moment][dilution];
    }

    /**
     *  @brief Return the prompt fission spectrum
     *
     *  @param[in] dilution   the dilution index requested
     */
    decltype(auto) chi( std::size_t dilution ) const {

      if ( this->chi_.size() != 0 ) {

        this->verifyIndex( dilution );
        return this->chi_[dilution];
      }
      else {

        throw std::runtime_error( "Requested chi when they are not present" );
      }
    }

    template < typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = this->MT();
      ControlRecord( this->ZA(), this->AWR(), this->NL(), this->NZ(),
                     this->LRFLAG(), this->NGN() ).print( it, MAT, MF, MT );
      auto records = makeRecords( this->temp_, this->cutoff_ig_, this->flux_,
                                  this->matrix_, this->chi_ );
      for ( const auto& record : records ) { record.print( it, MAT, MF, MT ); }
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


#endif // NJOY_ENDFTK_GSECTION_6