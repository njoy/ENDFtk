class SubSection {

  using SubSectionVariant = std::variant< LegendreCoefficients, // LANG=1
                                          Tabulated >;          // LANG=12,14
  SubSectionVariant data_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection/src/readSubSection.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection/src/ctor.hpp"

  /* get methods */
  const auto& data() const { return this->data_; }
  double energy() const { return std::visit( [] ( const auto& v ) -> double
                                                { return v.energy(); },
                                             this->data_ ); }
  int LANG() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.LANG(); },
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

  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection/src/print.hpp"
};
