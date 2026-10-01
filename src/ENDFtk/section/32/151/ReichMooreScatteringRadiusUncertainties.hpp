/**
 *  @class
 *  @brief The l-dependent uncertainties on the scattering radius for the
 *         Reich-Moore formalism
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ReichMooreScatteringRadiusUncertainties :
  protected ListRecord {

  /* auxiliary functions */

  static std::vector< double >
  generateList( double dap, std::vector< double >&& uncertainties ) {

    std::vector< double > list( 1, dap );
    list.reserve( 1 + uncertainties.size() );
    list.insert( list.end(), uncertainties.begin(), uncertainties.end() );
    return list;
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  ReichMooreScatteringRadiusUncertainties( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] dap              the default uncertainty
   *  @param[in] uncertainties    the l-dependent uncertainties
   */
  ReichMooreScatteringRadiusUncertainties( double dap,
                                           std::vector< double >&& uncertainties ) :
    // no try ... catch: exceptions will be handled in the derived class
    ReichMooreScatteringRadiusUncertainties(
        ListRecord( 0., 0., 0, 0, 0,
                    generateList( dap, std::move( uncertainties ) ) ) ) {}

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
  ReichMooreScatteringRadiusUncertainties( Iterator& it, const Iterator& end, long& lineNumber,
                     int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
    ReichMooreScatteringRadiusUncertainties(
        ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}

  /* get methods */

  /**
   *  @brief Return the default scattering radius uncertainty
   */
  double DAP() const { return ListRecord::list()[0]; }

  /**
   *  @brief Return the default scattering radius uncertainty
   */
  double defaultUncertainty() const { return this->DAP(); }

  /**
   *  @brief Return the l-dependent uncertainties
   */
  auto DAPL() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 1 );
  }

  /**
   *  @brief Return the l-dependent uncertainties
   */
  auto uncertainties() const { return this->DAPL(); }


  using ListRecord::NC;
  using ListRecord::print;
};
