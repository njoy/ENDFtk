using SubSectionVariant = std::variant< // LANG=1
                                        LegendreCoefficients,
                                        // LANG=2
                                        KalbachMann,
                                        // LANG=11-15
                                        Tabulated >;

class SubSection :
public SubSectionVariant {

public:
  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/SubSection/src/ctor.hpp"

  /* get methods */
  double energy() const { return std::visit( [] ( const auto& v ) -> double
                                                { return v.energy(); },
                                             *this ); }
  int LANG() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.LANG(); },
                                       *this ); }
  int ND() const { return std::visit( [] ( const auto& v ) -> long
                                         { return v.ND(); },
                                      *this ); }
  int NA() const { return std::visit( [] ( const auto& v ) -> long
                                         { return v.NA(); },
                                      *this ); }
  int NW() const { return std::visit( [] ( const auto& v ) -> long
                                         { return v.NW(); },
                                      *this ); }
  int NEP() const { return std::visit( [] ( const auto& v ) -> long
                                          { return v.NEP(); },
                                      *this ); }

  long NC() const { return std::visit( [] ( const auto& v ) -> long
                                          { return v.NC(); },
                                       *this ); }

  #include "ENDFtk/section/6/ContinuumEnergyAngle/SubSection/src/print.hpp"
};
