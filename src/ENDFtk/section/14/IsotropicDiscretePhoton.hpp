/**
 *  @class
 *  @brief The angular distribution for a specific discrete photon is isotropic
 *
 *  See ENDF102, section 14.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT IsotropicDiscretePhoton {

  /* fields */

  double eg_;
  double es_;

  /* auxiliary functions */

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  IsotropicDiscretePhoton( ControlRecord&& cont ) :
    IsotropicDiscretePhoton( cont.C1(), cont.C2() ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  IsotropicDiscretePhoton() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] energy   the photon energy
   *  @param[in] level    the energy of the level from which the photon
   *                      originates
   */
  IsotropicDiscretePhoton( double energy, double level ) :
      // no need for a try ... catch: nothing can go wrong here
      eg_( energy ), es_( level ) {}

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   */
  template< typename Iterator >
  IsotropicDiscretePhoton( Iterator& it, const Iterator& end, long& lineNumber,
                           int MAT, int MF, int MT )
    try : IsotropicDiscretePhoton(
              ControlRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing the isotropic angular "
                 "distribution for a discrete photon" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double ES() const { return this->es_; }

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double levelEnergy() const { return this->ES(); }

  /**
   *  @brief Return the photon energy or the binding energy
   */
  double EG() const { return this->eg_; }

  /**
   *  @brief Return the photon energy or the binding energy
   */
  double photonEnergy() const { return this->EG(); }

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  static constexpr bool LI() { return true; }

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  bool isotropicDistributions() const { return this->LI(); }

  /**
   *  @brief Return the distribution law
   */
  static constexpr int LTT() { return 0; }

  /**
   *  @brief Return the distribution law
   */
  int LAW() const { return this->LTT(); }

  /**
   *  @brief Return the number of lines in this MF12 component
   */
  static constexpr long NC() { return 1; }

  /**
   *  @brief Print this MF14 component
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

    ControlRecord( this->EG(), this->ES(), 0, 0, 0, 0 ).print( it, MAT, MF, MT );
  }
};
