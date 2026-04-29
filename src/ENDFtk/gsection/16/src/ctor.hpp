/**
 *  @brief Constructor from parameters with probabilities (Note: IG = 0)
 *
 *  @param[in]  mt              the section number
 *  @param[in]  zaid            the ZAID identifier
 *  @param[in]  awr             the atomic weight ratio
 *  @param[in]  lr              the break-up identifier flag
 *  @param[in]  ngn             the number of neutron energy groups
 *  @param[in]  temp            the temperature
 *  @param[in]  groups          the group index
 *  @param[in]  flux            the group-wise flux
 *  @param[in]  matrix          the transfer matrices
 */
GType( int mt, int zaid, double awr, int lr, int ngn, double temp,
       std::vector < std::vector< std::vector< double > > > flux,
       std::vector < std::vector< std::vector< std::vector< double > > > > matrix ) :
    Base(zaid, awr, mt),
    lr_(lr),
    ngn_(ngn),
    temp_(temp),
    flux_( std::move(flux) ),
    matrix_( std::move(matrix ) ) {

  verifySize( this->flux_, this->matrix_ );
}

private:

  GType( int mt, int zaid, double awr, int lr, int ngn,
         std::tuple< double,
                     std::vector< std::vector< std::vector< double > > >,
                     std::vector< std::vector< std::vector< std::vector< double > > > > >&& data ) :
      GType( mt, zaid, awr, lr, ngn,
             std::move( std::get<0>( data ) ),        // temp
             std::move( std::get<1>( data ) ),        // flux
             std::move( std::get<2>( data ) ) ) {}    // matrix

  GType( int mt, int zaid, double awr, int nl, int nz,  int lr, int ngn,
         std::tuple< std::vector< DataRecord >, int >&& record_data ) :
      GType( mt, zaid, awr, lr, ngn,
             makeMatrices( std::move( std::get<0>( record_data ) ), nl, nz, ngn,
                           std::move( std::get<1>( record_data ) ) ) ) {}

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
  try : GType( head.MT(), head.ZA(), head.AWR(), head.L1(),
               head.L2(), head.N1(), head.N2(),
               readRecords( begin, end, lineNumber, head.MAT(), head.MF(),
                            head.MT(), head.N2() ) ) {

          this->readSEND(begin, end, lineNumber, MAT, head.MF());
        }
  catch( std::exception& e ) {

    Log::info( "Encountered error while reading section {} of file {} fo material {}"
               " in GENDF file.", head.MT(), head.MF(), head.MAT() );
    throw e;
  }