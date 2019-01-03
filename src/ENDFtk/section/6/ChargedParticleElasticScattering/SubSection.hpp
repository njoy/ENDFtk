class SubSection {

  using SubSectionVariant = std::variant< NuclearAmplitudeExpansion, // LTP=1
                                          LegendreCoefficients,      // LTP=2
                                          NuclearPlusInterference >; // LTP>2
  SubSectionVariant data_;

protected:
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/SubSection/src/readSubSection.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/SubSection/src/ctor.hpp"

  /* get methods */
  const auto& data() const { return this->data_; }
  double energy() const { return std::visit( [] ( const auto& v ) -> double
                                                { return v.energy(); },
                                             this->data_ ); }
  int LTP() const { return std::visit( [] ( const auto& v ) -> long
                                          { return v.LTP(); },
                                       this->data_ ); }
  int NW() const { return std::visit( [] ( const auto& v ) -> long
                                         { return v.NW(); },
                                      this->data_ ); }
  int NL() const { return std::visit( [] ( const auto& v ) -> long
                                         { return v.NL(); },
                                      this->data_ ); }

  long NC() const { return std::visit( [] ( const auto& v ) -> long
                                          { return v.NC(); },
                                       this->data_ ); }

  #include "ENDFtk/section/6/ChargedParticleElasticScattering/SubSection/src/print.hpp"
};
