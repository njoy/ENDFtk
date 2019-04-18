template < typename Derived >
class Base {

public:

  /* get methods */

  /**
   *  @brief Return the MF number of the file
   */
  int MF() const {

    return static_cast< const Derived* >( this )->fileNumber();
  }

  /**
   *  @brief Verify if a given section (defined by the MT number) is defined
   *
   *  @param mt   the MT number of the section to be verified
   */
  bool hasMT( int mt ) const {

    return static_cast< const Derived* >( this )->hasSection( mt );
  }
};
