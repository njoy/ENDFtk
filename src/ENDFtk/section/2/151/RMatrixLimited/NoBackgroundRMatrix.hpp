/**
 *  @class
 *  @brief No background is given for the channel
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class NoBackGroundRMatrix : protected BaseBackGroundRMatrix< NoBackGroundRMatrix > {

  friend BaseBackGroundRMatrix< NoBackGroundRMatrix >;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/RMatrixLimited/NoBackGroundRMatrix/src/verifyLBK.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/RMatrixLimited/NoBackGroundRMatrix/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the background R-matrix representation
   */
  static constexpr long representation() { return 0; }

  using BaseBackGroundRMatrix::LBK;
  using BaseBackGroundRMatrix::LCH;
  using BaseBackGroundRMatrix::channelIndex;

  /**
   *  @brief Return the number of lines in this MF2/MT151 component
   */
  static constexpr long NC() { return 1; }

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
  }
};
