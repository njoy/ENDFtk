private:

/**
 *  @brief Private constructor
 */
ThermalScatteringData( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {}

public:

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
