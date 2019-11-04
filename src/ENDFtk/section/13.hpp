template<>
class Type< 13 > : protected Base {

public:

  #include "ENDFtk/section/13/TotalCrossSection.hpp"
  #include "ENDFtk/section/13/PartialCrossSection.hpp"

private:

  /* fields */
  std::optional< TotalCrossSection > total_;
  std::vector< PartialCrossSection > partials_;

  /* auxiliary functions */
  #include "ENDFtk/section/13/src/verifyNK.hpp"
  #include "ENDFtk/section/13/src/readTotalMultiplicity.hpp"
  #include "ENDFtk/section/13/src/readPartialMultiplicities.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/13/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the partial distributions defined in this section
   */
  const auto& photonProduction() const { return this->photon_; }

  /**
   *  @brief Return the number of partial cross sections (discrete photons
   *         and continuum)
   */
  int NK() const { return this->partials_.size(); }

  /**
  *  @brief Return the number of partial multiplicities (discrete photons
  *         and continuum)
   */
  int numberPartials() const { return this->NK(); }

  /**
   *  @brief Return the total cross section (optional)
   */
  const auto& totalCrossSection() const { return this->total_; }

  /**
   *  @brief Return the partial cross sections
   */
  auto partialCrossSections() const {

    return ranges::view::all( this->partials_ );
  }

  #include "ENDFtk/section/13/src/NC.hpp"
  #include "ENDFtk/section/13/src/print.hpp"

  using Base::MT;
  using Base::sectionNumber;
  using Base::ZA;
  using Base::atomicWeightRatio;
  using Base::AWR;
};



template<>
class Type< 13 > : protected Base {
public:
  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;

  static constexpr auto MF(){ return 13; }

  #include "ENDFtk/section/13/Subsection.hpp"

protected:
  std::vector< TabulationRecord > subsections_;

  #include "ENDFtk/section/13/src/readSubsections.hpp"

public:
  #include "ENDFtk/section/13/src/ctor.hpp"

  int NK() const { return std::max( 1, int( this->subsections_.size() ) - 1 ); }

  auto energies() const { return subsections_.front().x(); }
  auto crossSections() const { return subsections_.front().y(); }
  auto subsections() const {
    return
      this->subsections_
      | ranges::view::drop_exactly( this->NK() > 1 )
      | ranges::view::transform
        ( []( const auto& tabulationRecord ) -> const Subsection&
          { return static_cast< const Subsection& >( tabulationRecord ); } );
  }

  #include "ENDFtk/section/13/src/NC.hpp"
  #include "ENDFtk/section/13/src/print.hpp"
};
