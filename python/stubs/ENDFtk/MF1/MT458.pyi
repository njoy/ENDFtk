"""
MT458 - fission energy release components
"""
from __future__ import annotations
import pybind11_stubgen.typing_ext
import typing
__all__: list[str] = ['EnergyReleaseComponent', 'PolynomialComponents', 'Section', 'TabulatedComponents', 'ThermalPointComponents']
class EnergyReleaseComponent:
    """
    MF1 MT458 component - a tabulated fission energy release component
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> EnergyReleaseComponent:
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
    def __init__(self, ldrv: bool, ifc: int, boundaries: list[int], interpolants: list[int], energies: list[float], qvalues: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            ldrv            the primary evaluation flag (true/false)
            ifc             the index for the fission energy release component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the incident energy values
            qvalues         the fission q values
        """
    @typing.overload
    def __init__(self, component: EnergyReleaseComponent) -> None:
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
        The energy values
        """
    @property
    def EIFC(self) -> ...:
        """
        The fission energy release values
        """
    @property
    def IFC(self) -> int:
        """
        The index for the fission energy release component
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LDRV(self) -> bool:
        """
        The primary evaluation flag (true/false)
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
    def NP(self) -> int:
        """
        The number of points
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
    def component_index(self) -> int:
        """
        The index for the fission energy release component
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_points(self) -> int:
        """
        The number of points
        """
    @property
    def primary_evaluation_flag(self) -> bool:
        """
        The primary evaluation flag (true/false)
        """
    @property
    def q_values(self) -> ...:
        """
        The fission energy release values
        """
class PolynomialComponents:
    """
    MF1 MT458 component - Polynomial evaluation for fission energy release
                          components
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> PolynomialComponents:
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
    def __init__(self, efr: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]], enp: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]], end: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]], egp: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]], egd: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]], eb: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]], enu: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]], er: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]], et: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]]) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
            efr     the kinetic energy of the fission fragments
            enp     the kinetic energy of the prompt fission neutrons
            end     the kinetic energy of the delayed fission neutrons
            egp     the energy release by prompt gammas
            egd     the energy release by delayed gammas
            eb      the energy release by delayed betas
            enu     the energy release by neutrinos
            er      the total energy release minus neutrinos
            et      the total energy release
        """
    @typing.overload
    def __init__(self, component: PolynomialComponents) -> None:
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
        The energy release values and their uncertainties
        """
    @property
    def EB(self) -> ...:
        """
        The energy release by delayed betas and its uncertainty
        """
    @property
    def EFR(self) -> ...:
        """
        The kinetic energy of the fission fragments and its uncertainty
        """
    @property
    def EGD(self) -> ...:
        """
        The energy release by delayed gammas and its uncertainty
        """
    @property
    def EGP(self) -> ...:
        """
        The energy release by prompt gammas and its uncertainty
        """
    @property
    def END(self) -> ...:
        """
        The kinetic energy of the delayed fission neutrons and its uncertainty
        """
    @property
    def ENP(self) -> ...:
        """
        The kinetic energy of the prompt fission neutrons and its uncertainty
        """
    @property
    def ENU(self) -> ...:
        """
        The energy release by neutrinos and its uncertainty
        """
    @property
    def ER(self) -> ...:
        """
        The the total energy release minus the neutrino energy and its uncertainty
        """
    @property
    def ET(self) -> ...:
        """
        The the total energy release and its uncertainty
        """
    @property
    def LFC(self) -> int:
        """
        The tabulated energy release flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NFC(self) -> int:
        """
        The number of tabulated energy release components
        """
    @property
    def NPLY(self) -> int:
        """
        The polynomial expansion order
        """
    @property
    def delayed_betas(self) -> ...:
        """
        The energy release by delayed betas and its uncertainty
        """
    @property
    def delayed_gammas(self) -> ...:
        """
        The energy release by delayed gammas and its uncertainty
        """
    @property
    def delayed_neutrons(self) -> ...:
        """
        The kinetic energy of the delayed fission neutrons and its uncertainty
        """
    @property
    def energy_release(self) -> ...:
        """
        The energy release values and their uncertainties
        """
    @property
    def fission_fragments(self) -> ...:
        """
        The kinetic energy of the fission fragments and its uncertainty
        """
    @property
    def neutrinos(self) -> ...:
        """
        The energy release by neutrinos and its uncertainty
        """
    @property
    def number_tabulated_components(self) -> int:
        """
        The number of tabulated energy release components
        """
    @property
    def order(self) -> int:
        """
        The polynomial expansion order
        """
    @property
    def prompt_gammas(self) -> ...:
        """
        The energy release by prompt gammas and its uncertainty
        """
    @property
    def prompt_neutrons(self) -> ...:
        """
        The kinetic energy of the prompt fission neutrons and its uncertainty
        """
    @property
    def tabulated_energy_release(self) -> bool:
        """
        The tabulated energy release flag
        """
    @property
    def total(self) -> ...:
        """
        The the total energy release and its uncertainty
        """
    @property
    def total_minus_neutrinos(self) -> ...:
        """
        The the total energy release minus the neutrino energy and its uncertainty
        """
class Section:
    """
    MF1 MT458 section - fission energy release components
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
    def __init__(self, zaid: int, awr: float, fissionq: ThermalPointComponents | PolynomialComponents | TabulatedComponents) -> None:
        """
        Initialise the section
        
        Arguments:
            self        the section
            zaid        the ZA value of the material
            awr         the atomic weight ratio
            fissionq    the fission energy release data
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
    def LFC(self) -> int:
        """
        The tabulated energy release flag
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
    def NFC(self) -> int:
        """
        The number of tabulated energy release components
        """
    @property
    def NPLY(self) -> int:
        """
        The polynomial expansion order
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
    def energy_release(self) -> ThermalPointComponents | PolynomialComponents | TabulatedComponents:
        """
        The fission energy release data
        """
    @property
    def number_tabulated_components(self) -> int:
        """
        The number of tabulated energy release components
        """
    @property
    def order(self) -> int:
        """
        The polynomial expansion order
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def tabulated_energy_release(self) -> bool:
        """
        The tabulated energy release flag
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
class TabulatedComponents:
    """
    MF1 MT458 component - tabulated evaluation for fission energy release 
                          components
    """
    @typing.overload
    def __init__(self, thermal: ThermalPointComponents, tables: list[EnergyReleaseComponent]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            thermal    the thermal point evaluation of the energy release
            tables     the tabulated components
        """
    @typing.overload
    def __init__(self, component: TabulatedComponents) -> None:
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
    def LFC(self) -> int:
        """
        The tabulated energy release flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NFC(self) -> int:
        """
        The number of tabulated energy release components
        """
    @property
    def NPLY(self) -> int:
        """
        The polynomial expansion order
        """
    @property
    def number_tabulated_components(self) -> int:
        """
        The number of tabulated energy release components
        """
    @property
    def order(self) -> int:
        """
        The polynomial expansion order
        """
    @property
    def tabulated_EB(self) -> EnergyReleaseComponent | None:
        """
        The tabulated energy release by delayed betas
        """
    @property
    def tabulated_EFR(self) -> EnergyReleaseComponent | None:
        """
        The tabulated kinetic energy of the fission fragments
        """
    @property
    def tabulated_EGD(self) -> EnergyReleaseComponent | None:
        """
        The tabulated energy release by delayed gammas
        """
    @property
    def tabulated_EGP(self) -> EnergyReleaseComponent | None:
        """
        The tabulated energy release by prompt gammas
        """
    @property
    def tabulated_END(self) -> EnergyReleaseComponent | None:
        """
        The tabulated kinetic energy of the delayed fission neutrons
        """
    @property
    def tabulated_ENP(self) -> EnergyReleaseComponent | None:
        """
        The tabulated kinetic energy of the prompt fission neutrons
        """
    @property
    def tabulated_ENU(self) -> EnergyReleaseComponent | None:
        """
        The tabulated energy release by neutrinos
        """
    @property
    def tabulated_ER(self) -> EnergyReleaseComponent | None:
        """
        The tabulated total energy release minus the neutrino energy
        """
    @property
    def tabulated_ET(self) -> EnergyReleaseComponent | None:
        """
        The tabulated total energy release
        """
    @property
    def tabulated_delayed_betas(self) -> EnergyReleaseComponent | None:
        """
        The tabulated energy release by delayed betas
        """
    @property
    def tabulated_delayed_gammas(self) -> EnergyReleaseComponent | None:
        """
        The tabulated energy release by delayed gammas
        """
    @property
    def tabulated_delayed_neutrons(self) -> EnergyReleaseComponent | None:
        """
        The tabulated kinetic energy of the delayed fission neutrons
        """
    @property
    def tabulated_energy_release(self) -> bool:
        """
        The tabulated energy release flag
        """
    @property
    def tabulated_fission_fragments(self) -> EnergyReleaseComponent | None:
        """
        The tabulated kinetic energy of the fission fragments
        """
    @property
    def tabulated_neutrinos(self) -> EnergyReleaseComponent | None:
        """
        The tabulated energy release by neutrinos
        """
    @property
    def tabulated_prompt_gammas(self) -> EnergyReleaseComponent | None:
        """
        The tabulated energy release by prompt gammas
        """
    @property
    def tabulated_prompt_neutrons(self) -> EnergyReleaseComponent | None:
        """
        The tabulated kinetic energy of the prompt fission neutrons
        """
    @property
    def tabulated_total(self) -> EnergyReleaseComponent | None:
        """
        The the total energy release
        """
    @property
    def tabulated_total_minus_neutrinos(self) -> EnergyReleaseComponent | None:
        """
        The tabulated total energy release minus the neutrino energy
        """
    @property
    def thermal_point_values(self) -> ThermalPointComponents:
        """
        The thermal point values
        """
class ThermalPointComponents:
    """
    MF1 MT458 component - thermal point evaluation for fission energy release
                          components
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ThermalPointComponents:
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
    def __init__(self, efr: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], enp: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], end: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], egp: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], egd: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], eb: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], enu: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], er: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], et: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
            efr     the kinetic energy of the fission fragments
            enp     the kinetic energy of the prompt fission neutrons
            end     the kinetic energy of the delayed fission neutrons
            egp     the energy release by prompt gammas
            egd     the energy release by delayed gammas
            eb      the energy release by delayed betas
            enu     the energy release by neutrinos
            er      the total energy release minus neutrinos
            et      the total energy release
        """
    @typing.overload
    def __init__(self, component: ThermalPointComponents) -> None:
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
        The energy release values and their uncertainties
        """
    @property
    def EB(self) -> ...:
        """
        The energy release by delayed betas and its uncertainty
        """
    @property
    def EFR(self) -> ...:
        """
        The kinetic energy of the fission fragments and its uncertainty
        """
    @property
    def EGD(self) -> ...:
        """
        The energy release by delayed gammas and its uncertainty
        """
    @property
    def EGP(self) -> ...:
        """
        The energy release by prompt gammas and its uncertainty
        """
    @property
    def END(self) -> ...:
        """
        The kinetic energy of the delayed fission neutrons and its uncertainty
        """
    @property
    def ENP(self) -> ...:
        """
        The kinetic energy of the prompt fission neutrons and its uncertainty
        """
    @property
    def ENU(self) -> ...:
        """
        The energy release by neutrinos and its uncertainty
        """
    @property
    def ER(self) -> ...:
        """
        The the total energy release minus the neutrino energy and its uncertainty
        """
    @property
    def ET(self) -> ...:
        """
        The the total energy release and its uncertainty
        """
    @property
    def LFC(self) -> bool:
        """
        The tabulated energy release flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NFC(self) -> int:
        """
        The number of tabulated energy release components
        """
    @property
    def NPLY(self) -> int:
        """
        The polynomial expansion order
        """
    @property
    def delayed_betas(self) -> ...:
        """
        The energy release by delayed betas and its uncertainty
        """
    @property
    def delayed_gammas(self) -> ...:
        """
        The energy release by delayed gammas and its uncertainty
        """
    @property
    def delayed_neutrons(self) -> ...:
        """
        The kinetic energy of the delayed fission neutrons and its uncertainty
        """
    @property
    def energy_release(self) -> ...:
        """
        The energy release values and their uncertainties
        """
    @property
    def fission_fragments(self) -> ...:
        """
        The kinetic energy of the fission fragments and its uncertainty
        """
    @property
    def neutrinos(self) -> ...:
        """
        The energy release by neutrinos and its uncertainty
        """
    @property
    def number_tabulated_components(self) -> int:
        """
        The number of tabulated energy release components
        """
    @property
    def order(self) -> int:
        """
        The polynomial expansion order
        """
    @property
    def prompt_gammas(self) -> ...:
        """
        The energy release by prompt gammas and its uncertainty
        """
    @property
    def prompt_neutrons(self) -> ...:
        """
        The kinetic energy of the prompt fission neutrons and its uncertainty
        """
    @property
    def tabulated_energy_release(self) -> bool:
        """
        The tabulated energy release flag
        """
    @property
    def total(self) -> ...:
        """
        The the total energy release and its uncertainty
        """
    @property
    def total_minus_neutrinos(self) -> ...:
        """
        The the total energy release minus the neutrino energy and its uncertainty
        """
