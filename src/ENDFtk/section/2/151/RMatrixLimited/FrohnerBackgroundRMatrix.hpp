/**
 *  @class
 *  @brief Frohner parametrisation as a channel's background R-matrix
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT FrohnerBackgroundRMatrix : 
  protected BaseBackgroundRMatrix< FrohnerBackgroundRMatrix > {

  friend BaseBackgroundRMatrix< FrohnerBackgroundRMatrix >;

  /* fields */
  std::array< double, 5 > data_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/RMatrixLimited/FrohnerBackgroundRMatrix/src/extract.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/FrohnerBackgroundRMatrix/src/verifyLBK.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/RMatrixLimited/FrohnerBackgroundRMatrix/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the background R-matrix representation
   */
  static constexpr long representation() { return 3; }

  using BaseBackgroundRMatrix::LBK;
  using BaseBackgroundRMatrix::LCH;
  using BaseBackgroundRMatrix::channelIndex;

  /**
   *  @brief Return the energy down parameter in the SAMMY parametrisation
   */
  double ED() const { return this->data_[0]; }

  /**
   *  @brief Return the energy up parameter in the SAMMY parametrisation
   */
  double EU() const { return this->data_[1]; }

  /**
   *  @brief Return the R0 parameter in the SAMMY parametrisation
   */
  double R0() const { return this->data_[2]; }

  /**
   *  @brief Return the S0 parameter in the SAMMY parametrisation
   */
  double S0() const { return this->data_[3]; }

  /**
   *  @brief Return the GA parameter in the SAMMY parametrisation
   */
  double GA() const { return this->data_[4]; }

  /**
   *  @brief Return the number of lines in this MF2/MT151 component
   */
  static constexpr long NC() { return 3; }

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
    ListRecord( this->ED(), this->EU(), 0 ,0, 0,
                { this->R0(), this->S0(),
                  this->GA() } ).print( it, MAT, MF, MT );
  }
};
