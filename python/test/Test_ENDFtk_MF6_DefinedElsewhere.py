# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import DefinedElsewhere

class Test_ENDFtk_MF6_DefinedElsewhere( unittest.TestCase ) :
    """Unit test for the DefinedElsewhere class."""

    def test_component( self ) :

        # the data is given explicitly
        chunk = DefinedElsewhere( -4 )

        self.assertEqual( -4, chunk.LAW )
        self.assertEqual( 0, chunk.NC )
        self.assertEqual( '', chunk.to_string( 9228, 6, 5 ) )

        # the data is copied
        copy = DefinedElsewhere( chunk )

        self.assertEqual( -4, copy.LAW )
        self.assertEqual( 0, copy.NC )
        self.assertEqual( '', copy.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = DefinedElsewhere( -5 )

        self.assertEqual( -5, chunk.LAW )
        self.assertEqual( 0, chunk.NC )
        self.assertEqual( '', chunk.to_string( 9228, 6, 5 ) )

        # the data is copied
        copy = DefinedElsewhere( chunk )

        self.assertEqual( -5, copy.LAW )
        self.assertEqual( 0, copy.NC )
        self.assertEqual( '', copy.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = DefinedElsewhere( -14 )

        self.assertEqual( -14, chunk.LAW )
        self.assertEqual( 0, chunk.NC )
        self.assertEqual( '', chunk.to_string( 9228, 6, 5 ) )

        # the data is copied
        copy = DefinedElsewhere( chunk )

        self.assertEqual( -14, copy.LAW )
        self.assertEqual( 0, copy.NC )
        self.assertEqual( '', copy.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = DefinedElsewhere( -15 )

        self.assertEqual( -15, chunk.LAW )
        self.assertEqual( 0, chunk.NC )
        self.assertEqual( '', chunk.to_string( 9228, 6, 5 ) )

        # the data is copied
        copy = DefinedElsewhere( chunk )

        self.assertEqual( -15, copy.LAW )
        self.assertEqual( 0, copy.NC )
        self.assertEqual( '', copy.to_string( 9228, 6, 5 ) )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = DefinedElsewhere( -1 )

if __name__ == '__main__' :

    unittest.main()
