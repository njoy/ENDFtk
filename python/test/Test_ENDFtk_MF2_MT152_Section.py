# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT152 import Section
from ENDFtk.tree import Tape

class Test_ENDFtk_MF2_MT152_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 9.423900+4 2.369986+2          1          0          0          29437 2152     \n'
              ' 0.000000+0 0.000000+0          5          1         19          39437 2152     \n'
              ' 1.00000+10 2.500000+3 2.009120+1 1.343187+1 4.234708+0 2.424629+09437 2152     \n'
              ' 2.009120+1 2.550000+3 1.923568+1 1.375705+1 2.725074+0 2.753559+09437 2152     \n'
              ' 1.923568+1 3.000000+4 1.366039+1 1.156033+1 1.572008+0 5.280525-19437 2152     \n'
              ' 1.366039+1                                                       9437 2152     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  9437 2  0     \n'
    valid_FEND = '                                                                  9437 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9437 2  1     \n'

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 152, chunk.MT )
            self.assertEqual( 152, chunk.section_number )

            self.assertAlmostEqual( 94239., chunk.ZA )
            self.assertAlmostEqual( 2.369986e+2, chunk.AWR )
            self.assertAlmostEqual( 2.369986e+2, chunk.atomic_weight_ratio )

            self.assertEqual( 1, chunk.LSSF )
            self.assertEqual( 2, chunk.interpolation )

            self.assertEqual( 5, chunk.NREAC )
            self.assertEqual( 5, chunk.number_reactions )
            self.assertEqual( 1, chunk.NSIGZ )
            self.assertEqual( 1, chunk.number_dilutions )
            self.assertEqual( 3, chunk.NUNR )
            self.assertEqual( 3, chunk.number_energies )

            self.assertEqual( 0., chunk.TEMZ )
            self.assertEqual( 0., chunk.temperature )

            self.assertEqual( 1, len( chunk.SIGZ ) )
            self.assertEqual( 1, len( chunk.dilutions ) )
            self.assertAlmostEqual( 1e+10, chunk.SIGZ[0] )
            self.assertAlmostEqual( 1e+10, chunk.dilutions[0] )

            self.assertEqual( 3, len( chunk.EUNR ) )
            self.assertEqual( 3, len( chunk.energies ) )
            self.assertAlmostEqual( 2500., chunk.EUNR[0] )
            self.assertAlmostEqual( 2550., chunk.EUNR[1] )
            self.assertAlmostEqual( 30000., chunk.EUNR[2] )
            self.assertAlmostEqual( 2500., chunk.energies[0] )
            self.assertAlmostEqual( 2550., chunk.energies[1] )
            self.assertAlmostEqual( 30000., chunk.energies[2] )

            self.assertEqual( 3, len( chunk.total ) )
            self.assertEqual( 3, len( chunk.elastic ) )
            self.assertEqual( 3, len( chunk.fission ) )
            self.assertEqual( 3, len( chunk.capture ) )
            self.assertEqual( 3, len( chunk.current_weighted_total ) )
            self.assertEqual( 1, len( chunk.total[0] ) )
            self.assertEqual( 1, len( chunk.elastic[0] ) )
            self.assertEqual( 1, len( chunk.fission[0] ) )
            self.assertEqual( 1, len( chunk.capture[0] ) )
            self.assertEqual( 1, len( chunk.current_weighted_total[0] ) )
            self.assertAlmostEqual( 2.009120e+1, chunk.total[0][0] )
            self.assertAlmostEqual( 1.923568e+1, chunk.total[1][0] )
            self.assertAlmostEqual( 1.366039e+1, chunk.total[2][0] )
            self.assertAlmostEqual( 1.343187e+1, chunk.elastic[0][0] )
            self.assertAlmostEqual( 1.375705e+1, chunk.elastic[1][0] )
            self.assertAlmostEqual( 1.156033e+1, chunk.elastic[2][0] )
            self.assertAlmostEqual( 4.234708e+0, chunk.fission[0][0] )
            self.assertAlmostEqual( 2.725074e+0, chunk.fission[1][0] )
            self.assertAlmostEqual( 1.572008e+0, chunk.fission[2][0] )
            self.assertAlmostEqual( 2.424629e+0, chunk.capture[0][0] )
            self.assertAlmostEqual( 2.753559e+0, chunk.capture[1][0] )
            self.assertAlmostEqual( 5.280525e-1, chunk.capture[2][0] )
            self.assertAlmostEqual( 2.009120e+1, chunk.current_weighted_total[0][0] )
            self.assertAlmostEqual( 1.923568e+1, chunk.current_weighted_total[1][0] )
            self.assertAlmostEqual( 1.366039e+1, chunk.current_weighted_total[2][0] )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9437, 2 ) )

        # the data is given explicitly - infinite dilution only
        chunk = Section(  zaid = 94239., awr = 2.369986e+2, lssf = True,
                          interpolation = 2, temperature = 0.,
                          energies = [ 2500., 2550., 30000. ],
                          total = [ 2.009120e+1, 1.923568e+1, 1.366039e+1 ],
                          elastic = [ 1.343187e+1, 1.375705e+1, 1.156033e+1 ],
                          fission = [ 4.234708e+0, 2.725074e+0, 1.572008e+0 ],
                          capture = [ 2.424629e+0, 2.753559e+0, 5.280525e-1 ],
                          cwtotal = [ 2.009120e+1, 1.923568e+1, 1.366039e+1 ] )

        verify_chunk( self, chunk )

        # the data is given explicitly - infinite dilution only
        chunk = Section(  zaid = 94239., awr = 2.369986e+2, lssf = True,
                          interpolation = 2, temperature = 0.,
                          dilutions = [ 1e+10 ], energies = [ 2500., 2550., 30000. ],
                          total = [ [ 2.009120e+1 ], [ 1.923568e+1 ], [ 1.366039e+1 ] ],
                          elastic = [ [ 1.343187e+1 ], [ 1.375705e+1 ], [ 1.156033e+1 ] ],
                          fission = [ [ 4.234708e+0 ], [ 2.725074e+0 ], [ 1.572008e+0 ] ],
                          capture = [ [ 2.424629e+0 ], [ 2.753559e+0 ], [ 5.280525e-1 ] ],
                          cwtotal = [ [ 2.009120e+1 ], [ 1.923568e+1 ], [ 1.366039e+1 ] ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        material = list( tape.material( 9437 ) )[0]

        chunk = material.file( 2 ).section( 152 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
