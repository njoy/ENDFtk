/**
 *  @class
 *  @brief The resonance parameters for a given l value in the unresolved
 *         resonance covariance data.
 *
 *  See ENDF102, section 32.2.4 for more information.
 */
class LValue : protected ListRecord {

  /* auxiliary functions */

  static void
  verifySize( int NPL, int NJS ) {

    if ( NPL != 6 * NJS ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to 6 * NJS" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NJS value: {}", NJS );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< double >&& spins,
                std::vector< double >&& d,
                std::vector< double >&& gno,
                std::vector< double >&& gg,
                std::vector< double >&& gf,
                std::vector< double >&& gx ) {

    std::vector< double > list;
    unsigned int njs = spins.size();
    if ( ( d.size() != njs ) or ( gno.size() != njs ) or ( gg.size() != njs ) or
         ( gf.size() != njs ) or ( gx.size() != njs ) ) {

      Log::info( "The number of spin values and the resonance parameters are not "
                 "consistent" );
      Log::info( "NJS value: {}", njs );
      Log::info( "spins.size(): {}", spins.size() );
      Log::info( "d.size(): {}", d.size() );
      Log::info( "gno.size(): {}", gno.size() );
      Log::info( "gg.size(): {}", gg.size() );
      Log::info( "gf.size(): {}", gf.size() );
      Log::info( "gx.size(): {}", gx.size() );
      throw std::exception();
    }

    for ( unsigned int i = 0; i < njs; ++i ) {

      list.push_back( d[i] );
      list.push_back( spins[i] );
      list.push_back( gno[i] );
      list.push_back( gg[i] );
      list.push_back( gf[i] );
      list.push_back( gx[i] );
    }
    return list;
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  LValue( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySize( this->NPL(), this->N2() );
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] awri       the atomic weight ratio
   *  @param[in] l          the orbital angular momentum value
   *  @param[in] spins      the spin values (NJS values)
   *  @param[in] spacing    the level spacing values (NJS values)
   *  @param[in] gno        the average neutron widths (NJS values)
   *  @param[in] gg         the average gamma widths (NJS values)
   *  @param[in] gf         the average fission widths (NJS values)
   *  @param[in] gx         the average competitive widths (NJS values)
   */
  LValue( double awri, int l,
          std::vector< double >&& spins,
          std::vector< double >&& spacing,
          std::vector< double >&& gno,
          std::vector< double >&& gg,
          std::vector< double >&& gf,
          std::vector< double >&& gx )
    try :  LValue( ListRecord( awri, 0.0, l, 0.0, spins.size(),
                               generateList( std::move( spins ),
                                             std::move( spacing ),
                                             std::move( gno ),
                                             std::move( gg ),
                                             std::move( gf ),
                                             std::move( gx ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing l value resonance "
                 "parameters for unresolved resonance covariance data" );
      throw;
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
  LValue( Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT )
    try : LValue( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing l value resonance "
                 "parameters for unresolved resonance covariance data" );
      throw;
    }

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

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int L() const { return ListRecord::L1(); }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int orbitalMomentum() const { return this->L(); }

  /**
   *  @brief Return the number of J values for this l value
   */
  int NJS() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of J values for this l value
   */
  int numberSpinValues() const { return this->NJS(); }

  /**
   *  @brief Return the data for each of the J values
   */
  auto jValues() const {

    using namespace njoy::tools;
    auto chunked = ListRecord::list() | std23::views::chunk( 6 );
    using Range = decltype( chunked[0] );
    return chunked | std20::views::transform(
                       [] ( Range&& chunk ) -> JValue< Range >
                          { return { std::move( chunk ) }; } );
  }

  /**
   *  @brief Return the average level spacing values
   */
  auto D() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.D(); } );
  }

  /**
   *  @brief Return the average level spacing values
   */
  auto averageLevelSpacings() const { return this->D(); }

  /**
   *  @brief Return the spin values
   */
  auto AJ() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.AJ(); } );
  }

  /**
  *  @brief Return the spin values
   */
  auto spinValues() const { return this->AJ(); }

  /**
   *  @brief Return the average neutron width values.
   */
  auto GNO() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.GNO(); } );
  }

  /**
   *  @brief Return the average neutron width values.
   */
  auto averageNeutronWidths() const { return this->GNO(); }

  /**
   *  @brief Return the average gamma width values.
   */
  auto GG() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.GG(); } );
  }

  /**
   *  @brief Return the average gamma width values.
   */
  auto averageGammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the average fission width values.
   */
  auto GF() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.GF(); } );
  }

  /**
   *  @brief Return the average fission width values.
   */
  auto averageFissionWidths() const { return this->GF(); }

  /**
   *  @brief Return the average competitive width values.
   */
  auto GX() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.GX(); } );
  }

  /**
   *  @brief Return the average competitive width values.
   */
  auto averageCompetitiveWidths() const { return this->GX(); }

  using ListRecord::NC;
  using ListRecord::print;
};
