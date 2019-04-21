template<>
class Type< 5 > : protected Base {

public:

  #include "ENDFtk/section/5/PartialProbability.hpp"

  #include "ENDFtk/section/5/Parameter.hpp"
  #include "ENDFtk/section/5/EffectiveTemperature.hpp"

  #include "ENDFtk/section/5/TabulatedSpectrum.hpp"            // LF=1
  #include "ENDFtk/section/5/GeneralEvaporationSpectrum.hpp"   // LF=5
  using MaxwellianFissionSpectrum = EffectiveTemperature;      // LF=7
  using EvaporationSpectrum = EffectiveTemperature;            // LF=9
  #include "ENDFtk/section/5/WattSpectrum.hpp"                 // LF=11
  #include "ENDFtk/section/5/MadlandNixSpectrum.hpp"           // LF=12

  using LF1 = TabulatedSpectrum;
  using LF5 = GeneralEvaporationSpectrum;
  using LF7 = MaxwellianFissionSpectrum;
  using LF9 = EvaporationSpectrum;
  using LF11 = WattSpectrum;
  using LF12 = MadlandNixSpectrum;

  /** @typedef PartialDistribution
   *  @brief A partial secondary particle energy distribution of MF5
   *
   *  This partial distribution class is set up as a variant. LF=7 or 9
   *  are the same underlying type (EffectiveTemperature) so this 
   *  type is only used once in the variant.
   */
  using PartialDistribution =
            std::variant< TabulatedSpectrum,           // LF=1
                          GeneralEvaporationSpectrum,  // LF=5
                          EffectiveTemperature,        // LF=7 or 9
                          WattSpectrum,                // LF=11
                          MadlandNixSpectrum >;        // LF=12

  #include "ENDFtk/section/5/SubSection.hpp"

private:

  /* fields */
  std::vector< SubSection > subsections_;

  /* auxiliary functions */
  #include "ENDFtk/section/5/src/verifyNK.hpp"
  #include "ENDFtk/section/5/src/readSubSections.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/5/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number NK of subsections with partial distributions
   */
  int NK() const { return this->subsections_.size(); }

  /**
   *  @brief Return the number NK of subsections with partial distributions
   */
  int numberPartialDistributions() const { return this->NK(); }

  /**
   *  @brief Return the partial distributions defined in this section
   */
  auto distributions() const { return ranges::view::all( this->subsections_ ); }

  #include "ENDFtk/section/5/src/NC.hpp"
  #include "ENDFtk/section/5/src/print.hpp"

  using Base::MT;
  using Base::sectionNumber;
  using Base::ZA;
  using Base::atomicWeightRatio;
  using Base::AWR;
};
