template< typename Range >
auto makeTape( Range&& range ){
  return Tape< Range >{ std::forward< Range >( range ) };
}
