private:

/**
 *  @brief Intermediate private constructor
 */
GType( int zaid, double awr, int nz, ListRecord&& list ) :
    BaseWithoutMT(zaid, awr),
    nz_( nz ),
    parameters_( std::move( list ) ) {}

/**
 *  @brief Intermediate private constructor
 */
GType( int zaid, double awr, std::size_t nz, double temp,
       std::vector< double >&& sigz,
       std::vector< double >&& egn,
       std::vector< double >&& egg ) :
    GType( zaid, awr, nz,
           makeParameters( temp, std::move( sigz ),
                           std::move( egn ), std::move( egg ) ) ) {}

public:

/**
 *  @brief Constructor
 *  @param[in] zaid   the ZA value of the material
 *  @param[in] awr    the atomic weight ratio
 *  @param[in] temp   the temperature evaluated
 *  @param[in] sigz   the dilution values
 *  @param[in] egn    the neutron group structure
 *  @param[in] egg    the photon group structure
 */
GType( int zaid, double awr, double temp,
       std::vector< double > sigz,
       std::vector< double > egn,
       std::vector< double > egg ) :
  GType( zaid, awr, sigz.size(), temp,
         std::move( sigz ), std::move( egn ), std::move( egg ) ) {}

/**
 *  @brief Constructor (from buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] head         the head record of the section
 *  @param[in] begin        the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 */
template< typename Iterator >
GType( HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try : GType( head.ZA(), head.AWR(), head.L2(),
               ListRecord( begin, end, lineNumber, MAT, 1, 451 ) ) {

    readFendOrSend(begin, end, lineNumber, MAT, 1 );
  }
  catch( std::exception& e ) {

    Log::info( "Trouble reading gsection 451 of File 1 of Material {}", MAT );
    Log::info( "lineNumber: {}", lineNumber );
    throw e;
  }
