/**
 *  @class
 *  @brief A tabulated complex function as a channel's background R-matrix
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class TabulatedBackgroundRMatrix : protected BaseBackgroundRMatrix< TabulatedBackgroundRMatrix > {

  friend BaseBackgroundRMatrix< TabulatedBackgroundRMatrix >;

  /* fields */
  TabulationRecord real_;
  TabulationRecord imaginary_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/RMatrixLimited/TabulatedBackgroundRMatrix/src/extract.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/TabulatedBackgroundRMatrix/src/verify.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/TabulatedBackgroundRMatrix/src/verifyLBK.hpp"

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
  auto NP() const { return this->real_.NP(); }

  /**
   *  @brief Return the number of interpolation ranges
   */
  auto NR() const { return this->real_.NR(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->real_.interpolants(); }

  /**
   *  @brief Return the interpolation range boundaries.
   */
  auto boundaries() const { return this->real_.boundaries(); }

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

    return ranges::view::zip_with(
               [] ( double real, double imag ) -> std::complex< double >
                  { return { real, imag }; },
               this->real_.y(),
               this->imaginary_.y() );
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
