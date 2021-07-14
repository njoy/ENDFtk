# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import TapeIdentification

class Test_ENDFtk_TapeIdentification( unittest.TestCase ) :
    """Unit test for the TapeIdentification class."""

    chunk = ' some data about the tape                                            1 0  0     \n'

    def test_record( self ) :

        def verify_chunk( self, chunk ) :

            self.assertEqual( chunk.text, ' some data about the tape                                         ' )
            self.assertEqual( chunk.to_string(), self.chunk )

        chunk = TapeIdentification( text = ' some data about the tape' )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TapeIdentification( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
