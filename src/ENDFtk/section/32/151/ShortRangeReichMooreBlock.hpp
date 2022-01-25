/**
 *  @class
 *  @brief Short-range Reich-Moore resonance parameters and covariance data
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ShortRangeReichMooreBlock :
  protected ShortRangeBreitWignerReichMooreBlockBase {

public:

  // reusing the Reich-Moore resonance interface
  #include "ENDFtk/section/2/151/ReichMooreLValue/Resonance.hpp"

  /* constructor */
  #include "ENDFtk/section/32/151/ShortRangeReichMooreBlock/src/ctor.hpp"

  using ShortRangeBreitWignerReichMooreBlockBase::AWRI;
  using ShortRangeBreitWignerReichMooreBlockBase::atomicWeightRatio;
  using ShortRangeBreitWignerReichMooreBlockBase::MPAR;
  using ShortRangeBreitWignerReichMooreBlockBase::numberParametersWithCovariances;
  using ShortRangeBreitWignerReichMooreBlockBase::NRB;
  using ShortRangeBreitWignerReichMooreBlockBase::numberResonances;

  using ShortRangeBreitWignerReichMooreBlockBase::ER;
  using ShortRangeBreitWignerReichMooreBlockBase::resonanceEnergies;
  using ShortRangeBreitWignerReichMooreBlockBase::AJ;
  using ShortRangeBreitWignerReichMooreBlockBase::spinValues;

  /**
   *  @brief Return the neutron widths
   */
  auto GN() const { return ShortRangeBreitWignerReichMooreBlockBase::G1(); }

  /**
   *  @brief Return the neutron widths
   */
  auto neutronWidths() const { return this->GN(); }

  /**
   *  @brief Return the gamma widths
   */
  auto GG() const { return ShortRangeBreitWignerReichMooreBlockBase::G2(); }

  /**
   *  @brief Return the gamma widths
   */
  auto gammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the first fission widths
   */
  auto GFA() const { return ShortRangeBreitWignerReichMooreBlockBase::G3(); }

  /**
   *  @brief Return the first fission widths
   */
  auto firstFissionWidths() const { return this->GFA(); }

  /**
   *  @brief Return the second fission widths
   */
  auto GFB() const { return ShortRangeBreitWignerReichMooreBlockBase::G4(); }

  /**
   *  @brief Return the second fission widths
   */
  auto secondFissionWidths() const { return this->GFB(); }

  /**
   *  @brief Return the resonances
   */
  auto resonances() const {

    using Chunk = decltype( ShortRangeBreitWignerReichMooreBlockBase::resonances()[0] );
    return ShortRangeBreitWignerReichMooreBlockBase::resonances()
             | ranges::cpp20::views::transform(
                 [] ( Chunk&& chunk ) -> Resonance< Chunk >
                    { return { std::move( chunk ) }; } );
  }

  using ShortRangeBreitWignerReichMooreBlockBase::covarianceMatrixOrder;
  using ShortRangeBreitWignerReichMooreBlockBase::NVS;
  using ShortRangeBreitWignerReichMooreBlockBase::numberValues;
  using ShortRangeBreitWignerReichMooreBlockBase::covarianceMatrix;

  //! @todo provide convenience interface for the covariance data

  using ShortRangeBreitWignerReichMooreBlockBase::NC;
  using ShortRangeBreitWignerReichMooreBlockBase::print;
};
