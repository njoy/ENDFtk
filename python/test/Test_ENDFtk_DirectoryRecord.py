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

        record = DirectoryRecord( mf = 1, mt = 451, nc = 101, mod = 5 )

        self.assertEqual( record.MF, 1 )
        self.assertEqual( record.MT, 451 )
        self.assertEqual( record.NC, 101 )
        self.assertEqual( record.MOD, 5 )
        self.assertEqual( record.to_string( 125 ), self.chunk )

if __name__ == '__main__' :

    unittest.main()
