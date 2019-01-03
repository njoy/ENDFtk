using SubSectionVariant = std::variant< NuclearAmplitudeExpansion, // LTP=1
                                        LegendreCoefficients,      // LTP=2
                                        NuclearPlusInterference >; // LTP>2

class SubSection :
public SubSectionVariant {

protected:
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/SubSection/src/readSubSection.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/SubSection/src/ctor.hpp"

  /* get methods */
  double energy() const { return std::visit( [] ( const auto& v ) -> double
                                                { return v.energy(); },
                                             *this ); }
  int LTP() const { return std::visit( [] ( const auto& v ) -> long
                                          { return v.LTP(); },
                                       *this ); }
  int NW() const { return std::visit( [] ( const auto& v ) -> long
                                         { return v.NW(); },
                                      *this ); }
  int NL() const { return std::visit( [] ( const auto& v ) -> long
                                         { return v.NL(); },
                                      *this ); }

  long NC() const { return std::visit( [] ( const auto& v ) -> long
                                          { return v.NC(); },
                                       *this ); }

  #include "ENDFtk/section/6/ChargedParticleElasticScattering/SubSection/src/print.hpp"
};
