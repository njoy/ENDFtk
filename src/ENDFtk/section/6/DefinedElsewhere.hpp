/**
 *  @class
 *  @brief The distributions are defined elsewhere and no data is given
 *
 *  See ENDF102, section 6.2.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT DefinedElsewhere : protected NoLawDataGiven {

  /* fields */

  int law_;

  /* auxiliary functions */

  static void
  checkLAW( int law ) {

    if ( ( law != -4 ) and ( law != -5 ) and
         ( law != -14 ) and ( law != -15 ) ) {

      Log::error( "Encountered illegal negative LAW value" );
      Log::info( "LANG must be equal to -4, -5, -14 or -15" );
      Log::info( "LANG value: {}", law );
      throw std::exception();
    }
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  DefinedElsewhere() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] law    the law number to be used (-4, -5, -14, -15 only)
   */
  DefinedElsewhere ( int LAW ) : law_( LAW ) {

    checkLAW( this->LAW() );
  }

  /* methods */

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  int LAW() const { return this->law_; }

  using NoLawDataGiven::NC;
  using NoLawDataGiven::print;
};
