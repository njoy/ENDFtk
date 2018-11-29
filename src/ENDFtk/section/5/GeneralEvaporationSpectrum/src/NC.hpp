/** 
 *  @brief Return the number of lines in this MF5 component
 */
long NC() const {
  return this->temperature_.NC() + this->distribution_.NC();
};
