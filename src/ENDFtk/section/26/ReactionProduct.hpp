/**
 *  @class
 *  @brief A reaction product with multiplicity and distribution data
 *
 *  The ReactionProduct class is used to represent a reaction product in
 *  an ENDF MF26 section with an associated multiplicity and distribution
 *  (multiple options are available).
 *
 *  See ENDF102, section 26.2 for more information.
 */
class ReactionProduct {

  /* fields */
  Multiplicity multiplicity_;
  Distribution law_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/ReactionProduct/src/verifyLAW.hpp" // taken from MF6
  #include "ENDFtk/section/26/ReactionProduct/src/readDistribution.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ReactionProduct/src/ctor.hpp"  // taken from MF6

  /* methods */

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  int ZAP() const { return this->multiplicity_.ZAP(); }

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  int productIdentifier() const { return this->ZAP(); }

  /**
   *  @brief Return the atomic weight ratio of the projectile
   */
  double AWI() const { return this->multiplicity_.AWI(); }

  /**
   *  @brief Return the atomic weight ratio of the projectile
   */
  double projectileWeightRatio() const { return this->AWI(); }

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  int LAW() const { return this->multiplicity_.LAW(); }

  /**
   *  @brief Return the multiplicity
   */
  const Multiplicity& multiplicity() const { return this->multiplicity_; }

  /**
   *  @brief Return the distribution
   */
  const Distribution& distribution() const { return this->law_; }

  /**
   *  @brief Return the number of lines in this MF26 component
   */
  long NC() const { return this->multiplicity_.NC()
                             + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->law_ ); }

  #include "ENDFtk/section/6/ReactionProduct/src/print.hpp"  // taken from MF6
};
