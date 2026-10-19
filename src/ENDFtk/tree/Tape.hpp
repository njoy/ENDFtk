#ifndef NJOY_ENDFTK_TREE_TAPE
#define NJOY_ENDFTK_TREE_TAPE

// system includes
#include <vector>
#include <list>
#include <optional>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/TapeIdentification.hpp"
#include "ENDFtk/Tape.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "ENDFtk/tree/toMaterial.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @class
   *  @brief The ENDF tree tape to index and access ENDF data
   *
   *  This class is used to load an ENDF tape and index its content into
   *  the different ENDF tree components: materials, sections and files. This
   *  indexing operation performed at construction does not parse the underlying
   *  ENDF data. Once the tape is indexed, a user can request materials, files
   *  and sections to be parsed individually.
   *
   *  An ENDF tape starts with a tape identification (a label, which sometimes
   *  can contain a tape number).
   */
  class Tape {

    /* fields */

    std::optional< TapeIdentification > tpid_;
    std::list< Material > materials_;

    /* auxiliary function */

    /**
     *  @brief Return iterator to the file with the given mat number
     *
     *  @param[in] mat    the mat number
     */
    auto find( int mat ) {

      auto lower = std::lower_bound( this->materials_.begin(), this->materials_.end(), mat,
                                     [] ( auto&& left, auto&& right )
                                        { return left.materialNumber() < right; } );
      auto upper = std::upper_bound( this->materials_.begin(), this->materials_.end(), mat,
                                     [] ( auto&& left, auto&& right )
                                        { return left < right.materialNumber(); } );

      if ( lower != upper ) {

        return std::make_pair( lower, upper );
      }
      return std::make_pair( this->materials_.end(), this->materials_.end() );
    }

    /**
     *  @brief Return iterator to the file with the given mat number
     *
     *  @param[in] mat    the mat number
     */
    auto find( int mat ) const {

      auto lower = std::lower_bound( this->materials_.begin(), this->materials_.end(), mat,
                                     [] ( auto&& left, auto&& right )
                                        { return left.materialNumber() < right; } );
      auto upper = std::upper_bound( this->materials_.begin(), this->materials_.end(), mat,
                                     [] ( auto&& left, auto&& right )
                                        { return left < right.materialNumber(); } );

      if ( lower != upper ) {

        return std::make_pair( lower, upper );
      }
      return std::make_pair( this->materials_.end(), this->materials_.end() );
    }

    template < typename BufferIterator >
    static auto
    fill( BufferIterator position, const BufferIterator& end, long& lineNumber ) {

      std::list< Material > materials;

      auto compare = [] ( auto&& left, auto&& right )
                        { return left < right.materialNumber(); };

      auto begin = position;
      auto division = StructureDivision( position, end, lineNumber );

      while ( division.isHead() ) {

        auto iter = std::upper_bound( materials.begin(), materials.end(), division.tail.MAT(), compare );

        materials.emplace( iter, asHead( division ), begin, position, end, lineNumber );

        begin = position;
        division = StructureDivision( position, end, lineNumber );

        while ( division.isMend() ) {

          begin = position;
          division = StructureDivision( position, end, lineNumber );
          if ( position >= end ) {

            break;
          }
        }
      }

      if ( not division.isTend() ) {

        Log::error( "Did not find a valid TEND record in the tape" );
        throw std::exception();
      }

      return materials;
    }

    template < typename BufferIterator >
    static auto
    fill( BufferIterator position, const BufferIterator& end ){

      long lineNumber{ 0 };
      return fill( position, end, lineNumber );
    }

  public:

    /* constructor */

    /**
     *  @brief Empty tape constructor
     *
     *  @param[in] id    the tape identifier
     */
    Tape( TapeIdentification&& id ) : tpid_( std::move( id ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] buffer       the buffer from which a buffer can be constructed
     *  @param[in] lineNumber   the line numbers
     */
    template< typename Buffer >
    Tape( const Buffer& buffer, long lineNumber = 0 )
      try {

        using namespace njoy::tools;
        auto position = std20::begin( buffer );
        auto end = std20::end( buffer );
        this->tpid_ = TapeIdentification{ position, end, lineNumber };
        materials_ = fill( position, end, lineNumber );
      }
      catch ( std::exception& e ) {

        Log::info( "Trouble encountered while constructing a tape syntax tree." );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the materials with the requested MAT number
     *
     *  This function returns a range of materials since a tape can contain
     *  multiple instances of the same material (e.g. at different
     *  temperatures).
     *
     *  @param[in]   mat   the MAT number of the material to be returned
     */
    auto material( int mat ) const {

      auto range = this->find( mat );
      if ( range.first ==  range.second ) {

        Log::error( "Requested material number (MAT) does not"
                    " correspond to a stored material syntax tree" );
        Log::info( "Requested material number: {}", mat );
        throw std::out_of_range( "Requested material number (MAT) does not"
                                 " correspond to a stored material tree" );
      }


      using namespace njoy::tools;
      auto subrange = std20::ranges::subrange( range.first, range.second );

      return subrange | std20::views::all;
    }

    /**
     *  @brief Return the materials with the requested MAT number
     *
     *  This function returns a range of materials since a tape can contain
     *  multiple instances of the same material (e.g. at different
     *  temperatures).
     *
     *  @param[in]   mat   the MAT number of the material to be returned
     */
    auto material( int mat ) {

      using namespace njoy::tools;
      return
        static_cast< const Tape& >( *this ).material( mat )
        | std20::views::transform
          ( [] ( const auto& material ) -> Material&
               { return const_cast< Material& >( material ); } );
    }

    /**
     *  @brief Return the materials with the requested MAT number
     *
     *  This function returns a range of materials since a tape can contain
     *  multiple instances of the same material (e.g. at different
     *  temperatures).
     *
     *  @param[in]   mat   the MAT number of the material to be returned
     */
    auto MAT( int mat ) { return this->material( mat ); }

    /**
     *  @brief Return the materials with the requested MAT number
     *
     *  This function returns a range of materials since a tape can contain
     *  multiple instances of the same material (e.g. at different
     *  temperatures).
     *
     *  @param[in]   mat   the MAT number of the material to be returned
     */
    auto MAT( int mat ) const { return this->material( mat ); }

    /**
     *  @brief Return the number of times a material with the given MAT
     *         number is present
     *
     *  @param[in]   mat   the MAT number of the material
     */
    int numberMAT( int mat ) const {

      auto range = this->find( mat );
      return std::distance( range.first, range.second );
    }

    /**
     *  @brief Return the number of times a material with the given MAT
     *         number is present
     *
     *  @param[in]   mat   the MAT number of the material
     */
    int numberMaterial( int mat ) const { return this->numberMAT( mat ); }

    /**
     *  @brief Return whether or not the tape has a material with the given MAT
     *         number
     *
     *  @param[in]   mat   the MAT number of the material
     */
    bool hasMAT( int mat ) const {

      auto range = this->find( mat );
      return range.first != range.second;
    }

    /**
     *  @brief Return whether or not the tape has a material with the given MAT
     *         number
     *
     *  @param[in]   mat   the MAT number of the material
     */
    bool hasMaterial( int mat ) const { return this->hasMAT( mat ); }

    /**
     *  @brief Return all materials in the tape
     */
    auto materials() {

      using namespace njoy::tools;
      return std20::views::all( this->materials_ );
    }

    /**
     *  @brief Return all materials in the tape
     */
    auto materials() const {

      using namespace njoy::tools;
      return std20::views::all( this->materials_ );
    }

    /**
     *  @brief Return a begin iterator to all materials
     */
    auto begin() { return this->materials().begin(); }

    /**
     *  @brief Return an end iterator to all materials
     */
    auto end() { return this->materials().end(); }

    /**
     *  @brief Return a begin iterator to all materials
     */
    auto begin() const { return this->materials().begin(); }

    /**
     *  @brief Return an end iterator to all materials
     */
    auto end() const { return this->materials().end(); }

    /**
     *  @brief Return the number of materials in the tape
     */
    std::size_t size() const { return this->materials_.size(); }

    /**
     *  @brief Return the tape's content
     */
    auto content() const {

      std::string content;
      if ( this->tpid_.has_value() ) {

        auto output = std::back_inserter( content );
        this->tpid_->print( output, 0, 0, 0 );
      }

      for ( const auto& material : this->materials() ) {

        content += material.content();
      }

      if ( content.size() ) {

        auto output = std::back_inserter( content );
        TEND().print( output );
      }

      return content;
    }

    /**
     *  @brief Return the tape identification (the first line in the file)
     */
    const TapeIdentification& TPID() const { return *( this->tpid_ ); }

    /**
     *  @brief Return all unique material numbers in the tape
     */
    std::vector< int > materialNumbers() const {

      using namespace njoy::tools;
      auto keys = this->materials_ | std20::views::transform(
                                         [] ( auto&& material )
                                            { return material.materialNumber(); } );
      std::vector< int > materials( keys.begin(), keys.end() );
      std::sort( materials.begin(), materials.end() );
      materials.erase( std::unique( materials.begin(), materials.end() ), materials.end() );
      return materials;
    }

    /**
     *  @brief Remove all materials with the given MAT number
     *
     *  @param[in]   mat   the mat number of the materials to be removed
     */
    void remove( int mat ) {

      auto range = this->find( mat );
      this->materials_.erase( range.first, range.second );
    }

    /**
     *  @brief Insert the material in the tape
     *
     *  This function inserts the material in the ENDF tape tree. If one or more
     *  materials are already present, the new material is inserted after the
     *  materials that are already there.
     *
     *  @param[in]   material   the material to be inserted
     */
    void insert( Material&& material ) {

      auto compare = [] ( auto&& left, auto&& right )
                        { return left < right.materialNumber(); };
      auto iter = std::upper_bound( this->materials_.begin(), this->materials_.end(),
                                    material.MAT(), compare );

      this->materials_.emplace( iter, std::move( material ) );
    }

    /**
     *  @brief Insert the material in the tape
     *
     *  This function inserts the material in the ENDF tape tree. If one or more
     *  materials are already present, the new material is inserted after the
     *  materials that are already there.
     *
     *  @param[in]   material   the material to be inserted
     */
    void insert( const njoy::ENDFtk::Material& material ) {

      this->insert( toMaterial( material ) );
    }

    /**
     *  @brief Insert or replace the material in the tape
     *
     *  This function inserts the material in the ENDF tape tree. If one or more
     *  materials are already present, the old materials are removed before inserting
     *  the new material.
     *
     *  @param[in]   material   the material to be inserted
     */
    void replace( Material&& material ) {

      this->remove( material.MAT() );
      auto compare = [] ( auto&& left, auto&& right )
                        { return left.materialNumber() < right; };
      auto lower = std::lower_bound( this->materials_.begin(), this->materials_.end(),
                                     material.materialNumber(), compare );

      this->materials_.emplace( lower, std::move( material ) );
    }

    /**
     *  @brief Insert or replace the material in the tape
     *
     *  This function inserts the material in the ENDF tape tree. If one or more
     *  materials are already present, the old materials are removed before inserting
     *  the new material.
     *
     *  @param[in]   material   the material to be inserted
     */
    void replace( const njoy::ENDFtk::Material& material ) {

      this->replace( toMaterial( material ) );
    }

    /**
     *  @brief Parse the tape
     *
     *  @param[in] lineNumber   the line number to be used in parsing
     */
    ::njoy::ENDFtk::Tape parse( long& lineNumber ) const {

      std::string content = this->content();
      auto position = content.begin();
      auto end = content.end();

      return { position, end, lineNumber };
    }

    /**
     *  @brief Parse the tape
     */
    ::njoy::ENDFtk::Tape parse() const {

      long lineNumber = 1;
      return this->parse( lineNumber );
    }

    /**
     *  @brief Clean up the tape
     *
     *  This function removes the sequence numbers from the tape
     */
    void clean() {

      for ( auto& material : this->materials() ) {

        material.clean();
      }
    }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
