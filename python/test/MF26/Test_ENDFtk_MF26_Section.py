# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF26 import Section
from ENDFtk.MF26 import Multiplicity
from ENDFtk.MF26 import ReactionProduct
from ENDFtk.MF26 import ContinuumEnergyAngle
from ENDFtk.MF26.LAW1 import LegendreCoefficients
from ENDFtk.tree import Tape

class Test_ENDFtk_MF26_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 1.000000+3 9.992414-1          0          0          1          0 10026525     \n'
              ' 1.000000+3 9.992414-1          0          1          1          2 10026525     \n'
              '          2          4                                             10026525     \n'
              ' 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n'
              ' 0.000000+0 0.000000+0          1          2          1          2 10026525     \n'
              '          2          1                                             10026525     \n'
              ' 0.000000+0 1.000000+1          0          0          4          2 10026525     \n'
              ' 1.000000-1 2.139400+0 1.000000+1 2.122450-2                       10026525     \n'
              ' 0.000000+0 1.00000+11          0          0          4          2 10026525     \n'
              ' 1.000000-1 1.848230+0 1.00000+11 8.766410-3                       10026525     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                   10026  0     \n'
    valid_FEND = '                                                                   100 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9228 3  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1000, chunk.ZA )
            self.assertAlmostEqual( 9.992414e-1, chunk.AWR )
            self.assertAlmostEqual( 9.992414e-1, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.NK )
            self.assertEqual( 1, chunk.number_reaction_products )
            self.assertEqual( 525, chunk.MT )

            products = chunk.reaction_products
            self.assertEqual( 1, len( products ) )

            self.assertAlmostEqual( 1000., products[0].ZAP )
            self.assertAlmostEqual( 0.9992414, products[0].AWI )
            self.assertEqual( 1, products[0].LAW )

            self.assertAlmostEqual( 1000., products[0].multiplicity.ZAP )
            self.assertAlmostEqual( 0.9992414, products[0].multiplicity.AWI )
            self.assertEqual( 1, products[0].multiplicity.LAW )

            self.assertEqual( 2, products[0].multiplicity.NP )
            self.assertEqual( 1, products[0].multiplicity.NR )
            self.assertEqual( 1, len( products[0].multiplicity.interpolants ) )
            self.assertEqual( 1, len( products[0].multiplicity.boundaries ) )
            self.assertEqual( 4, products[0].multiplicity.interpolants[0] )
            self.assertEqual( 2, products[0].multiplicity.boundaries[0] )
            self.assertEqual( 2, len( products[0].multiplicity.energies ) )
            self.assertEqual( 2, len( products[0].multiplicity.multiplicities ) )
            self.assertAlmostEqual( 10., products[0].multiplicity.energies[0] )
            self.assertAlmostEqual( 1.e+11, products[0].multiplicity.energies[1] )
            self.assertAlmostEqual( 1., products[0].multiplicity.multiplicities[0] )
            self.assertAlmostEqual( 1., products[0].multiplicity.multiplicities[1] )

            law = products[0].distribution

            self.assertEqual( 1, law.LAW )
            self.assertEqual( 2, law.NE )
            self.assertEqual( 1, law.NR )
            self.assertEqual( 1, len( law.interpolants ) )
            self.assertEqual( 1, len( law.boundaries ) )
            self.assertEqual( 1, law.interpolants[0] )
            self.assertEqual( 2, law.boundaries[0] )

            energies = law.distributions

            self.assertEqual( 10., energies[0].incident_energy )
            self.assertEqual( 0, energies[0].ND )
            self.assertEqual( 0, energies[0].NA )
            self.assertEqual( 4, energies[0].NW )
            self.assertEqual( 2, energies[0].NEP )
            self.assertEqual( 2, len( energies[0].energies ) )
            self.assertAlmostEqual( .1, energies[0].energies[0] )
            self.assertAlmostEqual( 10., energies[0].energies[1] )
            self.assertEqual( 2, len( energies[0].coefficients ) )
            self.assertAlmostEqual( 2.1394, energies[0].coefficients[0][0] )
            self.assertAlmostEqual( 2.122450e-2, energies[0].coefficients[1][0] )
            self.assertEqual( 2, len( energies[0].total_emission_probabilities ) )
            self.assertAlmostEqual( 2.1394, energies[0].total_emission_probabilities[0] )
            self.assertAlmostEqual( 2.12245e-2, energies[0].total_emission_probabilities[1] )

            self.assertEqual( 1e+11, energies[1].incident_energy )
            self.assertEqual( 1, energies[1].LANG )
            self.assertEqual( 0, energies[1].ND )
            self.assertEqual( 0, energies[1].NA )
            self.assertEqual( 4, energies[1].NW )
            self.assertEqual( 2, energies[1].NEP )
            self.assertEqual( 2, len( energies[1].energies ) )
            self.assertAlmostEqual( .1, energies[1].energies[0] )
            self.assertAlmostEqual( 1e+11, energies[1].energies[1] )
            self.assertEqual( 2, len( energies[1].coefficients ) )
            self.assertAlmostEqual( 1.84823, energies[1].coefficients[0][0] )
            self.assertAlmostEqual( 8.76641e-3, energies[1].coefficients[1][0] )
            self.assertEqual( 2, len( energies[1].total_emission_probabilities ) )
            self.assertAlmostEqual( 1.84823, energies[1].total_emission_probabilities[0] )
            self.assertAlmostEqual( 8.76641e-3, energies[1].total_emission_probabilities[1] )

            self.assertEqual( 10, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 100, 26 ) )

        # the data is given explicitly
        zaid = 1000
        awr = .9992414
        mt = 525
        products = [
          ReactionProduct(
            Multiplicity( 1000, .9992414, 1, [ 2 ], [ 4 ],
                          [ 10., 1e+11 ],
                          [ 1., 1. ] ),
            ContinuumEnergyAngle(
              2, [ 2 ], [ 1 ],
              [ LegendreCoefficients(
                    10., 0, 0,
                    [ .1, 10. ],
                    [ [ 2.1394 ], [  .0212245 ] ] ),
                LegendreCoefficients(
                    1e+11, 0, 0, [ .1, 1e+11 ], [ [ 1.84823 ], [ .00876641 ] ] ) ] ) ) ]

        chunk = Section( mt = mt, zaid = zaid, awr = awr, products = products )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 100 ).file( 26 ).section( 525 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ =='__main__' :

    unittest.main()
