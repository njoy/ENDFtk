/**
 *  @class
 *  @brief Internal NJOY thermal scattering data (LAW=1, LANG=3)
 *
 *  The ThermalScatteringData class is used to represent an internal NJOY ENDF
 *  format for thermal scattering data. It is stored in MF6.
 *
 *  See NJOY2016 manual, section 7.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT ThermalScatteringData : protected ListRecord {

  /* auxiliary functions */

  static std::vector< double >
  generateList( double energy, std::vector< double >&& cosines ) {

    std::vector< double > list = { energy, 1. };
    list.insert( list.end(), cosines.begin(), cosines.end() );
    return list;
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  ThermalScatteringData( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ThermalScatteringData() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] energy   the incident energy
   *  @param[in] n2       the value for n2 (nl+1 or nu+2)
   *  @param[in] data     the data that goes into this component
   */
  ThermalScatteringData( double energy, int n2,
                         std::vector< double >&& data ) :
    ListRecord( 0., energy, 0, 0, n2, std::move( data ) ) {}

  /**
   *  @brief Constructor for LTT = 6
   *
   *  @param[in] energy    the incident energy
   *  @param[in] cosines   the equally probable cosine values
   */
  ThermalScatteringData( double energy, std::vector< double >&& cosines ) :
    ListRecord( 0., energy, 0, 0, cosines.size() + 2,
                generateList( energy, std::move( cosines ) ) ) {}

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] head         the head record of the section
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   */
  template< typename Iterator >
  ThermalScatteringData( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT )
    try : ThermalScatteringData( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading thermal scattering data "
                 "data (LAW=1 LANG=3)" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the LANG value
   */
  static constexpr int LANG() { return 3; }

  /**
   *  @brief Return the representation type
   */
  int representation() const { return this->LANG(); }

  /**
   *  @brief Return the incident energy
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the data contained in this component
   */
  auto data() const { return ListRecord::list(); }

  /**
   *  @brief Return the data contained in this component
   */
  int NW() const { return ListRecord::NPL(); }

  using ListRecord::N2;

  /**
   *  @brief Return the number of energy points
   */
  int NEP() const { return this->NW() / this->N2(); }

  /**
   *  @brief Return the number of energy points
   */
  int numberSecondaryEnergies() const { return this->NEP(); }

  /**
   *  @brief Return the LTT flag (the format representation type)
   */
  int LTT() const { return this->data().front() == this->incidentEnergy() ? 6 : 5; }

  /**
   *  @brief Return the number of energy points
   */
  auto EP() const {

    using namespace njoy::tools;
    return this->data() | std23::views::stride( this->N2() );
  }

  /**
   *  @brief Return the number of energy points
   */
  auto energies() const { return this->EP(); }

  /**
   *  @brief Return second value for every energy
   */
  auto PP() const {

    using namespace njoy::tools;
    return this->data() | std20::views::drop( 1 )
                        | std23::views::stride( this->N2() );
  }

  /**
   *  @brief Return the cosine values
   */
  auto MU() const {

    using namespace njoy::tools;
    return this->data()
             | std23::views::chunk( this->N2() )
             | std20::views::transform(
                   [] ( const auto& array )
                      { return array | std20::views::drop( 2 ); } );
  }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const { return this->MU();  }

  using ListRecord::NC;
  using ListRecord::print;
};
