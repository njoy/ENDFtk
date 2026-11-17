"""
MT455 - the number of delayed fission neutrons
"""
import ENDFtk.MF1
from __future__ import annotations
import typing
__all__: list[str] = ['DecayConstants', 'EnergyDependentConstants', 'EnergyIndependentConstants', 'Section']
class DecayConstants:
    """
    MF1 MT455 component - decay constants for delayed neutron precursors at                       a given incident energy
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> DecayConstants:
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
    def __init__(self, energy: float, constants: list[float], abundances: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            energy        the incident neutron energy
            constants     the precursor families decay constants
            abundances    the precursor families decay abundances
        """
    @typing.overload
    def __init__(self, component: DecayConstants) -> None:
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
    def E(self) -> float:
        """
        The incident energy value
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NNF(self) -> int:
        """
        The number of delayed neutron precursors
        """
    @property
    def abundances(self) -> ...:
        """
        The abundance values
        """
    @property
    def alphas(self) -> ...:
        """
        The abundance values
        """
    @property
    def decay_constants(self) -> ...:
        """
        The decay constants
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def lambdas(self) -> ...:
        """
        The decay constants
        """
    @property
    def number_precursors(self) -> int:
        """
        The number of delayed neutron precursors
        """
class EnergyDependentConstants:
    """
    MF1 MT455 component - energy dependent decay constants for delayed
                          neutron precursor families (LDG = 1)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> EnergyDependentConstants:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], constants: list[DecayConstants]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            constants       the decay constants
        """
    @typing.overload
    def __init__(self, component: EnergyDependentConstants) -> None:
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
    def E(self) -> ...:
        """
        The incident energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LDG(self) -> int:
        """
        The type of decay constants
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def NNF(self) -> int:
        """
        The number of delayed neutron precursors
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def constants(self) -> ...:
        """
        The decay contants
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_precursors(self) -> int:
        """
        The number of delayed neutron precursors
        """
    @property
    def type(self) -> int:
        """
        The type of decay constants
        """
class EnergyIndependentConstants:
    """
    MF1 MT455 component - energy independent decay constants for delayed
                          neutron precursor families (LDG = 0)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> EnergyIndependentConstants:
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
    def __init__(self, constants: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self         the component
            constants    the precursor families decay constants
        """
    @typing.overload
    def __init__(self, component: EnergyIndependentConstants) -> None:
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
    def LDG(self) -> int:
        """
        The type of decay constants
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NNF(self) -> int:
        """
        The number of delayed neutron precursors
        """
    @property
    def decay_constants(self) -> ...:
        """
        The decay constants
        """
    @property
    def lambdas(self) -> ...:
        """
        The decay constants
        """
    @property
    def number_precursors(self) -> int:
        """
        The number of delayed neutron precursors
        """
    @property
    def type(self) -> int:
        """
        The type of decay constants
        """
class Section:
    """
    MF1 MT455 section - the number of delayed fission neutrons
    """
    @staticmethod
    def from_string(section: str) -> Section:
        """
        Read the section from a string
        
        An exception is raised if something goes wrong while reading the
        section
        
        Arguments:
            section    the string representing the section
        """
    @typing.overload
    def __init__(self, zaid: int, awr: float, constants: EnergyIndependentConstants | EnergyDependentConstants, multiplicity: ENDFtk.MF1.PolynomialMultiplicity | ENDFtk.MF1.TabulatedMultiplicity) -> None:
        """
        Initialise the section
        
        Arguments:
            self            the section
            zaid            the ZA value of the material
            awr             the atomic weight ratio
            constants       the decay constant data
            multiplicity    the multiplicity data
        """
    @typing.overload
    def __init__(self, section: Section) -> None:
        """
        Initialise the section with another section
        
        Arguments:
            self       the section
            section    the section to be copied
        """
    def to_string(self, mat: int, mf: int) -> str:
        """
        Return the string representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
            mf      the MF number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def LDG(self) -> int:
        """
        The type of decay constants
        """
    @property
    def LNU(self) -> int:
        """
        The fission multiplicity representation type
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this section
        """
    @property
    def ZA(self) -> int:
        """
        The ZA identifier for the section
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def delayed_groups(self) -> EnergyIndependentConstants | EnergyDependentConstants:
        """
        The decay constant data for the delayed precursor groups
        """
    @property
    def nubar(self) -> ENDFtk.MF1.PolynomialMultiplicity | ENDFtk.MF1.TabulatedMultiplicity:
        """
        The fission multiplicity data
        """
    @property
    def representation(self) -> int:
        """
        The fission multiplicity representation type
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
    @property
    def type(self) -> int:
        """
        The type of decay constants
        """
