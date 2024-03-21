/**
 *  @class
 *  @brief Unresolved resonance data associated to a given angular momentum
 *         value J with fully energy dependent widths (this is the most
 *         general case for unresolved resonances).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT JValue : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependent/JValue/src/generateList.hpp"
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependent/JValue/src/verifySize.hpp"

  auto column( const int index ) const {

    return
      ListRecord::list()
        | ranges::views::drop_exactly( index + 6 )
        | ranges::views::stride(6);
  }

public:

  /* constructor */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependent/JValue/src/ctor.hpp"

  /**
   *  @brief Return the spin value
   */
  double AJ() const { return ListRecord::C1(); }

  /**
   *  @brief Return the spin value
   */
  double spin() const { return this->AJ(); }

  /**
   *  @brief Return the number of degrees of freedom for the neutron width.
   */
  int AMUN() const { return static_cast<int>( ListRecord::list()[3] ); }

  /**
   *  @brief Return the number of degrees of freedom for the neutron width.
   */
  int neutronWidthDegreesFreedom() const { return this->AMUN(); }

  /**
   *  @brief Return the number of degrees of freedom for the gamma width.
   */
  int AMUG() const { return static_cast<int>( ListRecord::list()[4] ); }

  /**
   *  @brief Return the number of degrees of freedom for the gamma width.
   */
  int gammaWidthDegreesFreedom() const { return JValue::AMUG(); }

  /**
   *  @brief Return the number of degrees of freedom for the fission width.
   */
  int AMUF() const { return static_cast<int>( ListRecord::list()[5] ); }

  /**
   *  @brief Return the number of degrees of freedom for the fission width.
   */
  int fissionWidthDegreesFreedom() const { return JValue::AMUF(); }

  /**
   *  @brief Return the number of degrees of freedom for the competitive width.
   */
  int AMUX() const { return static_cast<int>( ListRecord::list()[2] ); }

  /**
   *  @brief Return the number of degrees of freedom for the competitive width.
   */
  int competitiveWidthDegreesFreedom() const { return JValue::AMUX(); }

  /**
   *  @brief Return the energy values.
   */
  auto ES() const { return this->column( 0 ); }

  /**
   *  @brief Return the energy values.
   */
  auto energies() const { return this->ES(); }

  /**
   *  @brief Return the average level spacing.
   */
  auto D() const { return this->column( 1 ); }

  /**
   *  @brief Return the average level spacing.
   */
  auto averageLevelSpacings() const { return this->D(); }

  /**
   *  @brief Return the average neutron width.
   */
  auto GN() const { return this->column( 3 ); }

  /**
   *  @brief Return the average neutron width.
   */
  auto averageNeutronWidths() const { return this->GN(); }

  /**
   *  @brief Return the average gamma width.
   */
  auto GG() const { return this->column( 4 ); }

  /**
   *  @brief Return the average gamma width.
   */
  auto averageGammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the average fission widths (energy dependent).
   */
  auto GF() const { return this->column( 5 ); }

  /**
  *  @brief Return the average fission widths (energy dependent).
   */
  auto averageFissionWidths() const { return JValue::GF(); }

  /**
   *  @brief Return the average competitive width.
   */
  auto GX() const { return this->column( 2 ); }

  /**
  *  @brief Return the average competitive width.
   */
  auto averageCompetitiveWidths() const { return JValue::GX(); }

  /**
   *  @brief Return the interpolation type.
   */
  int INT() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of energy points.
   */
  unsigned int NE() const { return this->energies().size(); }

  /**
   *  @brief Return the number of interpolation ranges (always 1).
   */
  static constexpr int NR() { return 1; }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const {

    return std::array< int, 1 >{ this->INT() };
  }

  /**
   *  @brief Return the interpolation range boundaries.
   */
  auto boundaries() const {

    return std::array< int, 1 >{ static_cast<int>( this->NE() ) };
  }

  using ListRecord::NC;
  using ListRecord::print;
};
