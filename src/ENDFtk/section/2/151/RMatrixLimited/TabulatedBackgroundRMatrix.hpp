/**
 *  @class
 *  @brief A tabulated complex function as a channel's background R-matrix
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedBackgroundRMatrix :
  protected BaseBackgroundRMatrix< TabulatedBackgroundRMatrix > {

  friend BaseBackgroundRMatrix< TabulatedBackgroundRMatrix >;

  /* fields */
  TabulationRecord real_;
  TabulationRecord imaginary_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/RMatrixLimited/TabulatedBackgroundRMatrix/src/extract.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/TabulatedBackgroundRMatrix/src/verify.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/TabulatedBackgroundRMatrix/src/verifyLBK.hpp"

  /* workaround for the removal of range-v3 */

  // the range-v3 implementation used zip_transform on RBR() and RBI() but the
  // replacement capability does not work the way it should so we generate a vector
  // at construction time instead
  std::vector< std::complex< double > > complex_;
  #include "ENDFtk/section/2/151/RMatrixLimited/TabulatedBackgroundRMatrix/src/generateComplexNumbers.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/RMatrixLimited/TabulatedBackgroundRMatrix/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the background R-matrix representation
   */
  static constexpr long representation() { return 1; }

  using BaseBackgroundRMatrix::LBK;
  using BaseBackgroundRMatrix::LCH;
  using BaseBackgroundRMatrix::channelIndex;

  /**
   *  @brief Return the number of energy points.
   */
  unsigned int NP() const { return this->real_.NP(); }

  /**
   *  @brief Return the number of energy points.
   */
  unsigned int numberPoints() const { return this->NP(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  unsigned int NR() const { return this->real_.NR(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  unsigned int numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return this->real_.interpolants(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the interpolation range boundaries.
   */
  auto NBT() const { return this->real_.boundaries(); }

  /**
   *  @brief Return the interpolation boundaries.
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return this->real_.x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the real component of the R-matrix values
   */
  auto RBR() const { return this->real_.y(); }

  /**
   *  @brief Return the real component of the R-matrix values
   */
  auto real() const { return this->RBR(); }

  /**
   *  @brief Return the imaginary component of the R-matrix values
   */
  auto RBI() const { return this->imaginary_.y(); }

  /**
   *  @brief Return the imaginary component of the R-matrix values
   */
  auto imaginary() const { return this->RBI(); }

  /**
   *  @brief Return the complex R-matrix values
   */
  auto RB() const {

    // see note above about range-v3 removal workaround
    // using namespace njoy::tools;
    // return std23::views::zip_transform(
    //            [] ( double real, double imag ) -> std::complex< double >
    //               { return { real, imag }; },
    //            this->real_.y(),
    //            this->imaginary_.y() );
    using namespace njoy::tools;
    return this->complex_ | std20::views::all;
  }

  /**
   *  @brief Return the complex R-matrix values
   */
  auto rmatrix() const { return this->RB(); }

  /**
   *  @brief Return the number of lines in this MF2/MT151 component
   */
  long NC() const { return 1 + this->real_.NC() + this->imaginary_.NC(); }

  /**
   *  @brief Print this MF2/MT151 component
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    ControlRecord( 0.0, 0.0, this->LCH(),
                   this->LBK(), 0, 0 ).print( it, MAT, MF, MT );
    this->real_.print( it, MAT, MF, MT );
    this->imaginary_.print( it, MAT, MF, MT );
  }
};
