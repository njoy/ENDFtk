/** 
 *  @brief Return the number of lines in this MF5 component
 */
long NC() const {

  return this->parameters_[0].NC() + this->parameters_[1].NC();
};
