#ifndef NJOY_ENDFTK_SECTION_8_FISSIONYIELDDATA
#define NJOY_ENDFTK_SECTION_8_FISSIONYIELDDATA

// system includes

// other includes
#include "ENDFtk/ListRecord.hpp"
#include "range/v3/view/chunk.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/transform.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief Fission yield data for a specific incident energy (or energy
   *         independent yields)
   *
   *  This class is defined outside of any of the fission yield
   *  section::Type instances since this component is common to all of them.
   *
   *  See ENDF102, section 8.3 for more information.
   */
  class FissionYieldData : protected ListRecord {

  public:

    using Column = StrideRange< DropRange< AllRange< double > > >;

  private:

    /* auxiliary functions */
    #include "ENDFtk/section/8/FissionYieldData/src/verifySize.hpp"
    #include "ENDFtk/section/8/FissionYieldData/src/generateList.hpp"

    Column column( unsigned int i ) const {

      return ListRecord::list() | ranges::views::drop_exactly( i )
                                | ranges::views::stride( 4 );
    }

  public:

    #include "ENDFtk/section/8/FissionYieldData/FissionProduct.hpp"

    /* constructors */
    #include "ENDFtk/section/8/FissionYieldData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the interpolation type (or LE value)
     */
    int I() const { return ListRecord::L1(); }

    /**
     *  @brief Return the interpolation type (or LE value)
     */
    int interpolationType() const { return this->I(); }

    /**
     *  @brief Return whether or not the fission yields are energy dependent
     *         or not
     */
    bool LE() const { return this->I() == 0; }

    /**
     *  @brief Return whether or not the fission yield data is energy independent
     */
    bool isEnergyIndependent() const { return this->LE(); }

    /**
     *  @brief Return the incident energy for which the fission yields are given
     */
    double E() const { return ListRecord::C1(); }

    /**
     *  @brief Return the incident energy for which the fission yields are given
     */
    double incidentEnergy() const { return this->E(); }

    /**
     *  @brief Return the number of fission products
     */
    int NFP() const { return ListRecord::N2(); }

    /**
     *  @brief Return the number of fission products
     */
    int numberFissionProducts() const { return this->NFP(); }

    /**
     *  @brief Return the fission product ZA identifiers
     */
    Column ZAFP() const { return this->column( 0 ); }

    /**
     *  @brief Return the fission product ZA identifiers
     */
    Column fissionProductIdentifiers() const { return this->ZAFP(); }

    /**
     *  @brief Return the fission product isomeric states
     */
    Column FPS() const { return this->column( 1 ); }

    /**
     *  @brief Return the fission product isomeric states
     */
    Column isomericStates() const { return this->FPS(); }

    /**
     *  @brief Return the fission yield values
     */
    auto Y() const {

      return ListRecord::list() | ranges::views::drop_exactly( 2 )
                                | ranges::views::chunk( 2 )
                                | ranges::views::stride( 2 );
    }

    /**
     *  @brief Return the fission yield values and uncertainties
     */
    auto fissionYields() const { return this->Y(); }

    /**
     *  @brief Return the fission products
     */
    auto fissionProducts() const {

      using Chunk = decltype( ( ListRecord::list()
                                  | ranges::views::chunk( 4 ) )[0] );
      return ListRecord::list() | ranges::views::chunk( 4 )
               | ranges::cpp20::views::transform(
                   [] ( Chunk&& chunk ) -> FissionProduct< Chunk >
                      { return { std::move( chunk ) }; } );
    }

    using ListRecord::NC;
    using ListRecord::print;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
