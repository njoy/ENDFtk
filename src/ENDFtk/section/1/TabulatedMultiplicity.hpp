#ifndef NJOY_ENDFTK_SECTION_1_TABULATEDMULTIPLICITY
#define NJOY_ENDFTK_SECTION_1_TABULATEDMULTIPLICITY

// system includes

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/TabulationRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief Energy dependent fission multiplicity
   *
   *  This class is defined outside of any of the fission multiplicity
   *  section::Type instances since this component is common to all of them.
   *
   *  See ENDF102, section 1.2 for more information.
   */
  class ENDFTK_PYTHON_EXPORT TabulatedMultiplicity : protected TabulationRecord {

  public:

    /* constructors */

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    TabulatedMultiplicity() = default;
    #endif

    /**
     *  @brief Constructor
     *
     *  @param[in] boundaries       the interpolation range boundaries
     *  @param[in] interpolants     the interpolation types for each range
     *  @param[in] energies         the cosine values
     *  @param[in] multiplicities   the fission multiplicity values
     */
    TabulatedMultiplicity( std::vector< long >&& boundaries,
                           std::vector< long >&& interpolants,
                           std::vector< double >&& cosines,
                           std::vector< double >&& probabilities )
      try : TabulationRecord( 0.0, 0.0, 0, 0,
                              std::move( boundaries ),
                              std::move( interpolants ),
                              std::move( cosines ),
                              std::move( probabilities ) ) {}
      catch ( std::exception& e ) {

        Log::info( "Encountered error while constructing tabulated fission "
        	         "multiplicities" );
        throw;
      }

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     *  @param[in] MF           the expected MF number
     *  @param[in] MT           the expected MT number
     */
    template< typename Iterator >
    TabulatedMultiplicity( Iterator& begin, const Iterator& end,
                           long& lineNumber, int MAT, int MF, int MT )
      try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
      catch ( std::exception& e ) {

        Log::info( "Encountered error while constructing tabulated fission "
        	         "multiplicities" );
        throw;
      }

    /* methods */

    /**
     *  @brief Return the fission multiplicity representation type
     */
    static constexpr int LNU() { return 2; }

    /**
     *  @brief Return the fission multiplicity representation type
     */
    int representation() const { return this->LNU(); }

    /**
     *  @brief Return the incident energy values
     */
    auto E() const { return TabulationRecord::x(); }

    /**
     *  @brief Return the incident energy values
     */
    auto energies() const { return this->E(); }

    /**
     *  @brief Return the fission multiplicity values
     */
    auto NU() const { return TabulationRecord::y(); }

    /**
     *  @brief Return the fission multiplicity values
     */
    auto multiplicities() const { return this->NU(); }

    using TabulationRecord::NP;
    using TabulationRecord::NR;
    using TabulationRecord::numberPoints;
    using TabulationRecord::numberInterpolationRegions;
    using TabulationRecord::INT;
    using TabulationRecord::NBT;
    using TabulationRecord::interpolants;
    using TabulationRecord::boundaries;
    using TabulationRecord::NC;
    using TabulationRecord::print;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
