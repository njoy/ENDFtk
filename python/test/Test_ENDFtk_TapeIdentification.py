# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import TapeIdentification

class Test_ENDFtk_TapeIdentification( unittest.TestCase ) :
    """Unit test for the TapeIdentification class."""

    chunk = ' some data about the tape                                            1 0  0     \n'

    def test_record( self ) :

        record = TapeIdentification( text = ' some data about the tape                                          ' )

        self.assertEqual( record.text, ' some data about the tape                                          ' )
        self.assertEqual( record.to_string(), self.chunk )

if __name__ == '__main__' :

    unittest.main()
