# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT458 import ThermalPointComponents

class Test_ENDFtk_MF1_ThermalPointComponents( unittest.TestCase ) :
    """Unit test for the ThermalPointComponents class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0         18          99228 1458     \n'
              ' 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n'
              ' 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n'
              ' 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0         19          99228 1458     \n'
                ' 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n'
                ' 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n'
                ' 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n'
                ' 1.000000+6                                                       9228 1458     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.LFC )
            self.assertEqual( False, chunk.tabulated_energy_release )
            self.assertEqual( 0, chunk.NPLY )
            self.assertEqual( 0, chunk.order )
            self.assertEqual( 0, chunk.NFC )
            self.assertEqual( 0, chunk.number_tabulated_components )

            self.assertEqual( 9, len( chunk.E ) )
            self.assertEqual( 9, len( chunk.energy_release ) )

            self.assertEqual( 1.691300e+8, chunk.E[0][0] )
            self.assertEqual( 4.838000e+6, chunk.E[1][0] )
            self.assertEqual( 7.400000e+3, chunk.E[2][0] )
            self.assertEqual( 6.600000e+6, chunk.E[3][0] )
            self.assertEqual( 6.330000e+6, chunk.E[4][0] )
            self.assertEqual( 6.500000e+6, chunk.E[5][0] )
            self.assertEqual( 8.750000e+6, chunk.E[6][0] )
            self.assertEqual( 1.934054e+8, chunk.E[7][0] )
            self.assertEqual( 2.021554e+8, chunk.E[8][0] )

            self.assertEqual( 4.900000e+5, chunk.E[0][1] )
            self.assertEqual( 7.000000e+4, chunk.E[1][1] )
            self.assertEqual( 1.110000e+3, chunk.E[2][1] )
            self.assertEqual( 5.000000e+5, chunk.E[3][1] )
            self.assertEqual( 5.000000e+4, chunk.E[4][1] )
            self.assertEqual( 5.100000e+4, chunk.E[5][1] )
            self.assertEqual( 7.000000e+4, chunk.E[6][1] )
            self.assertEqual( 1.500000e+5, chunk.E[7][1] )
            self.assertEqual( 1.300000e+5, chunk.E[8][1] )

            self.assertEqual( 1.691300e+8, chunk.energy_release[0][0] )
            self.assertEqual( 4.838000e+6, chunk.energy_release[1][0] )
            self.assertEqual( 7.400000e+3, chunk.energy_release[2][0] )
            self.assertEqual( 6.600000e+6, chunk.energy_release[3][0] )
            self.assertEqual( 6.330000e+6, chunk.energy_release[4][0] )
            self.assertEqual( 6.500000e+6, chunk.energy_release[5][0] )
            self.assertEqual( 8.750000e+6, chunk.energy_release[6][0] )
            self.assertEqual( 1.934054e+8, chunk.energy_release[7][0] )
            self.assertEqual( 2.021554e+8, chunk.energy_release[8][0] )

            self.assertEqual( 4.900000e+5, chunk.energy_release[0][1] )
            self.assertEqual( 7.000000e+4, chunk.energy_release[1][1] )
            self.assertEqual( 1.110000e+3, chunk.energy_release[2][1] )
            self.assertEqual( 5.000000e+5, chunk.energy_release[3][1] )
            self.assertEqual( 5.000000e+4, chunk.energy_release[4][1] )
            self.assertEqual( 5.100000e+4, chunk.energy_release[5][1] )
            self.assertEqual( 7.000000e+4, chunk.energy_release[6][1] )
            self.assertEqual( 1.500000e+5, chunk.energy_release[7][1] )
            self.assertEqual( 1.300000e+5, chunk.energy_release[8][1] )

            self.assertEqual( 1.691300e+8, chunk.EFR[0] )
            self.assertEqual( 4.838000e+6, chunk.ENP[0] )
            self.assertEqual( 7.400000e+3, chunk.END[0] )
            self.assertEqual( 6.600000e+6, chunk.EGP[0] )
            self.assertEqual( 6.330000e+6, chunk.EGD[0] )
            self.assertEqual( 6.500000e+6, chunk.EB[0] )
            self.assertEqual( 8.750000e+6, chunk.ENU[0] )
            self.assertEqual( 1.934054e+8, chunk.ER[0] )
            self.assertEqual( 2.021554e+8, chunk.ET[0] )

            self.assertEqual( 4.900000e+5, chunk.EFR[1] )
            self.assertEqual( 7.000000e+4, chunk.ENP[1] )
            self.assertEqual( 1.110000e+3, chunk.END[1] )
            self.assertEqual( 5.000000e+5, chunk.EGP[1] )
            self.assertEqual( 5.000000e+4, chunk.EGD[1] )
            self.assertEqual( 5.100000e+4, chunk.EB[1] )
            self.assertEqual( 7.000000e+4, chunk.ENU[1] )
            self.assertEqual( 1.500000e+5, chunk.ER[1] )
            self.assertEqual( 1.300000e+5, chunk.ET[1] )

            self.assertEqual( 1.691300e+8, chunk.fission_fragments[0] )
            self.assertEqual( 4.838000e+6, chunk.prompt_neutrons[0] )
            self.assertEqual( 7.400000e+3, chunk.delayed_neutrons[0] )
            self.assertEqual( 6.600000e+6, chunk.prompt_gammas[0] )
            self.assertEqual( 6.330000e+6, chunk.delayed_gammas[0] )
            self.assertEqual( 6.500000e+6, chunk.delayed_betas[0] )
            self.assertEqual( 8.750000e+6, chunk.neutrinos[0] )
            self.assertEqual( 1.934054e+8, chunk.total_minus_neutrinos[0] )
            self.assertEqual( 2.021554e+8, chunk.total[0] )

            self.assertEqual( 4.900000e+5, chunk.fission_fragments[1] )
            self.assertEqual( 7.000000e+4, chunk.prompt_neutrons[1] )
            self.assertEqual( 1.110000e+3, chunk.delayed_neutrons[1] )
            self.assertEqual( 5.000000e+5, chunk.prompt_gammas[1] )
            self.assertEqual( 5.000000e+4, chunk.delayed_gammas[1] )
            self.assertEqual( 5.100000e+4, chunk.delayed_betas[1] )
            self.assertEqual( 7.000000e+4, chunk.neutrinos[1] )
            self.assertEqual( 1.500000e+5, chunk.total_minus_neutrinos[1] )
            self.assertEqual( 1.300000e+5, chunk.total[1] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 458 ) )

        # the data is given explicitly
        chunk = ThermalPointComponents( efr = [ 1.691300e+8, 4.900000e+5 ],
                                        enp = [ 4.838000e+6, 7.000000e+4 ],
                                        end = [ 7.400000e+3, 1.110000e+3 ],
                                        egp = [ 6.600000e+6, 5.000000e+5 ],
                                        egd = [ 6.330000e+6, 5.000000e+4 ],
                                        eb = [ 6.500000e+6, 5.100000e+4 ],
                                        enu = [ 8.750000e+6, 7.000000e+4 ],
                                        er = [ 1.934054e+8, 1.500000e+5 ],
                                        et = [ 2.021554e+8, 1.300000e+5 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ThermalPointComponents.from_string( self.chunk, 9228, 1, 458 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ThermalPointComponents( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = ThermalPointComponents.from_string( self.invalid, 9228, 1, 458 )

if __name__ == '__main__' :

    unittest.main()
