# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import InterpolationRecord

class Test_ENDFtk_InterpolationRecord( unittest.TestCase ) :
    """Unit test for the InterpolationRecord class."""

    chunk = ( ' 1.001000+3 9.991673-1        101        102          3          6 125 1451     \n'
              '          4          1          5          2          6          3 125 1451     \n' )

    def test_record( self ) :

        def verify_chunk( self, chunk ) :

            self.assertAlmostEqual( chunk.C1, 1001. )
            self.assertAlmostEqual( chunk.C2, 0.9991673 )
            self.assertEqual( chunk.L1, 101 )
            self.assertEqual( chunk.L2, 102 )

            self.assertEqual( chunk.NR, 3 )
            self.assertEqual( chunk.NZ, 6 )
            self.assertEqual( len( chunk.boundaries ), 3 )
            self.assertEqual( len( chunk.interpolants ), 3 )

            self.assertEqual( 4, chunk.boundaries[0] )
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( 6, chunk.boundaries[2] )

            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.interpolants[1] )
            self.assertEqual( 3, chunk.interpolants[2] )

            self.assertEqual( chunk.to_string( 125, 1, 451 ), self.chunk )

        chunk = InterpolationRecord( C1 = 1001., C2 = 0.9991673,
                            L1 = 101, L2 = 102,
                            boundaries = [ 4, 5, 6 ],
                            interpolants = [ 1, 2, 3 ] )

        verify_chunk( self, chunk )

        # the data is copied
        copy = InterpolationRecord( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
