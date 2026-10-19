#ifndef NJOY_ENDFTK_GSECTION_3
#define NJOY_ENDFTK_GSECTION_3

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

  //! @todo for now, errorr sections get printed as errorr sections. do we keep this?

  template <>
  class ENDFTK_PYTHON_EXPORT GType< 3 > : protected Base {

    /* fields */

    int lr_;
    double temp_;
    std::vector< unsigned int > groups_;

    // format flag: groupr (true), errorr (false)
    bool groupr_;

    // data is stored by moment and dilution
    std::vector< std::vector< std::vector< double > > > flux_;
    std::vector< std::vector< std::vector< double > > > sigma_;
    std::vector< std::vector< std::vector< double > > > ratio_;

    /* auxiliary functions */

    static auto
    makeVectors( const std::vector< DataRecord >& records,
                 int nmoments, int ndilutions, int ngroups ) {

      std::vector< std::vector< std::vector< double > > > flux;
      std::vector< std::vector< std::vector< double > > > sigma;
      std::vector< std::vector< std::vector< double > > > ratio;
      double temp;

      if ( nmoments <= 0 || ndilutions <= 0 || ngroups <= 0 ) {

        throw std::runtime_error( "Number of moments, dilutions and groups cannot be "
                                  "less than or equal to 0" );
      }
      std::size_t number_moments = nmoments;
      std::size_t number_dilutions = ndilutions;
      std::size_t number_groups = ngroups;

      if ( records.size() != 0 ) {

        bool has_ratios = records.front().NG2() == 3 ? true : false;
        temp = records.front().TEMP();

        flux.resize( number_moments );
        sigma.resize( number_moments );
        if ( has_ratios ) {

          ratio.resize( number_moments );
        }

        for ( const auto& record : records ) {

          auto g = record.IG() - 1;
          for ( unsigned int l = 0; l < number_moments; ++l ) {

            if ( flux[l].size() == 0 ) {

              flux[l].resize( number_dilutions );
              sigma[l].resize( number_dilutions );
              if ( has_ratios ) { ratio[l].resize( number_dilutions ); }
            }

            for ( unsigned int z = 0; z < number_dilutions; ++z ) {

              if (flux[l][z].size() == 0 ) {

                flux[l][z] = std::vector< double >( number_groups, 0. );
                sigma[l][z] = std::vector< double >( number_groups, 0. );
                if ( has_ratios ) { ratio[l][z] = std::vector< double >( number_groups, 0.); }
              }

              std::size_t index = z * number_moments + l;
              flux[l][z][g] = record.list()[ index ];
              if ( has_ratios ) {

                ratio[l][z][g] = record.list()[ index + 1 ];
                sigma[l][z][g] = record.list()[ number_moments * number_dilutions * 2 + index ];
              }
              else {

                sigma[l][z][g] = record.list()[ number_moments * number_dilutions + index ];
              }
            }
          }
        }
      }

      return std::make_tuple( temp, std::move( flux ), std::move( sigma ), std::move( ratio ) );
    }

    // version for flux, sigma and ratios
    static auto
    makeRecords( double temp,
                 const std::vector< std::vector< std::vector < double > > >& flux,
                 const std::vector< std::vector< std::vector < double > > >& sigma,
                 const std::vector< std::vector< std::vector < double > > >& ratio ) {

        // ng2 is 3 for ratio quantities, and ig2lo appears to be 1 for MF3
        bool has_ratio = ratio.size() > 0 ? true : false;
        int ng2 = ratio.size() > 0 ? 3 : 2;
        int ig2lo = 1;

        auto nmoments = flux.size();
        auto ndilutions = flux.front().size();
        unsigned int ngroups = flux.front().front().size();

        std::vector< DataRecord > records;
        for ( std::size_t g = 0; g < ngroups; ++g ) {

          std::vector< double > list;
          std::vector< double > xs;
          std::vector< double > ratios;
          list.reserve( ng2 * nmoments * ndilutions);
          xs.reserve( nmoments * ndilutions);
          if ( has_ratio ) { ratios.reserve( nmoments * ndilutions); }

          for ( unsigned int z = 0; z < ndilutions; ++z ) {

            for ( unsigned int l = 0; l < nmoments; ++l ) {

              if (sigma[l][z][g] != 0.0 || ( g == ngroups - 1 ) ) {

                list.push_back( flux[l][z][g] );
                xs.push_back( sigma[l][z][g] );
                if ( has_ratio ) { ratios.push_back( ratio[l][z][g] ); }
              }
            }
          }
          if ( has_ratio ) { list.insert( list.end(), ratios.begin(), ratios.end() ); }
          list.insert( list.end(), xs.begin(), xs.end() );
          if (list.size() != 0) {

            records.emplace_back( temp, ng2, ig2lo, g + 1, std::move( list ) );
          }
        }

        return records;
    }

    template< typename Iterator >
    static auto readRecords( Iterator& it, const Iterator& end, long& lineNumber,
                             int MAT, int MF, int MT, int NGN ) {

      std::vector< DataRecord > records;
      do {

        records.emplace_back( it, end, lineNumber, MAT, MF, MT );
      }
      while ( records.back().IG() < NGN );

      return records;
    }

    static void verifySize( const std::vector< std::vector< std::vector< double > > >& flux,
                            const std::vector< std::vector< std::vector< double > > >& sigma,
                            const std::vector< std::vector< std::vector< double > > >& ratio ) {

      auto ngroups = flux.size() > 0 ? flux.front().size() > 0
                                           ? flux.front().front().size()
                                           : 0
                                     : 0;
      if ( ngroups == 0 ) {

        Log::error( "The number of groups cannot be zero" );
        throw std::exception();
      }

      auto nmoments = sigma.size();
      if ( nmoments == 0 ) {

        Log::error( "The number of moments cannot be zero" );
        throw std::exception();
      }
      if ( ( nmoments != sigma.size() ) || ( nmoments != flux.size() ) ||
           ( ratio.size() != 0 && nmoments != ratio.size() ) ) {

        Log::error( "The number of moments is not consistent across the flux, cross section "
                    "and ratio data" );
        Log::info( "flux.size() = {}", flux.size() );
        Log::info( "sigma.size() = {}", sigma.size() );
        if ( ratio.size() > 0 ) {

          Log::info( "ratio.size() = {}", ratio.size() );
        }
        Log::info( "expected {}", nmoments );
        throw std::exception();
      }

      auto ndilutions = sigma.front().size();
      if ( ndilutions == 0 ) {

        Log::error( "The number of dilutions cannot be zero" );
        throw std::exception();
      }
      for ( std::size_t i = 0; i < nmoments; ++i ) {

        if ( ( ndilutions != sigma[i].size() ) || ( ndilutions != flux[i].size() ) ||
             ( ratio.size() != 0 && ndilutions != ratio[i].size() ) ) {

          Log::error( "The number of dilutions is not consistent across the flux, cross section "
                      "and ratio data for moment with index {}", i );
          Log::info( "flux[i].size() = {}", flux[i].size() );
          Log::info( "sigma[i].size() = {}", sigma[i].size() );
          if ( ratio.size() > 0 ) {

            Log::info( "ratio[i].size() = {}", ratio[i].size() );
          }
          Log::info( "expected {}", ndilutions );
          throw std::exception();
        }

        for ( std::size_t j = 0; j < ndilutions; ++j ) {

          if ( ( ngroups != sigma[i][j].size() ) || ( ngroups != flux[i][j].size() ) ||
               ( ratio.size() != 0 && ngroups != ratio[i][j].size() ) ) {

            Log::error( "The number of groups is not consistent across the flux, cross section "
                        "and ratio data for moment with index {} and dilution with index {}", i, j );
            Log::info( "flux[i][j].size() = {}", flux[i][j].size() );
            Log::info( "sigma[i][j].size() = {}", sigma[i][j].size() );
            if ( ratio.size() > 0 ) {

              Log::info( "ratio[i][j].size() = {}", ratio[i][j].size() );
            }
            Log::info( "expected {}", ngroups );
            throw std::exception();
          }
        }
      }
    }

    void verifyIndex( std::size_t moment, std::size_t dilution ) const {

      auto nmoments = this->sigma_.size();
      auto ndilutions = this->sigma_.front().size();

      if ( ( nmoments <= moment ) || ( ndilutions <= dilution ) ) {

        Log::error( "The moment and/or dilution index are out of range" );
        Log::info( "Total number of moments: {}, requested index: {}", nmoments, moment );
        Log::info( "Total number of dilutions: {}, requested index: {}", ndilutions, dilution );
        throw std::exception();
      }
    }

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param[in] mt       the section number
     *  @param[in] zaid     the ZAID identifier
     *  @param[in] awr      the atomic weight ratio
     *  @param[in] lr       the break-up identifier flag
     *  @param[in] temp     the temperature
     *  @param[in] groupr   the format flag
     *  @param[in] flux     the group-wise flux
     *  @param[in] sigma    the group-wise cross section
     *  @param[in] ratio    the group-wise ratios
     */
    GType( int mt, int zaid, double awr, int lr, double temp, bool groupr,
           std::vector< std::vector< std::vector< double > > > flux,
           std::vector< std::vector< std::vector< double > > > sigma,
           std::vector< std::vector< std::vector< double > > > ratio ) :
        Base( zaid, awr, mt ),
        lr_( lr ),
        temp_( temp ),
        groupr_( groupr ),
        flux_( std::move( flux ) ),
        sigma_( std::move( sigma ) ),
        ratio_( std::move( ratio ) ) {

      verifySize( this->flux_, this->sigma_, this->ratio_ );
    }

  public:

    /* constructor */

    /**
     *  @brief Constructor from parameters with ratio quantities
     *
     *  @param[in] mt       the section number
     *  @param[in] zaid     the ZAID identifier
     *  @param[in] awr      the atomic weight ratio
     *  @param[in] lr.      the break-up identifier flag
     *  @param[in] temp     the temperature
     *  @param[in] groups   the group indices
     *  @param[in] flux     the group-wise flux
     *  @param[in] sigma    the group-wise cross section
     *  @param[in] ratio    the group-wise ratios
     */
    GType( int mt, int zaid, double awr, int lr, double temp,
           std::vector< std::vector< std::vector< double > > > flux,
           std::vector< std::vector< std::vector< double > > > sigma,
           std::vector< std::vector< std::vector< double > > > ratio ) :
        GType( mt, zaid, awr, lr, temp, true,
               std::move( flux ), std::move( sigma ), std::move( ratio ) ) {}

    /**
     *  @brief Constructor from parameters without ratio quantities
     *
     *  @param[in] mt       the section number
     *  @param[in] zaid     the ZAID identifier
     *  @param[in] awr      the atomic weight ratio
     *  @param[in] lr.      the break-up identifier flag
     *  @param[in] temp     the temperature
     *  @param[in] groups   the group indices
     *  @param[in] flux     the group-wise flux
     *  @param[in] sigma    the group-wise cross section
     */
    GType( int mt, int zaid, double awr, int lr, double temp,
           std::vector< std::vector< std::vector< double > > > flux,
           std::vector< std::vector< std::vector< double > > > sigma ) :
      GType( mt, zaid, awr, lr, temp,
             std::move( flux ), std::move( sigma ), {} ) {}

    /**
     *  @brief Constructor for an ERRORR formatted section
     *
     *  @param[in] mt              the section number
     *  @param[in] zaid            the ZAID identifier
     *  @param[in] awr             the atomic weight ratio
     *  @param[in] crossSections   the group-wise cross sections
     */
    GType( int mt, int zaid, double awr,
           std::vector< double > crossSections ) :
        Base( zaid, awr, mt ),
        lr_( 0 ),
        temp_( 0. ),
        groupr_( false ),
        flux_( { { std::vector< double >( crossSections.size(), 0. ) } } ),
        sigma_( { { std::move( crossSections ) } } ),
        ratio_( {} ) {

      verifySize( this->flux_, this->sigma_, this->ratio_ );
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
    template<typename Iterator>
    GType(const HEAD& head,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT)
        try : Base( head.ZA(), head.AWR(), head.MT() ) {

            if ( head.N2() == 0 ) {

              // ERRORR format: the section body is a single list of NGN cross
              // sections at infinite dilution for Legendre order 0
              auto xs = record::Sequence::read< record::Real >(
                            head.N1(), begin, end, lineNumber,
                            head.MAT(), head.MF(), head.MT() );

              this->lr_ = 0;
              this->temp_ = 0.;
              this->groupr_ = false;
              this->flux_ = { { std::vector< double >( xs.size(), 0. ) } };
              this->sigma_ = { { std::move( xs ) } };
              this->ratio_ = {};
            }
            else {

              // GROUPR format: one data record per neutron group
              auto data = makeVectors(
                              readRecords( begin, end, lineNumber, head.MAT(),
                                           head.MF(), head.MT(), head.N2() ),
                              head.L1(), head.L2(), head.N2() );

              this->lr_ = head.N1();
              this->temp_ = std::move( std::get<0>( data ) );
              this->groupr_ = true;
              this->flux_ = std::move( std::get<1>( data ) );
              this->sigma_ = std::move( std::get<2>( data ) );
              this->ratio_ = std::move( std::get<3>( data ) );
            }

            verifySize( this->flux_, this->sigma_, this->ratio_ );
            this->readSEND(begin, end, lineNumber, MAT, head.MF());
        }
        catch(std::exception& e) {
            Log::info("Encountered error while reading section {} of file {} fo material {}"
                      " in GENDF file.", head.MT(), head.MF(), head.MAT());
            throw e;
        }

    /* methods */

    /**
     *  @brief Return the number of legendre moments
     */
    int NL() const {

      return this->sigma_.size();
    }

    /**
     *  @brief Return the number of legendre moments
     */
    int numberMoments() const {

      return this->NL();
    }

    /**
     *  @brief Return the number of dilution values
     */
    int NZ() const {

      return this->sigma_.front().size();
    }

    /**
     *  @brief Return the number of dilution values
     */
    int numberDilutions() const {

      return this->NZ();
    }

    /**
     *  @brief Return the break up flag
     */
    int LR() const {

      return this->lr_;
    }

    /**
     *  @brief Return the break up identifier flag
     */
    int breakUp() const {

      return this->LR();
    }

    /**
     *  @brief Return whether or not this is a GROUPR formatted section
     */
    bool isGroupr() const {

      return this->groupr_;
    }

    /**
     *  @brief Return whether or not this is an ERRORR formatted section
     */
    bool isErrorr() const {

      return ! this->isGroupr();
    }

    /**
     *  @brief Return the number of neutron groups
     */
    int NGN() const {

      return this->sigma_.front().front().size();
    }

    /**
     *  @brief Return the number of neutron groups
     */
    int numberNeutronGroups() const {

      return this->NGN();
    }

    /**
     *  @brief Return the temperature
     */
    double temperature() const {

      return this->temp_;
    }

    /**
     *  @brief Return the multigroup cross section for a given moment and dilution
     *
     *  @param[in] moment     the legendre moment requested
     *  @param[in] dilution   the dilution index requested
     */
    const std::vector< double >& crossSection( std::size_t moment, std::size_t dilution ) const {

      this->verifyIndex( moment, dilution );
      return this->sigma_[moment][dilution];
    }

    /**
     *  @brief Return the multigroup ratio data for a given moment and dilution
     *
     *  @param[in] moment     the legendre moment requested
     *  @param[in] dilution   the dilution index requested
     */
    const std::vector< double >& ratio( std::size_t moment, std::size_t dilution ) const {

      if (this->ratio_.size() != 0) {

        this->verifyIndex( moment, dilution );
        return this->ratio_[moment][dilution];
      }
      else {

        throw std::runtime_error( "Requested ratio when ratios are not present!" );
      }
    }

    /**
     *  @brief Return the group fluxes
     *
     *  @param[in] moment     the legendre moment requested
     *  @param[in] dilution   the dilution index requested
     */
    const std::vector< double >& flux( std::size_t moment, std::size_t dilution ) const {

      this->verifyIndex( moment, dilution );
      return this->flux_[moment][dilution];
    }

    template <typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = this->MT();
      if ( this->isErrorr() ) {

        ListRecord( this->ZA(), this->AWR(), 0, 0, 0,
                    std::vector< double >( this->sigma_[0][0] ) ).print( it, MAT, MF, MT );
      }
      else {

        ControlRecord( this->ZA(), this->AWR(), this->NL(), this->NZ(),
                       this->LR(), this->NGN() ).print( it, MAT, MF, MT ) ;
        auto records = makeRecords( this->temp_, this->flux_, this->sigma_, this->ratio_ );
        for ( const auto& record : records ) { record.print(it, MAT, MF, MT ); }
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

#endif