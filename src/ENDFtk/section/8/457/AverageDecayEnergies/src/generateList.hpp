static std::vector< double >
generateList( std::vector< std::array< double, 2 > >&& energies ) {

  return ranges::to< std::vector< double > >(
             ranges::cpp20::views::join( energies  ) );
}
