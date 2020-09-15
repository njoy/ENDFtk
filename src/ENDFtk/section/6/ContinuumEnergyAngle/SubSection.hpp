class SubSection : public Variant {

public:

  /* constructor */
  using Variant::Variant;

  /* get methods */

  /**
   *  @brief Return the incident energy
   */
  double energy() const { return std::visit( [] ( const auto& v ) -> double
                                                { return v.energy(); },
                                             *this ); }

  /**
   *  @brief Return the LANG value
   */
  int LANG() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.LANG(); },
                                       *this ); }

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return std::visit( [] ( const auto& v ) -> long
                                          { return v.NC(); },
                                       *this ); }

  #include "ENDFtk/section/6/ContinuumEnergyAngle/SubSection/src/print.hpp"
};
