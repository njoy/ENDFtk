/**
 *  @brief Return the descriptive data
 */
auto description() const {

  return
    ranges::view::concat
      ( this->description_
          | ranges::view::transform
            ( []( const auto& textRecord )->decltype(auto)
            { return textRecord.text(); } )
          | ranges::view::join( '\n' ),
        ranges::view::single( '\n' ) );
}
