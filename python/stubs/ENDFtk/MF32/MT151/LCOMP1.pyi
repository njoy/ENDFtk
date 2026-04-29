"""
LCOMP1 - general resolved resonance covariance components
"""
from __future__ import annotations
import typing
__all__: list[str] = ['CovarianceMatrix', 'ResonanceParameters']
class CovarianceMatrix:
    """
    MF32 MT151 section - covariance data for the R-matrix limited
                         representation (LCOMP = 1)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> CovarianceMatrix:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, values: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self        the component
            values      the values of the upper diagonal covaraince matrix
        """
    @typing.overload
    def __init__(self, component: CovarianceMatrix) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NPARB(self) -> int:
        """
        The order of the covariance matrix
        """
    @property
    def NVS(self) -> int:
        """
        The number of values in the upper triangular covariance matrix
        """
    @property
    def covariance_matrix(self) -> ...:
        """
        The upper triangular covariance matrix
        """
    @property
    def covariance_matrix_order(self) -> int:
        """
        The order of the covariance matrix
        """
    @property
    def number_values(self) -> int:
        """
        The number of values in the upper triangular covariance matrix
        """
class ResonanceParameters:
    """
    MF32 MT151 section - resonance parameters for the R-matrix limited
                         representation (LCOMP = 1)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ResonanceParameters:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, energies: list[float], parameters: list[list[float]]) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            energies      the resonance energies (NRS values)
            parameters    the resonance parameters (NRS times NCH values)
        """
    @typing.overload
    def __init__(self, component: ResonanceParameters) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def ER(self) -> ...:
        """
        The resonance energies
        """
    @property
    def GAM(self) -> ...:
        """
        The resonance parameters
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NCH(self) -> int:
        """
        The number of channels
        """
    @property
    def NRB(self) -> int:
        """
        The number of resonances
        """
    @property
    def NX(self) -> int:
        """
        The number of lines for all parameters
        """
    @property
    def number_channels(self) -> int:
        """
        The number of channels
        """
    @property
    def number_lines(self) -> int:
        """
        The number of lines for all parameters
        """
    @property
    def number_resonances(self) -> int:
        """
        The number of resonances
        """
    @property
    def resonance_energies(self) -> ...:
        """
        The resonance energies
        """
    @property
    def resonance_parameters(self) -> ...:
        """
        The resonance parameters
        """
