# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import ListRecord

class Test_ENDFtk_ListRecord( unittest.TestCase ) :
    """Unit test for the ListRecord class."""

    chunk = ( ' 1.001000+3 9.991673-1        101        102         10        103 125 1451     \n'
              ' 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 125 1451     \n'
              ' 6.000000+0 7.000000+0 8.000000+0 9.000000+0                       125 1451     \n' )

    def test_record( self ) :

        def verify_chunk( self, chunk ) :

            self.assertAlmostEqual( chunk.C1, 1001. )
            self.assertAlmostEqual( chunk.C2, 0.9991673 )
            self.assertEqual( chunk.L1, 101 )
            self.assertEqual( chunk.L2, 102 )
            self.assertEqual( chunk.N2, 103 )

            self.assertEqual( chunk.NPL, 10 )
            self.assertEqual( len( chunk.list ), 10 )

            self.assertEqual( 0., chunk.list[0] )
            self.assertEqual( 1., chunk.list[1] )
            self.assertEqual( 2., chunk.list[2] )
            self.assertEqual( 3., chunk.list[3] )
            self.assertEqual( 4., chunk.list[4] )
            self.assertEqual( 5., chunk.list[5] )
            self.assertEqual( 6., chunk.list[6] )
            self.assertEqual( 7., chunk.list[7] )
            self.assertEqual( 8., chunk.list[8] )
            self.assertEqual( 9., chunk.list[9] )

            self.assertEqual( chunk.to_string( 125, 1, 451 ), self.chunk )

        chunk = ListRecord( C1 = 1001., C2 = 0.9991673,
                            L1 = 101, L2 = 102, N2 = 103,
                            list = [ 0., 1., 2., 3., 4., 5., 6., 7., 8., 9. ] )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ListRecord( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
