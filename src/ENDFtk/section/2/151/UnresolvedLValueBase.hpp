/**
 *  @class
 *  @brief Base class for an l value in the unresolved resonances (used for
 *         energy dependent fission widths and all energy dependent widths).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
template < typename JValue > class UnresolvedLValueBase {

  /* fields */

  double awri_;
  int l_;
  std::vector< JValue > jvalues_;

  /* auxiliary functions */

  static void
  verifySize( int NJS ) {

    if ( NJS < 1 ) {

      Log::error( "Encountered illegal NJS value" );
      Log::info( "NJS should be larger than zero" );
      Log::info( "NJS value: {}", NJS );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  UnresolvedLValueBase( ControlRecord&& cont,
                        Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT ) :
    UnresolvedLValueBase( cont.C1(), cont.L1(),
                          readSequence< JValue >( it, end, lineNumber,
                                                  MAT, MF, MT, cont.N1() ) ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] awri       the atomic weight ratio
   *  @param[in] l          the orbital angular momentum value
   *  @param[in] jvalues    the unresolved resonance parameters for every J value
   *                        (NJS elements)
   */
  UnresolvedLValueBase( double awri, int l, std::vector< JValue >&& jvalues ) :
    awri_( awri ), l_( l ), jvalues_( std::move( jvalues ) ) {

      verifySize( this->NJS() );
    }

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
  UnresolvedLValueBase( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT ) :
    UnresolvedLValueBase( ControlRecord( it, end, lineNumber, MAT, MF, MT ),
                          it, end, lineNumber, MAT, MF, MT ) {}

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double AWRI() const { return this->awri_; }

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double atomicWeightRatio() const { return this->AWRI(); }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int L() const { return this->l_; }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int orbitalMomentum() const { return this->L(); }

  /**
   *  @brief Return the number of J values for this l value
   */
  int NJS() const { return this->jvalues_.size(); }

  /**
   *  @brief Return the number of J values for this l value
   */
  int numberSpinValues() const { return this->NJS(); }

  /**
   *  @brief Return the data for each of the J values
   */
  auto jValues() const {

    using namespace njoy::tools;
    return std20::views::all( this->jvalues_ );
  }

  /**
   *  @brief Return the number of fission width values
   */
  unsigned int NE() const { return this->jvalues_.front().NE(); }

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const {

    long NC = 1;
    for ( const auto& jvalue : this->jvalues_ ) { NC += jvalue.NC(); }
    return NC;
  };

  /**
   *  @brief Print this MF2 MT151 component
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

    ControlRecord( this->AWRI(), 0.0,
                   this->L(), 0,
                   this->NJS(), 0 ).print( it, MAT, MF, MT );
    for ( const auto& jvalue : this->jvalues_ ) {

      jvalue.print( it, MAT, MF, MT );
    }
  }
};
