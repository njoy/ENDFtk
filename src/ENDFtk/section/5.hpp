template<>
class Type< 5 > : protected Base {

public:

  #include "ENDFtk/section/5/PartialProbability.hpp"

  #include "ENDFtk/section/5/EffectiveTemperature.hpp"

  #include "ENDFtk/section/5/TabulatedSpectrum.hpp"            // LF=1
//  #include "ENDFtk/section/5/GeneralEvaporationSpectrum.hpp"   // LF=5
  using MaxwellianFissionSpectrum = EffectiveTemperature;        // LF=7
  using EvaporationSpectrum = EffectiveTemperature;              // LF=9
//  #include "ENDFtk/section/5/WattSpectrum.hpp"                 // LF=11
//  #include "ENDFtk/section/5/MadlandNixSpectrum.hpp"           // LF=12

  using LF1 = TabulatedSpectrum;
//  using LF5 = GeneralEvaporationSpectrum;
  using LF7 = MaxwellianFissionSpectrum;
  using LF9 = EvaporationSpectrum;
//  using LF11 = WattSpectrum;
//  using LF12 = MadlandNixSpectrum;

  /** @typedef Distribution
   *  @brief A partial secondary particle energy distribution of MF5
   *
   *  This partial distribution class is set up as a variant.
   */
  using Distribution = std::variant< TabulatedSpectrum,           // LF=1
//                                     GeneralEvaporationSpectrum,  // LF=5
                                     MaxwellianFissionSpectrum,   // LF=7
                                     EvaporationSpectrum >;//,         // LF=9
//                                     WattSpectrum,                // LF=11
//                                     MadlandNixSpectrum >;        // LF=12

//  #include "ENDFtk/section/5/PartialDistribution.hpp"

private:

  /* fields */
//  std::vector< PartialDistribution > partials_;

  /* auxiliary functions */
//  #include "ENDFtk/section/5/src/verifyNK.hpp"
//  #include "ENDFtk/section/5/src/readDistributions.hpp"

public:

  /* constructor */
//  #include "ENDFtk/section/5/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number NK of partial distributions
   */
//  int NK() const { return this->partials_.size(); }

  /**
   *  @brief Return the number NK of partial distributions
   */
//  int numberPartialDistributions() const { return this->NK(); }

  /**
   *  @brief Return the partial distributions defined in this section
   */
//  auto distributions() const {
//
//    return ranges::view::all( this->partials_ );
//  }

//  #include "ENDFtk/section/5/src/NC.hpp"
//  #include "ENDFtk/section/5/src/print.hpp"

//  using Base::MT;
//  using Base::ZA;
//  using Base::atomicWeightRatio;
//  using Base::AWR;
};

