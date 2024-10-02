# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF14 import IsotropicDiscretePhoton
from ENDFtk.MF14 import LegendreCoefficients
from ENDFtk.MF14 import TabulatedDistribution
from ENDFtk.MF14 import LegendreDistributions
from ENDFtk.MF14 import TabulatedDistributions
from ENDFtk.MF14 import Section
from ENDFtk.tree import Tape

class Test_ENDFtk_MF14_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk_LTT0 = ( ' 9.223500+4 2.330248+2          1          0          2          0922814  2     \n' )

    chunk_LTT1 = ( ' 9.223500+4 2.330248+2          0          1          2          1922814  2     \n'
                   ' 1.500000+6 2.000000+6          0          0          0          0922814  2     \n'
                   ' 4.438900+6 4.438900+6          0          0          1          2922814  2     \n'
                   '          2          3                                            922814  2     \n'
                   ' 0.000000+0 4.812998+6          0          0          2          0922814  2     \n'
                   ' 0.000000+0 4.076000-2                                            922814  2     \n'
                   ' 0.000000+0 1.500000+8          0          0          2          0922814  2     \n'
                   ' 0.000000+0 0.000000+0                                            922814  2     \n' )

    invalid = ( ' 9.223500+4 2.330250+2          0          4          1          0922814  2     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  922814  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9228 3  1     \n'

    def test_section( self ) :

        def verify_chunk_LTT0( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.MT )
            self.assertEqual( 2, chunk.section_number )

            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 2.330248e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330248e+2, chunk.atomic_weight_ratio )

            self.assertEqual( 0, chunk.NI )
            self.assertEqual( 0, chunk.number_isotropic_photons )
            self.assertEqual( 2, chunk.NK )
            self.assertEqual( 2, chunk.number_photons )

            self.assertEqual( 0, chunk.LTT )
            self.assertEqual( 0, chunk.LAW )
            self.assertEqual( True, chunk.LI )
            self.assertEqual( True, chunk.isotropic_distributions )

            self.assertEqual( 0, len( chunk.photon_angular_distributions ) )

            self.assertEqual( 1, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_LTT0 + self.valid_SEND,
                              chunk.to_string( 9228, 14 ) )

        def verify_chunk_LTT1( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.MT )
            self.assertEqual( 2, chunk.section_number )

            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 2.330248e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330248e+2, chunk.atomic_weight_ratio )

            self.assertEqual( 1, chunk.NI )
            self.assertEqual( 1, chunk.number_isotropic_photons )
            self.assertEqual( 2, chunk.NK )
            self.assertEqual( 2, chunk.number_photons )

            self.assertEqual( 1, chunk.LTT )
            self.assertEqual( 1, chunk.LAW )
            self.assertEqual( False, chunk.LI )
            self.assertEqual( False, chunk.isotropic_distributions )

            self.assertEqual( 2, len( chunk.photon_angular_distributions ) )

            isotropic = chunk.photon_angular_distributions[0]
            self.assertEqual( True, isinstance( isotropic, IsotropicDiscretePhoton ) )

            self.assertEqual( True, isotropic.LI )
            self.assertEqual( True, isotropic.isotropic_distributions )
            self.assertEqual( 0, isotropic.LTT )
            self.assertEqual( 0, isotropic.LAW )

            self.assertEqual( 1.5e+6, isotropic.EG )
            self.assertEqual( 1.5e+6, isotropic.photon_energy )
            self.assertEqual( 2e+6, isotropic.ES )
            self.assertEqual( 2e+6, isotropic.level_energy )

            photon = chunk.photon_angular_distributions[1]
            self.assertEqual( True, isinstance( photon, LegendreDistributions ) )

            self.assertEqual( False, photon.LI )
            self.assertEqual( False, photon.isotropic_distributions )
            self.assertEqual( 1, photon.LTT )
            self.assertEqual( 1, photon.LAW )

            self.assertEqual( 4.438900e+6, photon.EG )
            self.assertEqual( 4.438900e+6, photon.photon_energy )
            self.assertEqual( 4.438900e+6, photon.ES )
            self.assertEqual( 4.438900e+6, photon.level_energy )

            self.assertEqual( 2, photon.NE )
            self.assertEqual( 1, photon.NR )
            self.assertEqual( 1, len( photon.interpolants ) )
            self.assertEqual( 1, len( photon.boundaries ) )
            self.assertEqual( 3, photon.interpolants[0] )
            self.assertEqual( 2, photon.boundaries[0] )

            self.assertEqual( 2, len( photon.incident_energies ) )
            self.assertEqual( 2, len( photon.angular_distributions ) )

            self.assertEqual( 4.812998e+6, photon.incident_energies[0] )
            self.assertEqual( 15e+7, photon.incident_energies[1] )

            distributions = photon.angular_distributions

            d = distributions[0]
            self.assertEqual( 4.812998e+6, d.E )
            self.assertEqual( 4.812998e+6, d.incident_energy )
            self.assertEqual( 2, d.NL )
            self.assertEqual( 2, d.legendre_order )
            self.assertEqual( 2, len( d.coefficients ) )
            self.assertEqual( 0. , d.coefficients[0] )
            self.assertEqual( 4.076000e-2, d.coefficients[1] )

            d = distributions[1]
            self.assertEqual( 15e+7, d.E )
            self.assertEqual( 15e+7, d.incident_energy )
            self.assertEqual( 2, d.NL )
            self.assertEqual( 2, d.legendre_order )
            self.assertEqual( 2, len( d.coefficients ) )
            self.assertEqual( 0., d.coefficients[0] )
            self.assertEqual( 0., d.coefficients[1] )

            self.assertEqual( 8, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_LTT1 + self.valid_SEND,
                              chunk.to_string( 9228, 14 ) )

        # the data is given explicitly for LTT=0
        chunk = Section( mt = 2, zaid = 92235, awr = 2.330248e+2, nk = 2 )

        verify_chunk_LTT0( self, chunk )

        # the data is read from a string for LTT=0
        chunk = Section.from_string( self.chunk_LTT0 + self.valid_SEND )

        verify_chunk_LTT0( self, chunk )

        # the data is retrieved from a tree element and parsed for LTT=0
        tape = Tape.from_string( self.valid_TPID + self.chunk_LTT0 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 14 ).section( 2 ).parse()

        verify_chunk_LTT0( self, chunk )

        # the data is copied for LTT=0
        copy = Section( chunk )

        verify_chunk_LTT0( self, copy )

        # the data is given explicitly
        distributions = [ IsotropicDiscretePhoton( energy = 1.5e+6, level = 2.0e+6 ),
                          LegendreDistributions(
                            energy = 4.438900e+6, level = 4.438900e+6,
                            boundaries = [ 2 ], interpolants = [ 3 ],
                            distributions = [ LegendreCoefficients( 4.812998e+6, [ 0., 0.04076 ] ),
                                              LegendreCoefficients( 15e+7, [ 0., 0. ] ) ] ) ]

        chunk = Section( mt = 2, zaid = 92235, awr = 2.330248e+2,
                         photons = distributions )

        verify_chunk_LTT1( self, chunk )

        # the data is given explicitly
        distributions = [ LegendreDistributions(
                            energy = 4.438900e+6, level = 4.438900e+6,
                            boundaries = [ 2 ], interpolants = [ 3 ],
                            distributions = [ LegendreCoefficients( 4.812998e+6, [ 0., 0.04076 ] ),
                                              LegendreCoefficients( 15e+7, [ 0., 0. ] ) ] ) ]

        chunk = Section( mt = 2, zaid = 92235, awr = 2.330248e+2,
                         isotropic = [ [ 1.5e+6, 2.0e+6 ] ],
                         anisotropic = distributions )

        verify_chunk_LTT1( self, chunk )

        # the data is given explicitly
        distributions = [ LegendreDistributions(
                            energy = 4.438900e+6, level = 4.438900e+6,
                            boundaries = [ 2 ], interpolants = [ 3 ],
                            distributions = [ LegendreCoefficients( 4.812998e+6, [ 0., 0.04076 ] ),
                                              LegendreCoefficients( 15e+7, [ 0., 0. ] ) ] ) ]

        chunk = Section( mt = 2, zaid = 92235, awr = 2.330248e+2,
                         energies = [ 1.5e+6 ], levels = [ 2.0e+6 ],
                         anisotropic = distributions )

        verify_chunk_LTT1( self, chunk )

        # the data is read from a string for LTT=1
        chunk = Section.from_string( self.chunk_LTT1 + self.valid_SEND )

        verify_chunk_LTT1( self, chunk )

        # the data is retrieved from a tree element and parsed for LTT=1
        tape = Tape.from_string( self.valid_TPID + self.chunk_LTT1 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 14 ).section( 2 ).parse()

        verify_chunk_LTT1( self, chunk )

        # the data is copied for LTT=1
        copy = Section( chunk )

        verify_chunk_LTT1( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND for LTT=0
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk_LTT0 + self.invalid_SEND )

        # illegal SEND for LTT=1
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk_LTT1 + self.invalid_SEND )

        # illegal LTT
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.invalid + self.valid_SEND )

if __name__ == '__main__' :

    unittest.main()
