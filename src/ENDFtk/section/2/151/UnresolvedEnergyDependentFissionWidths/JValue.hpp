/**
 *  @class
 *  @brief Unresolved resonance data associated to a given angular momentum
 *         value J when only the fission width is energy dependent.
 *
 *  This JValue class applies to the case of energy dependent fission widths
 *  while all other widths are energy independent.
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class JValue : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/JValue/src/generateList.hpp"
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/JValue/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/JValue/src/ctor.hpp"

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int L() const { return ListRecord::L1(); }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int orbitalMomentum() const { return this->L(); }

  /**
   *  @brief Return the spin value
   */
  double AJ() const { return ListRecord::list()[1]; }

  /**
   *  @brief Return the spin value
   */
  double spin() const { return this->AJ(); }

  /**
   *  @brief Return the number of degrees of freedom for the neutron width.
   */
  double AMUN() const { return static_cast<int>( ListRecord::list()[2] ); }

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
  int AMUF() const { return ListRecord::L2(); }

  /**
   *  @brief Return the number of degrees of freedom for the fission width.
   */
  int fissionWidthDegreesFreedom() const { return JValue::AMUF(); }

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
   *  @brief Return the average level spacing.
   */
  double D() const { return ListRecord::list()[0]; }

  /**
   *  @brief Return the average level spacing.
   */
  double averageLevelSpacing() const { return this->D(); }

  /**
   *  @brief Return the average neutron width.
   */
  double GN() const { return ListRecord::list()[3]; }

  /**
   *  @brief Return the average neutron width.
   */
  double averageNeutronWidth() const { return this->GN(); }

  /**
   *  @brief Return the average gamma width.
   */
  double GG() const { return ListRecord::list()[4]; }

  /**
   *  @brief Return the average gamma width.
   */
  double averageGammaWidth() const { return this->GG(); }

  /**
   *  @brief Return the average competitive width.
   */
  static constexpr double GX() { return 0.0; }

  /**
  *  @brief Return the average competitive width.
   */
  static constexpr double averageCompetitiveWidth() { return JValue::GX(); }

  /**
   *  @brief Return the average fission widths (energy dependent).
   */
  auto GF() const {

    return ListRecord::list() | ranges::views::drop_exactly( 6 );
  }

  /**
  *  @brief Return the average fission widths (energy dependent).
   */
  auto averageFissionWidths() const {

    return JValue::GF();
  }

  /**
   *  @brief Return the number of average fission width points.
   */
  unsigned int NE() const { return this->GF().size(); }

  /**
   *  @brief Return the number of interpolation ranges (always 1).
   */
  static constexpr int NR() { return 1; }

  /**
   *  @brief Return the interpolants (always linear-linear).
   */
  static constexpr auto interpolants() { return std::array< int, 1 >{ 2 }; }

  /**
   *  @brief Return the interpolation range boundaries.
   */
  auto boundaries() const {

    return std::array< int, 1 >{ static_cast<int>( this->NE() ) };
  }

  using ListRecord::NC;
  using ListRecord::print;
};
