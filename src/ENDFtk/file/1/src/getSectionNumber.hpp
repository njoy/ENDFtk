static auto getSectionNumber( const SectionVariant& section ) {

  return std::visit( [] ( const auto& value )
                        { return value.MT(); },
                     section );
}
