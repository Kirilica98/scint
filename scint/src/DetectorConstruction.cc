///////////////////////////////////////////////////////////////////
//
// Apr/2015  E. Nacher -> DetectorConstruction.cc
//
///////////////////////////////////////////////////////////////////

#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Sphere.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4NistManager.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
using namespace CLHEP;

DetectorConstruction::DetectorConstruction()
{ }

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	
	//----------------------------------------------------
	// Material definitions
	//----------------------------------------------------
	
	G4String name, symbol;             //a=mass of a mole;
    G4double a, z, density,fractionmass;            //z=mean number of protons;
	
	G4int ncomponents, natoms;         
	
    G4Material *Air = G4NistManager::Instance()->FindOrBuildMaterial ("G4_AIR");
	
    //vodorod
       a = 1.01*g/mole;
        G4Element* elH = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);
       //uglerod
        a=12.01*g/mole;
        G4Element* elC=new G4Element(name="Carbon",symbol="C",z=6,a);
        //germaniy
        G4Material *ge = G4NistManager::Instance()->FindOrBuildMaterial ("G4_Ge");
        //Molekula 1 C16H26
        density=0.858*g/cm3;
        G4Material* M1=new G4Material(name="C16H26",density,ncomponents=2);
        M1->AddElement(elH,natoms=26);
        M1->AddElement(elC,natoms=16);
        //Molekula 2 C17H28
        density=0.858*g/cm3;
        G4Material* M2=new G4Material(name="C17H28",density,ncomponents=2);
        M2->AddElement(elH,natoms=28);
        M2->AddElement(elC,natoms=17);
        //Molekula 3 C18H30
        density=0.859*g/cm3;
        G4Material* M3=new G4Material(name="C18H30",density,ncomponents=2);
        M3->AddElement(elH,natoms=30);
        M3->AddElement(elC,natoms=18);
        //Molekula 4 C19H32
        density=0.859*g/cm3;
        G4Material* M4=new G4Material(name="C19H32",density,ncomponents=2);
        M4->AddElement(elH,natoms=30);
        M4->AddElement(elC,natoms=18);
        // Scintillator  LAB
        G4Material* Lab=new G4Material(name="Lab",density,ncomponents=4,kStateLiquid);
        Lab->AddMaterial(M1,fractionmass=13*perCent);
        Lab->AddMaterial(M2,fractionmass=27*perCent);
        Lab->AddMaterial(M3,fractionmass=35*perCent);
        Lab->AddMaterial(M4,fractionmass=25*perCent);
    //shiter PPO
        //Azot
        a=14.*g/mole;
        G4Element* elN=new G4Element(name="Azot",symbol="N",z=7,a);
        //oxygen
        a = 15.999*g/mole;
        G4Element* elO  = new G4Element(name="Oxygen" ,symbol="O" , z= 8., a);
        //PPO
        density=1.06*g/cm3;
        G4Material* PPO=new G4Material(name="PPO",density,ncomponents=4);
        PPO->AddElement(elH,natoms=11);
        PPO->AddElement(elC,natoms=15);
        PPO->AddElement(elO,natoms=1);
        PPO->AddElement(elN,natoms=1);
        //POPOP
        density=1.2*g/cm3;
        G4Material* POPOP=new G4Material(name="POPOP",density,ncomponents=4);
        POPOP->AddElement(elH,natoms=16);
        POPOP->AddElement(elC,natoms=24);
        POPOP->AddElement(elO,natoms=2);
        POPOP->AddElement(elN,natoms=2);
        //Lab+PPO+POPOP
        G4Material* scint=new G4Material(name="scint",density,ncomponents=3,kStateLiquid);
        scint->AddMaterial(Lab,fractionmass=99.99697*perCent);
        scint->AddMaterial(PPO,fractionmass=0.003*perCent);
        scint->AddMaterial(POPOP,fractionmass=0.00003*perCent);
      //Quartz
    //si
        a = 28.0855*g/mole;
    G4Element* Si  = new G4Element(name="Silicon"  ,symbol="Si" , z= 14., a);

    //quartz
    density = 2.20*g/cm3;
      G4Material* Quartz = new G4Material(name="Quartz", density, ncomponents=2);
      Quartz->AddElement(Si, natoms=1);
      Quartz->AddElement(elO, natoms=2);



	//------------------------------------------------------
	// Optical properties
	//------------------------------------------------------

      //scint->AddMaterialPropertiesTable(PPO);
      const G4int nEntries =215;
      G4double PhotonEnergy[nEntries] = {2.60*eV,2.61*eV,2.62*eV,2.63*eV,2.64*eV,2.65*eV,2.66*eV,2.67*eV,2.68*eV,2.69*eV,
                                         2.70*eV,2.71*eV,2.72*eV,2.73*eV,2.74*eV,2.75*eV,2.76*eV,2.77*eV,2.78*eV,2.79*eV,
                                         2.80*eV,2.81*eV,2.82*eV,2.83*eV,2.84*eV,2.85*eV,2.86*eV,2.87*eV,2.88*eV,2.89*eV,
                                         2.90*eV,2.91*eV,2.92*eV,2.93*eV,2.94*eV,2.95*eV,2.96*eV,2.97*eV,2.98*eV,2.99*eV,
                                         3.00*eV,3.01*eV,3.02*eV,3.03*eV,3.04*eV,3.05*eV,3.06*eV,3.07*eV,3.08*eV,3.09*eV,
                                         3.10*eV,3.11*eV,3.12*eV,3.13*eV,3.14*eV,3.15*eV,3.16*eV,3.17*eV,3.18*eV,3.19*eV,
                                         3.20*eV,3.21*eV,3.22*eV,3.23*eV,3.24*eV,3.25*eV,3.26*eV,3.27*eV,3.28*eV,3.29*eV,
                                         //visible
                                         3.30*eV,3.31*eV,3.32*eV,3.33*eV,3.34*eV,3.35*eV,3.36*eV,3.37*eV,3.38*eV,3.39*eV,
                                         3.40*eV,3.41*eV,3.42*eV,3.43*eV,3.44*eV,3.45*eV,3.46*eV,3.47*eV,3.48*eV,3.49*eV,
                                         3.50*eV,3.51*eV,3.52*eV,3.53*eV,3.54*eV,3.55*eV,3.56*eV,3.57*eV,3.58*eV,3.59*eV,
                                         3.60*eV,3.61*eV,3.62*eV,3.63*eV,3.64*eV,3.65*eV,3.66*eV,3.67*eV,3.68*eV,3.69*eV,
                                         3.70*eV,3.71*eV,3.72*eV,3.73*eV,3.74*eV,3.75*eV,3.76*eV,3.77*eV,3.78*eV,3.79*eV,
                                         3.80*eV,3.81*eV,3.82*eV,3.83*eV,3.84*eV,3.85*eV,3.86*eV,3.87*eV,3.88*eV,3.89*eV,
                                         3.90*eV,3.91*eV,3.92*eV,3.93*eV,3.94*eV,3.95*eV,3.96*eV,3.97*eV,3.98*eV,3.99*eV,
                                         4.00*eV,4.01*eV,4.02*eV,4.03*eV,4.04*eV,4.05*eV,4.06*eV,4.07*eV,4.08*eV,4.09*eV,
                                         4.10*eV,4.11*eV,4.12*eV,4.13*eV,4.14*eV,4.15*eV,4.16*eV,4.17*eV,4.18*eV,4.19*eV,
                                         4.20*eV,4.21*eV,4.22*eV,4.23*eV,4.24*eV,4.25*eV,4.26*eV,4.27*eV,4.28*eV,4.29*eV,
                                         4.30*eV,4.31*eV,4.32*eV,4.33*eV,4.34*eV,4.35*eV,4.36*eV,4.37*eV,4.38*eV,4.39*eV,
                                         4.40*eV,4.41*eV,4.42*eV,4.43*eV,4.44*eV,4.45*eV,4.46*eV,4.47*eV,4.48*eV,4.49*eV,
                                         4.50*eV,4.51*eV,4.52*eV,4.53*eV,4.54*eV,4.55*eV,4.56*eV,4.57*eV,4.58*eV,4.59*eV,
                                         4.60*eV,4.61*eV,4.62*eV,4.63*eV,4.64*eV,4.65*eV,4.66*eV,4.67*eV,4.68*eV,4.69*eV,
                                         4.70*eV,4.71*eV,4.72*eV,4.73*eV,4.74*eV};// UV



      G4double LabRefractionIndex[nEntries] = {1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                              1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                              1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                              1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                              1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                              1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                              1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5};

            G4double LabAbsorptionLength[nEntries] = {11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,
                                                      11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,
                                                      11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,
                                                      11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,
                                                      11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,
                                                      11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,
                                                      11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,11*m,
                                                      //uv

                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm,
                                                      0.1*mm,0.1*mm,0.1*mm,0.1*mm,0.1*mm};
      //scint

      G4MaterialPropertiesTable* LabMPT = new G4MaterialPropertiesTable();
      LabMPT->AddProperty("RINDEX",PhotonEnergy,LabRefractionIndex, nEntries);
      LabMPT->AddProperty("ABSLENGTH",PhotonEnergy,LabAbsorptionLength,nEntries);

      G4double ScintEnergy[nEntries] = {2.99*eV,3.2*eV};
      G4double ScintFast[nEntries]={0.5,0.5};

      LabMPT->AddProperty("FASTCOMPONENT",ScintEnergy,ScintFast,nEntries);

      LabMPT->AddConstProperty("SCINTILLATIONYIELD",11./keV);
      LabMPT->AddConstProperty("RESOLUTIONSCALE",1.);
      LabMPT->AddConstProperty("FASTTIMECONSTANT",20.*ns);
      LabMPT->AddConstProperty("YIELDRATIO",1.);
      scint->SetMaterialPropertiesTable(LabMPT);//check bugs

      //PPO-shifter(CHECK)

       G4double EmissionFiber[nEntries]={3.0,7.0,7.0,7.0,7.0,7.0,8.0,8.0,10.0,12.0,
                                         13.0,14.0,15.0,15.0,17.0,17.0,18.0,19.0,20.0,20.0,
                                         20.0,20.0,20.0,21.0,22.0,24.0,28.0,28.0,30.0,36.0,
                                         40.0,40.0,43.0,43.0,42.0,41.0,41.0,41.0,40.0,40.0,
                                         40.0,40.0,40.0,40.0,38.0,38.0,35.0,37.0,39.0,40.0,
                                         40.0,41.0,43.0,45.0,35.0,25.0,19.0,15.0,10.0,10.0,
                                         //wawelenngth=380 nm
                                         10.0,10.0,10.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
                                         //
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
                                         0.,0.,0.,0.,0.};

       G4MaterialPropertiesTable* MPTFiber = new G4MaterialPropertiesTable();
       MPTFiber->AddProperty("RINDEX",PhotonEnergy,LabRefractionIndex,nEntries);
       MPTFiber->AddProperty("WLSABSLENGTH",PhotonEnergy,LabAbsorptionLength,nEntries);
       MPTFiber->AddProperty("WLSCOMPONENT",PhotonEnergy, EmissionFiber, nEntries);
       MPTFiber->AddConstProperty("WLSTIMECONSTANT", 3.5*ns);
       scint->SetMaterialPropertiesTable(MPTFiber);

      //Ge
      G4double GeRefractionIndex[nEntries] =  {1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                 1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                 1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                                 1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,
                                               1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5};

          G4double GeAbsorptionLength[nEntries] = {1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                   1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,
                                                    1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m,1.0E-9*m};

          G4MaterialPropertiesTable* GeMPT = new G4MaterialPropertiesTable();

          GeMPT->AddProperty("RINDEX",PhotonEnergy,GeRefractionIndex,
                                 nEntries);
          GeMPT->AddProperty("ABSLENGTH",PhotonEnergy,GeAbsorptionLength,
                                 nEntries);

          ge->SetMaterialPropertiesTable(GeMPT);


          //quartz
          G4double QuartzRefractionIndex[nEntries] = {1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,
                                                      1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,
                                                      1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,
                                                      1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,
                                                      1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,
                                                      1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,
                                                      1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,
                                                      1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,
                                                      1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,
                                                      1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,1.47,
                                                      1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,
                                                      1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,
                                                      1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,
                                                      1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,1.48,
                                                      1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
                                                      1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
                                                      1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
                                                      1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
                                                      1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
                                                      1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
                                                      1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
                                                      1.49,1.49,1.49,1.49,1.49
                                                      };

          G4double QuartzAbsorptionLength [nEntries] = {23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,

                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                         23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                        23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,23.0*cm,
                                                       };

          G4MaterialPropertiesTable* QuartzMPT = new G4MaterialPropertiesTable();

          QuartzMPT->AddProperty("RINDEX",PhotonEnergy,QuartzRefractionIndex,
                                 nEntries);
          QuartzMPT->AddProperty("ABSLENGTH",PhotonEnergy,QuartzAbsorptionLength,
                                 nEntries);
          Quartz->SetMaterialPropertiesTable(QuartzMPT);

          //Air


          G4double AirRefractionIndex[nEntries] = {1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                  1,1,1,1,1,1,1,1,1,1,
                                                  1,1,1,1,1,1,1,1,1,1,
                                                  1,1,1,1,1,1,1,1,1,1,
                                                  1,1,1,1,1,1,1,1,1,1,
                                                  1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1,
                                                   1,1,1,1,1,1,1,1,1,1};


          G4double AirAbsorptionLength[nEntries] = {23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                   23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                   23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                   23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                   23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                   23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,
                                                    23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m,23.0*m
                                                   };

          G4MaterialPropertiesTable* AirMPT = new G4MaterialPropertiesTable();

          AirMPT->AddProperty("RINDEX",PhotonEnergy,AirRefractionIndex,
                                 nEntries);
          AirMPT->AddProperty("ABSLENGTH",PhotonEnergy,AirAbsorptionLength,
                                 nEntries);
          Air->SetMaterialPropertiesTable(AirMPT);
	//------------------------------------------------------
	// Detector geometry
	//------------------------------------------------------
	
	//     
	// World
	//
    G4bool checkOverlaps=true;
    G4double WorldSize= 210.*cm;
	
	G4Box* 
    solidWorld = new G4Box("World",		       	                  //its name
						   WorldSize/2,WorldSize/2,WorldSize/2);  //its size
	
	G4LogicalVolume* 
    logicWorld = new G4LogicalVolume(solidWorld,      	//its solid
                                     Air,	        //its material
									 "World");		    //its name
	
	G4VPhysicalVolume* 
    physiWorld = new G4PVPlacement(0,			    //no rotation
								   G4ThreeVector(),	//at (0,0,0)
								   "World",		    //its name
								   logicWorld,		//its logical volume
								   NULL,		    //its mother  volume
								   false,	       	//no boolean operation
								   0);			    //copy number
	
	
	//
	// Detector 
	//
    G4double EndScintRad=100*cm;
    G4double EndSD=101*cm;
    G4double StartAngle = 180.*deg;
   G4double EndAngle = 360.*deg;

    G4Sphere* solidDet =
      new G4Sphere("Detector",                    //its name, имя
          EndScintRad, EndSD, 0.*StartAngle,EndAngle,0.*StartAngle,0.5*EndAngle); //its size, размеры

    //Логический объем
    G4LogicalVolume* logicDet =
      new G4LogicalVolume(solidDet,            //its solid, объем
                          ge,             //its material, указываем материал детектора
                          "Detector");         //its name, его имя

    //Физический объем детектора
     G4VPhysicalVolume* phys_detector=new G4PVPlacement(0,                       //no rotation, так же без вращения
                      G4ThreeVector(0,0,0*cm), //at (0,0,5 см) положение центра детектора, он смещен на 5 см от центра объема World
                      logicDet,                //its logical volume, подключаем логический объем
                      "Detector",              //its name, имя физического объема
                      logicWorld,              //its mother  volume, родительский логический объем, помещаем в world!
                      false,                   //no boolean operation, без булевых операций
                      0);          //overlaps checking, флаг проверки перекрытия объемов

    //scint-sphere down
    G4double HighKolba=3*cm;
    G4double InKolbRad=4*mm;
    G4double OutKolbRad=5*mm;
    G4double zeroRad=0*cm;

    G4Sphere* solid_Lab=new G4Sphere("scint-Sphere",zeroRad,EndScintRad,0*StartAngle,EndAngle,0.*StartAngle,0.5*EndAngle);
    G4LogicalVolume* logic_Lab=new G4LogicalVolume(solid_Lab,scint,"scint-Sphere");
    G4VPhysicalVolume* phys_scint =new G4PVPlacement(0,G4ThreeVector(0,0,0*cm),logic_Lab,"scint-Sphere",logicWorld,false,0);


    //Quartz kolba
    G4Sphere* solid_QKS=new G4Sphere("kolba-sp",InKolbRad,OutKolbRad,0.*StartAngle,EndAngle,0.5*StartAngle,0.5*EndAngle);
    G4Tubs* solid_QKC=new G4Tubs("kolba-bok",InKolbRad,OutKolbRad,0.5*HighKolba,0.*StartAngle,EndAngle);

    G4UnionSolid* solid_kolba=new G4UnionSolid("kolba",solid_QKS,solid_QKC,0,G4ThreeVector(0*cm,0,1.5*cm));
    G4LogicalVolume* logic_kolba=new G4LogicalVolume(solid_kolba,Quartz,"kolba");
    G4VPhysicalVolume* phys_kolba=new G4PVPlacement(0,G4ThreeVector(),logic_kolba,"kolba",logicWorld,false,0);


    //(inside kolba) Change Material!
    G4Sphere* solid_inside_kolbdown=new G4Sphere("inside-down",zeroRad,InKolbRad,0.*StartAngle,EndAngle,0.5*StartAngle,0.5*EndAngle);
    G4Tubs* solid_inside_kolbabok=new G4Tubs("inside-bok",zeroRad,InKolbRad,0.5*HighKolba,StartAngle,EndAngle);

    G4UnionSolid* solid_inside=new G4UnionSolid("inside",solid_inside_kolbdown,solid_inside_kolbabok,0,G4ThreeVector(0,0,1.5*cm));
    G4LogicalVolume* logic_inside=new G4LogicalVolume(solid_inside,Air,"inside");
    G4VPhysicalVolume* phys_inside=new G4PVPlacement(0,G4ThreeVector(),logic_inside,"inside",logicWorld,false,0);


     //------------------------------------------------------
     // optical surfaces
     //------------------------------------------------------

    //quartz-scint
    G4OpticalSurface* OpQuaScintSurface =
    new G4OpticalSurface("CryPMTWinSurface");

    OpQuaScintSurface->SetType(dielectric_dielectric);
    OpQuaScintSurface->SetModel(glisur);
    OpQuaScintSurface->SetFinish(polished);

    G4LogicalBorderSurface* QuaScintSurface =
    new G4LogicalBorderSurface("QuaScintSurface",phys_kolba,phys_scint,
                               OpQuaScintSurface);
    //air-quartz
    G4OpticalSurface* OpAirQuaSurface =
    new G4OpticalSurface("OpInsideQuaSurface");

    OpAirQuaSurface->SetType(dielectric_dielectric);
    OpAirQuaSurface->SetModel(glisur);
    OpAirQuaSurface->SetFinish(polished);

    G4LogicalBorderSurface* AirQuaSurface =new G4LogicalBorderSurface("AirQuaSurface",phys_kolba,phys_inside,
                               OpAirQuaSurface);
    //scint-ge
    G4OpticalSurface* OpGeScintSurface =
    new G4OpticalSurface("OpGeScintSurfac");

    OpGeScintSurface->SetType(dielectric_dielectric);
    OpGeScintSurface->SetModel(glisur);
    OpGeScintSurface->SetFinish(polished);

    G4LogicalBorderSurface* GeScintSurface =
    new G4LogicalBorderSurface("GeScintSurface",phys_scint,phys_detector,
                               OpGeScintSurface);

	//------------------------------------------------------
	// visualization attributes
	//------------------------------------------------------
	
	logicWorld->SetVisAttributes(G4VisAttributes::Invisible);
	
    //Green color for colba
    G4VisAttributes* Att1= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    logic_kolba->SetVisAttributes(Att1);

    //Yellow color for scint
	G4VisAttributes* Att2= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
    logic_Lab->SetVisAttributes(Att2);
    //logic_Lab1->SetVisAttributes(Att2);

    //Blue color for detector
	G4VisAttributes* Att3= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    logicDet->SetVisAttributes(Att3);
	

	//
	
	return physiWorld;
}
