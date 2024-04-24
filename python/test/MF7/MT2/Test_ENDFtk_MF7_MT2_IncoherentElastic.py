# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT2 import IncoherentElastic

class Test_ENDFtk_MF7_MT2_IncoherentElastic( unittest.TestCase ) :
    """Unit test for the IncoherentElastic class."""

    chunk = ( ' 8.198006+1 0.000000+0          0          0          1          3  27 7  2     \n'
              '          3          2                                              27 7  2     \n'
              ' 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0  27 7  2     \n' )

    invalid = ( ' 8.198006+1 0.000000+0          0          0          1          4  27 7  2     \n'
                '          3          2                                              27 7  2     \n'
                ' 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0  27 7  2     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LTHR )
            self.assertEqual( 2, chunk.elastic_scattering_type )
            self.assertAlmostEqual( 8.198006e+1, chunk.SB )
            self.assertAlmostEqual( 8.198006e+1, chunk.bound_cross_section )
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
            self.assertEqual( 3, len( chunk.T ) )
            self.assertEqual( 3, len( chunk.temperatures ) )
            self.assertEqual( 3, len( chunk.W ) )
            self.assertEqual( 3, len( chunk.debye_waller_values ) )
            self.assertAlmostEqual( 296., chunk.T[0] )
            self.assertAlmostEqual( 400., chunk.T[1] )
            self.assertAlmostEqual( 500., chunk.T[2] )
            self.assertAlmostEqual( 296., chunk.temperatures[0] )
            self.assertAlmostEqual( 400., chunk.temperatures[1] )
            self.assertAlmostEqual( 500., chunk.temperatures[2] )
            self.assertAlmostEqual( 8.486993e+0, chunk.W[0] )
            self.assertAlmostEqual( 9.093191e+0, chunk.W[1] )
            self.assertAlmostEqual( 9.828159e+0, chunk.W[2] )
            self.assertAlmostEqual( 8.486993e+0, chunk.debye_waller_values[0] )
            self.assertAlmostEqual( 9.093191e+0, chunk.debye_waller_values[1] )
            self.assertAlmostEqual( 9.828159e+0, chunk.debye_waller_values[2] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 27, 7, 2 ) )

        # the data is given explicitly
        chunk = IncoherentElastic( sb = 8.198006e+1, boundaries = [ 3 ], interpolants = [ 2 ],
                                   temperatures = [ 296., 400., 500. ],
                                   integrals = [ 8.486993e+0, 9.093191e+0, 9.828159e+0 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = IncoherentElastic.from_string( self.chunk, 27, 7, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = IncoherentElastic( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = IncoherentElastic( sb = 8.198006e+1, boundaries = [ 3, 5 ], interpolants = [ 2 ],
                                       temperatures = [ 296., 400., 500. ],
                                       integrals = [ 8.486993e+0, 9.093191e+0, 9.828159e+0 ] )

        with self.assertRaises( Exception ) :

            chunk = IncoherentElastic.from_string( self.invalid, 27, 7, 2 )

if __name__ == '__main__' :

    unittest.main()
