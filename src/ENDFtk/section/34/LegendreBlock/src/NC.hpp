/**
 *  @brief Return the number of lines in this MF34 subsubsection
 */
long NC() const {

  long result = 1;

  // NI subsubsections
  for ( auto& ni : this->ni_ ) {
    std::visit( [&] ( const auto& v ) -> void
                    { result += v.NC(); },
                ni );
  }

  return result;

}
