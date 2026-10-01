/**
 *  @class
 *  @brief Base class for Breit-Wigner and Reich-Moore resonance parameters for
 *         a given l value
 *
 *  See ENDF102, section 2.2.1.1 and 2.2.1.2 for more information.
 */
class BreitWignerReichMooreLValueBase : protected ListRecord {

  /* auxiliary functions */

  static void
  verifySize( int NPL, int NRS ) {

    if ( NPL < 1 ) {

      Log::error( "Encountered empty list" );
      Log::info( "NPL should be larger than zero and equal to 6 * NRS" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NRS value: {}", NRS );
      throw std::exception();
    }

    if ( NRS < 1 ) {

      Log::error( "Encountered illegal NRS value" );
      Log::info( "NRS should be larger than zero" );
      Log::info( "NRS value: {}", NRS );
      throw std::exception();
    }

    if ( NPL != 6 * NRS ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to 6 * NRS" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NRS value: {}", NRS );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< double >&& energies,
                std::vector< double >&& spins,
                std::vector< double >&& column1,
                std::vector< double >&& column2,
                std::vector< double >&& column3,
                std::vector< double >&& column4 ) {

    unsigned int nrs = energies.size();
    if ( ( spins.size() != nrs ) or ( column1.size() != nrs ) or
         ( column2.size() != nrs ) or ( column3.size() != nrs ) or
         ( column4.size() != nrs ) ) {

      Log::info( "The number of resonances and the resonance parameters are not "
                 "consistent" );
      Log::info( "NRS value: {}", nrs );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "spins.size(): {}", spins.size() );
      Log::info( "column1.size(): {}", column1.size() );
      Log::info( "column2.size(): {}", column2.size() );
      Log::info( "column3.size(): {}", column3.size() );
      Log::info( "column4.size(): {}", column4.size() );
      throw std::exception();
    }

    std::vector< double > list;
    for ( unsigned int i = 0; i < nrs; ++i ) {

      list.push_back( energies[i] );
      list.push_back( spins[i] );
      list.push_back( column1[i] );
      list.push_back( column2[i] );
      list.push_back( column3[i] );
      list.push_back( column4[i] );
    }
    return list;
  }

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( i )
                              | std23::views::stride( 6 );
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  BreitWignerReichMooreLValueBase( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySize( this->NPL(), this->N2() );
  }

protected:

  /* constructor */

  public:
  /**
   *  @brief Constructor
   *
   *  @param[in] awri       the atomic weight ratio
   *  @param[in] c2         the value in C2
   *  @param[in] l          the orbital angular momentum value
   *  @param[in] l2         the value in l2
   *  @param[in] energies   the resonance energies (NRS values)
   *  @param[in] spins      the spin values (NRS values)
   *  @param[in] column1    the first width (NRS values)
   *  @param[in] column2    the second width (NRS values)
   *  @param[in] column3    the third width (NRS values)
   *  @param[in] column4    the fourth width (NRS values)
   */
  BreitWignerReichMooreLValueBase( double awri, double c2, int l, bool l2,
                                   std::vector< double >&& energies,
                                   std::vector< double >&& spins,
                                   std::vector< double >&& column1,
                                   std::vector< double >&& column2,
                                   std::vector< double >&& column3,
                                   std::vector< double >&& column4 ) :
    // no try ... catch: exceptions will be handled in the derived class
    BreitWignerReichMooreLValueBase(
            ListRecord( awri, c2, l, l2, energies.size(),
                        generateList( std::move( energies ),
                                      std::move( spins ),
                                      std::move( column1 ),
                                      std::move( column2 ),
                                      std::move( column3 ),
                                      std::move( column4 ) ) ) ) {}

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
  BreitWignerReichMooreLValueBase(
          Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
    BreitWignerReichMooreLValueBase( ListRecord( it, end, lineNumber,
                                                 MAT, MF, MT ) ) {}

  /**
   *  @brief Return the first width
   */
  auto G1() const { return BreitWignerReichMooreLValueBase::column( 2 ); }

  /**
   *  @brief Return the second width
   */
  auto G2() const { return BreitWignerReichMooreLValueBase::column( 3 ); }

  /**
   *  @brief Return the third width
   */
  auto G3() const { return BreitWignerReichMooreLValueBase::column( 4 ); }

  /**
   *  @brief Return the fourth width
   */
  auto G4() const { return BreitWignerReichMooreLValueBase::column( 5 ); }

  /**
   *  @brief Return the resonances
   */
  auto resonances() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::chunk(6);
  }

public:

  /* get methods */

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double AWRI() const { return ListRecord::C1(); }

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double atomicWeightRatio() const { return this->AWRI(); }

  using ListRecord::C2;

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int L() const { return ListRecord::L1(); }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int orbitalMomentum() const { return this->L(); }

  using ListRecord::L2;

  /**
   *  @brief Return the number of resonances for this l value
   */
  int NRS() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of resonances for this l value
   */
  int numberResonances() const { return this->NRS(); }

  /**
   *  @brief Return the resonance energies
   */
  auto ER() const { return BreitWignerReichMooreLValueBase::column( 0 ); }

  /**
  *  @brief Return the resonance energies
   */
  auto resonanceEnergies() const { return this->ER(); }

  /**
   *  @brief Return the spin values
   */
  auto AJ() const { return BreitWignerReichMooreLValueBase::column( 1 ); }

  /**
  *  @brief Return the spin values
   */
  auto spinValues() const { return this->AJ(); }

  using ListRecord::NC;
  using ListRecord::print;
};
