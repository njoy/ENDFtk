/**
 *  @class
 *  @brief Convenience interface for Reich-Moore resonances with
 *         covariance information (LCOMP = 2)
 *
 *  See ENDF102, section 32.2.3.2 for more information.
 */
template < typename Range >
class ENDFTK_PYTHON_EXPORT Resonance {

  /* fields */
  Range chunk;

public:

  /* constructor */
  Resonance( Range&& chunk ) : chunk( std::move( chunk ) ) {}

  /**
   *  @brief Return the resonance energy
   */
  double ER() const { return this->chunk[0]; }

  /**
   *  @brief Return the resonance energy
   */
  double resonanceEnergy() const { return this->ER(); }

  /**
   *  @brief Return the spin value
   */
  double AJ() const { return this->chunk[1]; }

  /**
   *  @brief Return the spin value
   */
  double spin() const { return this->AJ(); }

  /**
   *  @brief Return the neutron width
   */
  double GN() const { return this->chunk[2]; }

  /**
   *  @brief Return the neutron width
   */
  double neutronWidth() const { return this->GN(); }

  /**
   *  @brief Return the gamma width
   */
  double GG() const { return this->chunk[3]; }

  /**
   *  @brief Return the gamma width
   */
  double gammaWidth() const { return this->GG(); }

  /**
   *  @brief Return the first fission width
   */
  double GFA() const { return this->chunk[4]; }

  /**
   *  @brief Return the first fission width
   */
  double firstFissionWidth() const { return this->GFA(); }

  /**
   *  @brief Return the second fission width
   */
  double GFB() const { return this->chunk[5]; }

  /**
   *  @brief Return the second fission width
   */
  double secondFissionWidth() const { return this->GFB(); }

  /**
   *  @brief Return the resonance energy uncertainty
   */
  double DER() const { return this->chunk[6]; }

  /**
   *  @brief Return the resonance energy
   */
  double resonanceEnergyUncertainty() const { return this->DER(); }

  /**
   *  @brief Return the neutron uncertainty
   */
  double DGN() const { return this->chunk[8]; }

  /**
   *  @brief Return the neutron width uncertainty
   */
  double neutronWidthUncertainty() const { return this->DGN(); }

  /**
   *  @brief Return the gamma width uncertainty
   */
  double DGG() const { return this->chunk[9]; }

  /**
   *  @brief Return the gamma width uncertainty
   */
  double gammaWidthUncertainty() const { return this->DGG(); }

  /**
   *  @brief Return the first fission width uncertainty
   */
  double DGFA() const { return this->chunk[10]; }

  /**
   *  @brief Return the first fission width uncertainty
   */
  double firstFissionWidthUncertainty() const { return this->DGFA(); }

  /**
   *  @brief Return the second fission width uncertainty
   */
  double DGFB() const { return this->chunk[11]; }

  /**
   *  @brief Return the second fission width uncertainty
   */
  double secondFissionWidthUncertainty() const { return this->DGFB(); }
};
