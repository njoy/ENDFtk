/**
 *  @class
 *  @brief Incoherent elastic scattering law
 *
 *  The IncoherentElastic class is used to represent the incoherent elastic
 *  scattering law of MF7/MT2.
 *
 *  See ENDF102, section 7.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT IncoherentElastic : protected TabulationRecord {

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  IncoherentElastic() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] sb              the characteristic bound cross section
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] temperatures    the temperature values
   *  @param[in] integrals       the values of the Debye-Waller integral
   *                             divided by the atomic mass (expressed
   *                             in eV^-1)
   */
  IncoherentElastic( double sb,
                     std::vector< long >&& boundaries,
                     std::vector< long >&& interpolants,
                     std::vector< double >&& temperatures,
                     std::vector< double >&& integrals )
    try : TabulationRecord( sb, 0.0, 0, 0,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( temperatures ),
                            std::move( integrals ) ) {}
   catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing incoherent elastic "
                 "scattering data" );
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
  IncoherentElastic( Iterator& begin, const Iterator& end,
                        long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading incoherent elastic "
                 "scattering data" );
      throw;
    }

  /**
   *  @brief Return the LTHR flag for incoherent elastic scattering
   */
  static constexpr int LTHR() { return 2; }

  /**
   *  @brief Return the LTHR flag for incoherent elastic scattering
   */
  int elasticScatteringType() const { return this->LTHR(); }

  /**
   *  @brief Return the characteristic bound cross section (barns)
   */
  double SB() const { return TabulationRecord::C1(); }

  /**
   *  @brief Return the characteristic bound cross section (barns)
   */
  double boundCrossSection() const { return this->SB(); }

  /**
   *  @brief Return the temperature values
   */
  auto T() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the temperature values
   */
  auto temperatures() const { return this->T(); }

  /**
   *  @brief Return the Debye-Waller integral divided by the atomic mass (eV^-1)
   */
  auto W() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the Debye-Waller integral divided by the atomic mass (eV^-1)
   */
  auto debyeWallerValues() const { return this->W(); }

  /* get methods */

  using TabulationRecord::NP;
  using TabulationRecord::numberPoints;
  using TabulationRecord::NR;
  using TabulationRecord::numberInterpolationRegions;
  using TabulationRecord::INT;
  using TabulationRecord::interpolants;
  using TabulationRecord::NBT;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;

  /**
   *  @brief Return the number of temperature values
   */
  auto NT() const { return this->NP(); }

  /**
   *  @brief Return the number of temperature values
   */
  auto numberTemperatures() const { return this->NT(); }
};
