template<>
class Type< 7, 2 > : protected BaseWithoutMT< Type< 7, 2 > > {

  friend BaseWithoutMT< Type< 7, 2 > >;

public:

  #include "ENDFtk/section/7/2/CoherentElastic.hpp"
  #include "ENDFtk/section/7/2/IncoherentElastic.hpp"

  /** @typedef ScatteringLaw
   *  @brief The elastic scattering law of MF7/MT2
   *
   *  This scattering law class is set up as a variant because coherent and
   *  incoherent representations never occur together for a material.
   */
  using ScatteringLaw = std::variant< // LTHR=1
                                      CoherentElastic,
                                      // LTHR=2
                                      IncoherentElastic >;

private:

  /* fields */
  ScatteringLaw law_;

  /* auxiliary functions */
  #include "ENDFtk/section/7/2/src/readScatteringLaw.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/7/2/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the LTHR flag (coherent or incoherent elastic scattering)
   */
  int LTHR() const { return std::visit( [&] ( const auto& v ) -> long
                                            { return v.LTHR(); },
                                            this->law_ ); }

  /**
   *  @brief Return the LTHR flag (coherent or incoherent elastic scattering)
   */
  int elasticScatteringType() const { return this->LTHR(); }

  /**
   *  @brief Return the thermal scattering law (either coherent or incoherent)
   */
  const ScatteringLaw& scatteringLaw() const { return this->law_; }

  #include "ENDFtk/section/7/2/src/NC.hpp"

  #include "ENDFtk/section/7/2/src/print.hpp"

  /**
   *  @brief Return the MT number of the section
   */
  static constexpr int sectionNumber() { return 2; }

  using BaseWithoutMT::MT;
  using BaseWithoutMT::ZA;
  using BaseWithoutMT::atomicWeightRatio;
  using BaseWithoutMT::AWR;
};
