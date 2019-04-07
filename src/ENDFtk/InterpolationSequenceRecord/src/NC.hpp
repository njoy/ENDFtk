auto NC() const {
  auto NC = this->interpolation_.NC();
  for ( const auto& entry : this->sequence_ ) { NC += entry.NC(); }
  return NC;
};

