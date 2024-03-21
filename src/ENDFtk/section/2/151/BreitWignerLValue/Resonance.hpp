/**
 *  @class
 *  @brief Convenience interface for Breit-Wigner resonances
 *
 *  See ENDF102, section 2.2.1.1 for more information.
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
};
