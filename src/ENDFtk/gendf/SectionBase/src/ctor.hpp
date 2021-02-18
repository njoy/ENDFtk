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
  SectionBase( double ZA, double AWR, int MT,
               int NL, int NZ, int LRFLAG, int NGN,
               std::vector< DataRecord > records ) :
    SectionBase( ZA, AWR, MT, NL, NZ, LRFLAG, NGN,
                 mapRecords(records) ) {}  

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
