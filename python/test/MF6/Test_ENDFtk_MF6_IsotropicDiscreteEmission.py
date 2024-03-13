# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import IsotropicDiscreteEmission

class Test_ENDFtk_MF6_IsotropicDiscreteEmission( unittest.TestCase ) :
    """Unit test for the IsotropicDiscreteEmission class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.LAW )

            self.assertEqual( 0, chunk.NC )

            # verify string
            self.assertEqual( '', chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = IsotropicDiscreteEmission()

        verify_chunk( self, chunk )

        # the data is copied
        copy = IsotropicDiscreteEmission( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
