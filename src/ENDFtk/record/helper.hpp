namespace helper{

// TODO: change this to template function to avoid defaults
template< int position > constexpr const char* symbol = "";
template< > constexpr const char* symbol< 0 > = "MAT";
template< > constexpr const char* symbol< 1 > = "MF";
template< > constexpr const char* symbol< 2 > = "MT";

template< int position > constexpr const char* name = "";
template< > constexpr const char* name< 0 > = "material";
template< > constexpr const char* name< 1 > = "file";
template< > constexpr const char* name< 2 > = "section";

template< int w >
const std::string defaultString = defaultString< w - 1 > + " ";

template<>
const std::string defaultString< 0 > = "";

template< int entry >
constexpr int sum(){ return entry; }

template< int entry1, int entry2, int... entries >
constexpr int sum(){ return entry1 + sum< entry2, entries... >(); }

}
