/**
 *  @class
 *  @brief An angular distribution given as a tabulated function.
 *
 *  The TabulatedDistribution class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as a tabulated function.
 *
 *  This component is similar to the MF4 component of the same name (with the
 *  exception that this gives tabulated values for each outgoing energy value as
 *  well).
 *
 *  See ENDF102, section 6.2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedDistribution : protected Base {

  /* fields */

  int lang_;

  /* auxiliary functions */

  static void
  checkLANG( int lang ) {

    if ( ( lang != 11 ) and ( lang != 12 ) and ( lang != 13 ) and
         ( lang != 14 ) and ( lang != 15 ) ) {

      Log::error( "Encountered illegal LANG value for a tabulated LAW=1" );
      Log::info( "LANG must be equal to 11, 12, 13, 14 or 15" );
      Log::info( "LANG value: {}", lang );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( unsigned int na,
                std::vector< double >&& energies,
                std::vector< double >&& totalEmissionProbabilities,
                std::vector< std::vector< double > >&& cosines,
                std::vector< std::vector< double > >&& probabilities ) {

    if ( ( energies.size() != totalEmissionProbabilities.size() ) or
         ( energies.size() != cosines.size() ) or
         ( energies.size() != probabilities.size() ) ) {

      Log::error( "A total emission probability value f0 and a set of cosines "
                  "and probabilities must be given for each energy value" );
      Log::info( "Expected size: {}", energies.size() );
      Log::info( "Found f0 values: {}", totalEmissionProbabilities.size() );
      Log::info( "Found cosine sets: {}", cosines.size() );
      Log::info( "Found probability sets: {}", probabilities.size() );
      throw std::exception();
    }

    std::vector< double > list;
    for ( unsigned int i = 0; i < energies.size(); ++i ) {

      verifySorted( cosines[i], "Energy" );

      if ( ( cosines[i].size() != probabilities[i].size() ) or
           ( cosines[i].size() != na / 2 ) ) {

        Log::error( "The number of cosines and probabilities for each energy "
                    "value must be the same and equal to na/2" );
        Log::info( "Expected: {}", na / 2 );
        Log::info( "Found cosines: {}", cosines[i].size() );
        Log::info( "Found probabilities: {}", probabilities[i].size() );
        Log::info( "Energy: {}", energies[i] );
        throw std::exception();
      }

      list.push_back( energies[i] );
      list.push_back( totalEmissionProbabilities[i] );
      for ( unsigned int j = 0; j < cosines[i].size(); ++j ) {

        list.push_back( cosines[i][j] );
        list.push_back( probabilities[i][j] );
      }
    }
    return list;
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  TabulatedDistribution( int lang, ListRecord&& list ) :
    Base( std::move( list ) ), lang_( lang ) {

    checkLANG( this->LANG() );
  };

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  TabulatedDistribution() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] energy           the incident energy value
   *  @param[in] nd               the number of discrete energies
   *  @param[in] na               the number of angular parameters
   *  @param[in] energies         the energy values
   *  @param[in] emissions        the total emission probabilities
   *  @param[in] cosines          the energy values
   *  @param[in] probabilities    the Legendre coefficients
   */
  TabulatedDistribution( int lang, double energy, long nd, long na,
                         std::vector< double >&& energies,
                         std::vector< double >&& emissions,
                         std::vector< std::vector< double > >&& cosines,
                         std::vector< std::vector< double > >&& probabilities )
    try : TabulatedDistribution(
              lang,
              ListRecord( 0.0, energy, nd, na, energies.size(),
                          generateList( na,
                                        std::move( energies ),
                                        std::move( emissions ),
                                        std::move( cosines ),
                                        std::move( probabilities ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing tabulated distribution "
                 "data (LAW=1 LANG={})", lang );
      throw;
    }

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   */
  template< typename Iterator >
  TabulatedDistribution( int lang, Iterator& it, const Iterator& end,
                         long& lineNumber, int MAT, int MF, int MT )
    try : TabulatedDistribution( lang, ListRecord( it, end, lineNumber,
                                                   MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading tabulated distribution data "
                 "(LAW=1 LANG={})", lang );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the representation type
   */
  int LANG() const { return this->lang_; }

  /**
   *  @brief Return the representation type
   */
  int representation() const { return this->LANG(); }

  using Base::E;
  using Base::incidentEnergy;
  using Base::ND;
  using Base::numberDiscreteEnergies;
  using Base::NA;
  using Base::numberAngularParameters;
  using Base::NW;
  using Base::NEP;
  using Base::numberSecondaryEnergies;
  using Base::EP;
  using Base::energies;
  using Base::F0;
  using Base::totalEmissionProbabilities;

  /**
   *  @brief Return the cosine values
   */
  auto MU() const {

    using namespace njoy::tools;
    return Base::list()
             | std23::views::chunk( 2 + this->NA() )
             | std20::views::transform(
                  [] ( const auto& array )
                     { return array | std20::views::drop( 2 )
                                    | std23::views::stride( 2 ); } );
  }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const { return this->MU(); }

  /**
   *  @brief Return the distribution probabilities
   */
  auto F() const {

    using namespace njoy::tools;
    return Base::list()
             | std23::views::chunk( 2 + this->NA() )
             | std20::views::transform(
                  [] ( const auto& array )
                     { return array | std20::views::drop( 3 )
                                    | std23::views::stride( 2 ); } );
  }

  /**
   *  @brief Return the distribution probabilities
   */
  auto probabilities() const { return this->F(); }

  using Base::NC;
  using Base::print;
};
