/**
 *  @class
 *  @brief SAMMY parametrisation as a channel's background R-matrix
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class SammyBackGroundRMatrix : protected BaseBackGroundRMatrix< SammyBackGroundRMatrix > {

  friend BaseBackGroundRMatrix< SammyBackGroundRMatrix >;

  /* fields */
  std::array< double, 7 > data_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/RMatrixLimited/SammyBackGroundRMatrix/src/extract.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/SammyBackGroundRMatrix/src/verifyLBK.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/RMatrixLimited/SammyBackGroundRMatrix/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the background R-matrix representation
   */
  static constexpr long representation() { return 2; }

  using BaseBackGroundRMatrix::LBK;
  using BaseBackGroundRMatrix::LCH;
  using BaseBackGroundRMatrix::channelIndex;

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
   *  @brief Return the R1 parameter in the SAMMY parametrisation
   */
  double R1() const { return this->data_[3]; }

  /**
   *  @brief Return the R2 parameter in the SAMMY parametrisation
   */
  double R2() const { return this->data_[4]; }

  /**
   *  @brief Return the S0 parameter in the SAMMY parametrisation
   */
  double S0() const { return this->data_[5]; }

  /**
   *  @brief Return the S1 parameter in the SAMMY parametrisation
   */
  double S1() const { return this->data_[6]; }

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
                { this->R0(), this->R1(), this->R2(),
                  this->S0(), this->S1() } ).print( it, MAT, MF, MT );
  }
};
