/**
 *  @brief Return the descriptive data
 */
std::string description() const {

  std::ostringstream description;
  for ( const auto& record : this->description_ ) {

    description << record.text() << '\n';
  }
  return description.str();
}
