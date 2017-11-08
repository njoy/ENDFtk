using SubSectionVariant = std::variant< // LANG=1
                                        LegendreCoefficients,
                                        // LANG=12,14
                                        Tabulated >;

class SubSection :
public SubSectionVariant {

protected:
#include "ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection/src/readSubSection.hpp"

public:
  /* constructor */
#include "ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection/src/ctor.hpp"

  /* get methods */
  double energy() const { return std::visit( [] ( const auto& v ) -> double
                                                { return v.energy(); },
                                             *this ); }
  int LANG() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.LANG(); },
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

#include "ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection/src/print.hpp"
};
