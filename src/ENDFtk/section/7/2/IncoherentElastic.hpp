/**
 *  @class
 *  @brief Incoherent elastic scattering law
 *
 *  The IncoherentElastic class is used to represent the incoherent elastic
 *  scattering law of MF7/MT2.
 *
 *  See ENDF102, section 7.3 for more information.
 */
class IncoherentElastic : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/7/2/IncoherentElastic/src/ctor.hpp"

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
  AllRange< double > T() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the temperature values
   */
  AllRange< double > temperatures() const { return this->T(); }

  /**
   *  @brief Return the Debye-Waller integral divided by the atomic mass (eV^-1)
   */
  AllRange< double > W() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the Debye-Waller integral divided by the atomic mass (eV^-1)
   */
  AllRange< double > debyeWallerValues() const { return this->W(); }

  /* get methods */
  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
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
