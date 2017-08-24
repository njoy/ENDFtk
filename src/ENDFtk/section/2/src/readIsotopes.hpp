template< typename Iterator >
std::vector< resonanceParameters::Isotope > readIsotopes ( HEAD& head,
                                      Iterator& begin, 
                                      const Iterator& end, 
                                      long& lineNumber ){

  std::vector< resonanceParameters::Isotope > isotopes;

  auto NIS = head.N1();
  if( NIS < 1 ){
    Log::error( "NIS (number of isotopes) must be > 0" );
    throw std::exception();
  }
  else{
    isotopes.reserve( NIS );
  }

  while( NIS-- ){
    isotopes.emplace_back( begin, end, lineNumber, head.MAT(), 2, head.MT() );
  }

  return isotopes;
}
