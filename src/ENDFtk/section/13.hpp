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
  #include "ENDFtk/section/13/src/readTotalCrossSection.hpp"
  #include "ENDFtk/section/13/src/readPartialCrossSections.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/13/src/ctor.hpp"

  /* get methods */

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
