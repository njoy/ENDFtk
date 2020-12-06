# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT455 import DecayConstants
from ENDFtk.MF1.MT455 import EnergyDependentConstants

class Test_ENDFtk_MF1_MT455_EnergyDependentConstants( unittest.TestCase ) :
    """Unit test for the EnergyDependentConstants class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          29228 1455     \n'
              '          2          4                                            9228 1455     \n'
              ' 0.000000+0 1.000000-5          0          0         12          09228 1455     \n'
              ' 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n'
              ' 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n'
              ' 0.000000+0 2.000000+7          0          0         12          09228 1455     \n'
              ' 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n'
              ' 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0 1.100000+09228 1455     \n' )

    oddNPL = ( ' 0.000000+0 0.000000+0          0          0          1          29228 1455     \n'
               '          2          4                                            9228 1455     \n'
               ' 0.000000+0 1.000000-5          0          0         11          09228 1455     \n'
               ' 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n'
               ' 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0           9228 1455     \n'
               ' 0.000000+0 2.000000+7          0          0         11          09228 1455     \n'
               ' 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n'
               ' 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0           9228 1455     \n' )

    inconsistentNNF = ( ' 0.000000+0 0.000000+0          0          0          1          29228 1455     \n'
                        '          2          4                                            9228 1455     \n'
                        ' 0.000000+0 1.000000-5          0          0         12          09228 1455     \n'
                        ' 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n'
                        ' 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n'
                        ' 0.000000+0 2.000000+7          0          0         10          09228 1455     \n'
                        ' 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n'
                        ' 3.000000+0 3.100000+0 2.000000+0 2.100000+0                      9228 1455     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LDG )
            self.assertEqual( 1, chunk.type )
            self.assertEqual( 6, chunk.NNF )
            self.assertEqual( 6, chunk.number_precursors )

            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 4, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )

            self.assertEqual( 2, len( chunk.constants ) )
            self.assertAlmostEqual( 1e-5, chunk.constants[0].E )
            self.assertAlmostEqual( 2e+7, chunk.constants[1].E )
            self.assertAlmostEqual( 1e-5, chunk.constants[0].incident_energy )
            self.assertAlmostEqual( 2e+7, chunk.constants[1].incident_energy )

            self.assertEqual( 6, len( chunk.constants[0].lambdas ) )
            self.assertEqual( 6, len( chunk.constants[0].decay_constants ) )
            self.assertAlmostEqual( 1., chunk.constants[0].lambdas[0] )
            self.assertAlmostEqual( 2., chunk.constants[0].lambdas[1] )
            self.assertAlmostEqual( 3., chunk.constants[0].lambdas[2] )
            self.assertAlmostEqual( 4., chunk.constants[0].lambdas[3] )
            self.assertAlmostEqual( 5., chunk.constants[0].lambdas[4] )
            self.assertAlmostEqual( 6., chunk.constants[0].lambdas[5] )
            self.assertAlmostEqual( 1., chunk.constants[0].decay_constants[0] )
            self.assertAlmostEqual( 2., chunk.constants[0].decay_constants[1] )
            self.assertAlmostEqual( 3., chunk.constants[0].decay_constants[2] )
            self.assertAlmostEqual( 4., chunk.constants[0].decay_constants[3] )
            self.assertAlmostEqual( 5., chunk.constants[0].decay_constants[4] )
            self.assertAlmostEqual( 6., chunk.constants[0].decay_constants[5] )

            self.assertEqual( 6, len( chunk.constants[1].lambdas ) )
            self.assertEqual( 6, len( chunk.constants[1].decay_constants ) )
            self.assertAlmostEqual( 6., chunk.constants[1].lambdas[0] )
            self.assertAlmostEqual( 5., chunk.constants[1].lambdas[1] )
            self.assertAlmostEqual( 4., chunk.constants[1].lambdas[2] )
            self.assertAlmostEqual( 3., chunk.constants[1].lambdas[3] )
            self.assertAlmostEqual( 2., chunk.constants[1].lambdas[4] )
            self.assertAlmostEqual( 1., chunk.constants[1].lambdas[5] )
            self.assertAlmostEqual( 6., chunk.constants[1].decay_constants[0] )
            self.assertAlmostEqual( 5., chunk.constants[1].decay_constants[1] )
            self.assertAlmostEqual( 4., chunk.constants[1].decay_constants[2] )
            self.assertAlmostEqual( 3., chunk.constants[1].decay_constants[3] )
            self.assertAlmostEqual( 2., chunk.constants[1].decay_constants[4] )
            self.assertAlmostEqual( 1., chunk.constants[1].decay_constants[5] )

            self.assertEqual( 6, len( chunk.constants[0].alphas ) )
            self.assertEqual( 6, len( chunk.constants[0].abundances ) )
            self.assertAlmostEqual( 1.1, chunk.constants[0].alphas[0] )
            self.assertAlmostEqual( 2.1, chunk.constants[0].alphas[1] )
            self.assertAlmostEqual( 3.1, chunk.constants[0].alphas[2] )
            self.assertAlmostEqual( 4.1, chunk.constants[0].alphas[3] )
            self.assertAlmostEqual( 5.1, chunk.constants[0].alphas[4] )
            self.assertAlmostEqual( 6.1, chunk.constants[0].alphas[5] )
            self.assertAlmostEqual( 1.1, chunk.constants[0].abundances[0] )
            self.assertAlmostEqual( 2.1, chunk.constants[0].abundances[1] )
            self.assertAlmostEqual( 3.1, chunk.constants[0].abundances[2] )
            self.assertAlmostEqual( 4.1, chunk.constants[0].abundances[3] )
            self.assertAlmostEqual( 5.1, chunk.constants[0].abundances[4] )
            self.assertAlmostEqual( 6.1, chunk.constants[0].abundances[5] )

            self.assertEqual( 6, len( chunk.constants[1].alphas ) )
            self.assertEqual( 6, len( chunk.constants[1].abundances ) )
            self.assertAlmostEqual( 6.1, chunk.constants[1].alphas[0] )
            self.assertAlmostEqual( 5.1, chunk.constants[1].alphas[1] )
            self.assertAlmostEqual( 4.1, chunk.constants[1].alphas[2] )
            self.assertAlmostEqual( 3.1, chunk.constants[1].alphas[3] )
            self.assertAlmostEqual( 2.1, chunk.constants[1].alphas[4] )
            self.assertAlmostEqual( 1.1, chunk.constants[1].alphas[5] )
            self.assertAlmostEqual( 6.1, chunk.constants[1].abundances[0] )
            self.assertAlmostEqual( 5.1, chunk.constants[1].abundances[1] )
            self.assertAlmostEqual( 4.1, chunk.constants[1].abundances[2] )
            self.assertAlmostEqual( 3.1, chunk.constants[1].abundances[3] )
            self.assertAlmostEqual( 2.1, chunk.constants[1].abundances[4] )
            self.assertAlmostEqual( 1.1, chunk.constants[1].abundances[5] )

            self.assertEqual( 8, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 455 ) )

        # the data is given explicitly
        chunk = EnergyDependentConstants(
                    boundaries = [ 2 ], interpolants = [ 4 ],
                    constants = [ DecayConstants( 1e-5, [ 1., 2., 3., 4., 5., 6. ],
                                                  [ 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 ] ),
                                  DecayConstants( 2e+7, [ 6., 5., 4., 3., 2., 1. ],
                                                  [ 6.1, 5.1, 4.1, 3.1, 2.1, 1.1 ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = EnergyDependentConstants.from_string( self.chunk, 9228, 1, 455 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = EnergyDependentConstants( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = EnergyDependentConstants(
                        boundaries = [ 1 ], interpolants = [ 4 ],
                        constants = [ DecayConstants( 1e-5, [ 1., 2., 3., 4., 5., 6. ],
                                                      [ 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 ] ),
                                      DecayConstants( 2e+7, [ 6., 5., 4., 3., 2., 1. ],
                                                      [ 6.1, 5.1, 4.1, 3.1, 2.1, 1.1 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = EnergyDependentConstants.from_string( self.oddNPL, 9228, 1, 455 )

        with self.assertRaises( Exception ) :

            chunk = EnergyDependentConstants.from_string( self.inconsistentNNF, 9228, 1, 455 )

if __name__ == '__main__' :

    unittest.main()
