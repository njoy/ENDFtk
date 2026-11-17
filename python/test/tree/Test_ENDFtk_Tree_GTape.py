# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import TapeIdentification
from ENDFtk.tree import GTape
from ENDFtk.tree import GMaterial
from ENDFtk.tree import GFile
from ENDFtk.tree import GSection

class Test_ENDFtk_Tree_Tape( unittest.TestCase ) :
    """Unit test for the Tape class."""

    def test_empty_tape( self ) :

        # the tape is empty
        tape = GTape( id = TapeIdentification( 'this is my tape identification' ) )

        self.assertEqual( 0, len( tape.material_numbers ) )
        self.assertEqual( 0, len( tape.materials ) )

        self.assertEqual( 'this is my tape identification                                       0 0  0     \n'
                          '                                                                    -1 0  0     \n',
                          tape.content )

    def test_tape( self ) :

        def verify_chunk( self, tape ) :

            def verify_file1( self, file ) :

                self.assertEqual( 9228, file.MAT )
                self.assertEqual( 9228, file.material_number )
                self.assertEqual( 1, file.MF )
                self.assertEqual( 1, file.file_number )

                self.assertEqual( [ 451 ], file.section_numbers.to_list() )
                self.assertEqual( [ 451 ],
                                  [ section.MT for section in file.sections ] )

                self.assertEqual( True, file.has_MT( 451 ) )
                self.assertEqual( True, file.has_section( 451 ) )
                self.assertEqual( False, file.has_MT( 151 ) )
                self.assertEqual( False, file.has_section( 151 ) )
                self.assertEqual( False, file.has_MT( 1 ) )
                self.assertEqual( False, file.has_section( 1 ) )
                self.assertEqual( False, file.has_MT( 2 ) )
                self.assertEqual( False, file.has_section( 2 ) )
                self.assertEqual( False, file.has_MT( 102 ) )
                self.assertEqual( False, file.has_section( 102 ) )

                self.assertEqual( 12, len( file.content.split( '\n' ) ) )

            def verify_file3( self, file ) :

                self.assertEqual( 9228, file.MAT )
                self.assertEqual( 9228, file.material_number )
                self.assertEqual( 3, file.MF )
                self.assertEqual( 3, file.file_number )

                self.assertEqual( [ 1, 2, 4, 5, 16, 17, 18,
                                        51, 52, 53, 54, 55, 56, 57, 58, 59,
                                    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                                    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                                    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                                    91, 102, 103, 107, 452, 600 ], file.section_numbers.to_list() )
                self.assertEqual( [ 1, 2, 4, 5, 16, 17, 18,
                                        51, 52, 53, 54, 55, 56, 57, 58, 59,
                                    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                                    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                                    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                                    91, 102, 103, 107, 452, 600 ],
                                  [ section.MT for section in file.sections ] )

                self.assertEqual( False, file.has_MT( 451 ) )
                self.assertEqual( False, file.has_section( 451 ) )
                self.assertEqual( False, file.has_MT( 151 ) )
                self.assertEqual( False, file.has_section( 151 ) )
                self.assertEqual( True, file.has_MT( 1 ) )
                self.assertEqual( True, file.has_section( 1 ) )
                self.assertEqual( True, file.has_MT( 2 ) )
                self.assertEqual( True, file.has_section( 2 ) )
                self.assertEqual( True, file.has_MT( 102 ) )
                self.assertEqual( True, file.has_section( 102 ) )

                self.assertEqual( 1833, len( file.content.split( '\n' ) ) )

            def verify_file6( self, file ) :

                self.assertEqual( 9228, file.MAT )
                self.assertEqual( 9228, file.material_number )
                self.assertEqual( 6, file.MF )
                self.assertEqual( 6, file.file_number )

                self.assertEqual( [ 2, 5, 16, 17, 18,
                                        51, 52, 53, 54, 55, 56, 57, 58, 59,
                                    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                                    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                                    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                                    91 ], file.section_numbers.to_list() )
                self.assertEqual( [ 2, 5, 16, 17, 18,
                                        51, 52, 53, 54, 55, 56, 57, 58, 59,
                                    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                                    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                                    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                                    91 ],
                                  [ section.MT for section in file.sections ] )

                self.assertEqual( False, file.has_MT( 451 ) )
                self.assertEqual( False, file.has_section( 451 ) )
                self.assertEqual( False, file.has_MT( 151 ) )
                self.assertEqual( False, file.has_section( 151 ) )
                self.assertEqual( False, file.has_MT( 1 ) )
                self.assertEqual( False, file.has_section( 1 ) )
                self.assertEqual( True, file.has_MT( 2 ) )
                self.assertEqual( True, file.has_section( 2 ) )
                self.assertEqual( False, file.has_MT( 102 ) )
                self.assertEqual( False, file.has_section( 102 ) )

                self.assertEqual( 3631, len( file.content.split( '\n' ) ) )

            def verify_material( self, material ) :

                self.assertEqual( 9228, material.MAT )
                self.assertEqual( 9228, material.material_number )

                self.assertEqual( [ 1, 3, 6 ], material.file_numbers.to_list() )
                self.assertEqual( [ 1, 3, 6 ],
                                  [ file.MF for file in material.files ] )

                self.assertEqual( True, material.has_MF( 1 ) )
                self.assertEqual( True, material.has_file( 1 ) )
                self.assertEqual( False, material.has_MF( 2 ) )
                self.assertEqual( False, material.has_file( 2 ) )
                self.assertEqual( True, material.has_MF( 3 ) )
                self.assertEqual( True, material.has_file( 3 ) )
                self.assertEqual( False, material.has_MF( 4 ) )
                self.assertEqual( False, material.has_file( 4 ) )
                self.assertEqual( False, material.has_MF( 5 ) )
                self.assertEqual( False, material.has_file( 5 ) )
                self.assertEqual( True, material.has_MF( 6 ) )
                self.assertEqual( True, material.has_file( 6 ) )
                self.assertEqual( False, material.has_MF( 7 ) )
                self.assertEqual( False, material.has_file( 7 ) )

                verify_file1( self, material.MF( 1 ) )
                verify_file1( self, material.file( 1 ) )
                verify_file1( self, GFile( material.file( 1 ) ) )

                verify_file3( self, material.MF( 3 ) )
                verify_file3( self, material.file( 3 ) )
                verify_file3( self, GFile( material.file( 3 ) ) )

                verify_file6( self, material.MF( 6 ) )
                verify_file6( self, material.file( 6 ) )
                verify_file6( self, GFile( material.file( 6 ) ) )

                self.assertEqual( 5475, len( material.content.split( '\n' ) ) )

            self.assertEqual( "this is my tape identification                                    ",
                              tape.tape_id.text )
            self.assertEqual( "this is my tape identification                                    ",
                              tape.TPID.text )

            self.assertEqual( [ 9228 ], tape.material_numbers )

            self.assertEqual( False, tape.has_MAT( 100 ) )
            self.assertEqual( False, tape.has_material( 100 ) )
            self.assertEqual( True, tape.has_MAT( 9228 ) )
            self.assertEqual( True, tape.has_material( 9228 ) )
            self.assertEqual( False, tape.has_MAT( 9225 ) )
            self.assertEqual( False, tape.has_material( 9225 ) )

            materials = tape.materials
            self.assertEqual( 1, len( materials ) )

            material = materials.to_list()[0]
            verify_material( self, material )

            material = materials.front()
            verify_material( self, material )

            material = tape.MAT( 9228 )
            verify_material( self, material )

            material = tape.material( 9228 )
            verify_material( self, material )

            copy = GMaterial( material )
            verify_material( self, copy )

            self.assertEqual( 5477, len( tape.content.split( '\n' ) ) )

        # a valid ENDF tape
        filename = 'test/resources/n-092_U_235.gendf'

        # the data is read from a file
        with open( filename, 'r' ) as file :

            tape = GTape( file.read() )

        verify_chunk( self, tape )

        # the data is read from a file using the static from_file method
        tape = GTape.from_file( filename )

        # verify the tape's content
        verify_chunk( self, tape )

        # the data is copied
        copy = GTape( tape )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # unknown file
        with self.assertRaises( Exception ) :

            filename = 'some unexisting file'
            tape = GTape.from_file( filename )

if __name__ == '__main__' :

    unittest.main()
