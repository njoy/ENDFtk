/**
 *  @class
 *  @brief A reaction product with multiplicity and distribution data
 *
 *  The ReactionProduct class is used to represent a reaction product in
 *  an ENDF MF6 section with an associated multiplicity and distribution
 *  (multiple options are available).
 *
 *  See ENDF102, section 6.2 for more information.
 */
class ReactionProduct {

  /* fields */
  Multiplicity multiplicity_;
  Distribution law_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/ReactionProduct/src/verifyLAW.hpp"
  #include "ENDFtk/section/6/ReactionProduct/src/readDistribution.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ReactionProduct/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  double ZAP() const { return this->multiplicity_.ZAP(); }

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  double productIdentifier() const { return this->ZAP(); }

  /**
   *  @brief Return the atomic weight ratio of the reaction product
   */
  double AWP() const { return this->multiplicity_.AWP(); }

  /**
   *  @brief Return the atomic weight ratio of the reaction product
   */
  double productWeightRatio() const { return this->AWP(); }

  /**
   *  @brief Return the product modifier flag
   */
  int LIP() const { return this->multiplicity_.LIP(); }

  /**
   *  @brief Return the product modifier flag
   */
  int productModifierFlag() const { return this->LIP(); }

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
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->multiplicity_.NC()
                             + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->law_ ); }

  #include "ENDFtk/section/6/ReactionProduct/src/print.hpp"
};
