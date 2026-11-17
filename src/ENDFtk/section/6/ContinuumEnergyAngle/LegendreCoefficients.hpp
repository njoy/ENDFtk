/**
 *  @class
 *  @brief Angular distributions are given as Legendre coefficients
 *
 *  The LegendreCoefficients class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as Legendre coefficients.
 *
 *  This component is similar to the MF4 component of the same name (with the
 *  exception that this gives coefficients for each outgoing energy value as
 *  well).
 *
 *  See ENDF102, section 6.2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT LegendreCoefficients : protected Base {

  /* auxiliary functions */

  static std::vector< double >
  generateList( unsigned int na,
                std::vector< double >&& energies,
                std::vector< std::vector< double > >&& coefficients ) {

    std::vector< double > list;
    list.reserve( energies.size() * ( 2 + na ) );

    if ( energies.size() != coefficients.size() ) {

      Log::error( "The number of energies and number of sets if coefficients "
                  "must be the same" );
      Log::info( "Number of energies: {}", energies.size() );
      Log::info( "Number of coefficient sets: {}", coefficients.size() );
      throw std::exception();
    }

    for ( auto& entry : coefficients ) {

      if ( 1 + na != entry.size() ) {

        Log::error( "The number of coefficients for each energy value must "
                    "be the same" );
        Log::info( "Expected: {}", 1 + na );
        Log::info( "Found: {}", entry.size() );
        throw std::exception();
      }
    }

    for ( unsigned int i = 0; i < energies.size(); ++i ) {

      list.push_back( energies[i] );
      list.insert( list.end(), coefficients[i].begin(), coefficients[i].end() );
    }

    return list;
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  LegendreCoefficients() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] energy          the incident energy value
   *  @param[in] nd              the number of discrete energies
   *  @param[in] na              the number of angular parameters
   *  @param[in] energies        the energy values
   *  @param[in] coefficients    the Legendre coefficients
   */
  LegendreCoefficients( double energy, long nd, long na,
                        std::vector< double > energies,
                        std::vector< std::vector< double > >&& coefficients )
    try : Base( energy, nd, na, energies.size(),
                generateList( na, std::move( energies ),
                std::move( coefficients ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing Legendre coefficients "
                 "(LAW=1 LANG=1)" );
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
  LegendreCoefficients( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
    try : Base( it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading Legendre coefficients "
                 "(LAW=1 LANG=1)" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the representation type
   */
  static constexpr int LANG() { return 1; }

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
   *  @brief Return the Legendre order
   */
  long NL() const { return Base::NA(); }

  /**
   *  @brief Return the Legendre order
   */
  long legendreOrder() const { return this->NL(); }

  /**
   *  @brief Return the Legendre coefficients (one set for each outgoing energy)
   */
  auto A() const { return Base::data(); }

  /**
   *  @brief Return the Legendre coefficients (one set for each outgoing energy)
   */
  auto coefficients() const { return this->A(); }

  using Base::NC;
  using Base::print;
};
