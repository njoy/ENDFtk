# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT4 import AnalyticalFunctions

class Test_ENDFtk_MF7_MT4_AnalyticalFunctions( unittest.TestCase ) :
    """Unit test for the AnalyticalFunctions class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 0, chunk.NC )

            # verify string
            self.assertEqual( '', chunk.to_string( 27, 7, 4 ) )

        # the data is given explicitly
        chunk = AnalyticalFunctions()

        verify_chunk( self, chunk )

        # the data is copied
        copy = AnalyticalFunctions( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
