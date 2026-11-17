/**
 *  @class
 *  @brief Base class for legendre, tabulated and Kalbach-Mann distributions
 *
 *  See ENDF102, section 6.2.3.1 for more information.
 */
class Base : protected ListRecord {

  /* auxiliary functions */

  static void
  verifySize( int NW, int NA, int NEP ) {

    if ( NW != NEP * ( NA + 2 ) ) {

      Log::error( "Encountered illegal NA, NW and NEP values " );
      Log::info( "NW must be equal to NEP*(NA+2) for continuum energy-angle "
                 "distributions" );
      Log::info( "NW value: {}", NW );
      Log::info( "NA value: {}", NA );
      Log::info( "NEP value: {}", NEP );
      throw std::exception();
    }
  }

protected:

  /**
   *  @brief Return the data
   */
  auto data() const {

    using namespace njoy::tools;
    return ListRecord::list()
               | std23::views::chunk( 2 + this->NA() )
               | std20::views::transform( [] ( auto&& chunk )
                                             { return chunk | std20::views::drop( 1 ); } );
  }

public:

  /* methods */

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the number of discrete energies
   */
  long ND() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of discrete energies
   */
  long numberDiscreteEnergies() const { return this->ND(); }

  /**
   *  @brief Return the number of angular parameter values
   */
  long NA() const { return ListRecord::L2(); }

  /**
   *  @brief Return the number of angular parameter values
   */
  long numberAngularParameters() const { return this->NA(); }

  /**
   *  @brief Return the number of values
   */
  long NW() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the number of secondary energy values
   */
  long NEP() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of secondary energy values
   */
  long numberSecondaryEnergies() const { return this->NEP(); }

  /**
   *  @brief Return the secondary energy values
   */
  auto EP() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::stride( 2 + this->NA() );
  }

  /**
   *  @brief Return the secondary energy values
   */
  auto energies() const { return this->EP(); }

  /**
   *  @brief Return the total emission probabilities
   */
  auto F0() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 1 )
                              | std23::views::stride( 2 + this->NA() );
  }

  /**
   *  @brief Return the total emission probabilities
   */
  auto
  totalEmissionProbabilities() const {

    return this->F0();
  }

  using ListRecord::NC;
  using ListRecord::print;

protected:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  Base() = default;
  #endif

  Base( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySorted( this->energies() | njoy::tools::std20::views::drop( this->ND() ),
                  "Energy" );
    verifySize( this->NW(), this->NA(), this->NEP() );
  };

  Base( double energy, long nd, long na, long nep,
        std::vector< double >&& list ) :
    Base( ListRecord( 0.0, energy, nd, na, nep,
                      std::move( list ) ) ) {};

  template< typename Iterator >
  Base( Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT ) :
    Base( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
};
