# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF34 import Section
from ENDFtk.MF34 import ReactionBlock
from ENDFtk.MF34 import LegendreBlock
from ENDFtk import SquareMatrix
from ENDFtk.tree import Tape

class Test_ENDFtk_MF34_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = (
        " 9.423900+4 2.369986+2          0          1          0          1943734  2     \n"
        " 0.000000+0 0.000000+0          0         51          1          1943734  2     \n"
        " 0.000000+0 0.000000+0          1          1          0          1943734  2     \n"
        " 0.000000+0 0.000000+0          0          5          7          3943734  2     \n"
        " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734  2     \n"
        " 4.000000+0                                                       943734  2     \n" )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  943734  0     \n'
    valid_FEND = '                                                                  9437 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  943734  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # HEAD record
            self.assertEqual( 2, chunk.MT )
            self.assertEqual( 2, chunk.section_number )
            self.assertEqual( 94239,  chunk.ZA )
            self.assertEqual( 94239,  chunk.target_identifier )
            self.assertAlmostEqual( 2.369986e+2,  chunk.AWR )
            self.assertAlmostEqual( 2.369986e+2,  chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.LTT )
            self.assertEqual( 1, chunk.representation )
            self.assertEqual( 1, chunk.NMT1 )
            self.assertEqual( 1, chunk.number_reactions )
            self.assertEqual( 1, len(chunk.reactions) )

            sub = chunk.reactions[0]

            # subsection CONT record
            self.assertEqual( 0, sub.MAT1 )
            self.assertEqual( 0, sub.second_material_number )
            self.assertEqual( 51, sub.MT1 )
            self.assertEqual( 51, sub.second_section_number )
            self.assertEqual( 1, sub.NL )
            self.assertEqual( 1, sub.first_number_legendre )
            self.assertEqual( 1, sub.NL1 )
            self.assertEqual( 1, sub.second_number_legendre )
            self.assertEqual( 1, sub.NSS )
            self.assertEqual( 1, sub.number_legendre_blocks )
            self.assertEqual( 1, len(sub.legendre_blocks) )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9437, 34 ) )

        # the data is given explicitly
        chunk = Section(
            mt=2, zaid=94239, awr=2.369986e+2, ltt=1,
            reactions=[ReactionBlock(
                2, 51, 1, 1,
                [LegendreBlock(
                    1, 1, 0,
                    [SquareMatrix(
                        0, [0, 100, 200], [1, 2, 3, 4]
                        )]
                    )]
                )]
            )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9437 ).file( 34 ).section( 2 ).parse()

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
