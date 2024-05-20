/**
 *  @brief Return the descriptive data
 */
auto description() const {

  std::string description;
  for ( auto&& record : this->description_ ) {

    description += record.text();
    description += '\n';
  }
  return description;
}
