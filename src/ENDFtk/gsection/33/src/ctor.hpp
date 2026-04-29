/**
 *  @brief Constructor for covariance matrices
 *
 *  @param[in] mt           the section number
 *  @param[in] zaid         the ZAID identifier
 *  @param[in] awr          the atomic weight ratio
 *  @param[in] lr           the break-up identifier flag
 *  @param[in] ngn          the number of neutron groups
 *  @param[in] covr         the covariance matrices
 */
GType( int mt, int zaid, double awr, int lr, int ngn,
       std::map< std::size_t, std::vector< std::vector< double > > > covr ) :
    Base( zaid, awr, mt ),
    lr_( lr ),
    ngn_( ngn ),
    covariances_( std::move( covr ) ) {

  this->generateReactions();
}

private:

GType( int mt, int zaid, double awr, int lr, int ngn,
       std::vector< std::pair< std::size_t, std::vector< DataRecord > > >&& records ) :
    GType( mt, zaid, awr, lr, ngn,
           makeMatrices( records, ngn ) ) {}

GType( int mt, int zaid, double awr, int lr, std::tuple< int,
       std::vector< std::pair< std::size_t, std::vector< DataRecord > > > >&& data ) :
    GType( mt, zaid, awr, lr,
           std::get<0>( data ),                     // ngn
           std::move( std::get<1>( data ) ) ) {}    // records

public:

/**
 *  @brief Constructor from buffer/string
 *
 *  @tparam Iterator        buffer iterator
 *
 *  @param[in] head         the head record of the section
 *  @param[in] begin        the start for the iterator
 *  @param[in] end          the end for the iterator
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 */
template< typename Iterator >
GType( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
    try:
        GType( head.MT(), head.ZA(), head.AWR(), head.N1(),
               readRecords( begin, end, lineNumber, head.MAT(), head.MF(),
                            head.MT(), head.N2() ) ) {
        this->readSEND(begin, end, lineNumber, MAT, head.MF() );
    }
    catch( std::exception& e ) {

        Log::info( "Encountered error while reading section {} of file {} for material {}"
                   " in GENDF file.", head.MT(), head.MF(), head.MAT());
        throw e;
    }
