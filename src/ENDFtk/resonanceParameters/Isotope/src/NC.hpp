long NC() const {

  long NC = 1;
  for ( const auto& entry : this->ranges ) {

    std::visit( [&] ( const auto& v ) -> void
                    { NC += v.NC(); },
                entry );
  }
  return NC;
} 

