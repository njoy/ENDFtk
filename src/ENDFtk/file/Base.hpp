template < typename Derived >
class Base {

public:

  /* get methods */

  /**
   *  @brief Return the MF number of the file
   */
  constexpr int MF() const {

    return static_cast< const Derived* >( this )->fileNumber();
  }

  /**
   *  @brief Verify if a given section (defined by the MT number) is defined
   *
   *  @param mt   the MT number of the section to be verified
   */
  constexpr bool hasMT( int mt ) const {

    return static_cast< const Derived* >( this )->hasSection( mt );
  }

  /**
   *  @brief Retrieve a specific MT section
   *
   *  @param mt   the MT number of the section to be retrieved
   */
  template< typename Index >
  constexpr decltype( auto ) MT( Index sectionNo ) const {

    return static_cast< const Derived* >( this )->section( sectionNo );
  }

  /**
   *  @brief Retrieve a specific MT section
   *
   *  @param mt   the MT number of the section to be retrieved
   */
  template< typename Index > constexpr decltype( auto ) MT( Index sectionNo ) {

    return static_cast< const Derived* >( this )->section( sectionNo );
  }
};

