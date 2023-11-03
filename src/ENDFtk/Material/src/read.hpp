template< typename Iterator >
static auto
read( StructureDivision& division,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber ) {

  std::vector< FileVariant > files;
  while ( not division.isMend() ) {

    switch ( division.tail.MF() ) {

      case  1 : { files.emplace_back( file::Type<  1 >( division, begin, end, lineNumber ) ); break; }
      case  2 : { files.emplace_back( file::Type<  2 >( division, begin, end, lineNumber ) ); break; }
      case  3 : { files.emplace_back( file::Type<  3 >( division, begin, end, lineNumber ) ); break; }
      case  4 : { files.emplace_back( file::Type<  4 >( division, begin, end, lineNumber ) ); break; }
      case  5 : { files.emplace_back( file::Type<  5 >( division, begin, end, lineNumber ) ); break; }
      case  6 : { files.emplace_back( file::Type<  6 >( division, begin, end, lineNumber ) ); break; }
      case  7 : { files.emplace_back( file::Type<  7 >( division, begin, end, lineNumber ) ); break; }
      case  8 : { files.emplace_back( file::Type<  8 >( division, begin, end, lineNumber ) ); break; }
      case  9 : { files.emplace_back( file::Type<  9 >( division, begin, end, lineNumber ) ); break; }
      case 10 : { files.emplace_back( file::Type< 10 >( division, begin, end, lineNumber ) ); break; }
      case 12 : { files.emplace_back( file::Type< 12 >( division, begin, end, lineNumber ) ); break; }
      case 13 : { files.emplace_back( file::Type< 13 >( division, begin, end, lineNumber ) ); break; }
      case 14 : { files.emplace_back( file::Type< 14 >( division, begin, end, lineNumber ) ); break; }
      case 15 : { files.emplace_back( file::Type< 15 >( division, begin, end, lineNumber ) ); break; }
      case 23 : { files.emplace_back( file::Type< 23 >( division, begin, end, lineNumber ) ); break; }
      case 26 : { files.emplace_back( file::Type< 26 >( division, begin, end, lineNumber ) ); break; }
      case 27 : { files.emplace_back( file::Type< 27 >( division, begin, end, lineNumber ) ); break; }
      case 28 : { files.emplace_back( file::Type< 28 >( division, begin, end, lineNumber ) ); break; }
      case 32 : { files.emplace_back( file::Type< 32 >( division, begin, end, lineNumber ) ); break; }
      case 33 : { files.emplace_back( file::Type< 33 >( division, begin, end, lineNumber ) ); break; }
      case 34 : { files.emplace_back( file::Type< 34 >( division, begin, end, lineNumber ) ); break; }
      default : {

        int MF = division.tail.MF();
        Log::info( "Found unsupported file MF{} - skipping file", MF );

        Tail tail( division.tail.MAT(), division.tail.MF(), division.tail.MT() );
        while ( tail.MF() == MF ) {

          Text( begin, end );
          tail = Tail( begin, end, lineNumber );
        }

        //! @todo once all files are implemented remove the previous code and throw
        // throw std::exception();
      }
    }
    division = StructureDivision( begin, end, lineNumber );
  }
  verifyMEND( division, lineNumber );
  return std::move( files );
}
