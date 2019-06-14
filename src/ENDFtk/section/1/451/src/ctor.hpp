Type( double zaid, double awr, int lrp, int lfi, int nlib, int nmod,
      std::array< ControlRecord, 3 >&& parameters,
      std::vector< TextRecord >&& description,
      std::vector< DirectoryRecord >&& index ) :
  BaseWithoutMT( zaid, awr ), lrp_( lrp ), lfi_( lfi ), nlib_( nlib ), nmod_( nmod ),
  parameters_( std::move( parameters ) ),
  description_( std::move( description ) ),
  index_( std::move( index ) ) {}

Type( double zaid, double awr, int lrp, int lfi, int nlib, int nmod,
      double elis, double sta, int lis, int liso, int nfor,
      double awi, double emax, int lrel, int nsub, int nver,
      double temp, int ldrv,
      const std::string& description,
      std::vector< DirectoryRecord >&& index ) :
  BaseWithoutMT( zaid, awr ), lrp_( lrp ), lfi_( lfi ), nlib_( nlib ), nmod_( nmod ),
  parameters_( makeParameters( elis, sta, lis, liso, nfor,
                               awi, emax, lrel, nsub, nver,
                               temp, ldrv, 
                               ranges::distance(
                                   ranges::view::split( description, '\n' ) ),
                               index.size() ) ),
  description_( makeDescription( description ) ),
  index_( std::move( index ) ) {}

template< typename Iterator >
Type ( HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try:
    BaseWithoutMT( head, MAT, 1 ), lrp_( head.L1() ), lfi_( head.L2() ),
    nlib_( head.N1() ), nmod_( head.N2() ),
    parameters_( readParameters( begin, end, lineNumber, MAT ) ),
    description_( readRecords< TextRecord >( begin,
                                             end,
                                             lineNumber,
                                             MAT,
                                             this->parameters_[2].N1() ) ),
    index_( readRecords< DirectoryRecord >( begin,
                                            end,
                                            lineNumber,
                                            MAT,
                                            this->parameters_[2].N2() ) ) {
    readSEND(begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section 451 of File 1 of Material {}",
               MAT );
    Log::info( "lineNumber: {}", lineNumber );
    throw e;
  }

