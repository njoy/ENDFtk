#ifndef NJOY_ENDFTK_SECTION_1_POLYNOMIALMULTIPLICITY
#define NJOY_ENDFTK_SECTION_1_POLYNOMIALMULTIPLICITY

// system includes

// other includes
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
  class PolynomialMultiplicity : protected ListRecord {

  public:

    /* constructors */
    #include "ENDFtk/section/1/PolynomialMultiplicity/src/ctor.hpp"

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
