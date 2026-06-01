/**
 *  @brief Constructor for angular covariance matrix
 * 
 *  @param[in] mt           the section number
 *  @param[in] zaid         the ZAID identifier
 *  @param[in] awr          the atomic weight ratio
 *  @param[in] irelco       the covariance format
 *  @param[in] l            the legendre order
 *  @param[in] l1           the second legendre order
 *  @param[in] ngn          the number of neutron groups
 *  @param[in] ang_covr     the angular covariance matrix
 */
GType( int mt, int zaid, double awr, int irelco, int l, int l1, int ngn,
       std::vector< std::vector< double > > ang_covr ) : 
    Base( zaid, awr, mt ),
    l_( l ),
    l1_( l1 ),
    irelco_( irelco ),
    ngn_( ngn ),
    ang_covr_( std::move( ang_covr ) ) {}


private:

GType( int mt, int zaid, double awr, int irelco, int l, int l1, int ngn,
       std::vector< DataRecord >&& records ) :
    GType( mt, zaid, awr, irelco, l, l1, ngn,
           makeMatrices( records, ngn ) ) {}

GType( int mt, int zaid, double awr, int irelco, int l, int l1, 
       std::tuple< int, std::vector< DataRecord > >&& data ) :
    GType( mt, zaid, awr, irelco, l, l1,
           std::get<0>( data ),                     // ngn
           std::move( std::get<1>( data ) ) ) {}    // records

public:

/**
 *  @brief Constructor from buffer/string
 * 
 *  @tparam Iterator        buffer iterator
 * 
 *  @param[in] head         the head record of the section
 *  @param[in] begin        the start of the iterator
 *  @param[in] end          the end for the iterator
 *  @param[in] lineNumber   the current line number 
 *  @param[in] MAT          the expected MAT number
 */
template< typename Iterator >
GType( const HEAD&head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
    try:
        GType( head.MT(), head.ZA(), head.AWR(), head.L2(), head.N1(), head.N2(),
               readRecords(begin, end, lineNumber, head.MAT(), head.MF(),
                           head.MT() ) ) {
        this->readSEND(begin, end, lineNumber, MAT, head.MF() );
        }
        catch( std::exception& e ) {

            Log::info( "Encountered error while reading section {} of file {} for material {}"
                        " in GENDF file.", head.MT(), head.MF(), head.MAT());
            throw e;
        }