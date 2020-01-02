/**
 *  @class
 *  @brief Unresolved resonance data associated to a given angular momentum
 *         value J with fully energy dependent widths.
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class Jvalue : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/JValue/src/generateList.hpp"

  auto column( const int index ) const {
    return
      this->core.B()
      | ranges::view::drop_exactly( index + 6 )
      | ranges::view::stride(6);
  }

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/JValue/src/ctor.hpp"

  /**
   *  @brief Return the spin value
   */
  auto AJ() const { return ListRecord::C1(); }

  /**
   *  @brief Return the spin value
   */
  auto spin() const { return this->AJ(); }

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
   *  @brief Return the average level spacing.
   */
  double ES() const { return this->column( 0 ); }

  /**
   *  @brief Return the average level spacing.
   */
  double energies() const { return this->ES(); }

  /**
   *  @brief Return the average level spacing.
   */
  double D() const { return this->column( 1 ); }

  /**
   *  @brief Return the average level spacing.
   */
  double averageLevelSpacing() const { return this->D(); }

  /**
   *  @brief Return the average neutron width.
   */
  double GN() const { return this->column( 3 ); }

  /**
   *  @brief Return the average neutron width.
   */
  double averageNeutronWidth() const { return this->GN(); }

  /**
   *  @brief Return the average gamma width.
   */
  double GG() const { return this->column( 4 ); }

  /**
   *  @brief Return the average gamma width.
   */
  double averageGammaWidth() const { return this->GG(); }

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
  double GX() const { return this->column( 2 ); }

  /**
  *  @brief Return the average competitive width.
   */
  double averageCompetitiveWidth() const { return JValue::GX(); }

  int INT() const { return this->core.L1(); }
  int NE() const { return this->core.N2(); }

  using ListRecord::NC;
  using ListRecord::print;
};
