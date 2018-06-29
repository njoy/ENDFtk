/** 
 *  @brief Return the number of lines in this MF7/MT2 section
 */
long NC() const {
  long NC = 1;
  std::visit( [&] ( const auto& v ) -> void
                  { NC += v.NC(); },
              this->law_ );
  return NC;
};

