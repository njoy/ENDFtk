protected:

  SectionBase( double za, double awr, int mt,
               int nl, int nz, int lr, int ng,
               std::map< unsigned int, DataRecord >&& records ) :
    Base( za, awr, mt ),
    num_legendre_(nl),
    num_dilutions_(nz),
    breakup_(lr),
    num_groups_(ng),
    records_(records) {

    verifyRecords();
}

public:

  /**
   *  @brief Constructor from parameters
   *
   *  @param[in] za         the ZAID identifier
   *  @param[in] awr        the atomic weight ratio
   *  @param[in] mt         the section number
   *  @param[in] nl         the number of Legendre moments (order+1)
   *  @param[in] nz         the number of dilutions (sigma-zeros)
   *  @param[in] lr         the complex breakup flag
   *  @param[in] ng         the number of groups
   *  @param[in] records    the data records
   */
  SectionBase( double za, double awr, int mt,
               int nl, int nz, int lr, int ng,
               std::vector< DataRecord >&& records ) :
    SectionBase( za, awr, mt, nl, nz, lr, ng,
                 std::move( mapRecords( std::move( records ) ) ) ) {}

  /**
   *  @brief Constructor from buffer
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] head         the head record of the section
   *  @param[in] begin        the iterator for begin
   *  @param[in] end          the iterator for end
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   */
  template< typename Iterator >
  SectionBase( const HEAD& head,
               Iterator& begin,
               const Iterator& end,
               long& lineNumber,
               int MAT )
  try: SectionBase( head.ZA(), head.atomicWeightRatio(), head.MT(),
                    head.L1(), head.L2(), head.N1(), head.N2(),
                    readRecords( begin, end, MAT, head.MF(),
                                 head.MT(), head.N2() ) ) {

    this->readSEND( begin, end, lineNumber, head.MAT(), head.MF() );
  }
  catch( std::exception& e ) {
    Log::info( "Encountered error while reading section {} of file {} of "
               "material {} in GENDF file.",
               head.MT(), head.MF(), head.MAT() );
    throw e;
  }
