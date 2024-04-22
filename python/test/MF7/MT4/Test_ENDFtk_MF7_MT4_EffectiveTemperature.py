# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT4 import EffectiveTemperature

class Test_ENDFtk_MF7_MT4_EffectiveTemperature( unittest.TestCase ) :
    """Unit test for the EffectiveTemperature class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          3  27 7  4     \n'
              '          3          2                                              27 7  4     \n'
              ' 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n' )

    invalid = ( ' 1.001000+3 9.986234-1          0          1          1          59228 6  5     \n'
                '          4          2                                            9228 6  5     \n'
                ' 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n'
                ' 3.000000+7 2.149790-1                                            9228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.NP )
            self.assertEqual( 3, chunk.number_points )
            self.assertEqual( 3, chunk.NT )
            self.assertEqual( 3, chunk.number_temperatures )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 2, chunk.INT[0] )
            self.assertEqual( 3, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( 3, len( chunk.TMOD ) )
            self.assertEqual( 3, len( chunk.moderator_temperatures ) )
            self.assertEqual( 3, len( chunk.TEFF ) )
            self.assertEqual( 3, len( chunk.effective_temperatures ) )
            self.assertAlmostEqual( 293.6, chunk.TMOD[0] )
            self.assertAlmostEqual( 600., chunk.TMOD[1] )
            self.assertAlmostEqual( 1200., chunk.TMOD[2] )
            self.assertAlmostEqual( 293.6, chunk.moderator_temperatures[0] )
            self.assertAlmostEqual( 600., chunk.moderator_temperatures[1] )
            self.assertAlmostEqual( 1200., chunk.moderator_temperatures[2] )
            self.assertAlmostEqual( 5.332083e+2, chunk.TEFF[0] )
            self.assertAlmostEqual( 7.354726e+2, chunk.TEFF[1] )
            self.assertAlmostEqual( 1.270678e+3, chunk.TEFF[2] )
            self.assertAlmostEqual( 5.332083e+2, chunk.effective_temperatures[0] )
            self.assertAlmostEqual( 7.354726e+2, chunk.effective_temperatures[1] )
            self.assertAlmostEqual( 1.270678e+3, chunk.effective_temperatures[2] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 27, 7, 4 ) )

        # the data is given explicitly
        chunk = EffectiveTemperature( boundaries = [ 3 ], interpolants = [ 2 ],
                                      tmod = [ 293.6, 600., 1200. ],
                                      teff = [ 5.332083e+2, 7.354726e+2, 1.270678e+3 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = EffectiveTemperature.from_string( self.chunk, 27, 7, 4 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = EffectiveTemperature( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = EffectiveTemperature( boundaries = [ 3, 5 ], interpolants = [ 2 ],
                                          tmod = [ 293.6, 600., 1200. ],
                                          teff = [ 5.332083e+2, 7.354726e+2, 1.270678e+3 ] )

        with self.assertRaises( Exception ) :

            chunk = EffectiveTemperature.from_string( self.invalid, 27, 7, 4 )

if __name__ == '__main__' :

    unittest.main()
