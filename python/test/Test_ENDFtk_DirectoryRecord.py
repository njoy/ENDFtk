# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import DirectoryRecord

class Test_ENDFtk_DirectoryRecord( unittest.TestCase ) :
    """Unit test for the DirectoryRecord class."""

    chunk = '                                1        451        101          5 125 1451     \n'
    invalid = '                                1        451        101          5 125 14a1     \n'

    def test_record( self ) :

        def verify_chunk( self, chunk ) :

            self.assertEqual( chunk.MF, 1 )
            self.assertEqual( chunk.MT, 451 )
            self.assertEqual( chunk.NC, 101 )
            self.assertEqual( chunk.MOD, 5 )
            self.assertEqual( chunk.to_string( 125 ), self.chunk )

        chunk = DirectoryRecord( mf = 1, mt = 451, nc = 101, mod = 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = DirectoryRecord( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
