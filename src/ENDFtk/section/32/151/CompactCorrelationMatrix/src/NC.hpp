/**
 *  @brief Return the number of lines in this MF32 MT151 component
 */
long NC() const {

  return 1 + this->compact().size();
};
