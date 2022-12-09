# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import CompactCorrelationMatrix

class Test_ENDFtk_MF32_MT151_CompactCorrelationMatrix( unittest.TestCase ) :
    """Unit test for the CompactCorrelationMatrix class."""

    chunk = ( ' 0.000000+0 0.000000+0          2         12          4          0172532151     \n'
              '    2    1   2                                                    172532151     \n'
              '    3    1   3  8                                                 172532151     \n'
              '    7    5   8  5                                                 172532151     \n'
              '   10    4   1  0  1  0  1                                        172532151     \n' )

    invalid_ndigit = ( ' 0.000000+0 0.000000+0          7         12          4          0172532151     \n'
                       '    2    1   2                                                    172532151     \n'
                       '    3    1   3  8                                                 172532151     \n'
                       '    7    5   8  5                                                 172532151     \n'
                       '   10    4   1  0  1  0  1                                        172532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.NDIGIT )
            self.assertEqual( 2, chunk.number_digits )
            self.assertEqual( 12, chunk.NNN )
            self.assertEqual( 12, chunk.order )
            self.assertEqual( 8, len( chunk.I ) )
            self.assertEqual( 8, len( chunk.J ) )
            self.assertEqual( 8, len( chunk.correlations ) )

            self.assertEqual(  2, chunk.I[0] )
            self.assertEqual(  3, chunk.I[1] )
            self.assertEqual(  3, chunk.I[2] )
            self.assertEqual(  7, chunk.I[3] )
            self.assertEqual(  7, chunk.I[4] )
            self.assertEqual( 10, chunk.I[5] )
            self.assertEqual( 10, chunk.I[6] )
            self.assertEqual( 10, chunk.I[7] )
            self.assertEqual(  1, chunk.J[0] )
            self.assertEqual(  1, chunk.J[1] )
            self.assertEqual(  2, chunk.J[2] )
            self.assertEqual(  5, chunk.J[3] )
            self.assertEqual(  6, chunk.J[4] )
            self.assertEqual(  4, chunk.J[5] )
            self.assertEqual(  6, chunk.J[6] )
            self.assertEqual(  8, chunk.J[7] )

            self.assertAlmostEqual( 0.025, chunk.correlations[0] )
            self.assertAlmostEqual( 0.035, chunk.correlations[1] )
            self.assertAlmostEqual( 0.085, chunk.correlations[2] )
            self.assertAlmostEqual( 0.085, chunk.correlations[3] )
            self.assertAlmostEqual( 0.055, chunk.correlations[4] )
            self.assertAlmostEqual( 0.015, chunk.correlations[5] )
            self.assertAlmostEqual( 0.015, chunk.correlations[6] )
            self.assertAlmostEqual( 0.015, chunk.correlations[7] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1725, 32, 151 ) )

        # the data is given explicitly
        chunk = CompactCorrelationMatrix( order = 12,
                                          i = [ 2, 3, 3, 7, 7, 10, 10, 10 ],
                                          j = [ 1, 1, 2, 5, 6,  4,  6,  8 ],
                                          correlations = [ 0.025, 0.035, 0.085,
                                                           0.085, 0.055, 0.015,
                                                           0.015, 0.015 ],
                                          ndigit = 2 )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CompactCorrelationMatrix.from_string( self.chunk, 1725, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CompactCorrelationMatrix( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # the data is empty
        with self.assertRaises( Exception ) :

            chunk = CompactCorrelationMatrix( order = 12,
                                              i = [],
                                              j = [],
                                              correlations = [] )

        # different sizes
        with self.assertRaises( Exception ) :

            chunk = CompactCorrelationMatrix( order = 12,
                                              i = [ 3, 4 ],
                                              j = [ 1, 2 ],
                                              correlations = [ 0.015 ] )

        # invalid ndigit
        with self.assertRaises( Exception ) :

            chunk = CompactCorrelationMatrix( order = 12,
                                              i = [ 3, 4 ],
                                              j = [ 1, 2 ],
                                              correlations = [ 0.015, 0.025 ] ,
                                              ndigit = 7 )

        # a string with an invalid NDIGIT is used
        with self.assertRaises( Exception ) :

            chunk = CompactCorrelationMatrix.from_string( self.invalid_ndigit,
                                                          1725, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
