# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF33 import Section
from ENDFtk.MF33 import Subsection
from ENDFtk.MF33 import DerivedRedundant
from ENDFtk.MF33 import SquareMatrix
from ENDFtk.tree import Tape

class Test_ENDFtk_MF33_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( " 9.423900+4 2.369986+2          0          0          0          1943733  2     \n"
              " 1.000000+0 2.000000+0          3          4          1          1943733  2     \n"
              " 0.000000+0 0.000000+0          0          0          0          0943733  2     \n"
              " 2.500000+3 2.000000+7          0          0         14          7943733  2     \n"
              " 1.000000+0 1.000000+0-1.000000+0 4.000000+0-1.000000+0 1.600000+1943733  2     \n"
              "-1.000000+0 1.700000+1-1.000000+0 1.800000+1-1.000000+0 3.700000+1943733  2     \n"
              "-1.000000+0 1.020000+2                                            943733  2     \n"
              " 0.000000+0 0.000000+0          0          5          7          3943733  2     \n"
              " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943733  2     \n"
              " 4.000000+0                                                       943733  2     \n" )

    lump = " 9.423900+4 2.369986+2          0        850          0          0943733 51     \n"

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  943733  0     \n'
    valid_FEND = '                                                                  9437 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  943733  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 94239., chunk.ZA )
            self.assertAlmostEqual( 2.369986e+2, chunk.AWR )
            self.assertAlmostEqual( 2.369986e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 0, chunk.MTL)
            self.assertEqual( 0, chunk.lumped_covariance_index )
            self.assertEqual( 1, chunk.NL )
            self.assertEqual( 1, chunk.number_subsections )
            self.assertEqual( 1, len(chunk.subsections) )
            self.assertEqual( 2, chunk.MT )
            self.assertEqual( 2, chunk.section_number )

            sub = chunk.subsections[0]

            # subsection CONT record
            self.assertAlmostEqual( 1., sub.XMF1 )
            self.assertAlmostEqual( 1., sub.second_file_number )
            self.assertAlmostEqual( 2., sub.XLFS1 )
            self.assertAlmostEqual( 2., sub.second_final_excited_state )
            self.assertEqual( 3, sub.MAT1 )
            self.assertEqual( 3, sub.second_material_number )
            self.assertEqual( 4, sub.MT1 )
            self.assertEqual( 4, sub.second_section_number )
            self.assertEqual( 1, sub.NK )
            self.assertEqual( 1, sub.number_nc_type )
            self.assertEqual( 1, sub.NI )
            self.assertEqual( 1, sub.number_ni_type )
            self.assertEqual( 1, len(sub.components_ni) )
            self.assertEqual( 1, len(sub.components_ni) )

            self.assertEqual( 10, chunk.NC )

        def verify_lump(self, lump):

            # HEAD record
            self.assertAlmostEqual( 94239., lump.ZA );
            self.assertAlmostEqual( 2.369986e+2, lump.AWR );
            self.assertAlmostEqual( 2.369986e+2, lump.atomic_weight_ratio );
            self.assertEqual( 850, lump.MTL );
            self.assertEqual( 850, lump.lumped_covariance_index );
            self.assertEqual( 0, lump.NL );
            self.assertEqual( 0, lump.number_subsections );
            self.assertEqual( 0, len(lump.subsections) );
            self.assertEqual( 51, lump.MT );
            self.assertEqual( 51, lump.section_number );

            self.assertEqual( 1, lump.NC );

        # the data is given explicitly
        chunk = Section(
            mt=2, zaid=94239, awr=2.369986e+2,
            subsections=[Subsection(
                1., 2., 3, 4,
                [DerivedRedundant(
                    2.5e3, 2.0e7,
                    [1, -1, -1, -1, -1, -1, -1],
                    [1, 4, 16, 17, 18, 37, 102]
                    )],
                [SquareMatrix(
                    0, [0, 100, 200], [1, 2, 3, 4]
                    )]
                )]
            )

        lump = Section(mt=51, zaid=94239, awr=2.369986e+2, mtl=850)

        verify_chunk( self, chunk )
        verify_lump( self, lump )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )
        lump = Section.from_string( self.lump + self.valid_SEND )

        verify_chunk( self, chunk )
        verify_lump( self, lump )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9437 ).file( 33 ).section( 2 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
