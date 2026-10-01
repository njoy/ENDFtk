/**
 *  @class
 *  @brief The element information for thermal scattering moderators
 *
 *  See ENDF102, section 7.6 for more information.
 */
class ElementInformation : protected ListRecord {

  /* auxiliary functions */

  static void
  verifySize( int NPL, int NI ) {

    if ( NPL != NI * 6 ) {

      Log::error( "Encountered illegal NPL and NI values " );
      Log::info( "NPL must be equal to 6*NI for element information data" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NI value: {}", NI );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< unsigned int >&& identifiers,
                std::vector< unsigned int >&& states,
                std::vector< double >&& abundances,
                std::vector< double >&& weights,
                std::vector< double >&& xs ) {

    unsigned int ni = identifiers.size();
    if ( ( states.size() != ni ) or ( abundances.size() != ni ) or
         ( weights.size() != ni ) or ( xs.size() != ni ) ) {

      Log::info( "The number of isotopes and the eleemnt information data "
                 "are not consistent" );
      Log::info( "ni value: {}", ni );
      Log::info( "identifiers.size(): {}", identifiers.size() );
      Log::info( "states.size(): {}", states.size() );
      Log::info( "abundances.size(): {}", abundances.size() );
      Log::info( "weights.size(): {}", weights.size() );
      Log::info( "xs.size(): {}", xs.size() );
      throw std::exception();
    }

    std::vector< double > list;
    for ( unsigned int i = 0; i < ni; ++i ) {

      list.push_back( identifiers[i] );
      list.push_back( states[i] );
      list.push_back( abundances[i] );
      list.push_back( weights[i] );
      list.push_back( xs[i] );
      list.push_back( 0. );
    }
    return list;
  }

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( i )
                              | std23::views::stride( 6 );
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  ElementInformation( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySize( ListRecord::NPL(), this->NI() );
  };

public:

//  #include "ENDFtk/section/7/451/ElementInformation/Isotope.hpp"

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] atoms          the number of atoms in the molecule or unit cell
   *  @param[in] identifiers    the isotope identifiers (ZA identifier)
   *  @param[in] states         the isomeric state for each isotope
   *  @param[in] abundances     the isotope abundances
   *  @param[in] weights        the atomic weight ratios
   *  @param[in] xs             the free atom scattering cross sections
   */
  ElementInformation( unsigned int atoms,
                      std::vector< unsigned int >&& identifiers,
                      std::vector< unsigned int >&& states,
                      std::vector< double >&& abundances,
                      std::vector< double >&& weights,
                      std::vector< double >&& xs )
    try : ElementInformation(
              ListRecord( 0.0, 0.0,
                          atoms, 0, identifiers.size(),
                          generateList( std::move( identifiers ),
                                        std::move( states ),
                                        std::move( abundances ),
                                        std::move( weights ),
                                        std::move( xs ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing thermal scattering "
                 "element information" );
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
  ElementInformation( Iterator& begin, const Iterator& end,
                    long& lineNumber, int MAT, int MF, int MT )
    try : ElementInformation( ListRecord( begin, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing fission yields" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the number of atoms in the molecule or unit cell
   */
  int NAS() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of atoms in the molecule or unit cell
   */
  int numberAtoms() const { return this->NAS(); }

  /**
   *  @brief Return the number of isotopes in the element
   */
  int NI() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of isotopes in the element
   */
  int numberIsotopes() const { return this->NI(); }

  /**
   *  @brief Return the isotope ZA identifiers
   */
  auto ZAI() const { return this->column( 0 ); }

  /**
  *  @brief Return the isotope ZA identifiers
   */
  auto isotopeIdentifiers() const { return this->ZAI(); }

  /**
   *  @brief Return the isotope isomeric states
   */
  auto LISI() const { return this->column( 1 ); }

  /**
   *  @brief Return the isotope isomeric states
   */
  auto isomericStates() const { return this->LISI(); }

  /**
   *  @brief Return the isotope abundances
   */
  auto AFI() const { return this->column( 2 ); }

  /**
   *  @brief Return the isotope abundances
   */
  auto abundances() const { return this->AFI(); }

  /**
   *  @brief Return the isotope atomic weight ratios
   */
  auto AWRI() const { return this->column( 3 ); }

  /**
   *  @brief Return the isotope abundances
   */
  auto atomicWeightRatios() const { return this->AWRI(); }

  /**
   *  @brief Return the isotope free atom scattering cross sections
   */
  auto SFI() const { return this->column( 4 ); }

  /**
   *  @brief Return the isotope free atom scattering cross sections
   */
  auto freeScatteringCrossSections() const { return this->SFI(); }

  using ListRecord::NC;
  using ListRecord::print;
};
