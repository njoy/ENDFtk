/**
 *  @class
 *  @brief Base class for a channel's background R-matrix
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
template < typename Derived >
class BaseBackGroundRMatrix {

  /* fields */
  unsigned int index_;

protected:

  /* constructor */
  BaseBackGroundRMatrix( int index ) : index_( index ) {}

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
