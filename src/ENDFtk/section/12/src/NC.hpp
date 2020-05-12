/**
 *  @brief Return the number of lines in this MF12 section
 */
long NC() const {
  long NC = 1
          + std::visit( [&] ( const auto& v )
                            { return v.NC(); }, this->photon_ );
  return NC;
};
