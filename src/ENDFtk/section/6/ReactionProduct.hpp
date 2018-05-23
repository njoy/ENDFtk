class ReactionProduct {

  /* fields */
  Multiplicity multiplicity_;
  Distribution law_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/ReactionProduct/src/readDistribution.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ReactionProduct/src/ctor.hpp"

  /* get methods */
  double ZAP() const { return this->multiplicity_.ZAP(); }
  double AWP() const { return this->multiplicity_.AWP(); }
  int LIP() const { return this->multiplicity_.LIP(); }
  int LAW() const { return this->multiplicity_.LAW(); }

  const Multiplicity& multiplicity() const { return this->multiplicity_; }

  const Distribution& distribution() const { return this->law_; }

  long NC() const { return this->multiplicity_.NC()
                             + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->law_ ); }

  #include "ENDFtk/section/6/ReactionProduct/src/print.hpp"
};
