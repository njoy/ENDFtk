/** 
 *  @brief Return the number of lines in this MF4 section
 */
long NC() const {

  return 2 + std::visit( [&] ( const auto& v ) { return v.NC(); },
                         this->distributions_ );
};
