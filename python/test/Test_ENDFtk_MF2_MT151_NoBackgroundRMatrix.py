# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import NoBackgroundRMatrix

class Test_ENDFtk_MF2_MT151_NoBackgroundRMatrix( unittest.TestCase ) :
    """Unit test for the NoBackgroundRMatrix class."""

    chunk = ' 0.000000+0 0.000000+0          1          0          0          02625 2151     \n'

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 0, chunk.LBK )
            self.assertEqual( 0, chunk.representation )
            self.assertEqual( 1, chunk.LCH )
            self.assertEqual( 1, chunk.channel_index )

            self.assertEqual( 1, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 2, 151 ) )

        # the data is given explicitly
        chunk = NoBackgroundRMatrix( index = 1 )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = NoBackgroundRMatrix.from_string( self.chunk, 2625, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = NoBackgroundRMatrix( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
