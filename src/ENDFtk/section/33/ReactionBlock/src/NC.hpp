long NC() const {

  long result = 1;

  // NC subsubsections
  for ( auto& nc : this->nc_ ) {
    std::visit( [&] ( const auto& v ) -> void
                    { result += v.NC(); },
                nc );
  }

  // NI subsubsections
  for ( auto& ni : this->ni_ ) {
    std::visit( [&] ( const auto& v ) -> void
                    { result += v.NC(); },
                ni );
  }

  return result;

}
