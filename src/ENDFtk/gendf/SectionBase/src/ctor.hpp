protected:

  SectionBase( double ZA, double AWR, int MT,
               int NL, int NZ, int LRFLAG, int NGN,
               std::map< unsigned int, DataRecord > records ) :
    Base( ZA, AWR, MT ),
    num_legendre_(NL),
    num_dilutions_(NZ),
    breakup_(LRFLAG),
    num_groups_(NGN),
    records_(records) {

    verifyRecords();
}

public:
  
  /**
   *  @brief Constructor from parameters
   *
   *  @param[in] ZA         the ZAID identifier
   *  @param[in] AWR        the atomic weight ratio
   *  @param[in] MT         the section number
   *  @param[in] NL         the number of Legendre moments (order+1)
   *  @param[in] NZ         the number of dilutions (sigma-zeros)
   *  @param[in] LRFLAG     the complex breakup flag
   *  @param[in] NGN        the number of groups
   *  @param[in] records    the data records
   */
  SectionBase( double ZA, double AWR, int MT,
               int NL, int NZ, int LRFLAG, int NGN,
               std::vector< DataRecord > records ) :
    SectionBase( ZA, AWR, MT, NL, NZ, LRFLAG, NGN,
                 mapRecords(records) ) {}

  /**
   *  @brief Constructor from buffer
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] head         the head record of the section
   *  @param[in] begin        the iterator for begin
   *  @param[in] end          the iterator for end
   */
  template< typename Iterator >
  SectionBase( const HEAD& head,
               Iterator& begin,
               const Iterator& end )
  try: SectionBase( head.ZA(), head.atomicWeightRatio(), head.MT(),
                    head.L1(), head.L2(), head.N1(), head.N2(),
                    readRecords( begin, end, head.MAT(), head.MF(),
                               head.MT(), head.N2() ) ) {

    long lineNumber = 0;
    this->readSEND( begin, end, lineNumber, head.MAT(), head.MF() );
  }
  catch( std::exception& e ) {
    Log::info( "Encountered error while reading section {} of file {} of "
               "material {} in GENDF file.",
               head.MT(), head.MF(), head.MAT() );
    throw e;
  }
