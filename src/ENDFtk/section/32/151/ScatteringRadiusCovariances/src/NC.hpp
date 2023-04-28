/**
 *  @brief Return the number of lines in this MF32 subsubsection
 */
long NC() const {

  long NC = 1;
  for ( auto& ni : this->ni_ ) {

    std::visit( [&] ( const auto& v ) -> void
                    { NC += v.NC(); },
                ni );
  }
  return NC;
}
