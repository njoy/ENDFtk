/**
 *  @class
 *  @brief Convenience interface for Breit-Wigner resonances with
 *         covariance information (LCOMP = 0)
 *
 *  See ENDF102, section 32.2.1 for more information.
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
   *  @brief Return the competitive width
   */
  double GX() const {

    return this->GT() - this->GN() - this->GG() - this->GF();
  }

  /**
   *  @brief Return the competitive width
   */
  double competitiveWidth() const { return this->GX(); }

  /**
   *  @brief Return the resonance energy variance
   */
  double DE2() const { return this->chunk[6]; }

  /**
   *  @brief Return the resonance energy
   */
  double resonanceEnergyVariance() const { return this->DE2(); }

  /**
   *  @brief Return the neutron width variance
   */
  double DN2() const { return this->chunk[7]; }

  /**
   *  @brief Return the neutron width variance
   */
  double neutronWidthVariance() const { return this->DN2(); }

  /**
   *  @brief Return the neutron and gamma width covariance
   */
  double DNDG() const { return this->chunk[8]; }

  /**
   *  @brief Return the neutron and gamma width covariance
   */
  double neutronAndGammaWidthCovariance() const { return this->DNDG(); }

  /**
   *  @brief Return the gamma width variance
   */
  double DG2() const { return this->chunk[9]; }

  /**
   *  @brief Return the gamma width variance
   */
  double gammaWidthVariance() const { return this->DG2(); }

  /**
   *  @brief Return the neutron and fission width covariance
   */
  double DNDF() const { return this->chunk[10]; }

  /**
   *  @brief Return the neutron and fission width covariance
   */
  double neutronAndFissionWidthCovariance() const { return this->DNDF(); }

  /**
   *  @brief Return the gamma and fission width covariance
   */
  double DGDF() const { return this->chunk[11]; }

  /**
   *  @brief Return the neutron and fission width covariance
   */
  double gammaAndFissionWidthCovariance() const { return this->DGDF(); }

  /**
   *  @brief Return the fission width variance
   */
  double DF2() const { return this->chunk[12]; }

  /**
   *  @brief Return the fission width variance
   */
  double fissionWidthVariance() const { return this->DF2(); }

  /**
   *  @brief Return the spin and neutron width covariance
   */
  double DJDN() const { return this->chunk[13]; }

  /**
   *  @brief Return the spin and neutron width covariance
   */
  double spinAndNeutronWidthCovariance() const { return this->DJDN(); }

  /**
   *  @brief Return the spin and gamma width covariance
   */
  double DJDG() const { return this->chunk[14]; }

  /**
   *  @brief Return the spin and gamma width covariance
   */
  double spinAndGammaWidthCovariance() const { return this->DJDG(); }

  /**
   *  @brief Return the spin and fission width covariance
   */
  double DJDF() const { return this->chunk[15]; }

  /**
   *  @brief Return the spin and fission width covariance
   */
  double spinAndFissionWidthCovariance() const { return this->DJDF(); }

  /**
   *  @brief Return the spin variance
   */
  double DJ2() const { return this->chunk[16]; }

  /**
   *  @brief Return the spin variance
   */
  double spinVariance() const { return this->DJ2(); }
};
