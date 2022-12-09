/**
 *  @class
 *  @brief A compact correlation matrix
 *
 *  This is the only instance where INTG records are used, so we decided to not
 *  implement INTG records as a base record. This class will handle the
 *  compression and decompression. Some assumptions will be made to do this so,
 *  as a result, this class may not reproduce an existing compact matrix
 *  exactly as it was originally given.
 *
 *  See ENDF102, section 0.6.4.9 and 32.2.3 for more information.
 */
class CompactCorrelationMatrix {

  /* fields */
  int ndigit_;
  int nnn_;
  std::vector< unsigned int > i_;
  std::vector< unsigned int > j_;
  std::vector< double > correlations_;

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/CompactCorrelationMatrix/src/readMatrixElements.hpp"
  #include "ENDFtk/section/32/151/CompactCorrelationMatrix/src/verifyUnsigned.hpp"
  #include "ENDFtk/section/32/151/CompactCorrelationMatrix/src/compact.hpp"
  #include "ENDFtk/section/32/151/CompactCorrelationMatrix/src/verifyDigits.hpp"
  #include "ENDFtk/section/32/151/CompactCorrelationMatrix/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/CompactCorrelationMatrix/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of digits used for compacting
   */
  unsigned int NDIGIT() const { return this->ndigit_; }

  /**
   *  @brief Return the number of digits used for compacting
   */
  unsigned int numberDigits() const { return this->NDIGIT(); }

  /**
   *  @brief Return the order of the correlation matrix
   */
  unsigned int NNN() const { return this->nnn_; }

  /**
   *  @brief Return the order of the correlation matrix
   */
  unsigned int order() const { return this->NNN(); }

  /**
   *  @brief Return the i coordinates for which correlation values are
   *         available
   */
  auto I() const { return ranges::cpp20::views::all( this->i_ ); }

  /**
   *  @brief Return the j coordinates for which correlation values are
   *         available
   */
  auto J() const { return ranges::cpp20::views::all( this->j_ ); }

  /**
   *  @brief Return the correlation values
   */
  auto correlations() const {

    return ranges::cpp20::views::all( this->correlations_ );
  }

  #include "ENDFtk/section/32/151/CompactCorrelationMatrix/src/NC.hpp"
  #include "ENDFtk/section/32/151/CompactCorrelationMatrix/src/print.hpp"
};
