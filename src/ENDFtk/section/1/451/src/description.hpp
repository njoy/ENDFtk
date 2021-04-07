/**
 *  @brief Return the descriptive data
 */
auto description() const {

  return
    ranges::views::concat
      ( this->description_
          | ranges::views::transform
            ( []( const auto& textRecord )->decltype(auto)
            { return textRecord.text(); } )
          | ranges::views::join( '\n' ),
        ranges::cpp20::views::single( '\n' ) );
}
