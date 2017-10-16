template< typename Iterator >
auto readSubsections( Iterator& begin, 
                      const Iterator& end, 
                      long& lineNumber, 
                      int MAT, int MT, int NK ){
  std::vector< Subsection > SSs;
  SSs.reserve( NK );

  while( NK != 0 ){
    SSs.push_back( Subsection( begin, end, lineNumber, MAT, MT ) );
    --NK;
  }

  return SSs;
}
