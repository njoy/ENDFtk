class SubSection {

  using SubSectionVariant = std::variant< LegendreCoefficients, // LANG=1
                                          KalbachMann,          // LANG=2
                                          Tabulated >;          // LANG=11-15
  SubSectionVariant data_;

public:
  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/SubSection/src/ctor.hpp"

  /* get methods */
  const auto& data() const { return this->data_; }
  double energy() const { return std::visit( [] ( const auto& v ) -> double
                                                { return v.energy(); },
                                             this->data_ ); }
  int LANG() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.LANG(); },
                                       this->data_ ); }
  int ND() const { return std::visit( [] ( const auto& v ) -> long
                                         { return v.ND(); },
                                      this->data_ ); }
  int numberDiscreteEnergies() const { return this->ND(); }
  int NA() const { return std::visit( [] ( const auto& v ) -> long
                                         { return v.NA(); },
                                      this->data_ ); }
  int numberAngularParameters() const { return this->NA(); }
  int NW() const { return std::visit( [] ( const auto& v ) -> long
                                         { return v.NW(); },
                                      this->data_ ); }
  int NEP() const { return std::visit( [] ( const auto& v ) -> long
                                          { return v.NEP(); },
                                      this->data_ ); }
  int numberSecondaryEnergies() const { return this->NEP(); }

  long NC() const { return std::visit( [] ( const auto& v ) -> long
                                          { return v.NC(); },
                                       this->data_ ); }

  #include "ENDFtk/section/6/ContinuumEnergyAngle/SubSection/src/print.hpp"
};
