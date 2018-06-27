template<>
class Type< 7, 4 > : protected Base {

public:

  #include "ENDFtk/section/7/4/ScatteringLawConstants.hpp"

  #include "ENDFtk/section/7/4/AnalyticalFunctions.hpp"
  #include "ENDFtk/section/7/4/Tabulated.hpp"

  #include "ENDFtk/section/7/4/EffectiveTemperature.hpp"

  /** @typedef ScatteringLaw
   *  @brief The incoherent inelastic scattering law of MF7/MT4
   *
   *  This scattering law class is set up as a variant because the incoherent
   *  inelastic scattering law in MF7/MT4 can either be a given as analytical
   *  functions or as a tabulated S(a,b) function.
   */
  using ScatteringLaw = std::variant< // B(1)=0
                                      AnalyticalFunctions,
                                      // B(1)!=0
                                      Tabulated >;

private:

  /* fields */
  int lat_;
  int lasym_;

  ScatteringLawConstants b_;
  ScatteringLaw law_;

  EffectiveTemperature principal_;
  std::vector< std::optional< EffectiveTemperature > > secondary_;

  /* auxiliary functions */
  #include "ENDFtk/section/7/4/src/readSecondaryTemperatures.hpp"
  #include "ENDFtk/section/7/4/src/readScatteringLaw.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/7/4/src/ctor.hpp"

  /* get methods */
  int LAT() const { return this->lat_; }
  int LASYM() const { return this->lasym_; }

  const ScatteringLawConstants& constants() const { return this->b_; }

  const ScatteringLaw& scatteringLaw() const { return this->law_; }

  const EffectiveTemperature& principalEffectiveTemperature() const {
    return this->principal_;
  }

  auto secondaryEffectiveTemperatures() const {
    return ranges::make_iterator_range( this->secondary_.begin(),
                                        this->secondary_.end() );
  }

  #include "ENDFtk/section/7/4/src/NC.hpp"

  #include "ENDFtk/section/7/4/src/print.hpp"

  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;
  using Base::AWR;
};
