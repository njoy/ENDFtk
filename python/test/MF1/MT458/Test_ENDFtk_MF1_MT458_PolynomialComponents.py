# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT458 import PolynomialComponents

class Test_ENDFtk_MF1_PolynomialComponents( unittest.TestCase ) :
    """Unit test for the PolynomialComponents class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          1         36         189228 1458     \n'
              ' 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n'
              ' 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n'
              ' 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n'
              '-2.660000-1 2.660000-2 3.004000-1 3.004000-2 0.000000+0 0.000000+09228 1458     \n'
              ' 7.770000-2 7.770000-3-7.500000-2 7.600000-3-7.700000-2 7.800000-39228 1458     \n'
              '-1.000000-1 1.000000-2-3.790000-2 3.790000-3-1.379000-1 1.379000-29228 1458     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          1         37         189228 1458     \n'
                ' 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n'
                ' 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n'
                ' 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n'
                '-2.660000-1 2.660000-2 3.004000-1 3.004000-2 0.000000+0 0.000000+09228 1458     \n'
                ' 7.770000-2 7.770000-3-7.500000-2 7.600000-3-7.700000-2 7.800000-39228 1458     \n'
                '-1.000000-1 1.000000-2-3.790000-2 3.790000-3-1.379000-1 1.379000-29228 1458     \n'
                ' 1.000000+6                                                       9228 1458     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.LFC )
            self.assertEqual( False, chunk.tabulated_energy_release )
            self.assertEqual( 1, chunk.NPLY )
            self.assertEqual( 1, chunk.order )
            self.assertEqual( 0, chunk.NFC )
            self.assertEqual( 0, chunk.number_tabulated_components )

            self.assertEqual( 9, len( chunk.E ) )
            self.assertEqual( 9, len( chunk.energy_release ) )

            #self.assertAlmostEqual( 1.691300e+8, chunk.E[0][0][0] )
            #self.assertAlmostEqual( 4.838000e+6, chunk.E[1][0][0] )
            #self.assertAlmostEqual( 7.400000e+3, chunk.E[2][0][0] )
            #self.assertAlmostEqual( 6.600000e+6, chunk.E[3][0][0] )
            #self.assertAlmostEqual( 6.330000e+6, chunk.E[4][0][0] )
            #self.assertAlmostEqual( 6.500000e+6, chunk.E[5][0][0] )
            #self.assertAlmostEqual( 8.750000e+6, chunk.E[6][0][0] )
            #self.assertAlmostEqual( 1.934054e+8, chunk.E[7][0][0] )
            #self.assertAlmostEqual( 2.021554e+8, chunk.E[8][0][0] )

            #self.assertAlmostEqual( 4.900000e+5, chunk.E[0][0][1] )
            #self.assertAlmostEqual( 7.000000e+4, chunk.E[1][0][1] )
            #self.assertAlmostEqual( 1.110000e+3, chunk.E[2][0][1] )
            #self.assertAlmostEqual( 5.000000e+5, chunk.E[3][0][1] )
            #self.assertAlmostEqual( 5.000000e+4, chunk.E[4][0][1] )
            #self.assertAlmostEqual( 5.100000e+4, chunk.E[5][0][1] )
            #self.assertAlmostEqual( 7.000000e+4, chunk.E[6][0][1] )
            #self.assertAlmostEqual( 1.500000e+5, chunk.E[7][0][1] )
            #self.assertAlmostEqual( 1.300000e+5, chunk.E[8][0][1] )

            #self.assertAlmostEqual( 1.691300e+8, chunk.energy_release[0][0][0] )
            #self.assertAlmostEqual( 4.838000e+6, chunk.energy_release[1][0][0] )
            #self.assertAlmostEqual( 7.400000e+3, chunk.energy_release[2][0][0] )
            #self.assertAlmostEqual( 6.600000e+6, chunk.energy_release[3][0][0] )
            #self.assertAlmostEqual( 6.330000e+6, chunk.energy_release[4][0][0] )
            #self.assertAlmostEqual( 6.500000e+6, chunk.energy_release[5][0][0] )
            #self.assertAlmostEqual( 8.750000e+6, chunk.energy_release[6][0][0] )
            #self.assertAlmostEqual( 1.934054e+8, chunk.energy_release[7][0][0] )
            #self.assertAlmostEqual( 2.021554e+8, chunk.energy_release[8][0][0] )

            #self.assertAlmostEqual( 4.900000e+5, chunk.energy_release[0][0][1] )
            #self.assertAlmostEqual( 7.000000e+4, chunk.energy_release[1][0][1] )
            #self.assertAlmostEqual( 1.110000e+3, chunk.energy_release[2][0][1] )
            #self.assertAlmostEqual( 5.000000e+5, chunk.energy_release[3][0][1] )
            #self.assertAlmostEqual( 5.000000e+4, chunk.energy_release[4][0][1] )
            #self.assertAlmostEqual( 5.100000e+4, chunk.energy_release[5][0][1] )
            #self.assertAlmostEqual( 7.000000e+4, chunk.energy_release[6][0][1] )
            #self.assertAlmostEqual( 1.500000e+5, chunk.energy_release[7][0][1] )
            #self.assertAlmostEqual( 1.300000e+5, chunk.energy_release[8][0][1] )

            #self.assertAlmostEqual( -2.660000e-1, chunk.E[0][1][0] )
            #self.assertAlmostEqual( 3.004000e-1,  chunk.E[1][1][0] )
            #self.assertAlmostEqual( 0.0, chunk.E[2][1][0] )
            #self.assertAlmostEqual( 7.770000e-2,  chunk.E[3][1][0] )
            #self.assertAlmostEqual( -7.500000e-2, chunk.E[4][1][0] )
            #self.assertAlmostEqual( -7.700000e-2, chunk.E[5][1][0] )
            #self.assertAlmostEqual( -1.000000e-1, chunk.E[6][1][0] )
            #self.assertAlmostEqual( -3.790000e-2, chunk.E[7][1][0] )
            #self.assertAlmostEqual( -1.379000e-1, chunk.E[8][1][0] )

            #self.assertAlmostEqual( 2.660000e-2, chunk.E[0][1][1] )
            #self.assertAlmostEqual( 3.004000e-2, chunk.E[1][1][1] )
            #self.assertAlmostEqual( 0.0, chunk.E[2][1][1] )
            #self.assertAlmostEqual( 7.770000e-3, chunk.E[3][1][1] )
            #self.assertAlmostEqual( 7.600000e-3, chunk.E[4][1][1] )
            #self.assertAlmostEqual( 7.800000e-3, chunk.E[5][1][1] )
            #self.assertAlmostEqual( 1.000000e-2, chunk.E[6][1][1] )
            #self.assertAlmostEqual( 3.790000e-3, chunk.E[7][1][1] )
            #self.assertAlmostEqual( 1.379000e-2, chunk.E[8][1][1] )

            #self.assertAlmostEqual( -2.660000e-1, chunk.energy_release[0][1][0] )
            #self.assertAlmostEqual( 3.004000e-1,  chunk.energy_release[1][1][0] )
            #self.assertAlmostEqual( 0.0, chunk.energy_release[2][1][0] )
            #self.assertAlmostEqual( 7.770000e-2,  chunk.energy_release[3][1][0] )
            #self.assertAlmostEqual( -7.500000e-2, chunk.energy_release[4][1][0] )
            #self.assertAlmostEqual( -7.700000e-2, chunk.energy_release[5][1][0] )
            #self.assertAlmostEqual( -1.000000e-1, chunk.energy_release[6][1][0] )
            #self.assertAlmostEqual( -3.790000e-2, chunk.energy_release[7][1][0] )
            #self.assertAlmostEqual( -1.379000e-1, chunk.energy_release[8][1][0] )

            #self.assertAlmostEqual( 2.660000e-2, chunk.energy_release[0][1][1] )
            #self.assertAlmostEqual( 3.004000e-2, chunk.energy_release[1][1][1] )
            #self.assertAlmostEqual( 0.0, chunk.energy_release[2][1][1] )
            #self.assertAlmostEqual( 7.770000e-3, chunk.energy_release[3][1][1] )
            #self.assertAlmostEqual( 7.600000e-3, chunk.energy_release[4][1][1] )
            #self.assertAlmostEqual( 7.800000e-3, chunk.energy_release[5][1][1] )
            #self.assertAlmostEqual( 1.000000e-2, chunk.energy_release[6][1][1] )
            #self.assertAlmostEqual( 3.790000e-3, chunk.energy_release[7][1][1] )
            #self.assertAlmostEqual( 1.379000e-2, chunk.energy_release[8][1][1] )

            self.assertAlmostEqual( 1.691300e+8, chunk.EFR[0][0] )
            self.assertAlmostEqual( 4.838000e+6, chunk.ENP[0][0] )
            self.assertAlmostEqual( 7.400000e+3, chunk.END[0][0] )
            self.assertAlmostEqual( 6.600000e+6, chunk.EGP[0][0] )
            self.assertAlmostEqual( 6.330000e+6, chunk.EGD[0][0] )
            self.assertAlmostEqual( 6.500000e+6, chunk.EB[0][0] )
            self.assertAlmostEqual( 8.750000e+6, chunk.ENU[0][0] )
            self.assertAlmostEqual( 1.934054e+8, chunk.ER[0][0] )
            self.assertAlmostEqual( 2.021554e+8, chunk.ET[0][0] )

            self.assertAlmostEqual( 4.900000e+5, chunk.EFR[0][1] )
            self.assertAlmostEqual( 7.000000e+4, chunk.ENP[0][1] )
            self.assertAlmostEqual( 1.110000e+3, chunk.END[0][1] )
            self.assertAlmostEqual( 5.000000e+5, chunk.EGP[0][1] )
            self.assertAlmostEqual( 5.000000e+4, chunk.EGD[0][1] )
            self.assertAlmostEqual( 5.100000e+4, chunk.EB[0][1] )
            self.assertAlmostEqual( 7.000000e+4, chunk.ENU[0][1] )
            self.assertAlmostEqual( 1.500000e+5, chunk.ER[0][1] )
            self.assertAlmostEqual( 1.300000e+5, chunk.ET[0][1] )

            self.assertAlmostEqual( 1.691300e+8, chunk.fission_fragments[0][0] )
            self.assertAlmostEqual( 4.838000e+6, chunk.prompt_neutrons[0][0] )
            self.assertAlmostEqual( 7.400000e+3, chunk.delayed_neutrons[0][0] )
            self.assertAlmostEqual( 6.600000e+6, chunk.prompt_gammas[0][0] )
            self.assertAlmostEqual( 6.330000e+6, chunk.delayed_gammas[0][0] )
            self.assertAlmostEqual( 6.500000e+6, chunk.delayed_betas[0][0] )
            self.assertAlmostEqual( 8.750000e+6, chunk.neutrinos[0][0] )
            self.assertAlmostEqual( 1.934054e+8, chunk.total_minus_neutrinos[0][0] )
            self.assertAlmostEqual( 2.021554e+8, chunk.total[0][0] )

            self.assertAlmostEqual( 4.900000e+5, chunk.fission_fragments[0][1] )
            self.assertAlmostEqual( 7.000000e+4, chunk.prompt_neutrons[0][1] )
            self.assertAlmostEqual( 1.110000e+3, chunk.delayed_neutrons[0][1] )
            self.assertAlmostEqual( 5.000000e+5, chunk.prompt_gammas[0][1] )
            self.assertAlmostEqual( 5.000000e+4, chunk.delayed_gammas[0][1] )
            self.assertAlmostEqual( 5.100000e+4, chunk.delayed_betas[0][1] )
            self.assertAlmostEqual( 7.000000e+4, chunk.neutrinos[0][1] )
            self.assertAlmostEqual( 1.500000e+5, chunk.total_minus_neutrinos[0][1] )
            self.assertAlmostEqual( 1.300000e+5, chunk.total[0][1] )

            self.assertAlmostEqual( -2.660000e-1, chunk.EFR[1][0] )
            self.assertAlmostEqual( 3.004000e-1,  chunk.ENP[1][0] )
            self.assertAlmostEqual( 0.0, chunk.END[1][0] )
            self.assertAlmostEqual( 7.770000e-2,  chunk.EGP[1][0] )
            self.assertAlmostEqual( -7.500000e-2, chunk.EGD[1][0] )
            self.assertAlmostEqual( -7.700000e-2, chunk.EB[1][0] )
            self.assertAlmostEqual( -1.000000e-1, chunk.ENU[1][0] )
            self.assertAlmostEqual( -3.790000e-2, chunk.ER[1][0] )
            self.assertAlmostEqual( -1.379000e-1, chunk.ET[1][0] )

            self.assertAlmostEqual( 2.660000e-2, chunk.EFR[1][1] )
            self.assertAlmostEqual( 3.004000e-2, chunk.ENP[1][1] )
            self.assertAlmostEqual( 0.0, chunk.END[1][1] )
            self.assertAlmostEqual( 7.770000e-3, chunk.EGP[1][1] )
            self.assertAlmostEqual( 7.600000e-3, chunk.EGD[1][1] )
            self.assertAlmostEqual( 7.800000e-3, chunk.EB[1][1] )
            self.assertAlmostEqual( 1.000000e-2, chunk.ENU[1][1] )
            self.assertAlmostEqual( 3.790000e-3, chunk.ER[1][1] )
            self.assertAlmostEqual( 1.379000e-2, chunk.ET[1][1] )

            self.assertAlmostEqual( -2.660000e-1, chunk.fission_fragments[1][0] )
            self.assertAlmostEqual( 3.004000e-1,  chunk.prompt_neutrons[1][0] )
            self.assertAlmostEqual( 0.0, chunk.delayed_neutrons[1][0] )
            self.assertAlmostEqual( 7.770000e-2,  chunk.prompt_gammas[1][0] )
            self.assertAlmostEqual( -7.500000e-2, chunk.delayed_gammas[1][0] )
            self.assertAlmostEqual( -7.700000e-2, chunk.delayed_betas[1][0] )
            self.assertAlmostEqual( -1.000000e-1, chunk.neutrinos[1][0] )
            self.assertAlmostEqual( -3.790000e-2, chunk.total_minus_neutrinos[1][0] )
            self.assertAlmostEqual( -1.379000e-1, chunk.total[1][0] )

            self.assertAlmostEqual( 2.660000e-2, chunk.fission_fragments[1][1] )
            self.assertAlmostEqual( 3.004000e-2, chunk.prompt_neutrons[1][1] )
            self.assertAlmostEqual( 0.0, chunk.delayed_neutrons[1][1] )
            self.assertAlmostEqual( 7.770000e-3, chunk.prompt_gammas[1][1] )
            self.assertAlmostEqual( 7.600000e-3, chunk.delayed_gammas[1][1] )
            self.assertAlmostEqual( 7.800000e-3, chunk.delayed_betas[1][1] )
            self.assertAlmostEqual( 1.000000e-2, chunk.neutrinos[1][1] )
            self.assertAlmostEqual( 3.790000e-3, chunk.total_minus_neutrinos[1][1] )
            self.assertAlmostEqual( 1.379000e-2, chunk.total[1][1] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 458 ) )

        # the data is given explicitly
        chunk = PolynomialComponents( efr = [ [ 1.691300e+8, 4.900000e+5 ], [ -2.66e-1, 2.66e-2 ] ],
                                      enp = [ [ 4.838000e+6, 7.000000e+4 ], [ 3.004e-1, 3.004e-2 ] ],
                                      end = [ [ 7.400000e+3, 1.110000e+3 ], [ 0., 0. ] ],
                                      egp = [ [ 6.600000e+6, 5.000000e+5 ], [ 7.77e-2, 7.77e-3 ] ],
                                      egd = [ [ 6.330000e+6, 5.000000e+4 ], [ -7.500e-2, 7.600e-3 ] ],
                                      eb  = [ [ 6.500000e+6, 5.100000e+4 ], [ -7.700e-2, 7.800e-3 ] ],
                                      enu = [ [ 8.750000e+6, 7.000000e+4 ], [ -1.00e-1, 1.00e-2 ] ],
                                      er  = [ [ 1.934054e+8, 1.500000e+5 ], [ -3.790e-2, 3.790e-3 ] ],
                                      et  = [ [ 2.021554e+8, 1.300000e+5 ], [ -1.379e-1, 1.379e-2 ] ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = PolynomialComponents.from_string( self.chunk, 9228, 1, 458 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = PolynomialComponents( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # inconsistent sizes
        with self.assertRaises( Exception ) :

            chunk = PolynomialComponents( efr = [ [ -2.66e-1, 2.66e-2 ] ],
                                          enp = [ [ 4.838000e+6, 7.000000e+4 ], [ 3.004e-1, 3.004e-2 ] ],
                                          end = [ [ 7.400000e+3, 1.110000e+3 ], [ 0., 0. ] ],
                                          egp = [ [ 6.600000e+6, 5.000000e+5 ], [ 7.77e-2, 7.77e-3 ] ],
                                          egd = [ [ 6.330000e+6, 5.000000e+4 ], [ -7.500e-2, 7.600e-3 ] ],
                                          eb  = [ [ 6.500000e+6, 5.100000e+4 ], [ -7.700e-2, 7.800e-3 ] ],
                                          enu = [ [ 8.750000e+6, 7.000000e+4 ], [ -1.00e-1, 1.00e-2 ] ],
                                          er  = [ [ 1.934054e+8, 1.500000e+5 ], [ -3.790e-2, 3.790e-3 ] ],
                                          et  = [ [ 2.021554e+8, 1.300000e+5 ], [ -1.379e-1, 1.379e-2 ] ] )

        with self.assertRaises( Exception ) :

            chunk = PolynomialComponents.from_string( self.invalid, 9228, 1, 458 )

if __name__ == '__main__' :

    unittest.main()
