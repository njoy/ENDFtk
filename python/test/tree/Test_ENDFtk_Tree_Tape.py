# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import TapeIdentification
from ENDFtk.tree import Tape
from ENDFtk.tree import Material
from ENDFtk.tree import File
from ENDFtk.tree import Section
from ENDFtk.MF3 import Section as ParsedSection

class Test_ENDFtk_Tree_Tape( unittest.TestCase ) :
    """Unit test for the Tape class."""

    def test_empty_tape( self ) :

        # the tape is empty
        tape = Tape( id = TapeIdentification( 'this is my tape identification' ) )

        self.assertEqual( 0, len( tape.material_numbers ) )
        self.assertEqual( 0, len( tape.materials ) )

        self.assertEqual( 'this is my tape identification                                       0 0  0     \n'
                          '                                                                    -1 0  0     \n',
                          tape.content )

    def test_tape( self ) :

        def verify_chunk( self, tape ) :

            def verify_file1( self, file ) :

                self.assertEqual( 125, file.MAT )
                self.assertEqual( 125, file.material_number )
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

                self.assertEqual( 125, len( file.content.split( '\n' ) ) )

            def verify_file2( self, file ) :

                self.assertEqual( 125, file.MAT )
                self.assertEqual( 125, file.material_number )
                self.assertEqual( 2, file.MF )
                self.assertEqual( 2, file.file_number )

                self.assertEqual( [ 151 ], file.section_numbers.to_list() )
                self.assertEqual( [ 151 ],
                                  [ section.MT for section in file.sections ] )

                self.assertEqual( False, file.has_MT( 451 ) )
                self.assertEqual( False, file.has_section( 451 ) )
                self.assertEqual( True, file.has_MT( 151 ) )
                self.assertEqual( True, file.has_section( 151 ) )
                self.assertEqual( False, file.has_MT( 1 ) )
                self.assertEqual( False, file.has_section( 1 ) )
                self.assertEqual( False, file.has_MT( 2 ) )
                self.assertEqual( False, file.has_section( 2 ) )
                self.assertEqual( False, file.has_MT( 102 ) )
                self.assertEqual( False, file.has_section( 102 ) )

                self.assertEqual( 7, len( file.content.split( '\n' ) ) )

            def verify_file3( self, file ) :

                self.assertEqual( 125, file.MAT )
                self.assertEqual( 125, file.material_number )
                self.assertEqual( 3, file.MF )
                self.assertEqual( 3, file.file_number )

                self.assertEqual( [ 1, 2, 102 ], file.section_numbers.to_list() )
                self.assertEqual( [ 1, 2, 102 ],
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

                self.assertEqual( 110, len( file.content.split( '\n' ) ) )

            def verify_file4( self, file ) :

                self.assertEqual( 125, file.MAT )
                self.assertEqual( 125, file.material_number )
                self.assertEqual( 4, file.MF )
                self.assertEqual( 4, file.file_number )

                self.assertEqual( [ 2 ], file.section_numbers.to_list() )
                self.assertEqual( [ 2 ],
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

                self.assertEqual( 199, len( file.content.split( '\n' ) ) )

            def verify_file6( self, file ) :

                self.assertEqual( 125, file.MAT )
                self.assertEqual( 125, file.material_number )
                self.assertEqual( 6, file.MF )
                self.assertEqual( 6, file.file_number )

                self.assertEqual( [ 102 ], file.section_numbers.to_list() )
                self.assertEqual( [ 102 ],
                                  [ section.MT for section in file.sections ] )

                self.assertEqual( False, file.has_MT( 451 ) )
                self.assertEqual( False, file.has_section( 451 ) )
                self.assertEqual( False, file.has_MT( 151 ) )
                self.assertEqual( False, file.has_section( 151 ) )
                self.assertEqual( False, file.has_MT( 1 ) )
                self.assertEqual( False, file.has_section( 1 ) )
                self.assertEqual( False, file.has_MT( 2 ) )
                self.assertEqual( False, file.has_section( 2 ) )
                self.assertEqual( True, file.has_MT( 102 ) )
                self.assertEqual( True, file.has_section( 102 ) )

                self.assertEqual( 204, len( file.content.split( '\n' ) ) )

            def verify_file33( self, file ) :

                self.assertEqual( 125, file.MAT )
                self.assertEqual( 125, file.material_number )
                self.assertEqual( 33, file.MF )
                self.assertEqual( 33, file.file_number )

                self.assertEqual( [ 1, 2, 102 ], file.section_numbers.to_list() )
                self.assertEqual( [ 1, 2, 102 ],
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

                self.assertEqual( 1568, len( file.content.split( '\n' ) ) )

            def verify_material( self, material ) :

                self.assertEqual( 125, material.MAT )
                self.assertEqual( 125, material.material_number )

                self.assertEqual( [ 1, 2, 3, 4, 6, 33 ], material.file_numbers.to_list() )
                self.assertEqual( [ 1, 2, 3, 4, 6, 33 ],
                                  [ file.MF for file in material.files ] )

                self.assertEqual( True, material.has_MF( 1 ) )
                self.assertEqual( True, material.has_file( 1 ) )
                self.assertEqual( True, material.has_MF( 2 ) )
                self.assertEqual( True, material.has_file( 2 ) )
                self.assertEqual( True, material.has_MF( 3 ) )
                self.assertEqual( True, material.has_file( 3 ) )
                self.assertEqual( True, material.has_MF( 4 ) )
                self.assertEqual( True, material.has_file( 4 ) )
                self.assertEqual( False, material.has_MF( 5 ) )
                self.assertEqual( False, material.has_file( 5 ) )
                self.assertEqual( True, material.has_MF( 6 ) )
                self.assertEqual( True, material.has_file( 6 ) )
                self.assertEqual( False, material.has_MF( 7 ) )
                self.assertEqual( False, material.has_file( 7 ) )

                verify_file1( self, material.MF( 1 ) )
                verify_file1( self, material.file( 1 ) )
                verify_file1( self, File( material.file( 1 ) ) )

                verify_file2( self, material.MF( 2 ) )
                verify_file2( self, material.file( 2 ) )
                verify_file2( self, File( material.file( 2 ) ) )

                verify_file3( self, material.MF( 3 ) )
                verify_file3( self, material.file( 3 ) )
                verify_file3( self, File( material.file( 3 ) ) )

                verify_file4( self, material.MF( 4 ) )
                verify_file4( self, material.file( 4 ) )
                verify_file4( self, File( material.file( 4 ) ) )

                verify_file6( self, material.MF( 6 ) )
                verify_file6( self, material.file( 6 ) )
                verify_file6( self, File( material.file( 6 ) ) )

                verify_file33( self, material.MF( 33 ) )
                verify_file33( self, material.file( 33 ) )
                verify_file33( self, File( material.file( 33 ) ) )

                self.assertEqual( 2209, len( material.content.split( '\n' ) ) )

            self.assertEqual( " $Rev::          $  $Date::            $                          ",
                              tape.tape_id.text )
            self.assertEqual( " $Rev::          $  $Date::            $                          ",
                              tape.TPID.text )

            self.assertEqual( [ 125 ], tape.material_numbers )

            self.assertEqual( False, tape.has_MAT( 100 ) )
            self.assertEqual( False, tape.has_material( 100 ) )
            self.assertEqual( True, tape.has_MAT( 125 ) )
            self.assertEqual( True, tape.has_material( 125 ) )
            self.assertEqual( False, tape.has_MAT( 9225 ) )
            self.assertEqual( False, tape.has_material( 9225 ) )

            materials = tape.materials
            self.assertEqual( 1, len( materials ) )

            material = materials.to_list()[0]
            verify_material( self, material )

            material = materials.front()
            verify_material( self, material )

            material = tape.MAT( 125 )
            verify_material( self, material )

            material = tape.material( 125 )
            verify_material( self, material )

            copy = Material( material )
            verify_material( self, copy )

            self.assertEqual( 2211, len( tape.content.split( '\n' ) ) )

        # a valid ENDF tape
        filename = 'test/resources/n-001_H_001.endf'

        # the data is read from a file
        with open( filename, 'r' ) as file :

            tape = Tape( file.read() )

        verify_chunk( self, tape )

        # the data is read from a file using the static from_file method
        tape = Tape.from_file( filename )

        # verify the tape's content
        verify_chunk( self, tape )

        # the data is copied
        copy = Tape( tape )

        verify_chunk( self, copy )

    def test_insert_replace_remove( self ) :

        tape = Tape.from_file( 'test/resources/n-001_H_001.endf' )
        copy = Tape( tape )

        material = tape.materials.front()
        file = material.file( 3 )

        # remove a file from a material
        material.remove( 2 )
        self.assertEqual( [ 1, 3, 4, 6, 33 ], material.file_numbers.to_list() )
        self.assertEqual( [ 1, 3, 4, 6, 33 ], tape.materials.front().file_numbers.to_list() )

        # remove a section from a material
        material.remove( 3, 2 )
        self.assertEqual( [ 1, 3, 4, 6, 33 ], material.file_numbers.to_list() )
        self.assertEqual( [ 1, 102 ], file.section_numbers.to_list() )
        self.assertEqual( [ 1, 3, 4, 6, 33 ], tape.materials.front().file_numbers.to_list() )
        self.assertEqual( [ 1, 102 ], tape.materials.front().file(3).section_numbers.to_list() )

        # remove a section from a file
        file.remove( 102 )
        self.assertEqual( [ 1, 3, 4, 6, 33 ], material.file_numbers.to_list() )
        self.assertEqual( [ 1 ], file.section_numbers.to_list() )
        self.assertEqual( [ 1, 3, 4, 6, 33 ], tape.materials.front().file_numbers.to_list() )
        self.assertEqual( [ 1 ], tape.materials.front().file(3).section_numbers.to_list() )

        # insert a section into a file
        data = copy.materials.front().file( 3 ).section( 102 )
        file.insert( data )
        self.assertEqual( [ 1, 3, 4, 6, 33 ], material.file_numbers.to_list() )
        self.assertEqual( [ 1, 102 ], file.section_numbers.to_list() )
        self.assertEqual( [ 1, 3, 4, 6, 33 ], tape.materials.front().file_numbers.to_list() )
        self.assertEqual( [ 1, 102 ], tape.materials.front().file(3).section_numbers.to_list() )

        # insert a section into a material
        data = copy.materials.front().file( 3 ).section( 2 )
        file.insert( data )
        self.assertEqual( [ 1, 3, 4, 6, 33 ], material.file_numbers.to_list() )
        self.assertEqual( [ 1, 2, 102 ], file.section_numbers.to_list() )
        self.assertEqual( [ 1, 3, 4, 6, 33 ], tape.materials.front().file_numbers.to_list() )
        self.assertEqual( [ 1, 2, 102 ], tape.materials.front().file(3).section_numbers.to_list() )

        # insert a file into a material
        data = copy.materials.front().file( 2 )
        material.insert( data )
        self.assertEqual( [ 1, 2, 3, 4, 6, 33 ], material.file_numbers.to_list() )
        self.assertEqual( [ 1, 2, 3, 4, 6, 33 ], tape.materials.front().file_numbers.to_list() )

    def test_insert_replace_parsed_section( self ) :

        tape = Tape.from_file( 'test/resources/n-001_H_001.endf' )
        copy = Tape( tape )

        material = tape.materials.front()
        file = material.file( 3 )

        data = ParsedSection( mt = 103,  zaid = 1001, lr = 0, awr = 0.9991673,
                              qm = 2.224648e+6, qi = 3.224648e+6,
                              interpolants = [ 5, 2 ], boundaries = [ 3, 6 ],
                              energies = [ 1e-5, 2e-5, 7.5e+5,
                                           1.9e+7, 1.95e+7, 2e+7 ],
                              xs = [ 1.672869e+1, 1.182897e+1, 3.347392e-5,
                                     2.751761e-5, 2.731301e-5, 2.710792e-5 ] )

        # insert a parsed section into a file
        file.insert( data )
        self.assertEqual( [ 1, 2, 102, 103 ], file.section_numbers.to_list() )

        # the section was replaced correctly (testing some data)
        section = file.section( 103 ).parse()
        self.assertEqual( 2, len( section.boundaries ) )
        self.assertEqual( 2, len( section.interpolants ) )

        # inserting it again throws an exception
        with self.assertRaises( Exception ) :

            file.insert( data )

        data = ParsedSection( mt = 103,  zaid = 1001, lr = 0, awr = 0.9991673,
                              qm = 2.224648e+6, qi = 3.224648e+6,
                              interpolants = [ 2 ], boundaries = [ 2 ],
                              energies = [ 1e-5, 2e+7 ],
                              xs = [ 1., 2. ] )

        # replacing a parsed section into a file
        file.insert_or_replace( data )
        self.assertEqual( [ 1, 2, 102, 103 ], file.section_numbers.to_list() )

        # the section was replaced correctly (testing some data)
        section = file.section( 103 ).parse()
        self.assertEqual( 1, len( section.boundaries ) )
        self.assertEqual( 1, len( section.interpolants ) )

    def test_failures( self ) :

        print( '\n' )

        # unknown file
        with self.assertRaises( Exception ) :

            filename = 'some unexisting file'
            tape = Tape.from_file( filename )

if __name__ == '__main__' :

    unittest.main()
