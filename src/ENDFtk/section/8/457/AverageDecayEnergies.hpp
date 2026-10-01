/**
 *  @class
 *  @brief Half life information and average decay energies for radiation types
 *
 *  The AverageDecayEnergies class is used to store the half life and the
 *  average decay energies from MF8/MT457.
 *
 *  All quantities are given as values with associated uncertainties so these
 *  are handled as arrays.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT AverageDecayEnergies : protected ListRecord {

  /* members */

  /* auxiliary functions */

  static void
  verifyNC( int NC ) {

    if ( ( NC != 3 ) and ( NC != 17 ) ) {

      Log::error( "Encountered illegal NC value" );
      Log::info( "NC must be equal to either 3 or 17" );
      Log::info( "NC value: {}", NC );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< std::array< double, 2 > >&& energies ) {

    std::vector< double > list;
    list.reserve( energies.size() * 2 );
    for ( auto&& entry : energies ) {

      list.push_back( entry[0] );
      list.push_back( entry[1] );
    }
    return list;
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   *
   *  The number of values in the list should be 2 * 3 or 2 * 17, this is checked.
   */
  AverageDecayEnergies( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifyNC( this->numberDecayEnergies() );
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  The number of decay energies must be either 3 or 17, this is checked.
   *
   *  @param[in] halflife   the half life and its associated uncertainty
   *  @param[in] energies   the decay energies and uncertainties for the various
   *                        radiation types (either 3 or 17 pairs)
   */
  AverageDecayEnergies( std::array< double, 2 > halflife,
                        std::vector< std::array< double, 2 > >&& energies )
    try : AverageDecayEnergies( ListRecord( halflife[0], halflife[1], 0, 0, 0,
                                            generateList( std::move( energies ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing average decay energy "
                 "data" );
      throw;
    }

  /**
   *  @brief Constructor
   *
   *  This empty constructor is used for a stable nuclide.
   */
  AverageDecayEnergies() :
    AverageDecayEnergies( ListRecord( 0.0, 0.0, 0, 0, 0,
                                      { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ) ) {}

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
  AverageDecayEnergies( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
    try : AverageDecayEnergies( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading average decay energy data" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the discrete energy value and uncertainty
   */
  auto T() const {

    return std::array< double, 2 >( {{ ListRecord::C1(),
                                       ListRecord::C2() }} ); }

  /**
   *  @brief Return the discrete energy value and uncertainty
   */
  auto halfLife() const { return this->T(); }

  /**
   *  @brief Return the number of decay energy values NC
   */
  int NCE() const { return ListRecord::NPL() / 2; }

  /**
   *  @brief Return the number of decay energy values NC
   */
  int numberDecayEnergies() const { return this->NCE(); }

  /**
   *  @brief Return the decay energies and their uncertainties
   *
   *  This returns a range of pairs (the decay energy value and its uncertainty)
   */
  auto E() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::chunk( 2 );
  }

  /**
   *  @brief Return the decay energies and their uncertainties
   *
   *  This returns a range of pairs (the decay energy value and its uncertainty)
   */
  auto decayEnergies() const { return this->E(); }

  /**
   *  @brief Return the decay energy and uncertainty for light particle decay
   *
   *  This is always present and equal to the sum of decay energies for all
   *  light particles.
   */
  auto ELP() const { return this->decayEnergies()[0]; }

  /**
   *  @brief Return the decay energy and uncertainty for light particle decay
   *
   *  This is always present and equal to the sum of decay energies for all
   *  light particles.
   */
  auto lightParticleDecayEnergy() const { return this->ELP(); }

  /**
   *  @brief Return the decay energy and uncertainty for electromagnetic
   *         radiation.
   *
   *  This is always present.
   */
  auto EEM() const { return this->decayEnergies()[1]; }

  /**
   *  @brief Return the decay energy and uncertainty for electromagnetic
   *         radiation.
   *
   *  This is always present.
   */
  auto electromagneticDecayEnergy() const { return this->EEM(); }

  /**
   *  @brief Return the decay energy and uncertainty for heavy particle decay
   *
   *  This is always present and equal to the sum of decay energies for all
   *  heavy particles (neutrons, alphas, spontaneous fission, etc.).
   */
  auto EHP() const { return this->decayEnergies()[2]; }

  /**
   *  @brief Return the decay energy and uncertainty for heavy particle decay
   *
   *  This is always present and equal to the sum of decay energies for all
   *  heavy particles (neutrons, alphas, spontaneous fission, etc.).
   */
  auto heavyParticleDecayEnergy() const { return this->EHP(); }

  using ListRecord::NC;
  using ListRecord::print;
};
