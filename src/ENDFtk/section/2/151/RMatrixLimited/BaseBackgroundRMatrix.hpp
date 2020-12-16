/**
 *  @class
 *  @brief Base class for a channel's background R-matrix
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
template < typename Derived >
class BaseBackgroundRMatrix {

  /* fields */
  unsigned int index_;

protected:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  BaseBackgroundRMatrix() = default;
  #endif

  BaseBackgroundRMatrix( int index ) : index_( index ) {}

public:

  /* get methods */

  /**
   *  @brief Return the background R-matrix representation
   */
  constexpr int LBK() const {

      return static_cast< const Derived* >( this )->representation();
  }

  /**
   *  @brief Return the channel index
   */
  constexpr int LCH() const { return this->index_; }

  /**
   *  @brief Return the channel index
   */
  constexpr int channelIndex() const { return this->LCH(); }
};
