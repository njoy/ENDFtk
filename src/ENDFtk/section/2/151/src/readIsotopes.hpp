template< typename Iterator >
std::vector< resonanceParameters::Isotope >
readIsotopes( const HEAD& head,
              Iterator& begin,
              const Iterator& end,
              long& lineNumber ){

  std::vector< resonanceParameters::Isotope > isotopes;

  auto NIS = head.N1();
  isotopes.reserve( NIS );

  while( NIS-- ) {

    isotopes.emplace_back( begin, end, lineNumber, head.MAT(), 2, head.MT() );
  }

  return isotopes;
}
