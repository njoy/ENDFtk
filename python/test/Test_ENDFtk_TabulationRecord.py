# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import TabulationRecord

class Test_ENDFtk_TabulationRecord( unittest.TestCase ) :
    """Unit test for the TabulationRecord class."""

    chunk = ( ' 1.001000+3 9.991673-1        101        102          3          6 125 1451     \n'
              '          4          1          5          2          6          3 125 1451     \n'
              ' 1.000000+0 3.000000+0 2.000000+0 4.000000+0 3.000000+0 5.000000+0 125 1451     \n'
              ' 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 1451     \n' )

    def test_record( self ) :

        def verify_chunk( self, chunk ) :

            self.assertAlmostEqual( chunk.C1, 1001. )
            self.assertAlmostEqual( chunk.C2, 0.9991673 )
            self.assertEqual( chunk.L1, 101 )
            self.assertEqual( chunk.L2, 102 )

            self.assertEqual( chunk.NR, 3 )
            self.assertEqual( chunk.NP, 6 )
            self.assertEqual( len( chunk.boundaries ), 3 )
            self.assertEqual( len( chunk.interpolants ), 3 )
            self.assertEqual( len( chunk.x ), 6 )
            self.assertEqual( len( chunk.y ), 6 )

            self.assertEqual( 4, chunk.boundaries[0] )
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( 6, chunk.boundaries[2] )

            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.interpolants[1] )
            self.assertEqual( 3, chunk.interpolants[2] )

            self.assertEqual( 1., chunk.x[0] )
            self.assertEqual( 2., chunk.x[1] )
            self.assertEqual( 3., chunk.x[2] )
            self.assertEqual( 4., chunk.x[3] )
            self.assertEqual( 5., chunk.x[4] )
            self.assertEqual( 6., chunk.x[5] )

            self.assertEqual( 3., chunk.y[0] )
            self.assertEqual( 4., chunk.y[1] )
            self.assertEqual( 5., chunk.y[2] )
            self.assertEqual( 6., chunk.y[3] )
            self.assertEqual( 7., chunk.y[4] )
            self.assertEqual( 8., chunk.y[5] )

            self.assertEqual( chunk.to_string( 125, 1, 451 ), self.chunk )

        chunk = TabulationRecord( C1 = 1001., C2 = 0.9991673,
                            L1 = 101, L2 = 102,
                            boundaries = [ 4, 5, 6 ],
                            interpolants = [ 1, 2, 3 ],
                            x = [ 1., 2., 3., 4., 5., 6. ],
                            y = [ 3., 4., 5., 6., 7., 8. ] )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TabulationRecord( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
