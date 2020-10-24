/**
 *  @class
 *  @brief Base class for distributions without data
 *
 *  See ENDF102, section 6.2 for more information.
 */
class NoLawDataGiven {

protected:

    NoLawDataGiven() = default;

public:

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  static constexpr long NC() { return 0; }

  /**
   *  @brief Print this MF6 component
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator&, int, int, int ) const { return; }
};
