/**
 *  @class
 *  @brief Convenience interface for unresolved resonance data associated to a
 *         given angular momentum value J for MF32.
 *
 *  See ENDF102, section 32.2.4 for more information.
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
  double AJ() const { return this->chunk[1]; }

  /**
   *  @brief Return the spin value
   */
  double spin() const { return this->AJ(); }

  /**
   *  @brief Return the average level spacing.
   */
  double D() const { return this->chunk[0]; }

  /**
   *  @brief Return the average level spacing.
   */
  double averageLevelSpacing() const { return this->D(); }

  /**
   *  @brief Return the average neutron width.
   */
  double GNO() const { return this->chunk[2]; }

  /**
   *  @brief Return the average neutron width.
   */
  double averageNeutronWidth() const { return this->GNO(); }

  /**
   *  @brief Return the average gamma width.
   */
  double GG() const { return this->chunk[3]; }

  /**
   *  @brief Return the average gamma width.
   */
  double averageGammaWidth() const { return this->GG(); }

  /**
   *  @brief Return the average fission width.
   */
  double GF() const { return this->chunk[4]; }

  /**
  *  @brief Return the average fission width.
   */
  double averageFissionWidth() const { return this->GF(); }

  /**
   *  @brief Return the average competitive width.
   */
  double GX() const { return this->chunk[5]; }

  /**
   *  @brief Return the average competitive width.
   */
  double averageCompetitiveWidth() const { return this->GX(); }
};
