/**
 *  @class
 *  @brief The element information for thermal scattering moderators
 *
 *  See ENDF102, section 7.6 for more information.
 */
class ElementInformation : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/7/451/ElementInformation/src/verifySize.hpp"
  #include "ENDFtk/section/7/451/ElementInformation/src/generateList.hpp"

  auto column( unsigned int i ) const {

    return ListRecord::list() | ranges::views::drop_exactly( i )
                              | ranges::views::stride( 6 );
  }

public:

//  #include "ENDFtk/section/7/451/ElementInformation/Isotope.hpp"

  /* constructor */
  #include "ENDFtk/section/7/451/ElementInformation/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of atoms in the molecule or unit cell
   */
  int NAS() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of atoms in the molecule or unit cell
   */
  int numberAtoms() const { return this->NAS(); }

  /**
   *  @brief Return the number of isotopes in the element
   */
  int NI() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of isotopes in the element
   */
  int numberIsotopes() const { return this->NI(); }

  /**
   *  @brief Return the isotope ZA identifiers
   */
  auto ZAI() const { return this->column( 0 ); }

  /**
  *  @brief Return the isotope ZA identifiers
   */
  auto isotopeIdentifiers() const { return this->ZAI(); }

  /**
   *  @brief Return the isotope isomeric states
   */
  auto LISI() const { return this->column( 1 ); }

  /**
   *  @brief Return the isotope isomeric states
   */
  auto isomericStates() const { return this->LISI(); }

  /**
   *  @brief Return the isotope abundances
   */
  auto AFI() const { return this->column( 2 ); }

  /**
   *  @brief Return the isotope abundances
   */
  auto abundances() const { return this->AFI(); }

  /**
   *  @brief Return the isotope atomic weight ratios
   */
  auto AWRI() const { return this->column( 3 ); }

  /**
   *  @brief Return the isotope abundances
   */
  auto atomicWeightRatios() const { return this->AWRI(); }

  /**
   *  @brief Return the isotope free atom scattering cross sections
   */
  auto SFI() const { return this->column( 4 ); }

  /**
   *  @brief Return the isotope free atom scattering cross sections
   */
  auto freeScatteringCrossSections() const { return this->SFI(); }

//  /**
//   *  @brief Return the resonances
//   */
//  auto resonances() const {
//
//    using Chunk = decltype( ( ListRecord::list() | ranges::views::chunk(18) )[0] );
//    return ListRecord::list() | ranges::views::chunk(18)
//             | ranges::cpp20::views::transform(
//                 [] ( Chunk&& chunk ) -> Resonance< Chunk >
//                    { return { std::move( chunk ) }; } );
//  }

  using ListRecord::NC;
  using ListRecord::print;
};
