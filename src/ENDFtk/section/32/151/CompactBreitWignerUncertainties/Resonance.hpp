/**
 *  @class
 *  @brief Convenience interface for Breit-Wigner resonances with
 *         covariance information (LCOMP = 2)
 *
 *  See ENDF102, section 32.2.3.1 for more information.
 */
template < typename Range >
class Resonance {

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
   *  @brief Return the total width
   */
  double GT() const { return this->chunk[2]; }

  /**
   *  @brief Return the total width
   */
  double totalWidth() const { return this->GT(); }

  /**
   *  @brief Return the neutron width
   */
  double GN() const { return this->chunk[3]; }

  /**
   *  @brief Return the neutron width
   */
  double neutronWidth() const { return this->GN(); }

  /**
   *  @brief Return the gamma width
   */
  double GG() const { return this->chunk[4]; }

  /**
   *  @brief Return the gamma width
   */
  double gammaWidth() const { return this->GG(); }

  /**
   *  @brief Return the fission width
   */
  double GF() const { return this->chunk[5]; }

  /**
   *  @brief Return the fission width
   */
  double fissionWidth() const { return this->GF(); }

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
  double DGN() const { return this->chunk[9]; }

  /**
   *  @brief Return the neutron width uncertainty
   */
  double neutronWidthUncertainty() const { return this->DGN(); }

  /**
   *  @brief Return the gamma width uncertainty
   */
  double DGG() const { return this->chunk[10]; }

  /**
   *  @brief Return the gamma width uncertainty
   */
  double gammaWidthUncertainty() const { return this->DGG(); }

  /**
   *  @brief Return the fission width uncertainty
   */
  double DGF() const { return this->chunk[11]; }

  /**
   *  @brief Return the fission width uncertainty
   */
  double fissionWidthUncertainty() const { return this->DGF(); }
};
