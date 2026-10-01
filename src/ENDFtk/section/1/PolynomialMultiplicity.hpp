#ifndef NJOY_ENDFTK_SECTION_1_POLYNOMIALMULTIPLICITY
#define NJOY_ENDFTK_SECTION_1_POLYNOMIALMULTIPLICITY

// system includes

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief Fission multiplicity given as a polynomial expansion
   *
   *  This class is defined outside of any of the fission multiplicity
   *  section::Type instances since this component is common to all of them.
   *
   *  See ENDF102, section 1.2 for more information.
   */
  class ENDFTK_PYTHON_EXPORT PolynomialMultiplicity : protected ListRecord {

  public:

    /* constructors */

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    PolynomialMultiplicity() = default;
    #endif

    /**
     *  @brief Constructor
     *
     *  @param[in] coefficients    the polynomial coefficients
     */
    PolynomialMultiplicity( std::vector< double >&& coefficients )
      try : ListRecord( 0.0, 0.0, 0, 0, 0, std::move( coefficients ) ) {}
      catch ( std::exception& e ) {

        Log::info( "Encountered error while constructing polynomial fission "
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
    PolynomialMultiplicity( Iterator& begin, const Iterator& end,
                            long& lineNumber, int MAT, int MF, int MT )
      try : ListRecord( begin, end, lineNumber, MAT, MF, MT ) {}
      catch ( std::exception& e ) {

        Log::info( "Encountered error while constructing polynomial fission "
        	         "multiplicities" );
        throw;
      }

    /* methods */

    /**
     *  @brief Return the fission multiplicity representation type
     */
    static constexpr int LNU() { return 1; }

    /**
     *  @brief Return the fission multiplicity representation type
     */
    int representation() const { return this->LNU(); }

    /**
     *  @brief Return the number of coefficients in the polynomial expansion
     */
    int NCO() const { return ListRecord::NPL(); } // NC is used for number of lines

    /**
     *  @brief Return the number of coefficients in the polynomial expansion
     */
    int numberCoefficients() const { return this->NCO(); }

    /**
     *  @brief Return the coefficients
     */
    auto C() const { return ListRecord::list(); }

    /**
     *  @brief Return the coefficients
     */
    auto coefficients() const { return this->C(); }

    using ListRecord::NC;
    using ListRecord::print;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
