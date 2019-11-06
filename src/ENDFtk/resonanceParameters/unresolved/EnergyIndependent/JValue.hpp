/**
 *  @class
 *  @brief Convenience interface for unresolved resonance data associated to a
 *         given angular momentum value J.
 *
 *  This range contains the average level spacing, the actual J value,
 *  the number degrees of freedom and the average neutron and gamma widths.
 *
 *  This JValue class applies to the case of energy independent widths (and
 *  fission is absent).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
template < typename Range >
class JValue {

  Range chunk;

public:

  /* constructor */
  JValue( Range&& chunk ) : chunk( std::move( chunk ) ) {}

  /**
   *  @brief Return the spin value
   */
  auto AJ() const { return this->chunk[1]; }

  /**
   *  @brief Return the spin value
   */
  auto spin() const { return this->AJ(); }

  /**
   *  @brief Return the average level spacing.
   */
  double D() const { return this->chunk[0]; }

  /**
   *  @brief Return the average level spacing.
   */
  double averageLevelSpacing() const { return this->D(); }

  /**
   *  @brief Return the number of degrees of freedom for the neutron width.
   */
  int AMUN() const { return static_cast<int>( this->chunk[2] ); }

  /**
   *  @brief Return the number of degrees of freedom for the neutron width.
   */
  int neutronWidthDegreesFreedom() const { return this->AMUN(); }

  /**
   *  @brief Return the number of degrees of freedom for the gamma width.
   */
  static constexpr int AMUG() { return 0; }

  /**
   *  @brief Return the number of degrees of freedom for the gamma width.
   */
  static constexpr int gammaWidthDegreesFreedom() { return JValue::AMUG(); }

  /**
   *  @brief Return the number of degrees of freedom for the fission width.
   */
  static constexpr int AMUF() { return 0; }

  /**
   *  @brief Return the number of degrees of freedom for the fission width.
   */
  static constexpr int fissionWidthDegreesFreedom() { return JValue::AMUF(); }

  /**
   *  @brief Return the number of degrees of freedom for the competitive width.
   */
  static constexpr int AMUX() { return 0; }

  /**
   *  @brief Return the number of degrees of freedom for the competitive width.
   */
  static constexpr int competitiveWidthDegreesFreedom() {

    return JValue::AMUX();
  }

  /**
   *  @brief Return the average neutron width.
   */
  double GN() const { return this->chunk[3]; }

  /**
   *  @brief Return the average neutron width.
   */
  double averageNeutronWidth() const { return this->GN(); }

  /**
   *  @brief Return the average gamma width.
   */
  double GG() const { return this->chunk[4]; }

  /**
   *  @brief Return the average gamma width.
   */
  double averageGammaWidth() const { return this->GG(); }

  /**
   *  @brief Return the average fission width.
   */
  static constexpr double GF() { return 0.0; }

  /**
  *  @brief Return the average fission width.
   */
  static constexpr double averageFissionWidth() { return JValue::GF(); }

  /**
   *  @brief Return the average competitive width.
   */
  static constexpr double GX() { return 0.0; }

  /**
  *  @brief Return the average competitive width.
   */
  static constexpr double averageCompetitiveWidth() { return JValue::GX(); }
};
