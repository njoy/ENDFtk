# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import ChargedParticleElasticScattering
from ENDFtk.MF6.LAW5 import LegendreCoefficients
from ENDFtk.MF6.LAW5 import NuclearPlusInterference
from ENDFtk.MF6.LAW5 import NuclearAmplitudeExpansion

class Test_ENDFtk_MF6_ChargedParticleElasticScattering( unittest.TestCase ) :
    """Unit test for the ChargedParticleElasticScattering class."""

    chunk = ( ' 5.000000-1 0.000000+0          1          0          1          29228 6  5     \n'
              '          2          1                                            9228 6  5     \n'
              ' 0.000000+0 1.000000-5          1          0         12          39228 6  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
              ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
              ' 0.000000+0 2.000000+7         15          0          6          39228 6  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n' )

    invalid = ( ' 5.000000-1 0.000000+0          1          0          1          29228 6  5     \n'
                '          2          1                                            9228 6  5     \n'
                ' 0.000000+0 1.000000-5          0          0         12          39228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
                ' 0.000000+0 2.000000+7         15          0          6          39228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 5, chunk.LAW )
            self.assertAlmostEqual( 0.5, chunk.SPI )
            self.assertAlmostEqual( 0.5, chunk.spin )
            self.assertEqual( True, chunk.LIDP )
            self.assertEqual( True, chunk.identical_particles )
            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 2, chunk.number_incident_energies )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 1, chunk.INT[0] )
            self.assertEqual( 2, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )

            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertAlmostEqual( 1e-5, chunk.E[0] )
            self.assertAlmostEqual( 2e+7, chunk.E[1] )
            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 2e+7, chunk.incident_energies[1] )

            energies = chunk.distributions
            self.assertEqual( True, isinstance( energies[0], NuclearAmplitudeExpansion ) )
            self.assertEqual( True, isinstance( energies[1], NuclearPlusInterference ) )

            subsection1 = energies[0]
            self.assertAlmostEqual( 1e-5, subsection1.E )
            self.assertAlmostEqual( 1e-5, subsection1.incident_energy )
            self.assertEqual( 1, subsection1.LTP )
            self.assertEqual( 12, subsection1.NW )
            self.assertEqual( 3, subsection1.NL )
            self.assertEqual( 4, len( subsection1.B ) )
            self.assertEqual( 4, len( subsection1.scattering_coefficients ) )
            self.assertAlmostEqual( 1., subsection1.B[0] )
            self.assertAlmostEqual( 2., subsection1.B[1] )
            self.assertAlmostEqual( 3., subsection1.B[2] )
            self.assertAlmostEqual( 4., subsection1.B[3] )
            self.assertAlmostEqual( 1., subsection1.scattering_coefficients[0] )
            self.assertAlmostEqual( 2., subsection1.scattering_coefficients[1] )
            self.assertAlmostEqual( 3., subsection1.scattering_coefficients[2] )
            self.assertAlmostEqual( 4., subsection1.scattering_coefficients[3] )
            self.assertEqual( 4, len( subsection1.AR ) )
            self.assertEqual( 4, len( subsection1.real_interference_coefficients ) )
            self.assertAlmostEqual( 5., subsection1.AR[0] )
            self.assertAlmostEqual( 7., subsection1.AR[1] )
            self.assertAlmostEqual( 9., subsection1.AR[2] )
            self.assertAlmostEqual( 11., subsection1.AR[3] )
            self.assertAlmostEqual( 5., subsection1.real_interference_coefficients[0] )
            self.assertAlmostEqual( 7., subsection1.real_interference_coefficients[1] )
            self.assertAlmostEqual( 9., subsection1.real_interference_coefficients[2] )
            self.assertAlmostEqual( 11., subsection1.real_interference_coefficients[3] )
            self.assertEqual( 4, len( subsection1.AI ) )
            self.assertEqual( 4, len( subsection1.imaginary_interference_coefficients ) )
            self.assertAlmostEqual( 6., subsection1.AI[0] )
            self.assertAlmostEqual( 8., subsection1.AI[1] )
            self.assertAlmostEqual( 10., subsection1.AI[2] )
            self.assertAlmostEqual( 12., subsection1.AI[3] )
            self.assertAlmostEqual( 6., subsection1.imaginary_interference_coefficients[0] )
            self.assertAlmostEqual( 8., subsection1.imaginary_interference_coefficients[1] )
            self.assertAlmostEqual( 10., subsection1.imaginary_interference_coefficients[2] )
            self.assertAlmostEqual( 12., subsection1.imaginary_interference_coefficients[3] )
            self.assertEqual( 4, len( subsection1.A ) )
            self.assertEqual( 4, len( subsection1.interference_coefficients ) )
            self.assertAlmostEqual( 5.+6.j, subsection1.A[0] )
            self.assertAlmostEqual( 7.+8.j, subsection1.A[1] )
            self.assertAlmostEqual( 9.+10.j, subsection1.A[2] )
            self.assertAlmostEqual( 11.+12.j, subsection1.A[3] )
            self.assertAlmostEqual( 5.+6.j, subsection1.interference_coefficients[0] )
            self.assertAlmostEqual( 7.+8.j, subsection1.interference_coefficients[1] )
            self.assertAlmostEqual( 9.+10.j, subsection1.interference_coefficients[2] )
            self.assertAlmostEqual( 11.+12.j, subsection1.interference_coefficients[3] )

            subsection2 = energies[1]
            self.assertAlmostEqual( 2e+7, subsection2.E )
            self.assertAlmostEqual( 2e+7, subsection2.incident_energy )
            self.assertEqual( 15, subsection2.LTP )
            self.assertEqual( 6, subsection2.NW )
            self.assertEqual( 3, subsection2.NL )
            self.assertEqual( 3, len( subsection2.MU ) )
            self.assertEqual( 3, len( subsection2.cosines ) )
            self.assertAlmostEqual( 1., subsection2.MU[0] )
            self.assertAlmostEqual( 3., subsection2.MU[1] )
            self.assertAlmostEqual( 5., subsection2.MU[2] )
            self.assertAlmostEqual( 1., subsection2.cosines[0] )
            self.assertAlmostEqual( 3., subsection2.cosines[1] )
            self.assertAlmostEqual( 5., subsection2.cosines[2] )
            self.assertEqual( 3, len( subsection2.PNI ) )
            self.assertEqual( 3, len( subsection2.probabilities ) )
            self.assertAlmostEqual( 2., subsection2.PNI[0] )
            self.assertAlmostEqual( 4., subsection2.PNI[1] )
            self.assertAlmostEqual( 6., subsection2.PNI[2] )
            self.assertAlmostEqual( 2., subsection2.probabilities[0] )
            self.assertAlmostEqual( 4., subsection2.probabilities[1] )
            self.assertAlmostEqual( 6., subsection2.probabilities[2] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = ChargedParticleElasticScattering(
                    spin = 0.5, lidp = 1,
                    boundaries = [ 2 ], interpolants = [ 1 ],
                    distributions = [
                        NuclearAmplitudeExpansion( 1e-5, 3, [ 1., 2., 3., 4. ],
                                                            [ 5. + 6.j, 7. + 8.j,
                                                              9. + 10.j, 11. + 12.j ] ),
                        NuclearPlusInterference( 2e+7, 15, [1., 3., 5. ], [ 2., 4., 6.] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ChargedParticleElasticScattering.from_string( self.chunk, 9228, 6, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ChargedParticleElasticScattering( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = ChargedParticleElasticScattering(
                        spin = 0.5, lidp = 1,
                        boundaries = [ 2,4 ], interpolants = [ 1 ],
                        distributions = [
                            NuclearAmplitudeExpansion( 1e-5, 3, [ 1., 2., 3., 4. ],
                                                                [ 5. + 6.j, 7. + 8.j,
                                                                  9. + 10.j, 11. + 12.j ] ),
                            NuclearPlusInterference( 2e+7, 15, [1., 3., 5. ], [ 2., 4., 6.] ) ] )

        with self.assertRaises( Exception ) :

            chunk = ChargedParticleElasticScattering.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
