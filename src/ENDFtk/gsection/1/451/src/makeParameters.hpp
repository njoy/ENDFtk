static auto
makeParameters( double temp,  std::vector< double > sigz,
                std::vector< double > egn, std::vector< double > egg ) {

  std::vector< double > data = {};
  data.reserve( sigz.size() + egn.size() + egg.size() );

  auto ngn = egn.size() - 1;
  auto ngg = egg.size() - 1;

  data.insert( data.end(), sigz.begin(), sigz.end() );
  data.insert( data.end(), egn.begin(), egn.end() );
  data.insert( data.end(), egg.begin(), egg.end() );
  return ListRecord( temp, 0, ngn, ngg, 0, std::move( data ) );
}

static auto
makeParameters( double temp, std::vector< double > egn ) {

  return ListRecord( temp, 0, egn.size() - 1, 0, 0, std::move( egn ) );
}