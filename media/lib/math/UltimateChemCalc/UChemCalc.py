
#utilze periodictable for getting
#all element symbols and atomic
#masses
import periodictable as per
#
#use the wx package for
#creating/displaying graphics (buttons, textboxes,
#background panel color, etc.)
import wx
#
#import the wx package's
#scrollable panel so it can
#be used to assist in displaying
#the application on a wide range
#of screen sizes
import wx.lib.scrolledpanel
#
#Utilize sympy for creating
#the matrices used within the
#chemical equation balancer
import sympy
#
#use the string module
#in order to get a list of
#all ascii_letters for the
#chemical equation balancer
import string
#
#use regular expressions to
#simplify error detection
import re
#
#use webbrowser module to open webpage...
import webbrowser as wb
#
########### Purpose: The purpose of this program is to provide a user-friendly interface for navigating chemistry based
#                    conversion problems. The types of conversion problems provided range from basic mole conversions, to
#                    all stoichiometry based convrsion problems, and finally, a select amount of molarity based problems.
#                    Furthermore, users have the ability to balance chemistry equations (basic/complex ones and equations involving
#                    charges). An experimental lewis structure calculator is being developed as well; it will be released
#                    sometime after the release of this initial version.


########### Functionality: The main functionality of the program begins at the bottom of this page in the section labeled
#                          application setup. First, all global variables are defined, followed by the wxPython frame and panel.
#                          After the wxPython components are setup, all periodic table buttons and problem based buttons are created
#                          through various setup functions; the first setup function to be called is periodic_setup(), followed by
#                          problemButtons(), and then finally, review() (responsible for setting up the review video buttons).
#                          Upon any of the buttons being clicked, a function binded to the button will be called, executing the
#                          main functionality the button is associated with.




#SECTION---ONE--------------------------------------------------------------------------------------------
#This is the Zeroth section of the Ultimate Chemistry Calculator. This section is responsible for
#defining all mole conversion functions to be used by the desktop version of the Ultimate Chemistry
#Calculator.

#Grams to Moles                                                                                                                                                                              
def gramToMole(gram,molarMass):
    return gram / molarMass

#Grams to Molels to Particles              
def gramToMoleToParticle(gram,molarMass):
    return (gram / molarMass) * (6.022*(10**23))

#Grams to Moles to Particles to Atoms      
def gramToMoleToParticleToAtom(gram,molarMass,atoms):
    return (gram / molarMass) * (6.022*(10**23)) * atoms

#Moles to Grams                            
def moleToGram(moles,molarMass):
    return moles * molarMass

#Moles to Particles                        
def moleToParticle(moles):
    return moles * (6.022 * (10**23))

#Moles to Molecules to Atoms               
def moleToMoleculeToAtom(moles,atoms):
    return moles * (6.022 * (10**23)) * atoms

#Molecules to Atoms                        
def moleculeToAtom(molecule,atoms):
    return molecule * atoms

#Particles to Moles                        
def particleToMole(particle):
    return (particle / (6.022 * (10**23)))

#Particles to Grams                        
def particleToGram(particle,molarMass):
    return (particle / (6.022 * (10**23))) * molarMass

#Liters to Grams (Gas at STP)              
def LiterToGram(liter,molarMass):
    return (liter * molarMass) / 22.4

#Liters to Particles (Gas at STP)          
def LiterToParticle(liter):
    return (liter * (6.022*(10**23))) / 22.4

#Liters to Atoms (Gas at STP)              
def LiterToAtom(liter, atom):
    return ((liter * (6.022*(10**23)))*atom) / 22.4

#Moles to Liters (Gas at STP)              
def MoleToLiter(mole):
    return mole * 22.4

#Liters to Moles (Gas at STP)              
def LiterToMole(liter):
    return liter / 22.4

#Grams to Liters (Gas at STP)              
def GramToLiter(gram, molarMass):
    return (gram * 22.4) / molarMass

#Particles to Liters (Gas at STP)                                                                                                                                                                  
def ParticleToLiter(particles):
    return (particles * 22.4) / (6.022 * (10**23))

#Moles to Moles (Stoichiometry)            
def MoleToMole(given,mole1,mole2):
    return (given * mole2) / mole1

#Grams to Grams (Stoichiometry)            
def SGramToGram(given,molarMass,known,unknown,molarMass2):
    return (given * unknown * molarMass2) / (molarMass * known)

#Grams to Moles (Stoichiometry)            
def SGramToMole(gram,molarMass,known,unknown):
    return (gram * unknown) / (known * molarMass)

#Grams to Particles (Stoichiomeetry)       
def GramToParticle(gram,molarMass,known,unknown):
    return (gram * unknown * (6.022*(10**23))) / (molarMass * known)

#Liters to Moles (Molarity Problem)        
def LiquidLiterToMole(liter,molarL):
    return liter / molarL

#Liters to Grams (Molarity Problem)        
def LiquidLiterToGram(liter,molarL,molarMass):
    return (liter * molarMass) / molarL

#Liters to Particles (Molarity Problem)    
def LiquidLiterToParticles(liter,molarL):
    return (liter * (6.022*(10**23))) / molarL

#Grams to Atoms (Stoichiometry)            
def SGramToAtom(gram,molarMass1,known,unknown,atoms):
    return (gram * unknown * (6.022*(10**23)) * atoms) / (known * molarMass1)

#Grams to Liters (Stoichiometry)           
def SGramToLiter(gram,molarMass,known,unknown):
    return (gram * unknown * 22.4) / (molarMass * known)

#Moles to Grams (Stoichiometry)            
def SMoleToGram(mole,known,unknown,molarMass):
    return (mole * unknown * molarMass) / known

#Moles to Particles (Stoichiometry)        
def SMoleToParticle(mole,known,unknown):
    return (mole *  unknown * (6.022*(10**23))) / known

#Moles to Atoms (Stoichiometry)            
def SMoleToAtoms(mole,known,unknown,atoms):
    return (mole * unknown * atoms * (6.022*(10**23))) / known

#Moles to Liters (Stoichiometry)           
def SMoleToLiter(mole,known,unknown):
    return (mole * unknown * 22.4) / known

#Particles to Grams (Stoichiometry)        
def SParticleToGram(particle,known,unknown,molarMass):
    return (particle * unknown * molarMass) / (known * (6.022*(10**23)))

#Particles to Moles (Stoichiometry)        
def SParticleToMole(particle,known,unknown):
    return (particle * unknown) / (known * (6.022*(10**23)))

#Particles to Particles (Stoichiometry)    
def SParticleToParticle(particle,known,unknown):
    return (particle * unknown) / known

#Particles to Atoms (Stoichiometry)        
def SParticleToAtom(particle,known,unknown,atom):
    return (particle * unknown * atom) / known

#Particles to Liters (Stoichiometry)       
def SParticleToLiter(particle,known,unknown):
    return (particle * unknown * 22.4) / (known * (6.022*(10**23)))

#Liters to Grams (Stoichiometry)           
def SLiterToGram(liter,known,unknown,molarMass):
    return (liter * unknown * molarMass) / (22.4 * known)

#Liters to Moles (Stoichiometry)           
def SLiterToMole(liter,known,unknown):
    return (liter * unknown) / (22.4 * known)

#Liters to Particles (Stoichiometry)
def SLiterToParticle(liter,known,unknown):
    return (liter * unknown * (6.022*(10**23))) / (22.4 * known)

#Liters to Atoms (Stoichiometry)          
def SLiterToAtom(liter,known,unknown,atoms):
    return (liter * unknown * (6.022*(10**23)) * atoms) / (22.4 * known)

#Liters to Liters (Stoichiometry)          
def SLiterToLiter(liter,known,unknown):
    return (liter * unknown) / known

#END OF SECTION ZERO--------------------------------------------------------------------------------





#SECTION---ONE--------------------------------------------------------------------------------------------
#This marks the first major section of the Ultimate chemistry calculator 1. This section is responsible for
#the creation of all periodic table objects.

#reference positions
#for placing elements
w = None

#row 1 list
L1 = [per.H,per.He]


#row 2 list
L2 = [per.Li,per.Be,per.B,per.C,per.N,per.O,per.F,per.Ne]


#row 3 list
L3 = [per.Na,per.Mg,per.Al,per.Si,per.P,per.S,per.Cl,per.Ar]


#row 4
L4 = [per.K,per.Ca,per.Sc,per.Ti,per.V,per.Cr,per.Mn,per.Fe,per.Co,per.Ni,per.Cu,per.Zn,per.Ga,per.Ge,per.As,per.Se,per.Br,per.Kr]


#row 5
L5 = [per.Rb,per.Sr,per.Y,per.Zr,per.Nb,per.Mo,per.Tc,per.Ru,per.Rh,per.Pd,per.Ag,per.Cd,per.In,per.Sn,per.Sb,per.Te,per.I,per.Xe]


#row 6
L6 = [per.Cs,per.Ba,"57-51",per.Hf,per.Ta,per.W,per.Re,per.Os,per.Ir,per.Pt,per.Au,per.Hg,per.Ti,per.Pb,per.Bi,per.Po,per.At,per.Rn]


#row 7
L7 = [per.Fr,per.Ra,"89-103",per.Rf,per.Db,per.Sg,per.Bh,per.Hs,per.Mt,per.Ds,per.Rg,per.Cn,per.Nh,per.Fl,per.Mc,per.Lv,per.Ts,per.Og]


#Lanthanides
Lanth = [per.La,per.Ce,per.Pr,per.Nd,per.Pm,per.Sm,per.Eu,per.Gd,per.Tb,per.Dy,per.Ho,per.Er,per.Tm,per.Yb,per.Lu]


#Actinides
Actin = [per.Ac,per.Th,per.Pa,per.U,per.Np,per.Pu,per.Am,per.Cm,per.Bk,per.Cf,per.Es,per.Fm,per.Md,per.No,per.Lr]


#add all periodic table buttons and
#element symbols / atomic masses
def periodic_setup(addToPanel):
    #add all element buttons
    

    #add buttons with individual row functions...
    x = 0
    y = 0
    for r in range(1):

        #row 1
        add_row_one(addToPanel,x,y)

        #row 2
        add_row_two(addToPanel,x,(y + 45))
        
        #row 3
        add_row_three(addToPanel,x,(y + 90))

        #row 4
        add_row_four(addToPanel,x,(y + 135))

        #row 5
        add_row_five(addToPanel,x,(y + 180))

        #row 6
        add_row_six(addToPanel,x,(y + 225))

        #row 7
        add_row_seven(addToPanel,x,(y + 270))

#create row one element buttons
def add_row_one(Parent,x,y):
    global w
    #add two buttons (hydrogen and helium)
    for s in range(2):
        starWars = wx.Button(Parent,id = s,label=""+L1[s].symbol+"\n"+str(round(L1[s].mass,4)),pos=wx.Point(x,y),size=(84,38))
        starWars.Bind(wx.EVT_BUTTON, arrID1)
        print("Button Size (Periodic): "+str(starWars.GetSize()))
        print("Position: "+str(starWars.GetPosition()))
        if(s == 0):
            w = starWars
        if (s == 0):
            x = (x + 90) * 17

#create row two element buttons
def add_row_two(Parent,x,y):

    #add first two buttons (L2) 
    for t in range(2):
        yoda = wx.Button(Parent,id = t,label=""+L2[t].symbol+"\n"+str(round(L2[t].mass,4)),pos=wx.Point(x,y),size=(84,38))
        yoda.Bind(wx.EVT_BUTTON,arrID2)
        if (t == 0):
            x = x + 90
        else:
            x = x * 12

    #add the other six buttons
    for g in range(6):
        luke = wx.Button(Parent,id = 2 + g,label=""+L2[g + 2].symbol+"\n"+str(round(L2[g + 2].mass,4)),pos=wx.Point(x,y),size=(84,38))
        luke.Bind(wx.EVT_BUTTON,arrID2)
        if (g != 5):
            x = x + 90


#create row three element buttons
def add_row_three(Parent,x,y):

    #add first two buttons (L3)
    for e in range(2):
        obiWan = wx.Button(Parent,id = e,label=""+L3[e].symbol+"\n"+str(round(L3[e].mass,4)),pos=wx.Point(x,y),size=(84,38))
        obiWan.Bind(wx.EVT_BUTTON,arrID3)
        if (e == 0):
            x = x + 90
        else:
            x = x * 12


    #add the other six buttons
    for v in range(6):
        quiGonn = wx.Button(Parent,id = 2 + v,label=""+L3[v + 2].symbol+"\n"+str(round(L3[v + 2].mass,4)),pos=wx.Point(x,y),size=(84,38))
        quiGonn.Bind(wx.EVT_BUTTON,arrID3)
        if (v != 5):
            x = x + 90


#create row four element buttons
def add_row_four(Parent,x,y):

    #add all eighteen buttons (L4)
    for f in range(18):
        anakin = wx.Button(Parent,id = f,label=""+L4[f].symbol+"\n"+str(round(L4[f].mass,4)),pos=wx.Point(x,y),size=(84,38))
        anakin.Bind(wx.EVT_BUTTON,arrID4)
        if (f != 17):
            x = x + 90

#create row five element buttons
def add_row_five(Parent,x,y):

    #add all eighteen buttons (L5)
    for o in range(18):
        dooku = wx.Button(Parent,id = o,label=""+L5[o].symbol+"\n"+str(round(L5[o].mass,4)),pos=wx.Point(x,y),size=(84,38))
        dooku.Bind(wx.EVT_BUTTON,arrID5)
        if (o != 17):
            x = x + 90

#create the Lanthanide buttons
def add_row_six(Parent,x,y):
    #add all seventeen buttons (L6)
    #plus the Lanthanides
    for q in range(18):
        if (q == 2):
            tyranus = wx.Button(Parent,id = q,label=L6[q],pos=wx.Point(x,y))
        else:
            sidious = wx.Button(Parent,id = q,label=""+L6[q].symbol+"\n"+str(round(L6[q].mass,4)),pos=wx.Point(x,y),size=(84,38))
            sidious.Bind(wx.EVT_BUTTON,arrID6)

        if (q != 17):
            x = x + 90


    #make sure to re-adjust x and y
    x = 180
    y = y + 90
    for qr in range(15):
        shaakTi = wx.Button(Parent,id = qr,label=""+Lanth[qr].symbol+"\n"+str(round(Lanth[qr].mass,4)),pos=wx.Point(x,y),size=(84,38))
        shaakTi.Bind(wx.EVT_BUTTON,arrID8)
        if (qr != 14):
            x = x + 90

#create the Actinide buttons
def add_row_seven(Parent,x,y):
    #add all seventeen buttons (L7)
    #plus the Actinides
    for z in range(18):
        if (z == 2):
            luminara = wx.Button(Parent,label=L7[z],pos=wx.Point(x,y))
        else:
            ploe = wx.Button(Parent,id = z,label=""+L7[z].symbol+"\n"+str(round(L7[z].mass,4)),pos=wx.Point(x,y),size=(84,38))
            ploe.Bind(wx.EVT_BUTTON,arrID7)

        if (z != 17):
            x = x + 90


    #make sure to re-adjust x and y                                                                                                                            
    x = 180
    y = y + 90

    for sr in range(15):
        plaguis = wx.Button(Parent,id = sr,label=""+Actin[sr].symbol+"\n"+str(round(Actin[sr].mass,4)),pos=wx.Point(x,y),size=(84,38))
        plaguis.Bind(wx.EVT_BUTTON,arrID9)
        if (sr != 14):
            x = x + 90


#END OF SECTION ONE--------------------------------------------------------------------------------

















#SECTION---TWO--------------------------------------------------------------------------------------------
#This marks the beginning of section two.
#Section Two is responsible for the linkage
#of all imported conversion functions to the appropriate buttons
#(the conversion functions within the "conversionM" module)


#Create mole-conversion, problem, buttons
#and bind the mole conversion functions
#to their associated buttons.
def moleConversionButtons(parent,x,y):
    
    #bind the grams to moles problem to function gtm
    temp0 = wx.Button(parent,id = 0,label="Grams to Moles",pos=wx.Point(x,y))
    temp0.Bind(wx.EVT_BUTTON,gTm)

    #bind the Grams to Particles problem to function mTa
    temp1 = wx.Button(parent,id = 5,label="Grams to Particles",pos=wx.Point(x,y + 45))
    temp1.Bind(wx.EVT_BUTTON,mTa)

    #bind the Grams to Atoms problem to function gTa
    temp2 = wx.Button(parent,id = 8,label="Grams to Atoms",pos=wx.Point(x,y + 90))
    temp2.Bind(wx.EVT_BUTTON,gTa)

    #bind the Moles to Grams problem to function gTm
    temp3 = wx.Button(parent,id = 3,label="Moles to Grams",pos=wx.Point(x,y + 135))
    temp3.Bind(wx.EVT_BUTTON,gTm)

    #bind the Moles to Particles problem to function mTp
    temp4 = wx.Button(parent,id = 1,label="Moles to Particles",pos=wx.Point(x,y + 180))
    temp4.Bind(wx.EVT_BUTTON,mTp)

    #bind the Moles to Atoms problem to function mTa
    temp5 = wx.Button(parent,id = 6,label="Moles to Atoms",pos=wx.Point(x,y + 225))
    temp5.Bind(wx.EVT_BUTTON,mTa)

    #bind the Molecules to Atoms problem to function mTp
    temp6 = wx.Button(parent,id = 4,label="Molecules to Atoms",pos=wx.Point(x,y + 270))
    temp6.Bind(wx.EVT_BUTTON,mTp)

    #bind the Particles to Moles problem to function mTp
    temp7 = wx.Button(parent,id = 2,label="Particles to Moles",pos=wx.Point(x,y + 315))
    temp7.Bind(wx.EVT_BUTTON,mTp)

    #bind the Particlse to Grams problem to function mTa
    temp8 = wx.Button(parent,id = 7,label="Particles to Grams",pos=wx.Point(x,y + 360))
    temp8.Bind(wx.EVT_BUTTON,mTa)

    #bind the Gas: Liters to Grams problem to function mTa
    temp9 = wx.Button(parent,id=9,label = "Gas: Liters to Grams",pos=wx.Point(x,y+405))
    temp9.Bind(wx.EVT_BUTTON,mTa)

    #bind the Gas: Liters to Particles problem to function mTa
    temp10 = wx.Button(parent,id=10,label = "Gas: Liters to Particles",pos=wx.Point(x,y+450))
    temp10.Bind(wx.EVT_BUTTON,mTa)

    #bind the Gas: Liters to Atoms problem to function gTa
    temp11 = wx.Button(parent,id=11,label = "Gas: Liters to Atoms",pos=wx.Point(x,y+495))
    temp11.Bind(wx.EVT_BUTTON,gTa)

    #bind the Gas: Moles to Liters problem to function gTm
    temp12 = wx.Button(parent,id=12,label = "Gas: Moles to Liters",pos=wx.Point(160,630 + 45))
    temp12.Bind(wx.EVT_BUTTON,gTm)

    #bind the Gas: Liters to Moles problem to function gTm
    temp13 = wx.Button(parent,id=13,label = "Gas: Liters to Moles",pos=wx.Point(160, 675 + 45))
    temp13.Bind(wx.EVT_BUTTON,gTm)

    #bind the Gas: Grams to Liters problem to function mTa
    temp14 = wx.Button(parent,id=14,label = "Gas: Grams to Liters",pos=wx.Point(160,720 + 45))
    temp14.Bind(wx.EVT_BUTTON,mTa)

    #bind the Gas: Particles to Liters problem to function mTa
    temp15 = wx.Button(parent,id=16,label = "Gas: Particles to Liters",pos=wx.Point(160,765 + 45))
    temp15.Bind(wx.EVT_BUTTON,mTa)

    #bind the Stoichiometry: Grams to Grams problem to function gTa
    temp16 = wx.Button(parent,id=17,label = "Stoichiometry: Grams to Grams",pos=wx.Point(160,855))
    temp16.Bind(wx.EVT_BUTTON,gTa)

    #bind the Stoichiometry:Grams to Moles problem to function mTa
    temp17 = wx.Button(parent,id=18,label = "Stoichiometry: Grams to Moles",pos=wx.Point(160,900))
    temp17.Bind(wx.EVT_BUTTON,mTa)

    #bind the Stoichiometry: Grams to Particles problem to function gTa
    temp18 = wx.Button(parent,id=19,label = "Stoichiometry: Grams to Particles",pos=wx.Point(160,945))
    temp18.Bind(wx.EVT_BUTTON,gTa)

    #bind the Stoichiometry: Grams to Atoms problem to function SgTa
    temp19 = wx.Button(parent,id=20,label = "Stoichiometry: Grams to Atoms",pos=wx.Point(405,855))
    temp19.Bind(wx.EVT_BUTTON,SgTa)

    #bind the Stoichiometry (Gas): Grams to Liters problem to function gTa
    temp20 = wx.Button(parent,id=21,label = "Stoichiometry (Gas): Grams to Liters",pos=wx.Point(405,900))
    temp20.Bind(wx.EVT_BUTTON,gTa)

    #bind the Stoichiometry: Moles to Grams problem to function mTa
    temp21 = wx.Button(parent,id=22,label = "Stoichiometry: Moles to Grams",pos=wx.Point(405,945))
    temp21.Bind(wx.EVT_BUTTON,mTa)

    #bind the Stoichiometry: Moles to Moles problem to function gTm
    temp22 = wx.Button(parent,id=23,label = "Stoichiometry: Moles to Moles",pos=wx.Point(650,855))
    temp22.Bind(wx.EVT_BUTTON,gTm)

    #bind the Stoichiometry: Moles to Particles problem to function mTa
    temp23 = wx.Button(parent,id=24,label = "Stoichiometry: Moles to Particles",pos=wx.Point(650,900))
    temp23.Bind(wx.EVT_BUTTON,mTa)

    #bind the Stoichiometry: Moles to Atoms problem to function gTa
    temp24 = wx.Button(parent,id=25,label = "Stoichiometry: Moles to Atoms",pos=wx.Point(650,945))
    temp24.Bind(wx.EVT_BUTTON,gTa)

    #bind the Stoichiometry (Gas): Moles to Liters problem to function mTa
    temp24 = wx.Button(parent,id=26,label = "Stoichiometry (Gas): Moles to Liters",pos=wx.Point(895,855))
    temp24.Bind(wx.EVT_BUTTON,mTa)

    #bind the Stoichiometry: Particles to Grams problem to function gTa
    temp25 = wx.Button(parent,id=27,label = "Stoichiometry: Particles to Grams",pos=wx.Point(895,900))
    temp25.Bind(wx.EVT_BUTTON,gTa)

    #bind the Stoichiometry: Particles to Moles problem to function mTa
    temp26 = wx.Button(parent,id=28,label = "Stoichiometry: Particles to Moles",pos=wx.Point(895,945))
    temp26.Bind(wx.EVT_BUTTON,mTa)

    #bind the Stoichiometry: Particles to Particles problem to function gTa
    temp27 = wx.Button(parent,id=29,label = "Stoichiometry: Particles to Particles",pos=wx.Point(1140 + 10,855))
    temp27.Bind(wx.EVT_BUTTON,gTa)

    #bind the Stoichiometry: Particles to Atoms problem to function SgTa
    temp28 = wx.Button(parent,id=30,label = "Stoichiometry: Particles to Atoms",pos=wx.Point(1140 + 10,900))
    temp28.Bind(wx.EVT_BUTTON,SgTa)

    #bind the Stoichiometry (Gas): Particles to Liters problem to function gTa
    temp29 = wx.Button(parent,id=31,label = "Stoichiometry (Gas): Particles to Liters",pos=wx.Point(1140 + 10,945))
    temp29.Bind(wx.EVT_BUTTON,gTa)

    #bind the Stoichiometry (Gas): Liters to Grams problem to function gTa
    temp30 = wx.Button(parent,id=32,label = "Stoichiometry (Gas): Liters to Grams",pos=wx.Point(405,810))
    temp30.Bind(wx.EVT_BUTTON,gTa)

    #bind the Stoichiometry (Gas): Liters to Moles problem to function mTa
    temp31 = wx.Button(parent,id=33,label = "Stoichiometry (Gas): Liters to Moles",pos=wx.Point(650,810))
    temp31.Bind(wx.EVT_BUTTON,mTa)

    #bind the Stoichiometry (Gas): Liters to Particles problem to function gTa
    temp32 = wx.Button(parent,id=34,label = "Stoichiometry(Gas): Liters to Particles",pos=wx.Point(895,810))
    temp32.Bind(wx.EVT_BUTTON,gTa)

    #bind the Stoichiometry (Gas): Liters to Atoms problem to function SgTa
    temp33 = wx.Button(parent,id=35,label = "Stoichiometry (Gas): Liters to Atoms",pos=wx.Point(1140 + 10,810))
    temp33.Bind(wx.EVT_BUTTON,SgTa)

    #bind the Stoichiometry (Gas): Liters to Liters problem to function gTa
    temp34 = wx.Button(parent,id=36,label = "Stoichiometry (Gas): Liters to Liters",pos=wx.Point(405,765))
    temp34.Bind(wx.EVT_BUTTON,gTa)

    #bind the Liquids: Liters to Moles problem to function gTm
    temp35 = wx.Button(parent,id=37,label = "Liquids: Liters to Moles",pos=wx.Point(650,765))
    temp35.Bind(wx.EVT_BUTTON,gTm)

    #bind the Liquids: Liters to Grams problem to function mTa
    temp36 = wx.Button(parent,id=38,label = "Liquids: Liters to Grams",pos=wx.Point(895,765))
    temp36.Bind(wx.EVT_BUTTON,mTa)

    #bind the Liquids: Liters to Particles problem to function mTa
    temp37 = wx.Button(parent,id=39,label = "Liquids: Liters to Particles",pos=wx.Point(1140 + 10,765))
    temp37.Bind(wx.EVT_BUTTON,mTa)



#END OF SECTION TWO--------------------------------------------------------------------------------






















#SECTION---THREE--------------------------------------------------------------------------------------------
#Section three has one job and that is to close the application when given the signal

#quit application function                    
def quit1(event):
    
    #use the close function
    #of the global variable
    #frame to end the application
    global frame

    #reset set 1 before leaving...
    global set1

    #reset it...
    set1 = 0
    
    #reset application so
    #a new wx object can be
    #created when start is called...
    global application
    
    #close the frame to end
    #the application
    frame.Close()

    #reset application...
    del application

#END OF SECTION THREE--------------------------------------------------------------------------------


















#SECTION---FOUR-------------------------------------------------------------------------------------------- 
#Section four is responsible for the creation of all problem buttons

#Create chemical balancing button
def propertyButton(parent,x,y):
    temp = wx.Button(parent,id = 100,label="Chemical Equation Balancing and Stoichiometry",pos=wx.Point(x,y))
    temp.Bind(wx.EVT_BUTTON,ChemBalanceButtons)

#add quit application button
def quitApp(parent,x,y):
    quit = wx.Button(panel,label = "EXIT APPLICATION",pos=wx.Point(x,y))
    quit.Bind(wx.EVT_BUTTON,quit1)



#setup all problem buttons
def problemButtons(addToParent):

    #start placing the buttons at
    #the far left below the periodic table.
    #In the end, several columns of problem buttons
    #spanning from left to right of the application window
    #will be the result
    x = 0;
    y = 450;
    moleConversionButtons(addToParent,x,y)

    #the function above will leave a gap
    #in the second column it creates to the far right.
    #This gap will be filled with the chemical equation
    #balancing mole conversion button.
    x = 160
    y = 450
    propertyButton(addToParent,x,y)

    #add the quit application button
    #to the far right of the application
    #window.
    x = 720 + 750
    y = 880
    quitApp(addToParent,x,y)

    #setup beginning instructions
    #within the center of the application
    x = 720
    y = 490
    instruction(addToParent,x,y)

#instruction setup
def instruction(parent,x,y):
    global direction
    direction = wx.StaticText(parent,label = "Directions: Pick a problem type from the array of buttons to the far left and bottom.\nInstructions for each problem will be given upon clicking a problem type...",pos = wx.Point(x,y))


#review video buttons setup
def review(addToParent):
    rev = wx.Button(addToParent,label = "Mole Conversions Online Review Video (NEED INTERNET)",pos = wx.Point(160,450 + 90 + 45))
    rev.Bind(wx.EVT_BUTTON, moleReview)
    rev2 = wx.Button(addToParent,label = "Stoichiometry Online Review Video (NEED INTERNET)",pos = wx.Point(160,450 + 90 + 45 + 45))
    rev2.Bind(wx.EVT_BUTTON, stoichiometryReview)


#open up mole review video...
def stoichiometryReview(event):

    #open url...
    wb.open("https://drive.google.com/file/d/1VwRYIIwHQ9TCBaEC_oGBXP1bXVpNccBM/view", new = 1)

    
    
#open up mole review video...
def moleReview(event):

    #open url...
    wb.open("https://drive.google.com/file/d/11MBDYXM1Smc0t7QlPx7x2pWQSijkLSh2/view", new = 1)
    
    
#create all buttons associated with the
#chemical equation balancing problem
def ChemBalanceButtons(event):

    #all global variables that will be
    #referenced and assigned new values
    #
    #label variable for holding the
    #first displayed instruction
    global direction
    #
    #chemical equation arrow symbol
    global arrow
    #
    #chemical equation plus symbol
    global plus
    #
    #left parenthese
    global Cosmo
    #
    #right parenthese
    global Wanda
    #
    #left bracket
    global Robin
    #
    #right bracket
    global Batman
    #
    #the text box containing the
    #chemical equation
    global equation
    #
    #the most current problem type
    global molarVar
    #
    #signals if a new problem is ready
    #to be setup
    global set1
    #
    #the calculate button
    global calculate2
    #
    #the answer text box
    global answer
    #
    #The direction variable for telling the user
    #what to do...
    global direction
    #
    #the third calculate button...
    global calculate3
    #
    #The fourth calculate button...
    global calculate4


    #if no other problem is active at the moment
    #immediately setup the balancing chemical equations
    #problem.
    if(set1 == 0):

            #keep track of which problem is currently
            #setup
            molarVar = 14

            #after assigning the problem type to molarVar,
            #reset set1 to contain 100; communicating that
            #a deletion process will have to occur for a
            #different problem to be setup.
            set1 = 100

            #if this problem happens to be the first
            #problem selected by the user, destroy
            #the general purpose instruction so it doesn't
            #get in the way.
            if(direction != None):
                direction.Destroy()
                direction = None

            #use wi, hi to adjust the placement of newly created elements
            #to the correct position. This must be done due to the fact that
            #when the scroll bar is used, the (0,0) coordinate reference changes with
            #the scrolling. Thus, wi and hi are used to find the orientation associated
            #with the original reference.
            wi,hi = w.GetPosition()

            #create the answer text box
            answer = wx.TextCtrl(panel,pos=wx.Point((720+750)+wi,490+hi),size=wx.Size(200,300),style=wx.TE_MULTILINE)
            answer.write("Answer will appear here...")

            #create the arrow symbol button associated with differentiating products and reactants: H2 + O2 -> H20
            arrow = wx.Button(panel,id = 1001,label="->",pos=wx.Point(160+wi,495+hi),size=wx.Size(30,30))
            arrow.Bind(wx.EVT_BUTTON,setEquation)

            #create the plus symbol button associaited with two or more reactants reacting: H2 + O2
            plus = wx.Button(panel,id = 1000,label="+",pos=wx.Point(190+wi,495+hi),size=wx.Size(30,30))
            plus.Bind(wx.EVT_BUTTON,setEquation)

            #create a button associated with the left parenthese: (SO4)2
            Cosmo = wx.Button(panel,id = 1002,label="(",pos=wx.Point(220+wi,495+hi),size=wx.Size(30,30))
            Cosmo.Bind(wx.EVT_BUTTON,setEquation)

            #create a button associated with the right parenthese: (SO4)2
            Wanda = wx.Button(panel,id = 1003,label=")",pos=wx.Point(250+wi,495+hi),size=wx.Size(30,30))
            Wanda.Bind(wx.EVT_BUTTON,setEquation)

            #create a button associated with the left bracket symbol: [-2]
            Robin = wx.Button(panel,id = 1004,label="[",pos=wx.Point(280+wi,495+hi),size=wx.Size(30,30))
            Robin.Bind(wx.EVT_BUTTON,setEquation)

            #create a button associated with the right bracket symbol: [-2]
            Batman = wx.Button(panel,id = 1005,label="]",pos=wx.Point(310+wi,495+hi),size=wx.Size(30,30))
            Batman.Bind(wx.EVT_BUTTON,setEquation)

            #create the textbox where the user punches in the chemical equation...
            equation = wx.TextCtrl(panel,pos=wx.Point(160+wi,540+hi),size=wx.Size(200,20),style=wx.TE_MULTILINE)

            #create the calculation button that the user will press when he or she wishes to
            #balance the chemical equation within the input text box.
            calculate2 = wx.Button(panel,label = "Normal Balance",pos=wx.Point((360)+wi,495+hi))
            calculate2.Bind(wx.EVT_BUTTON,balanceEquation)

            #create the calculate3 button for reactions in acid solution
            calculate3 = wx.Button(panel,label = "Balance in Acidic Solution",pos=wx.Point((480)+wi,495+hi))
            calculate3.Bind(wx.EVT_BUTTON,acidBalance)

            #create the calculate4 button for reactions in acid solution
            calculate4 = wx.Button(panel,label = "Balance in Basic Solution",pos=wx.Point((480)+wi,540+hi))
            calculate4.Bind(wx.EVT_BUTTON,basicBalance)
            
            wi,hi = w.GetPosition()
            direction = wx.StaticText(panel,label = "Chemical Equation Balancer Instructions:\n1. Use the periodic table to punch in elements...\nFor instance, press H two times to write H with subscript two into the equation bar.\n2. Use the extra buttons provided to form your chemical equation...\n3. When including charges, use the bracket buttons provided. For instnace:\nH[+1]+SO3[-2]->...\n4. If you make a mistake, erase what you have manually\nand try again (this is how the function resets).\n\n***WARNING: If using the Acidic/Basic features of the chemical equation balancer, know that\nit is a new feature that is currently in the beta testing phase;\nright away, it can be said that not all output will be correct for certain inputs.\nThis is due to the fact that when two or more free variables show up, the program tries a different combination of H2O and H+/OH-\non either side of the equation. Most of the time these combinations will filter out\nthe incorrect answers, but other times, it doesn't filter all of them because some have correct form after gaussian elimination.\nAn oxidation number solver will correct this in the next version, but for now, take output with a grain of salt.",pos = wx.Point(670+wi,490+hi))
            
    #if another problem is currently setup
    #enter the delet1 button in order to delete
    #the current problem, and then re-enter
    #ChemBalanceButtons() in order to setup
    #the chemical balancing problem.
    else:
        delete1()
        ChemBalanceButtons(event)



#END OF SECTION FOUR--------------------------------------------------------------------------------


























#SECTION---FIVE--------------------------------------------------------------------------------------------
#Section Five is responsible for playing the review videos

#play video
def play(event):

    #re-write code...
    return

#END OF SECTION FIVE--------------------------------------------------------------------------------



























#SECTION---SIX--------------------------------------------------------------------------------------------
#Section six is responsible for putting together all parts of the
#chemical equation (for chemical equation balancing)

#process the button pushes associated with the
#chemical balancing problem by inserting the
#corresponding symbol into the equation/input
#text box.
def setEquation(event):

    #There is actually no need
    #for this global declaration
    #since it isn't being modified.
    #However, it is declared just to let any
    #readers know that it is actively utilized
    #within this function to write new contents
    #to the chemical equation text box that it
    #references.
    global equation

    #use the event reference to get all
    #data associated with the button that
    #was pushed.
    button = event.GetEventObject()

    #now extract the id from the pushed
    #button
    id = button.GetId()

    #write the appropraite symbol
    #to the equation/input text box
    #based on the associated id
    #extracted from the event object
    if(id == 1000):
        equation.write('+')
    elif(id == 1002):
        equation.write('(')
    elif(id == 1003):
        equation.write(')')
    elif(id == 1004):
        equation.write('[')
    elif(id == 1005):
        equation.write(']')
    else:
        equation.write("->")

#Process each request the user makes when clicking buttons
#so the button's associated symbol will be put within the
#chemical equation text box as input. The user can continue
#to engage in this process until he/she is ready to click
#the calculate button for chemical balancing.
#The buttons that will ultimately activate this
#function are the periodic table buttons.
def chemicalEquation(event):

        #The subscripts global variable
        #keeps track of how many elments of
        #a certain should be represented in
        #the chemical equation text box.
        global subscripts
        #
        #The equation global variable isn't
        #actually being modified, but is delcared
        #just to let any readers know that it is
        #actively used withini this function to
        #write contents to the text box it references
        global equation
        #
        #The elementID global variable isn't
        #actually being modified, but is declared
        #just to let any readers know that it is
        #actively used to help determine which element symbol
        #was selected by the user.
        global elementID
        #
        #The chemEquation global variable keeps
        #track of the current state of the equation
        #inputed by the user (in string form) and is actively modified,
        #as the user pushes input buttons, to hold the
        #most up to date chemical equation corresponding
        #to the users button pushes.
        global chemEquation
        #
        #The prev global variable keeps track
        #of the most recent element symbol
        #accessed by the user. Once the user
        #selects a new element symbol for entry
        #into the chemEquation string, prev will
        #not correspond with the most recent symbol,
        #and the subscript variable will be reset.
        global prev
        #
        #molar12 refers to the most recently selected
        #element symbol
        global molar12
        #
        #The rows global variable will encrement
        #with each new element symbol that is selected
        #by the user; it will then be used to create the
        #coefficient matrix so the chemical equation can
        #be balanced via linear algebra
        global rows
        #
        #The arrName2 global variable
        #keeps a history of all elements present within
        #the chemical equation punched in by the user.
        global arrName2


        #get associated element id corresponding
        #to the button push
        button = event.GetEventObject()
        num = button.GetId()

        #Get rid of any spaces to avoid any
        #errors
        if(' ' in equation.GetValue()):
            tr = equation.GetValue()
            equation.Clear()
            tr.replace(" ","")
            equation.write(tr)

        #In case the user decides to
        #erase the input, reset the subscript
        #variable.
        #Or if there are no conetents within
        #the equation text box.
        if(equation.GetValue() == ""):
            subscripts = 0

        #get element symbol from the correct periodic 
        #table array based on the elementID value...                                                                                                                                             
        if(elementID == 1):
            molar12 = L1[num].symbol
        elif(elementID == 2):
            molar12 = L2[num].symbol
        elif(elementID == 3):
            molar12 = L3[num].symbol
        elif(elementID == 4):
            molar12 = L4[num].symbol
        elif(elementID == 5):
            molar12 = L5[num].symbol
        elif(elementID == 6):
            molar12 = L6[num].symbol
        elif(elementID == 7):
            molar12 = L7[num].symbol
        elif(elementID == 8):
            molar12 = Lanth[num].symbol
        else:
            molar12 = Actin[num].symbol

        #Increment the subscripts variable after an
        #element is selected by the user. Note, this does not
        #mean that the subscript value will be updated to
        #the equation text box; the element symbol first has
        #to be compared to the most previous symbol used.
        subscripts = subscripts + 1

        #If no input is within the equation
        #text box or all input has been erased,
        #write the recently selected element symbol
        #to the equation text box with an associated
        #subscript of 1.
        if(subscripts == 1):

            #write the recently chosen element symbol
            #to the equation text box
            equation.write(molar12)

            #record the most recent element symbol by
            #assigning it to the prev variable.
            prev = molar12

            #The new element symbol represents a row;
            #increment the row variable...
            rows = rows + 1

            #append the recently chosen element symbol
            #to the history record arrName2 so it can be
            #referenced as needed within the chemical equation
            #balancing functions...
            arrName2.append(molar12)

        #In the case that there is some form of input
        #present within the equation text box...
        else:

            #If the same element as the previous has just been selected and no other forms of input in the form of a plus sign or greater than sign
            #came before, append the current subscript value to the input string within the equation text box.
            if(molar12 == prev and equation.GetValue()[len(equation.GetValue()) - 1] != '+' and equation.GetValue()[len(equation.GetValue()) - 1] != '>'):

                #Should the subscript be equal to two, just append the
                #subscript value to the input string within the equation
                #text box.
                if(subscripts == 2):
                    equation.write(str(subscripts))
                    chemEquation = equation.GetValue()

                #If the subscript value is greater than two,
                #extract the input string from the equation text
                #box and form into a list of characters. Next, pop
                #the last subscript value from the end of the list
                #and replace with the new subscript value; follow this step
                #with the clearing of the contents within the equation text box.
                #Finally, take the list representing the new input chemcial equation,
                #form into a string, and write the string to the equation text box.
                else:

                    #convert input string to list format...
                    list1 = list(chemEquation)

                    #pop the last subscript value from the
                    #list...
                    list1.pop()

                    #append the new subscript value to the list...
                    list1.append(str(subscripts))

                    #clear the old input string from the equation
                    #text box...
                    equation.Clear()

                    #Convert the new input representation from
                    #list format to string format and write to
                    #the equation text box...
                    equation.write(''.join(list1))

            #If an element different from the previous has been selected,
            #reset the subscripts variable to 1 and prev variable to the recently
            #selected element symbol, and then write the new symbol to 
            #the equation text box.
            else:

                #reset the subscripts variable
                #to one...
                subscripts = 1

                #reset the prev variable to the recently
                #selected element symbol...
                prev = molar12

                #If an element symbol separator in the form of a plus sign or greater than sign is confronted as the most previous input and the recently selected element
                #symbol is not within the arrName2 history, append it to the arrName2 history list.
                if((equation.GetValue()[len(equation.GetValue()) - 1] == '+' or equation.GetValue()[len(equation.GetValue()) - 1] == '>') and Notcontains2(molar12,arrName2)):

                    #If this block is entered, it means a new element was encountered, and since
                    #each row is associated with a unique element, the row variable should be
                    #incremented...
                    rows = rows + 1

                    #append the new element to the arrName2 list...
                    arrName2.append(molar12)

                #Write he new element symbol to the equation
                #text box.
                equation.write(molar12)

#END OF SECTION SIX--------------------------------------------------------------------------------

























#SECTION---SEVEN-------------------------------------------------------------------------------------------- 

#notAppended() serves the same purpose
#as Notcontains2(), only it doesn't accept
#parameters and is ONLY used within the
#chemical equation balancing functions.
def notAppended():
    global arrName
    global sub

    for rt in arrName:
        if(rt == sub):
            return 0
    #no match was made                                                                                                                                                                                                                   
    return 1

#alphaInLine() checks a string
#for a presence of any letters.
def alphaInLine(line):
    for x in line:
        if(x.isalpha()):
            return 1
    return 0

#The Notcontains2() function is used
#within the chemicalEquation function to check
#if a selected element symbol is within the arrName2
#history list.
def Notcontains2(component, data):
    for g in data:
        if(g == component):
            return 0

    #if data does not contain component
    #return 1 to proceed with row incrementing
    return 1

#END OF SECTION SEVEN--------------------------------------------------------------------------------





























#SECTION---EIGHT-------------------------------------------------------------------------------------------- 
#This section is responsible for detecting if the constructed
#chemical equation has the wrong format

#The EquationWrong() function is responsible for
#returning an error code should the chemical equation
#within the equation text box have the wrong format.
def EquationWrong():

    #The equation global variable isn't
    #actually modified in this case, but is declared
    #to let any readers know that it is repeatedly
    #utilized to get the value within the text box
    #it references.
    global equation
    #
    #arrName serves the same purpose as arrName2, only
    #in this case it is used to detect errors within
    #the chemical equation. arrName2 could have been used,
    #but doing so wouldn't take into account potential unknown elements that
    #the user could introduce into the text box through the keyboard
    #(the user can also use the keyboard for providing input). For instance,
    #when the user is done punching in input via buttons, the arrName2 will
    #hold a record of all elements, but this is only because the function
    #responsible upholding arrName2's history is binded to the input buttons; if the user
    #were to type in an element symbol (not using the buttons), the arrName2 variable wouldn't keep
    #a record of the new element symbol. Thus, creating a new element list
    #is necessary during the chemical equation balancing process.
    global arrName
    #
    #The sub global variable assists in the process of finding
    #unique elements to store in arrName.
    global sub

    #initialize sub and arrName variables
    sub = ""
    arrName = []

    #get contents of text box
    chem = equation.GetValue()

    #Make sure + and -> components have a presence.
    #If not, immediately return an error code.
    if(not('+' in chem and '->' in chem)):
        return -2


    #Make sure there isn't more than one reaction symbol: ->
    #Perform a splice right after the first -> and see if another -> is present
    #in the second substring. If so, immediately return an error code.
    if(chem.index('->') + 2 < len(chem)):
        splice = chem[chem.index('->') + 2:len(chem)]
        if('->' in splice):
            return -3


    #Check for appropriate pairing/contents of parentheses if present. If
    #the contents or pairing is flawd, return an error code.
    code = BracketParentheseMatch(chem,'(',')')
    if(code != 0):
        return code

    #Check for appropriate pairing/contents/position of brackets if present.
    #If the pairing, contents, or positioning is wrong, return an error code.
    code = BracketParentheseMatch(chem,'[',']')
    if(code != 0):
        return code




    #bare bones equation must contain no coefficients,lone partial segments, or sequential +/-/> characters
    for BonJovie in range(len(chem)):

        #The very first element cannot be a digit, '-' or '>' character, and cannot be a '+' character
        if((chem[BonJovie].isdigit() or chem[BonJovie] == '-' or chem[BonJovie] == '>' or chem[BonJovie] == '+') and BonJovie == 0):
            return -1

        #The equation cannot end with a '+'
        elif(chem[BonJovie] == '+' and (BonJovie + 1 == len(chem))):
            return -1

        #The equation cannot have an inappropriate placement of +,-,> characters or inappropriate placement of coefficients
        elif(chem[BonJovie] == '+' and (chem[BonJovie + 1] == '+' or chem[BonJovie + 1].isdigit() or chem[BonJovie + 1] == '-' or chem[BonJovie + 1] == '>')):
            if(not('[' in chem and chem[BonJovie - 1] == '[')):
                return -1

        #The equation cannot end with a '-'
        elif(chem[BonJovie] == '-' and (BonJovie + 1 == len(chem))):
            return -1

        #The equation cannot have an inappropriate placement of +,-,> characters or inappropriate placement of coefficients
        elif(chem[BonJovie] == '-' and (chem[BonJovie + 1] == '+' or chem[BonJovie + 1].isdigit() or chem[BonJovie + 1] == '-' or chem[BonJovie + 1].isalpha())):
            if(not('[' in chem and chem[BonJovie - 1] == '[')):
                return -1

        #The equation cannot end with a > character
        elif(chem[BonJovie] == '>' and (BonJovie + 1 == len(chem))):

            #If the previous character is a '-' character
            #return the '1' error code
            if(chem[BonJovie - 1] == '-'):
                return 1

            #return the -1 error code
            return -1
        
        #If the current character is '>' and there is not a '-'
        #character before it, return a -1 error code
        elif(chem[BonJovie] == '>' and (chem[BonJovie - 1] != '-')):
            return -1



    #if all is good so far, loop through all elements with counter
    countMe = 0

    #Print the current chemical equation to the terminal
    #window
    print(chem)

    #put together two separate lists of elemnts, one that
    #accounts for all elements on the reactant side and one
    #that accounts for all elements on the product side...
    arOne = []
    arTwo = []

    #flag indicating that the '->' symbol has been passed up...
    On = False
    
    #loop through and put together a list of elements 
    for k in chem:

        #only take interest if the current character represents a letter
        if(k.isalpha()):

            #if the character is an upper case letter and the current
            #length of the sub string variable is 0, append the letter to
            #to the sub variable.
            if(k.isupper() and len(sub) == 0):

                #append the upper case character to the sub variable
                sub += k

                #if the next element isn't a lower case letter, then an element has just been appended to the
                #sub variable. Check if the lement has already been appended to arrName...if not, append it...
                #if yes, then ignore it. 
                if((countMe + 1 == len(chem) or not(chem[countMe + 1].islower())) and notAppended()):
                    arrName.append(sub)

                    #when finished appending to arrName, clear the sub
                    #variable
                    sub = ""

                #if the current letter isn't a part of a two letter element symbol and is already appended
                #to the arrName list, erase the sub variable...
                elif((countMe + 1 == len(chem) or not(chem[countMe + 1].islower())) and not(notAppended())):

                    #erase the sub variable by resetting to an empty string...
                    sub = ""

            #if the current character is a lowercase letter and the
            #lenth of the sub variable is equal to one (meaning an upper case letter is
            #already stored in it), then a full element has just been come across; the lower case
            #letter should be concatenated to the end of the sub variable and then the sub variable
            #should be appended to arrName if it's not already present...
            elif(k.islower() and len(sub) == 1):

                #concatenate the lower case letter to the end of sub
                sub += k

                #check if the current element is already within arrName
                if(notAppended()):

                    #append sub to arrName if not present
                    #within arrName already
                    arrName.append(sub)

                #after appending, clear the sub variable
                sub = ""

            #If the current letter is lower case and the sub variable
            #has a length of zero, return an error code since no element
            #begins with a lower case letter.
            elif(k.islower() and len(sub) == 0):

                #clear arrName for the next attempt
                arrName = []

                #return error code three
                return 3

        #increment countMe, which acts
        #as an index in each iteration
        countMe = countMe + 1

    
    #no errors found
    return 0



#BracketPareentheseMatch ensures that all of the brackets and parenthesis within
#the equation match. If not, an error code is returne...
def BracketParentheseMatch(chemLine,left,right):

    #check for proper parentheses usage by utilizing the
    #following variables to make sure the same number of each
    #parenthesis/bracket type are used...
    SamWinchester = 0
    DeanWinchester = 0

    #first check if potential pairs are present
    if(right in chemLine and not(left in chemLine)):
        return 2
    elif(left in chemLine and not(right in chemLine)):
        return 2

    #Enter this block if a right and left form of bracket/parenthesis
    #were found within the chemLine. Now additional analysis in the form
    #of the number of each type needs to be performed...
    elif(left in chemLine and right in chemLine):

        #check for same number of parentheses of each type
        for x in chemLine:
            if(x == left):
                SamWinchester = SamWinchester + 1
        for x in chemLine:
            if(x == right):
                DeanWinchester = DeanWinchester + 1

        #if both variabes used above do not equal each other,
        #return error code two
        if(SamWinchester != DeanWinchester):
            return 2

        #if the same number of parenthesis for each type are found,
        #make sure pairing is done correctly...
        else:

            #check for appropriate pairing of parentheses/brackets
            #by utilizing the one/two variables
            one = 0
            two = 0

            #perform the check for appropriate parenthesis/bracket
            #pairing
            for x in chemLine:
                if(x == right or x == left):
                    if(x == left and one == 0):
                        one = 2
                    elif(x == right and one != 0 and two == 0):
                        two = 2
                    else:
                        return 2
                    if(one != 0 and two != 0):
                        one = 0
                        two = 0


    #check for proper contents of the brackets/parentheses
    #first get index values for all left and right components
    indecesL = []
    indecesR = []

    #get the index values of the brackets/parentheses
    for s in range(len(chemLine)):
        if(chemLine[s] == left):
            indecesL.append(s)
        elif(chemLine[s] == right):
            indecesR.append(s)

    #second, start pulling substrings that are within the brackets/parentheses
    #and start searching the contents!

    #The error code to be returned is initialy assigned
    #the value None...
    num = None

    #Brackets are associated with the error code
    #five and parentheses are associated with the error code
    #seven...
    if(left == '('):
        num = 5
    else:
        num = 7

    #perform the process of pulling substrings contained within the brackets/parentheses
    #and searching for appropriate content...
    for x in range(len(indecesL)):

        #Pull a substring from the first set of parentheses/brackets...
        CaptJackSparrow = chemLine[indecesL[x] + 1: indecesR[x]]
        if('>' in CaptJackSparrow):
            return num

        #special case number 1 (user forgets to give input to parenthese or bracket pairs)
        elif(CaptJackSparrow == ""):

            #return error code nine if no contents for a pair or pairs of parentheses
            #was given...
            if(left == '('):
                return 9

            #return error code eleven if no conetents for a pair or pairs of brackets
            #was given...
            else:
                return 11

        #The very first element within a pair of brackets or parentheses should
        #not be a digit...
        elif(CaptJackSparrow[0].isdigit()):
            return num

        #The '-' character cannot be within a set of
        #parentheses
        elif('-' in CaptJackSparrow and right == '('):
            return num

        #The '+' character cannot be within a set of
        #parentheses
        elif('+' in CaptJackSparrow and right == '('):
            return num

        #special case number 2: The user ends the equation right after a right parenthese or forgets to put
        #a subscript right after a right parenthese, throw error code ten...
        elif(right == ')' and not(indecesR[x] + 1 != len(chemLine) and chemLine[indecesR[x] + 1].isdigit())):
            return 10

        #If brackets occur within a set of parentheses, throw error code num...
        elif(('[' in CaptJackSparrow or ']' in CaptJackSparrow) and right == '('):
            return num

        #If parentheses occur within a set of brackets, throw error code num...
        elif(('(' in CaptJackSparrow or ')' in CaptJackSparrow) and right == '['):
            return num

        #Letters cannot occur within brackets, only charges (digits) and the '+'
        #character or '-' character. If letters are present, throw error code num...
        elif(right == ']' and alphaInLine(CaptJackSparrow)):
            return num

        #Make sure that '-' is used correctly within brackets
        elif('-' in CaptJackSparrow and right == '['):

            #If the previous character is a left bracket and the right character is a digit, then so far, '-' is being used
            #correctly; perform further analysis. If not, immediately return error code num...
            if(CaptJackSparrow[CaptJackSparrow.index('-') - 1] == '[' and CaptJackSparrow[CaptJackSparrow.index('-') + 1].isdigit()):

                #Get the substring that goes from the righ digit element to the end of the current substring to
                #make sure that only digits are used.
                AlexRusso = CaptJackSparrow[CaptJackSparrow.index('-') + 1:]

                #If '-' appears again or '('/'+' appears, throw error code num...
                if('-' in AlexRusso or '(' in AlexRusso or '+' in AlexRusso):
                    return num

            #return error code num if the first condition was not met.
            else:
                return num

        #Make sure that '+' is used correctly within the brackets...
        elif('+' in CaptJackSparrow and right == '['):

            #If the previous character is a left bracket and the right character is a digit, then so far, '-' is being used
            #correctly; perform further analysis. If not, immediately return error code num...
            if(CaptJackSparrow[CaptJackSparrow.index('+') - 1] == '[' and CaptJackSparrow[CaptJackSparrow.index('+') + 1].isdigit()):

                #Get the substring that goes from the righ digit element to the end of the current substring to
                #make sure that only digits are used.
                MaxRusso = CaptJackSparrow[CaptJackSparrow.index('+') + 1:]

                #If '+' appears again or '-'/'(' appears, throw error code num...
                if('-' in MaxRusso or '(' in MaxRusso or '+' in MaxRusso):
                    return num

            #return error code num if the first condition was not met...
            else:
                return num




    #Check for appropriate positioning of paired brackets (if present)
    #use the indecesL and indecesR variables from above

    #first retrieve the correct error numbers
    if(left == '['):

        #Assign the error code that will be used when an error is confronted.
        #Like in this case, and above in some areas, a variable did not have to be used,
        #but it made the development process a lot easier while trying different layouts and modifying
        #certain areas that weren't working. For instance, rather than having to re-type various number codes
        #for different segments that might have to be re-done (if there is a faulty segment) just assign the numbers
        #to a variable, based on what is being tested, at the biginning and use the same variable throughout.
        num = 8

        #Loop through all parenthese/bracket pairs
        for x in range(len(indecesL)):

            #1. The first element of the chemical equation cannot be a bracket or parenthese.
            #2. A bracket or parenthese cannot come right after a '>', '+', or '-' character.
            #If any of these conditions are met, return the num error code...
            if(indecesL[x] == 0 or chemLine[indecesL[x] - 1] == '>' or chemLine[indecesL[x] - 1] == '+' or chemLine[indecesL[x] - 1] == '-'):
                return num

            #If the bracket is followed by a digit, letter, or '>' character, throw the num error code.
            #The first check within the condition below: indecesR[x]+1 != len(chemLine), ensures that an illegal memory search isn't performed.
            elif(indecesR[x]+1 != len(chemLine) and (chemLine[indecesR[x] + 1].isdigit() or chemLine[indecesR[x] + 1].isalpha() or chemLine[indecesR[x] + 1] == '>')):
                return num
            

    #return 0 if no error was found
    return 0

#END OF SECTION EIGHT-------------------------------------------------------------------------------- 























#SECTION---NINE-------------------------------------------------------------------------------------------- 
#Section Nine is dedicated to actually balancing a chemical equation.
#This section also holds responsibility for executing all error detection functions.


#basic solution balance...
def basicBalance(event):

    #global equation variable...
    global equation

    #gain access to AB global variable...
    global AB

    #answer text box...
    global answer

    #arrName variable...
    global arrName
    
    #get the equation within the equation
    #text box...
    chem = equation.GetValue()

    #get error code...
    code = EquationWrong()

    #return the code message...
    returnError(code)

    #see if code == 0...
    if(code != 0):

        #return from the function...
        return


    #go over all six possibilities...
    for x in range(7):

        #change AB
        AB = None

        #copy variable...
        copy = None
            
        #all possibilities...
        if(x == 0):
                
            #modify copy...
            copy = "H2O+"+chem+"+OH[-1]"
                
        elif(x == 1):
                
            #modify copy...
            copy = "OH[-1]+"+chem+"+H2O"

        elif(x == 2):
                
            #modify copy...
            copy = "OH[-1]+"+chem

        elif(x == 3):
                
            #modify copy...
            copy = "H2O+"+chem

        elif(x == 4):

            #modify copy...
            copy = chem+"+OH[-1]"

        elif(x == 5):
                
            #modify copy...
            copy = chem+"+H2O"

        else:
                
            #modify copy...
            copy = chem

        #change arrName...
        arrName = uniqueElements(copy)
            
        #balance...
        result = linearBalance(copy)
            
        #check AB...
        if(AB == None):

            #clear answer...
            answer.Clear()

            #clear equation...
            equation.Clear()
                
            #write answer...
            answer.write(result)
                
            #break out of loop...
            break

        elif(x == 6 and result == None):

            #clear answer text box...
            answer.Clear()
                
            #write message...
            answer.write("None of the linear algebra trials succeeded. Assuming the input equation is a redox equation, it is possible that it is still solvable if the number of elements (charge included if in the equation) is greater than the number of unknown coefficients; when the number of elements is greater than unknown coefficients by 2 or more, more than one free variable is introduced, and solving via linear algebra is no longer accurate. The next version of this software will include an Oxidation Number Solver within a half reaction algorithm in order to solve some of these unsolvable cases...")

#acid solution balance...
def acidBalance(event):

    #global equation variable...
    global equation

    #gain access to AB global variable...
    global AB

    #answer text box...
    global answer

    #arrName variable...
    global arrName
    
    #get the equation within the equation
    #text box...
    chem = equation.GetValue()

    #get error code...
    code = EquationWrong()

    #return the code message...
    returnError(code)

    #see if code == 0...
    if(code != 0):

        #return from the function...
        return


    #go over all six possibilities...
    for x in range(7):

        #change AB
        AB = None

        #copy variable...
        copy = None
            
        #all possibilities...
        if(x == 0):
                
            #modify copy...
            copy = "H2O+"+chem+"+H[+1]"
                
        elif(x == 1):
                
            #modify copy...
            copy = "H[+1]+"+chem+"+H2O"

        elif(x == 2):
                
            #modify copy...
            copy = "H[+1]+"+chem

        elif(x == 3):
                
            #modify copy...
            copy = "H2O+"+chem

        elif(x == 4):

            #modify copy...
            copy = chem+"+H[+1]"

        elif(x == 5):
                
            #modify copy...
            copy = chem+"+H2O"

        else:
                
            #modify copy...
            copy = chem

        #change arrName...
        arrName = uniqueElements(copy)
            
        #balance...
        result = linearBalance(copy)
            
        #check AB...
        if(AB == None):

            #clear answer...
            answer.Clear()

            #clear equation...
            equation.Clear()
                
            #write answer...
            answer.write(result)
                
            #break out of loop...
            break

        elif(x == 6 and result == None):

            #clear answer text box...
            answer.Clear()
                
            #write message...
            answer.write("None of the linear algebra trials succeeded. Assuming the input equation is a redox equation, it is possible that it is still solvable if the number of elements (charge included if in the equation) is greater than the number of unknown coefficients; when the number of elements is greater than unknown coefficients by 2 or more, more than one free variable is introduced, and solving via linear algebra is no longer accurate. The next version of this software will include an Oxidation Number Solver within a half reaction algorithm in order to solve some of these unsolvable cases...")


#get all unique elements...
def uniqueElements(half):

    #element list...
    L = []

    #segment variable...
    seg = ""
        
    #get elements in first half...
    for x in range(len(half)):

        #see if the character is capital...
        if(half[x].isupper() and len(seg) == 0):

            #update seg...
            seg = seg + half[x]

        elif(half[x].isupper()):

            #add seg to list...
            if(not(seg in L)):
                L.append(seg)

            #update seg...
            seg = "" + half[x]

        elif(half[x].islower()):

            #update seg...
            seg = seg + half[x]

            #add seg to list...
            if(not(seg in L)):
                L.append(seg)

            #update seg to length 0...
            seg = ""

        #the case that a capitol letter is last in the string...
        if(x == len(half)-1 and len(seg) == 1):

            #append seg...
            if(not(seg in L)):
                L.append(seg)

    #return list...
    return L
                

#get a list of elements...
def getElements(half):
        
    #element list...
    L = []

    #segment variable...
    seg = ""
        
    #get elements in first half...
    for x in range(len(half)):

        #see if the character is capital...
        if(half[x].isupper() and len(seg) == 0):

            #update seg...
            seg = seg + half[x]

        elif(half[x].isupper()):

            #add seg to list...
            L.append(seg)

            #update seg...
            seg = "" + half[x]

        elif(half[x].islower()):

            #update seg...
            seg = seg + half[x]

            #add seg to list...
            L.append(seg)

            #update seg to length 0...
            seg = ""

        #the case that a capitol letter is last in the string...
        if(x == len(half)-1 and len(seg) == 1):

            #append seg...
            L.append(seg)

    #return list...
    return L
            
#error code return...
def returnError(code):

    #global anser variable...
    global answer

    #If any errors are present within the chemical equationo, EquationWrong() above will return an error code value
    #to the code variable.
    if(code == -3 or code == -2 or code == -1 or code == 1 or code == 2 or code == 3 or code == 4 or code == 5 or code == 6 or code == 7 or code == 8 or code == 9 or code == 10 or code == 11 or code == 12):

        #If an error is found, clear the contents of the answer text box
        #and only display the error code message.
        answer.Clear()

        #All of the following blocks are didicated to error code conditions and
        #Their associated messages...
        if(code == -3):
            answer.write("Can't have more than one reaction symbol: ->. Try Again!")
        elif(code == -2):
            answer.write("Missing + and/or -> components! Try Again!\nIf + and/or -> are missing, it is not a valid chemical reaction.")
        elif(code == -1):
            answer.write("There is a coefficient present before a element/molecule and/or inapropriate placement of '+', '-', and/or '>' characters. Try Again!")
        elif(code == 1):
            answer.write("Incomplete chemical equation. Try Again!")
        elif(code == 2):
            answer.write("Either the number of parentheses of each type are unbalanced (there must be the same # of ( and ) parenthesese) or the parenthesese of each type are not paired correctly -> (pair). Try Again!")
        elif(code == 3):
            answer.write("Invalid Element Input! Try Again!")
        elif(code == 4):
            answer.write("Either the number of brackets of each type are unnbalanced (there must be the same # of [ and ] brackets) or the brackets of each type are not paired correctly -> [pair]. Try Again!")
        elif(code == 5):
            answer.write("Parenthese pair contents is incorrect. Try Again!")
        elif(code == 6):
            answer.write("Parenthese pair positioning is incorrect. Try Again!")
        elif(code == 7):
            answer.write("Bracket pair contents is incorrect. Try Again!")
        elif(code == 8):
            answer.write("Bracket pair positioning is incorrect. Try Again!")
        elif(code == 9):
            answer.write("Parenthese pair has no contents. Try Again!")
        elif(code == 10):
            answer.write("Incorrect use of Parenthese. There should be a subscript after the right parenthese. For instance:\nCu3(PO4)2")
        elif(code == 11):
            answer.write("Bracket pair has no contents. Try Again!")
        elif(code == 12):
            answer.write("Not a valid chemical equation. Try Again!")


#check if element is in substring...
def inSubstring(el, substring):


    #check if el is length 2...
    if(len(el) == 2):
        if(el in substring):
            return substring.index(el)
        else:
            return -1
    else:
        for x in range(len(substring)):
            if(substring[x] == el and x+1 != len(substring) and not(substring[x+1].islower())):

                return x

            elif(substring[x] == el and x+1 == len(substring)):

                return x

        return -1
            
    
#Perform the process of balancing the chemical equation given
#by the user...
def balanceEquation(event):

    #acid/base flag variable...
    global AB
    
    #Nothing within the equation
    #is modified, but since it is referenced,
    #it is mentiond within the global variable
    #section.
    global equation

    #Not used for anything important at the moment, but
    #did serve a big purpose during testing. It will stay
    #here if a need for it should arise again; this would
    #involve modifying its value.
    global output

    #The number of columns required for the
    #coefficient matrix.
    global columns

    #The number of rows required for the
    #coefficient matrix.
    global rows

    #A free variable that was used for experimenting. It's global
    #declaration will remain here in case it is needed again.
    global up

    #Not modified in this section, but is referenced
    #a couple of times. This declaration serves the purpose
    #of reminding any readers that the global variable arrName
    #is used for extracting the list values associatd with it.
    global arrName

    #This variable is no longer utilized within this function
    #but will remain here in case a design change occurs in the future.
    global sub

    #The value associated with answer isn't actually modified,
    #but it is referenced so the actual answer can be written to 
    #the answer text box.
    global answer

    #Subscripts was accessed within this function at one
    #point as well, but no more due to design changes. This delcaration
    #will remain here in case another change occurrs in the future.
    global subscripts


    #get string value of text box
    chem = equation.GetValue()
              
    #Perform initial security check
    #first to see if the chemical equation
    #provided by the user is valid...
    code = EquationWrong()

    #display the error...
    returnError(code)

    #see if there was an error...
    if(code != 0):

        #return since there was an error...
        return

  
    #get all indeces of '+' in the chemical equation....

    #substring will hold all of the element/compound segments that
    #exist in betweeen '+' and '->' symbols...
    substring = []

    #holds the indeces of all '+' characters
    indeces = []

    #Used for pulling substrings that are between
    #the '+' and '->' symbols
    countMe = 0

    #Get all indeces associatedd with the '+'
    #characters.
    for g in range(len(chem)):
        if(chem[g] == '+' or chem[g] == '-'):
            if(chem[g - 1] != '['):
                indeces.append(g)

    #now extract the substrings and append them
    #to the list associated with the substring variable.
    for g in range(len(indeces) + 1):
        if(countMe == 0):
            substring.append(chem[:indeces[g]])
            countMe = indeces[g]
        elif(g < len(indeces)):
            substring.append(chem[countMe:indeces[g]])
            countMe = indeces[g]
        else:
            substring.append(chem[countMe:])

    #The number of rows present within the
    #coefficient matrix be the same as the number of
    #unique elements present within the chemical equation.
    rows = len(arrName)
    
    #make sure to account for charges
    #(a row is reserved for all charges)
    if('[' in chem):
        rows += 1

    #The number of substrings extracted from
    #the chemical equation will be the same as the
    #number of columns needed within the coefficient matrix.
    columns = len(substring)

    #initial matrix template
    matrix = [[]] * rows
        
    #Insert all collumns into the matrix template
    for x in range(rows):
        matrix[x] = [0] * columns


    #now create the matrix... But first add all values:

    #Right now we only care about the values associated
    #with elements. Reduce the row variable for now if charges
    #are present.
    if('[' in chem):
        tempRow = rows - 1
    else:
        tempRow = rows

    #look over elements first
    for x in range(tempRow):

        #Get an element symbol from
        #the arrName list
        el = arrName[x]

        #Used to indiciate if the products portion of the
        #chemical equation has been reached (after the '->' symbol)...
        flag9 = 0

        #Add values to each column for the
        #corresponding row...
        for k in range(columns):
                
            #Enter this block if the element is within one of the
            #pulled substrings...
            nindex = inSubstring(el, substring[k])
            if(el in substring[k] and nindex > -1):

                #enter this block if the element symbol is only one capital letter.
                if(len(el) == 1):

                    #Detect if a digit comes after the element symbol. If so, assign that digit value to the matrix cell
                    if((nindex + 1 != len(substring[k])) and substring[k][nindex + 1].isdigit()):

                        #Get the entire subscript...
                        #First get an even smaller substring
                        sty = substring[k][nindex + 2:]
                        
                        #now based on the smaller substring, extract the whole subscript
                        #(it most likely will only be one digit, but it could be more)
                        subscript2 = substring[k][nindex + 1]
                        for gh in range(len(sty)):

                            #check if the current element is a digit, and if so,
                            #append it to subscript2
                            if(sty[gh].isdigit()):

                                #append the digit to subscript2
                                subscript2 += sty[gh]

                            #if the element is not a digit, then the end of all subscript
                            #recording is done...
                            else:

                                #break out of the for loop
                                break

                        #once '->' has been passed, all subscript values must
                        #be multiplied by negative one.
                        if(('>' in substring[k]) or flag9 == 100):
                            matrix[x][k] = -1 * int(subscript2)
                            if(flag9 == 0):
                                flag9 = 100
                        
                        #If '->' has not been passed, assign the positive value
                        #to matrix...
                        else:
                            matrix[x][k] = int(subscript2)

                    #If not digit is detected after the element symbol, assign a value of
                    #positive or negative one...
                    else:
                        if('>' in substring[k] or flag9 == 100):
                            matrix[x][k] = -1
                            if(flag9 == 0):
                                flag9 = 100
                        else:
                            matrix[x][k] = 1

                #If an element made of two letters (one capital and one lowercase), move two elements ahead in order to
                #begin getting the subscript...
                else:

                    #Detect if a digit comes after the element symbol, and if so, assing that value to the matrix...
                    if((nindex + 2 != len(substring[k])) and substring[k][nindex + 2].isdigit()):

                        #Get the entire subscript...
                        #First get an even smaller substring
                        sty = substring[k][nindex + 3:]
                        
                        #now based on the smaller substring, extract the whole subscript
                        #(it most likely will only be one digit, but it could be more)
                        subscript3 = substring[k][nindex + 2]
                        for gh in range(len(sty)):

                            #check if the current element is a digit, and if so,
                            #append it to subscript2
                            if(sty[gh].isdigit()):

                                #append the digit to subscript2
                                subscript3 += sty[gh]

                            #if the element is not a digit, then the end of all subscript
                            #recording is done...
                            else:

                                #break out of the for loop
                                break

                        #If the '->' symbol has been passed,
                        #assign the subscript value multiplied by -1
                        if('>' in substring[k] or flag9 == 100):
                            matrix[x][k] = -1 * int(subscript3)
                            if(flag9 == 0):
                                flag9 = 100

                        #assign the positive version of the subscript if
                        #the '->' symbol has not been passed...
                        else:
                            matrix[x][k] = int(subscript3)

                    #assign a value of one or negative one if no
                    #digit is found after the element symbol...
                    else:
                        if('>' in substring[k] or flag9 == 100):
                            matrix[x][k] = -1
                            if(flag9 == 0):
                                flag9 = 100
                        else:
                            matrix[x][k] = 1
                
                #make sure to incorporate digit after parenthese if any
                #for instance: (H2SO4)2

                #first make sure that the element is actually within the parenthesis
                if(')' in substring[k]):

                    #check if the location of the element symbol is within the bounds of the parenthese pair...
                    if((nindex > substring[k].index('(')) and (nindex < substring[k].index(')'))):

                        #Get the entire subscript...
                        #First get an even smaller substring
                        stm = substring[k][substring[k].index(')') + 1:]
                        
                        #now based on the smaller substring, extract the whole subscript
                        #(it most likely will only be one digit, but it could be more)
                        subscript4 = ""
                        for gh in range(len(stm)):

                            #check if the current element is a digit, and if so,
                            #append it to subscript2
                            if(stm[gh].isdigit()):

                                #append the digit to subscript2
                                subscript4 += stm[gh]

                            #if the element is not a digit, then the end of all subscript
                            #recording is done...
                            else:

                                #break out of the for loop
                                break

                        #assign the subscript4 value to the matrix cell...
                        matrix[x][k] = matrix[x][k] * int(subscript4)
                
            #Make sure to indicate if a crossover from the ractants to
            #the products side of the chemical equation ahs been reached
            #by assigning the flag9 variable the value 100.
            else:
                if('>' in substring[k]):
                    flag9 = 100
    
    #Now look over the charges
    if('[' in chem):

        #reset the flag9 variable
        flag9 = 0

        #go over each substring..
        for y in range(columns):

            #Assign a charge value to the matrix if brackets
            #are present...
            if('[' in substring[y]):

                #Receive the charge value within the bracket pair...
                Megatron = int(substring[y][substring[y].index('[') + 1:substring[y].index(']')])

                #Make megatron a negative value if '->' has been passed...
                if('>' in substring[y] or flag9 == 100):
                    matrix[rows-1][y] = Megatron * -1
                    if(flag9 == 0):
                        flag9 = 100

                #Leave megatron as a positive value if '->' has not
                #been passed...
                else:
                    matrix[rows-1][y] = Megatron

            #assign 100 to flag9 if '->' is passed...
            elif('>' in substring[y]):
                flag9 = 100

    #turn 2d array represented by the matrix variable 
    #into a sympy matrix...
    matrix = sympy.Matrix(matrix)
    
    #now balance the equation
    reduced = matrix.rref()

    if(IsUnbalanceable(reduced)):

        answer.Clear()
        answer.write("Equation is unbalanceable via linear algebra, due to no solution or more than one free variable. If the input equation is a redox equation, it is possible that it is still solvable if the number of elements (charge included if in the equation) is greater than the number of unknown coefficients; when the number of elements is greater than unknown coefficients, more than one free variable is introduced, and solving via linear algebra is no longer accurate....")
        return
    
    #Provide the balanced equation...
    else:

        #get individual equations from matrix
        arrEquations = []

        #create a blank equation variable
        equ = ""

        #hold in memory all lower case letters
        alphas = string.ascii_lowercase

        #counter for alphas
        counter = 0
        
        #hold a denominator value wheen necessary
        denominator = None

        #List of denominators
        denominators = []

        #increment variable...
        colCount = 1
        
        #n will be used to access the overall row and y will
        #be used to aid in creating separate equations to be evaluated...
        for n in range(columns * rows):

            #start writing the new equation
            if(reduced[0][n] == 1 and ((n+1)/columns != colCount)):
                equ += alphas[counter]+'='
                counter = counter + 1

            elif((n+1)/columns == colCount and not(reduced[0][n] < 0)):

                #check if n is on the last position...
                if(not(colCount == rows and reduced[0][n] == 0)):
                
                    answer.Clear()
                    answer.write("Inconclusive...")
                    return

            #The end of a row has been reached once a negative value
            #has been reached.
            elif(reduced[0][n] < 0 and (n+1)/columns == colCount):

                #invert the negative value and assign to equation
                equ += str(-1*reduced[0][n])

                #append the equation to the equations
                #structure
                arrEquations.append(equ)

                #reset equation variable
                equ = ""

                #store the inverted negative value in a temp
                #variable...
                temp = str(-1*reduced[0][n])

                #Find the greatest denominator value
                if(denominator == None and '/' in str(reduced[0][n])):
                    index = temp.index('/')
                    denominator = int(temp[index + 1:])
                elif('/' in str(reduced[0][n]) and int(temp[temp.index('/') + 1:]) > denominator):
                    denominator = int(temp[temp.index('/') + 1:])

                #save all denominators within structure so we can find Least common multiple later...
                if('/' in str(reduced[0][n])):
                    denominators.append(int(temp[temp.index('/') + 1:]))

                colCount = colCount + 1

            elif((n+1)/columns == colCount):

                #increment colCount...
                colCount = colCount + 1

        #find the least common multiple if denominators were present
        if(denominator != None and len(denominators) > 1):
            LCM = denominator
            BarneyStinson = 0
            while(BarneyStinson == 0):
                for x in range(len(denominators)):
                    if(LCM % denominators[x] != 0):
                        break
                    elif(LCM % denominators[x] == 0 and (x + 1 == len(denominators))):
                        BarneyStinson = 10
                        break
                if(BarneyStinson == 0):
                    LCM += 1

            denominator = LCM


        #output the new equation to terminal window
        print(arrEquations)

        #setup a new equation variable
        newE = ""

        #If no denominators were present after reduction
        if(denominator == None):
            
            #in the case of no fractions         
            coeff = 0

            #Create the new balanced chemical equation
            for u2 in range(len(list(chem))):
                if(u2 == 0 or (((list(chem)[u2 - 1] == '+' and list(chem)[u2-2] != '[') or list(chem)[u2 - 1] == '>') and coeff != len(arrEquations))):
                    newE += str(arrEquations[coeff][arrEquations[coeff].index('=') + 1:])
                    newE += chem[u2]
                    coeff = coeff + 1
                else:
                    newE += chem[u2]

        #if denominators were present after reduction
        else:

            #in the case of fractions                 
            coeff = 0

            #create the new balanced chemical equation
            for u2 in range(len(list(chem))):
                if(u2 == 0 or (((list(chem)[u2 - 1] == '+' and list(chem)[u2-2] != '[') or list(chem)[u2 - 1] == '>') and coeff != len(arrEquations))):
                    str1 = arrEquations[coeff][arrEquations[coeff].index('=') + 1:]

                    #Make sure to multiply by the value within denominator...
                    if('/' not in str1):
                        newE += str(int(arrEquations[coeff][arrEquations[coeff].index('=') + 1:]) * denominator)
                        newE += chem[u2]

                    #If '/' is in the equation, divide the numerator and denominator and then
                    #multiply by the vale within denominator...
                    else:
                        num1 = str1[:str1.index('/')]
                        num2 = str1[str1.index('/') + 1:]
                        num3 = int((int(num1) / int(num2)) * denominator)
                        if(num3 != 1):
                            newE += str(num3)
                        newE += chem[u2]
                    coeff = coeff + 1
                elif((list(chem)[u2 - 1] == '+' and list(chem)[u2-2] != '[') or list(chem)[u2 - 1] == '>'):
                    newE += str(denominator)
                    newE += chem[u2]
                else:
                    newE += chem[u2]
            
        
    #write new equation to the answer text box
    answer.write("\n" + newE)

    #Now erase the contents of the equation
    #textbox
    equation.Clear()
    subscripts = 0

    #reset variables
    columns = 0
    rows = 0



#Perform the process of balancing the chemical equation given
#by the user...
def linearBalance(chem):

    #acid/base flag variable...
    global AB
    
    #Nothing within the equation
    #is modified, but since it is referenced,
    #it is mentiond within the global variable
    #section.
    global equation

    #Not used for anything important at the moment, but
    #did serve a big purpose during testing. It will stay
    #here if a need for it should arise again; this would
    #involve modifying its value.
    global output

    #The number of columns required for the
    #coefficient matrix.
    global columns

    #The number of rows required for the
    #coefficient matrix.
    global rows

    #A free variable that was used for experimenting. It's global
    #declaration will remain here in case it is needed again.
    global up

    #Not modified in this section, but is referenced
    #a couple of times. This declaration serves the purpose
    #of reminding any readers that the global variable arrName
    #is used for extracting the list values associatd with it.
    global arrName

    #This variable is no longer utilized within this function
    #but will remain here in case a design change occurs in the future.
    global sub

    #The value associated with answer isn't actually modified,
    #but it is referenced so the actual answer can be written to 
    #the answer text box.
    global answer

    #Subscripts was accessed within this function at one
    #point as well, but no more due to design changes. This delcaration
    #will remain here in case another change occurrs in the future.
    global subscripts
  
    #get all indeces of '+' in the chemical equation....

    #substring will hold all of the element/compound segments that
    #exist in betweeen '+' and '->' symbols...
    substring = []

    #holds the indeces of all '+' characters
    indeces = []

    #Used for pulling substrings that are between
    #the '+' and '->' symbols
    countMe = 0

    #Get all indeces associatedd with the '+'
    #characters.
    for g in range(len(chem)):
        if(chem[g] == '+' or chem[g] == '-'):
            if(chem[g - 1] != '['):
                indeces.append(g)

    #now extract the substrings and append them
    #to the list associated with the substring variable.
    for g in range(len(indeces) + 1):
        if(countMe == 0):
            substring.append(chem[:indeces[g]])
            countMe = indeces[g]
        elif(g < len(indeces)):
            substring.append(chem[countMe:indeces[g]])
            countMe = indeces[g]
        else:
            substring.append(chem[countMe:])

    #The number of rows present within the
    #coefficient matrix be the same as the number of
    #unique elements present within the chemical equation.
    rows = len(arrName)

    #make sure to account for charges
    #(a row is reserved for all charges)
    if('[' in chem):
        rows += 1

    #The number of substrings extracted from
    #the chemical equation will be the same as the
    #number of columns needed within the coefficient matrix.
    columns = len(substring)

    #initial matrix template
    matrix = [[]] * rows
        
    #Insert all collumns into the matrix template
    for x in range(rows):
        matrix[x] = [0] * columns


    #now create the matrix... But first add all values:

    #Right now we only care about the values associated
    #with elements. Reduce the row variable for now if charges
    #are present.
    if('[' in chem):
        tempRow = rows - 1
    else:
        tempRow = rows

    #look over elements first
    for x in range(tempRow):

        #Get an element symbol from
        #the arrName list
        el = arrName[x]

        #Used to indiciate if the products portion of the
        #chemical equation has been reached (after the '->' symbol)...
        flag9 = 0

        #Add values to each column for the
        #corresponding row...
        for k in range(columns):
                
            #Enter this block if the element is within one of the
            #pulled substrings...
            nindex = inSubstring(el, substring[k])
            if(el in substring[k] and nindex > -1):

                #enter this block if the element symbol is only one capital letter.
                if(len(el) == 1):

                    #Detect if a digit comes after the element symbol. If so, assign that digit value to the matrix cell
                    if((nindex + 1 != len(substring[k])) and substring[k][nindex + 1].isdigit()):

                        #Get the entire subscript...
                        #First get an even smaller substring
                        sty = substring[k][nindex + 2:]
                        
                        #now based on the smaller substring, extract the whole subscript
                        #(it most likely will only be one digit, but it could be more)
                        subscript2 = substring[k][nindex + 1]
                        for gh in range(len(sty)):

                            #check if the current element is a digit, and if so,
                            #append it to subscript2
                            if(sty[gh].isdigit()):

                                #append the digit to subscript2
                                subscript2 += sty[gh]

                            #if the element is not a digit, then the end of all subscript
                            #recording is done...
                            else:

                                #break out of the for loop
                                break

                        #once '->' has been passed, all subscript values must
                        #be multiplied by negative one.
                        if(('>' in substring[k]) or flag9 == 100):
                            matrix[x][k] = -1 * int(subscript2)
                            if(flag9 == 0):
                                flag9 = 100
                        
                        #If '->' has not been passed, assign the positive value
                        #to matrix...
                        else:
                            matrix[x][k] = int(subscript2)

                    #If not digit is detected after the element symbol, assign a value of
                    #positive or negative one...
                    else:
                        if('>' in substring[k] or flag9 == 100):
                            matrix[x][k] = -1
                            if(flag9 == 0):
                                flag9 = 100
                        else:
                            matrix[x][k] = 1

                #If an element made of two letters (one capital and one lowercase), move two elements ahead in order to
                #begin getting the subscript...
                else:

                    #Detect if a digit comes after the element symbol, and if so, assing that value to the matrix...
                    if((nindex + 2 != len(substring[k])) and substring[k][nindex + 2].isdigit()):

                        #Get the entire subscript...
                        #First get an even smaller substring
                        sty = substring[k][nindex + 3:]
                        
                        #now based on the smaller substring, extract the whole subscript
                        #(it most likely will only be one digit, but it could be more)
                        subscript3 = substring[k][nindex + 2]
                        for gh in range(len(sty)):

                            #check if the current element is a digit, and if so,
                            #append it to subscript2
                            if(sty[gh].isdigit()):

                                #append the digit to subscript2
                                subscript3 += sty[gh]

                            #if the element is not a digit, then the end of all subscript
                            #recording is done...
                            else:

                                #break out of the for loop
                                break

                        #If the '->' symbol has been passed,
                        #assign the subscript value multiplied by -1
                        if('>' in substring[k] or flag9 == 100):
                            matrix[x][k] = -1 * int(subscript3)
                            if(flag9 == 0):
                                flag9 = 100

                        #assign the positive version of the subscript if
                        #the '->' symbol has not been passed...
                        else:
                            matrix[x][k] = int(subscript3)

                    #assign a value of one or negative one if no
                    #digit is found after the element symbol...
                    else:
                        if('>' in substring[k] or flag9 == 100):
                            matrix[x][k] = -1
                            if(flag9 == 0):
                                flag9 = 100
                        else:
                            matrix[x][k] = 1
                
                #make sure to incorporate digit after parenthese if any
                #for instance: (H2SO4)2

                #first make sure that the element is actually within the parenthesis
                if(')' in substring[k]):

                    #check if the location of the element symbol is within the bounds of the parenthese pair...
                    if((nindex > substring[k].index('(')) and (nindex < substring[k].index(')'))):

                        #Get the entire subscript...
                        #First get an even smaller substring
                        stm = substring[k][substring[k].index(')') + 1:]
                        
                        #now based on the smaller substring, extract the whole subscript
                        #(it most likely will only be one digit, but it could be more)
                        subscript4 = ""
                        for gh in range(len(stm)):

                            #check if the current element is a digit, and if so,
                            #append it to subscript2
                            if(stm[gh].isdigit()):

                                #append the digit to subscript2
                                subscript4 += stm[gh]

                            #if the element is not a digit, then the end of all subscript
                            #recording is done...
                            else:

                                #break out of the for loop
                                break

                        #assign the subscript4 value to the matrix cell...
                        matrix[x][k] = matrix[x][k] * int(subscript4)
                
            #Make sure to indicate if a crossover from the ractants to
            #the products side of the chemical equation ahs been reached
            #by assigning the flag9 variable the value 100.
            else:
                if('>' in substring[k]):
                    flag9 = 100
    
    #Now look over the charges
    if('[' in chem):

        #reset the flag9 variable
        flag9 = 0

        #go over each substring..
        for y in range(columns):

            #Assign a charge value to the matrix if brackets
            #are present...
            if('[' in substring[y]):

                #Receive the charge value within the bracket pair...
                Megatron = int(substring[y][substring[y].index('[') + 1:substring[y].index(']')])

                #Make megatron a negative value if '->' has been passed...
                if('>' in substring[y] or flag9 == 100):
                    matrix[rows-1][y] = Megatron * -1
                    if(flag9 == 0):
                        flag9 = 100

                #Leave megatron as a positive value if '->' has not
                #been passed...
                else:
                    matrix[rows-1][y] = Megatron

            #assign 100 to flag9 if '->' is passed...
            elif('>' in substring[y]):
                flag9 = 100

    #turn 2d array represented by the matrix variable 
    #into a sympy matrix...
    matrix = sympy.Matrix(matrix)
    
    #now balance the equation
    reduced = matrix.rref()

    print(reduced)
    
    #check if the equation can be balanced...
    if(IsUnbalanceable(reduced)):

        answer.Clear()
        AB = 23
        return

    #Provide the balanced equation...
    else:

        #get individual equations from matrix
        arrEquations = []

        #create a blank equation variable
        equ = ""

        #hold in memory all lower case letters
        alphas = string.ascii_lowercase

        #counter for alphas
        counter = 0
        
        #hold a denominator value wheen necessary
        denominator = None

        #List of denominators
        denominators = []

        #increment variable...
        colCount = 1
        
        #n will be used to access the overall row and y will
        #be used to aid in creating separate equations to be evaluated...
        for n in range(columns * rows):

            #start writing the new equation
            if(reduced[0][n] == 1 and ((n+1)/columns != colCount)):
                equ += alphas[counter]+'='
                counter = counter + 1

            elif((n+1)/columns == colCount and not(reduced[0][n] < 0)):

                #check if n is on the last position...
                if(not(colCount == rows and reduced[0][n] == 0)):
                
                    answer.Clear()
                    AB = 54
                    return

            #The end of a row has been reached once a negative value
            #has been reached.
            elif(reduced[0][n] < 0 and (n+1)/columns == colCount):

                #invert the negative value and assign to equation
                equ += str(-1*reduced[0][n])

                #append the equation to the equations
                #structure
                arrEquations.append(equ)

                #reset equation variable
                equ = ""

                #store the inverted negative value in a temp
                #variable...
                temp = str(-1*reduced[0][n])

                #Find the greatest denominator value
                if(denominator == None and '/' in str(reduced[0][n])):
                    index = temp.index('/')
                    denominator = int(temp[index + 1:])
                elif('/' in str(reduced[0][n]) and int(temp[temp.index('/') + 1:]) > denominator):
                    denominator = int(temp[temp.index('/') + 1:])

                #save all denominators within structure so we can find Least common multiple later...
                if('/' in str(reduced[0][n])):
                    denominators.append(int(temp[temp.index('/') + 1:]))

                #increment colCount...
                colCount = colCount + 1
                    
            elif((n+1)/columns == colCount):

                #increment colCount...
                colCount = colCount + 1

        #find the least common multiple if denominators were present
        if(denominator != None and len(denominators) > 1):
            LCM = denominator
            BarneyStinson = 0
            while(BarneyStinson == 0):
                for x in range(len(denominators)):
                    if(LCM % denominators[x] != 0):
                        break
                    elif(LCM % denominators[x] == 0 and (x + 1 == len(denominators))):
                        BarneyStinson = 10
                        break
                if(BarneyStinson == 0):
                    LCM += 1

            denominator = LCM


        #output the new equation to terminal window
        print(arrEquations)

        #setup a new equation variable
        newE = ""

        #If no denominators were present after reduction
        if(denominator == None):
            
            #in the case of no fractions         
            coeff = 0

            #Create the new balanced chemical equation
            for u2 in range(len(list(chem))):
                if(u2 == 0 or (((list(chem)[u2 - 1] == '+' and list(chem)[u2-2] != '[') or list(chem)[u2 - 1] == '>') and coeff != len(arrEquations))):
                    newE += str(arrEquations[coeff][arrEquations[coeff].index('=') + 1:])
                    newE += chem[u2]
                    coeff = coeff + 1
                else:
                    newE += chem[u2]

        #if denominators were present after reduction
        else:

            #in the case of fractions                 
            coeff = 0

            #create the new balanced chemical equation
            for u2 in range(len(list(chem))):
                if(u2 == 0 or (((list(chem)[u2 - 1] == '+' and list(chem)[u2-2] != '[') or list(chem)[u2 - 1] == '>') and coeff != len(arrEquations))):
                    str1 = arrEquations[coeff][arrEquations[coeff].index('=') + 1:]

                    #Make sure to multiply by the value within denominator...
                    if('/' not in str1):
                        newE += str(int(arrEquations[coeff][arrEquations[coeff].index('=') + 1:]) * denominator)
                        newE += chem[u2]

                    #If '/' is in the equation, divide the numerator and denominator and then
                    #multiply by the vale within denominator...
                    else:
                        num1 = str1[:str1.index('/')]
                        num2 = str1[str1.index('/') + 1:]
                        num3 = int((int(num1) / int(num2)) * denominator)
                        if(num3 != 1):
                            newE += str(num3)
                        newE += chem[u2]
                    coeff = coeff + 1
                elif((list(chem)[u2 - 1] == '+' and list(chem)[u2-2] != '[') or list(chem)[u2 - 1] == '>'):
                    newE += str(denominator)
                    newE += chem[u2]
                else:
                    newE += chem[u2]
            
        
    #write new equation to the answer text box
    return newE

    #reset subscripts
    subscripts = 0

    #reset variables
    columns = 0
    rows = 0

#END OF SECTION NINE--------------------------------------------------------------------------------
































#SECTION---TEN--------------------------------------------------------------------------------------------
#This section is responsible for detecting if a chemical equation is unbalanceable.

#Check to see if the chemical equation is balanceable or not
#when given the corresponding coefficient matrix...
def IsUnbalanceable(matrix):

    #The global columnas and rows variables
    #aren't actually being modified here, but they are
    #declared anyways to let the reader know that they will
    #be used throghout this function...
    global rows
    global columns

    #check for all zeros in rest of rows and for variable = 0
    if((rows == columns) or (rows == columns - 1)):
        num = FreeOrZero(rows,columns,matrix)
        if(num == 1):
            return 1
        else:
            return 0

    # check if there are two or more free variables right off the bat
    elif((columns - rows) > 1):
        return 1

    #for cases with more rows than columns
    #the last several rows will be full of zeros due to rref()
    #check the matrix as if it were a regular m x m matrix
    elif((rows - columns) >= 1):
       num = FreeOrZero(columns,columns,matrix) 
       if(num == 1):
           return 1
       else:
           return 0






#If another free variable is found or a row
#contains the form, 0 = 1 (indicating there is no solution).
def FreeOrZero(row,column,matrix):

    #both variables below are or counting
    #characteristics that indicate an unbalanceable
    #chemical equation...
    LordVoldemort = 0
    HarryPotter = 0

    #Go through each row, beginning with the last one...
    for t in range(row - 1,0,-1):

        #For each row, go through each column cell...
        for x in range((t * column) - column, t * column):

            #search for another free variable by counting
            #all zeros within the row
            if(matrix[0][x] == 0):
                LordVoldemort = LordVoldemort + 1

            #search for a one within the row...
            elif(matrix[0][x] == 1 or matrix[0][x] != 1):
                HarryPotter = HarryPotter + 1

        #If a whole row of zeros is found or a row with an ending
        #one is found, the equation is unbalnceable; return error code
        #one...
        if(LordVoldemort == column):
            return 1
        elif(HarryPotter == 1):
            return 1

        #reset variables
        LordVoldemort = 0
        HarryPotter = 0

    #No error found, return 0...
    return 0

#END OF SECTION TEN--------------------------------------------------------------------------------


































#SECTION---ELEVEN--------------------------------------------------------------------------------------------
#All of the buttons that make up the periodic table have to be linked to a certain function.
#This section acts as the director in choosing which function will be activated if a periodic table
#button is clicked. For instance, if the chemical equation balancing section is activated, the
#gobal molarVar variable will be set to 14, and whenever a periodic table button is clicked, the
#symbol will be transferred over to the chemical equation text box throgh the chemicalEquation function. However, if another mole conversion
#section is activated, the elementsTObox function will be entered instead.  

#array id classification functions:
def arrID1(event):
    global elementID
    global molarVar
    elementID = 1
    if(molarVar == 14):
        chemicalEquation(event)
    else:
        elementsTObox(event)

def arrID2(event):
    global elementID
    global molarVar
    elementID = 2
    if(molarVar == 14):
        chemicalEquation(event)
    else:
        elementsTObox(event)

def arrID3(event):
    global elementID
    global molarVar
    elementID = 3
    if(molarVar == 14):
        chemicalEquation(event)
    else:
        elementsTObox(event)

def arrID4(event):
    global elementID
    global molarVar
    elementID = 4
    if(molarVar == 14):
        chemicalEquation(event)
    else:
        elementsTObox(event)

def arrID5(event):
    global elementID
    global molarVar
    elementID = 5
    if(molarVar == 14):
        chemicalEquation(event)
    else:
        elementsTObox(event)

def arrID6(event):
    global elementID
    global molarVar
    elementID = 6
    if(molarVar == 14):
        chemicalEquation(event)
    else:
        elementsTObox(event)

def arrID7(event):
    global elementID
    global molarVar
    elementID = 7
    if(molarVar == 14):
        chemicalEquation(event)
    else:
        elementsTObox(event)

def arrID8(event):
    global elementID
    global molarVar
    elementID = 8
    if(molarVar == 14):
        chemicalEquation(event)
    else:
        elementsTObox(event)

def arrID9(event):
    global elementID
    global molarVar
    elementID = 9
    if(molarVar == 14):
        chemicalEquation(event)
    else:
        elementsTObox(event)

#END OF SECTION ELEVEN--------------------------------------------------------------------------------



























#SECTION---TWELEVE-------------------------------------------------------------------------------------------- 
#This section is responsible for deleting elements when a new problem is chosen.

#NOTE: Stoichiometry problems and chemical equation balancing problems can be
#      displayed simultaneously. -> Thus, deletions won't always be necessary.

#delete ratio objects
def delete1():
    
    #molarVar and set1 aren't modified
    #in this function anymore (they were at one point). However,
    #their declarations will stay here in case a design change occurs in the
    #future.
    global molarVar
    global set1

    #gain access to text boxes and buttons
    #so they can be appropriately destroyed
    #(Each variablel below corresponds to buttons
    #and text boxes). These variables don't actually
    #have to be accessed since the function is not assinging
    #them new values. However, they are declared here to let any
    #readers know that these are global variables used to reference
    #different text boxes and buttons.
    global input
    global first
    global second
    global third
    global fourth
    global fifth
    global sixth
    global seventh
    global eighth
    global answer
    global calculate
    global arrow
    global plus
    global Cosmo
    global Wanda
    global Robin
    global Batman
    global equation
    global output
    global calculate2
    global calculate3
    global calculate4
    global right
    global left
    global direction
    
    #delete a setup that corresponds to
    #a particular molarVar variable...
    if((molarVar == 10 or molarVar == 11)):
        input.Destroy()
        first.Destroy()
        second.Destroy()
        calculate.Destroy()
        answer.Destroy()

    elif(molarVar == 12):
        input.Destroy()
        first.Destroy()
        second.Destroy()
        third.Destroy()
        fourth.Destroy()
        answer.Destroy()
        calculate.Destroy()

    elif(molarVar == 13):
        input.Destroy()
        first.Destroy()
        second.Destroy()
        third.Destroy()
        fourth.Destroy()
        fifth.Destroy()
        sixth.Destroy()

        #delete the checkboxes associated with
        #molarVar == 13 setup.
        if(right != None and left != None):
            right.Destroy()
            left.Destroy()
            right = None
            left = None
        answer.Destroy()
        calculate.Destroy()
            
    elif(molarVar == 15):
            input.Destroy()
            first.Destroy()
            second.Destroy()
            third.Destroy()
            fourth.Destroy()
            fifth.Destroy()
            sixth.Destroy()
            seventh.Destroy()
            eighth.Destroy()
            answer.Destroy()
            calculate.Destroy()

    else:
            arrow.Destroy()
            plus.Destroy()
            equation.Destroy()
            Cosmo.Destroy()
            Wanda.Destroy()
            Robin.Destroy()
            Batman.Destroy()
            calculate2.Destroy()
            calculate3.Destroy()
            calculate4.Destroy()
            answer.Destroy()

    #set set1 back to zero
    set1 = 0
            
#END OF SECTION TWELVE-------------------------------------------------------------------------------- 
























#SECTION---THIRTEEN--------------------------------------------------------------------------------------------
#This section is dedicated to setting up all unit version problems -> Includes: stoichiometry problems, molarity
#                                                                               problems, and basic mole conversion
#                                                                               problems.

#build grams to moles and moles to grams setup
def gTm(event):

    global set1
    global direction
    global sto
    global rOl
    global molarVar
    global problem
    global stoTwo
    global double
    global last
    global last2


    if(direction != None):
        direction.Destroy()
        direction = None
    
    button = event.GetEventObject()
    rOl = button.GetId()


    if(set1 == 0):
        global input
        global first
        global second
        global calculate
        global answer
        
        #assign set1 100
        set1 = 100

        wi, hi = w.GetPosition()
        input = wx.TextCtrl(panel,pos=wx.Point(470+wi,490+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        second = wx.TextCtrl(panel,pos=wx.Point(720+wi,450+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        first = wx.TextCtrl(panel,pos=wx.Point(720+wi,530+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        if(double == 0):
            answer = wx.TextCtrl(panel,pos=wx.Point((720+750)+wi,490+hi),size=wx.Size(200,300),style=wx.TE_MULTILINE)
            answer.write("Answer will appear here...")
        calculate = wx.Button(panel,label = "Calculate",pos=wx.Point((720+750)+wi,800+hi))
        calculate.Bind(wx.EVT_BUTTON,callMoleFunc)
        
        #insert default values
        if(rOl == 0):
            input.write("# Grams (type value)")
            first.write("# Grams (Use Periodic Table)")
            second.write("1 Mole")
        elif(rOl == 23):
            input.write("# Moles (type value)")
            first.write("# Moles (type coefficient of known substance)")
            second.write("# Moles (type coefficient of unknown substance)")
        elif(rOl == 12):
            input.write("# Moles (type value)")
            second.write("22.4 Liters")
            first.write("1 Mole")
        elif(rOl == 13):
            input.write("# Liters (type value)")
            second.write("1 Mole")
            first.write("22.4 Liters")
        elif(rOl == 37):
            input.write("# Liters (type value)")
            first.write("# Liters (type volume portion of molarity ratio)")
            second.write("1 Mole")
        else:
            input.write("# Moles (type value)")
            second.write("# Grams (Use Periodic Table)")
            first.write("1 Mole")
        
        #set molarVar variable
        molarVar = 10

    else:
        delete1()
        gTm(event)


#build moles to particle, particles to moles,
#and molecules to atoms setup
def mTp(event):

    global set1
    global direction
    global double
    global last2

    if(direction != None):
        direction.Destroy()
        direction = None

    if(set1 == 0):
        global input
        global first
        global second
        global molarVar
        global rOl
        global calculate
        global answer

        #assign set1 100
        set1 = 100
        
        wi, hi = w.GetPosition()
        button = event.GetEventObject()
        rOl = button.GetId()
        input = wx.TextCtrl(panel,pos=wx.Point(470+wi,490+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        second = wx.TextCtrl(panel,pos=wx.Point(720+wi,450+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        first = wx.TextCtrl(panel,pos=wx.Point(720+wi,530+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        if(double == 0):
            answer = wx.TextCtrl(panel,pos=wx.Point((720+750)+wi,490+hi),size=wx.Size(200,300),style=wx.TE_MULTILINE)
            answer.write("Answer will appear here...")
        calculate = wx.Button(panel,label = "Calculate",pos=wx.Point((720+750)+wi,800+hi))
        calculate.Bind(wx.EVT_BUTTON,callMoleFunc)

        #insert default values
        if(rOl == 1):
            input.write("# Moles (Type Value)")
            first.write("1 Mole")
            second.write("6.022*10^23 Particles")
        elif(rOl == 2):
            input.write("# Particles (Type Value)")
            first.write("6.022*10^23 Particles")
            second.write("1 Mole")
        else:
            input.write("# Molecules (Type Value)")
            first.write("1 Molecule")
            second.write("# Atoms (Type Value)")

        #set mole ratio type
        molarVar = 11

    else:
        delete1()
        mTp(event)

#build grams to particles, moles to atoms, and particles to grams setup
def mTa(event):

    global set1
    global direction
    global rOl
    global double
    global sto
    global stoTwo
    global last
    global last2

    if(direction != None):
        direction.Destroy()
        direction = None


    button = event.GetEventObject()
    rOl = button.GetId()


    if(set1 == 0):
        global input
        global first
        global second
        global third
        global fourth
        global molarVar
        global calculate
        global answer
        global third
        global fourth
 
        #assign set1 100
        set1 = 100
       
        wi,hi = w.GetPosition()
        input = wx.TextCtrl(panel,pos=wx.Point(470+wi,490+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        second = wx.TextCtrl(panel,pos=wx.Point(720+wi,450+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        first = wx.TextCtrl(panel,pos=wx.Point(720+wi,530+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        third = wx.TextCtrl(panel,pos=wx.Point(970+wi,450+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        fourth = wx.TextCtrl(panel,pos=wx.Point(970+wi,530+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        if(double == 0):
            answer = wx.TextCtrl(panel,pos=wx.Point((720+750)+wi,490+hi),size=wx.Size(200,300),style=wx.TE_MULTILINE)
            answer.write("Answer will appear here...")
        calculate = wx.Button(panel,label = "Calculate",pos=wx.Point((720+750)+wi,800+hi))
        calculate.Bind(wx.EVT_BUTTON,callMoleFunc)

        #insert default values
        if(rOl == 5):
            input.write("# Grams (Type Value)")
            first.write("# Grams (Use Periodic Table)")
            second.write("1 Mole")
            third.write("6.022*10^23 Particles")
            fourth.write("1 Mole")
        elif(rOl == 6):
            input.write("# Moles (Type Value)")
            first.write("1 Mole")
            second.write("6.022*10^23 Molecules")
            third.write("# Atoms (Type Value)")
            fourth.write("1 Molecule")
        elif(rOl == 9):
            input.write("# Liters (Type Value)")
            first.write("22.4 Liters")
            second.write("1 Mole")
            third.write("# Grams (Use Periodic Table)")
            fourth.write("1 Mole")
        elif(rOl == 10):
            input.write("# Liters (Type Value)")
            first.write("22.4 Liters")
            second.write("1 Mole")
            third.write("6.022*10^23 Particles")
            fourth.write("1 Mole")
        elif(rOl == 14):
            input.write("# Grams (type value)")
            first.write("# Grams (Use Periodic Table)")
            second.write("1 Mole")
            third.write("22.4 Liters")
            fourth.write("1 Mole")
        elif(rOl == 16):
            input.write("# Particles (Type Value)")
            first.write("6.022*10^23 Particles")
            second.write("1 Mole")
            third.write("22.4 Liters")
            fourth.write("1 Mole")
        elif(rOl == 18):
            input.write("# Grams (Type Value)")
            first.write("# Grams (Use Periodic Table)")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
        elif(rOl == 22):
            input.write("# Moles (Type Value)")
            first.write("# Moles (type value of known substance)")
            second.write("# Moles (type value of unknown substance)")
            third.write("# Grams (Use Periodic Table)")
            fourth.write("1 Mole")
        elif(rOl == 24):
            input.write("# Moles (type value)")
            first.write("# Moles (type value of known substance)")
            second.write("# Moles (type value of unknown substance)")
            third.write("6.022*10^23 Particles")
            fourth.write("1 Mole")
        elif(rOl == 26):
            input.write("# Moles (type value)")
            first.write("# Moles (type value of known substance)")
            second.write("# Moles (type value of unknown substance)")
            third.write("22.4 Liters")
            fourth.write("1 Mole")
        elif(rOl == 28):
            input.write("# Particles (type value)")
            first.write("6.022*10^23 Particles")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
        elif(rOl == 33):
            input.write("# Liters (type value)")
            first.write("22.4 Liters")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
        elif(rOl == 38):
            input.write("# Liters (type value)")
            first.write("# Liters (type volume component of molarity)")
            second.write("1 Mole")
            third.write("# Grams (Use Periodic Table)")
            fourth.write("1 Mole")
        elif(rOl == 39):
            input.write("# Liters (type value)")
            first.write("# Liters (type volume component of molarity)")
            second.write("1 Mole")
            third.write("6.022*10^23 Particles")
            fourth.write("1 Mole")
        else:
            input.write("# Particles (Type Value)")
            first.write("6.022*10^23 Particles")
            second.write("1 Mole")
            third.write("# Grams (Use Periodic Table)")
            fourth.write("1 Mole")

        #set mole ratio type
        molarVar = 12

    else:
        delete1()
        mTa(event)

#build grams to atoms setup
def gTa(event):

    global set1
    global direction
    global sto
    global stoTwo
    global rOl
    global double
    global last
    global last2


    if(direction != None):
        direction.Destroy()
        direction = None


    button = event.GetEventObject()
    rOl = button.GetId()



    if(set1 == 0):
        global input
        global first
        global second
        global molarVar
        global calculate
        global answer
        global third
        global fourth
        global fifth
        global sixth
        global right
        global left

        #assign set1 100
        set1 = 100


        wi,hi = w.GetPosition()
        input = wx.TextCtrl(panel,pos=wx.Point(470+wi,490+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        second = wx.TextCtrl(panel,pos=wx.Point(720+wi,450+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        first = wx.TextCtrl(panel,pos=wx.Point(720+wi,530+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        third = wx.TextCtrl(panel,pos=wx.Point(970+wi,450+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        fourth = wx.TextCtrl(panel,pos=wx.Point(970+wi,530+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        fifth = wx.TextCtrl(panel,pos=wx.Point(1220+wi,450+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        sixth = wx.TextCtrl(panel,pos=wx.Point(1220+wi,530+hi),size=wx.Size(200,40),style=wx.TE_MULTILINE)
        if(double == 0):
            answer = wx.TextCtrl(panel,pos=wx.Point((720+750)+wi,490+hi),size=wx.Size(200,300),style=wx.TE_MULTILINE)
            answer.write("Answer will appear here...")
        if(rOl == 17):
            left = wx.CheckBox(panel,id = 2000,label = "Left-most Molar Mass", pos = wx.Point(720+wi,570+hi))
            left.SetValue(True)
            left.Bind(wx.EVT_CHECKBOX,switchMe)
            right = wx.CheckBox(panel,id = 2001,label = "Right-most Molar Mass", pos = wx.Point(1220+wi,432+hi))
            right.Bind(wx.EVT_CHECKBOX,switchMe)
        calculate = wx.Button(panel,label = "Calculate",pos=wx.Point((720+750)+wi,800+hi))
        calculate.Bind(wx.EVT_BUTTON,callMoleFunc)

        if(rOl == 8):
            #insert default values
            input.write("# Grams (type value)")
            first.write("# Grams (Use Periodic Table)")
            second.write("1 Mole")
            third.write("6.022*10^23 Molecules")
            fourth.write("1 Mole")
            fifth.write("# Atoms (type value)")
            sixth.write("1 Molecule")
        elif(rOl == 11):
            input.write("# Liters (type value)")
            first.write("22.4 Liters")
            second.write("1 Mole")
            third.write("6.022*10^23 Molecules")
            fourth.write("1 Mole")
            fifth.write("# Atoms (type value)")
            sixth.write("1 Molecule")
        elif(rOl == 17):
            input.write("# Grams (type value of known substance)")
            first.write("# Grams (Use Periodic Table)")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
            fifth.write("# Grams (Use Periodic Table)")
            sixth.write("1 Mole")
        elif(rOl == 19):
            input.write("# Grams (type value of known substance)")
            first.write("# Grams (Use Periodic Table)")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
            fifth.write("6.022*10^23 Particles")
            sixth.write("1 Mole")
        elif(rOl == 21):
            input.write("# Grams (type value)")
            first.write("# Grams (Use Periodic Table)")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
            fifth.write("22.4 Liters")
            sixth.write("1 Mole")
        elif(rOl == 25):
            input.write("# Moles (type value)")
            first.write("# Moles (type value of known substance)")
            second.write("# Moles (type value of unknown substance)")
            third.write("6.022*10^23 Molecules")
            fourth.write("1 Mole")
            fifth.write("# Atoms (type value)")
            sixth.write("1 Molecule")
        elif(rOl == 27):
            input.write("# Particles (type value)")
            first.write("6.022*10^23 Particles")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
            fifth.write("# Grams (Use Periodic Table)")
            sixth.write("1 Mole")
        elif(rOl == 29):
            input.write("# Particles (type value)")
            first.write("6.022*10^23 Particles")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
            fifth.write("6.022*10^23 Particles")
            sixth.write("1 Mole")
        elif(rOl == 31):
            input.write("# Particles (type value)")
            first.write("6.022*10^23 Particles")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
            fifth.write("22.4 Liters")
            sixth.write("1 Mole")
        elif(rOl == 32):
            input.write("# Liters (type value)")
            first.write("22.4 Liters")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
            fifth.write("# Grams (Use Periodic Table)")
            sixth.write("1 Mole")
        elif(rOl == 34):
            input.write("# Liters (type value)")
            first.write("22.4 Liters")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
            fifth.write("6.022*10^23 Particles")
            sixth.write("1 Mole")
        else:
            input.write("# Liters (type value)")
            first.write("22.4 Liters")
            second.write("1 Mole")
            third.write("# Moles (type value of unknown substance)")
            fourth.write("# Moles (type value of known substance)")
            fifth.write("22.4 Liters")
            sixth.write("1 Mole")
        #set mole ratio type
        molarVar = 13

    else:
        delete1()
        gTa(event)


def SgTa(event):
    global set1
    global direction
    global sto
    global stoTwo
    global rOl
    global double
    global last
    global last2

    if(direction != None):
        direction.Destroy()
        direction = None


    button = event.GetEventObject()
    rOl = button.GetId()


    if(set1 == 0):
        global input
        global first
        global second
        global molarVar
        global calculate
        global answer
        global third
        global fourth
        global fifth
        global sixth
        global seventh
        global eighth


        #assign set1 100    
        set1 = 100
        wi,hi = w.GetPosition()
        input = wx.TextCtrl(panel,pos=wx.Point(470+wi,490+hi),size=wx.Size(150,40),style=wx.TE_MULTILINE)
        second = wx.TextCtrl(panel,pos=wx.Point(670+wi,450+hi),size=wx.Size(150,40),style=wx.TE_MULTILINE)
        first = wx.TextCtrl(panel,pos=wx.Point(670+wi,530+hi),size=wx.Size(150,40),style=wx.TE_MULTILINE)
        third = wx.TextCtrl(panel,pos=wx.Point(870+wi,450+hi),size=wx.Size(150,40),style=wx.TE_MULTILINE)
        fourth = wx.TextCtrl(panel,pos=wx.Point(870+wi,530+hi),size=wx.Size(150,40),style=wx.TE_MULTILINE)
        fifth = wx.TextCtrl(panel,pos=wx.Point(1070+wi,450+hi),size=wx.Size(150,40),style=wx.TE_MULTILINE)
        sixth = wx.TextCtrl(panel,pos=wx.Point(1070+wi,530+hi),size=wx.Size(150,40),style=wx.TE_MULTILINE)
        seventh = wx.TextCtrl(panel,pos=wx.Point(1270+wi,450+hi),size=wx.Size(150,40),style=wx.TE_MULTILINE)
        eighth = wx.TextCtrl(panel,pos=wx.Point(1270+wi,530+hi),size=wx.Size(150,40),style=wx.TE_MULTILINE)
        if(double == 0):
            answer = wx.TextCtrl(panel,pos=wx.Point((720+750)+wi,490+hi),size=wx.Size(200,300),style=wx.TE_MULTILINE)
            answer.write("Answer will appear here...")
        calculate = wx.Button(panel,label = "Calculate",pos=wx.Point((720+750)+wi,800+hi))
        calculate.Bind(wx.EVT_BUTTON,callMoleFunc)

        if(rOl == 20):
            input.write("# Grams (type value)")
            first.write("# Grams\n(Use Periodic Table)")
            second.write("1 Mole")
            third.write("# Moles\n(unknown substance)")
            fourth.write("# Moles\n(known substance)")
            fifth.write("6.022*10^23\nMolecules")
            sixth.write("1 Mole")
            seventh.write("# Atoms (type value)")
            eighth.write("1 Molecule")
        elif(rOl == 30):
            input.write("# Particles (type value)")
            first.write("6.022*10^23\nParticles")
            second.write("1 Mole")
            third.write("# Moles\n(unknown substance)")
            fourth.write("# Moles\nknown substance")
            fifth.write("6.022*10^23\nMolecules")
            sixth.write("1 Mole")
            seventh.write("# Atoms\n(type value)")
            eighth.write("1 Molecule")
        elif(rOl == 35):
            input.write("# Liters (type value)")
            first.write("22.4 Liters")
            second.write("1 Mole")
            third.write("# Moles\n(unknown substance)")
            fourth.write("# Moles\n(known substance)")
            fifth.write("6.022*10^23\nMolecules")
            sixth.write("1 Mole")
            seventh.write("# Atoms (type value)")
            eighth.write("1 Molecule")
        
        
        #set molarVar variabl
        molarVar = 15

    else:
        delete1()
        SgTa(event)

#END OF SECTION THIRTEEN--------------------------------------------------------------------------------

























#SECTION---FOURTEEN--------------------------------------------------------------------------------------------
#This section is meant to switch between molar mass text boxes so the user can enter molar mass
#values appropriately. The switchMe() function is SPECIFICALLY meant for the stoichiometry grams to grams
#problem. 

#Alternate between checkbox state values.
#There are two checkboxes and each corresponds a molar mass value.
def switchMe(event):
    global left
    global right

    checkBox = event.GetEventObject()
    num = checkBox.GetId()

    if(left.IsChecked() and num == 2001):
        right.SetValue(True)
        left.SetValue(False)
    elif(right.IsChecked() and num == 2000):
        right.SetValue(False)
        left.SetValue(True)
    elif(not(left.IsChecked()) and num == 2000):
        left.SetValue(True)
        right.SetValue(False)
    elif(not(right.IsChecked()) and num == 2001):
        right.SetValue(True)
        left.SetValue(False)


#END OF SECTION FOURTEEN--------------------------------------------------------------------------------


































#SECTION---FIFTEEN--------------------------------------------------------------------------------------------
#This section is responsible for calculating the number of significant figures a final answer will have and
#making sure the final answer outputed to the screen displays the correct number of significant figures.

#determine the number of significant figures
def sFigures(temp, sigFig):
    
    #create temporary sig fig counter
    sCounter = 0

    #counter
    b = 0

    #nonzero flag
    zFlag = 0

    while(b < len(temp)):
        if(temp[b] != '0' and temp[b] != '.' and temp[b] != '*'):
            sCounter = sCounter + 1
        elif(temp[b] == '0' and sCounter > 0):
            sCounter = sCounter + 1
        elif(temp[b] == '*'):
            b = len(temp)
        b = b + 1

    #follow rules of multiplication
    if(sigFig == None):
        sigFig = sCounter
    elif(sCounter < sigFig):
        sigFig = sCounter
    
    #return sigFig
    return sigFig



#apply sig figs -> returns type string (function should be used for writing strings only)
#This function could be modified to return type float, but upon converting from float to string or vice versa, any trailing 0
#acting as a significant figure is cut off (with the exception of using scientific notation -> 0's aren't cut off).
def applySig(number,numSigs):
    
    #access problem type
    global rOl

    #make copy just in case
    number2 = number

    #convert to string value
    number = str(number)

    #*************************************put all final answers in scientific notation

    #loop flag
    z = 0

    #character counter
    g = 0
        
    #first digit flag
    flagOne = 0

        
    #account for decimal point
    numSigs = numSigs - 1


    temp = "{:"+'.'+str(numSigs)+"e}"
    return temp.format(number2)

#END OF SECTION FIFTEEN--------------------------------------------------------------------------------




























#SECTION---SIXTEEN--------------------------------------------------------------------------------------------
#This section is responsible for calculating the final answers for all unit conversion related problems. This
#includes stoichiometry problems, molarity problems, and basic mole conversion problems.

#call corresponding mole conversion functions after calculate button
#is clicked
def callMoleFunc(event):
    global rOl
    global first
    global second
    global input
    global answer
    global fifth
    global third

    if(rOl == 0):
        #parse text box data for input
        grams = parseMe(input,2)
        molarMass = parseMe(first,2)
        mole = wholeCheck(second)
        if(grams == "Error" or molarMass == "Error" or mole == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = sFigures(grams,None)
            two = sFigures(molarMass,one)
            
            #perform calculation and apply sig figs
            number = gramToMole(float(grams),float(molarMass))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Moles")
    elif(rOl == 1):
        #parse text box data for input         
        moles = parseMe(input,1)
        moles2 = wholeCheck(first)
        part = wholeCheck5(second)
        if(moles == "Error" or moles2 == "Error" or part == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 4
            two = sFigures(moles,one)

            #perform calculation and apply sig figs                                                                                                                       
            number = moleToParticle(float(moles))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Particles")
    elif(rOl == 2):
        #parse text box data for input                                                                                                                                                                                                    
        particles = parseMe(input,3)
        one = wholeCheck5(first)
        two = wholeCheck(second)
        if(particles == "Error" or one == "Error" or two == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:

            #sig fig comparison variables                                                                                                                                                                                                 
            one = sFigures(particles,None)
            print(one)
            #reformat molecules to be converted to float
            particles = particles.replace('*10^','e')

            #perform calculation and apply sig figs                                                                                                                                                                                       
            number = particleToMole(float(particles))
            answer.Clear()
            answer.write("Answer: " + applySig(number,one) + " Moles")
    elif(rOl == 3):
        molarMass = parseMe(second, 2)
        moles = parseMe(input, 1)
        one = wholeCheck(first)
        if(molarMass == "Error" or moles == "Error" or one == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            
            #sig fig comparison variables
            one = sFigures(molarMass,None)
            two = sFigures(moles,one)

            #perform calculation
            number = moleToGram(float(moles),float(molarMass))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Grams")
    elif(rOl == 4):
        molecules = parseMe(input, 5)
        Atoms = parseMe(second, 4)
        one = wholeCheck2(first)
        if(molecules == "Error" or Atoms == "Error" or one == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig variables, don't compute sig figs
            #of Atoms as it is an exact number
            one = sFigures(molecules,None)

            #re-format molecules to be converted to float
            molecules = molecules.replace('*10^','e')

            #perform calculation
            number = moleculeToAtom(float(molecules),float(Atoms))
            answer.Clear()
            answer.write("Answer: " + applySig(number,one) + " Atoms")
    elif(rOl == 5):
        grams = parseMe(input, 2)
        molarMass = parseMe(first, 2)
        two = wholeCheck(second)
        three = wholeCheck5(third)
        four = wholeCheck(fourth)
        if(grams == "Error" or molarMass == "Error" or two == "Error" or three == "Error" or four == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:

            #sig fig comparison variables
            one = 4
            two = sFigures(grams,one)
            three = sFigures(molarMass,two)

            #perform computation
            number = gramToMoleToParticle(float(grams),float(molarMass))
            answer.Clear()
            answer.write("Answer: " + applySig(number,three) + " Particles")
    elif(rOl == 6):
        mole = parseMe(input, 1)
        Atoms = parseMe(third, 4)
        one = wholeCheck(first)
        two = wholeCheck4(second)
        four = wholeCheck2(fourth)
        if(mole == "Error" or Atoms == "Error" or one == "Error" or two == "Error" or four == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:

            #sig fig comparison variables
            one = 4
            two = sFigures(mole,one)

            #perform computation
            number = moleToMoleculeToAtom(float(mole),float(Atoms))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Atoms")
    elif(rOl == 7):
        particles = parseMe(input, 3)
        molarMass = parseMe(third, 2)
        one = parseMe(first, 3)
        two = wholeCheck(second)
        four = wholeCheck(fourth)
        if(particles == "Error" or molarMass == "Error" or one == "Error" or two == "Error" or four == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            
            #sig fig comparison variables
            one = 4
            two = sFigures(particles,one)
            three = sFigures(molarMass,two)
            
            #re-format particles to be converted to float
            particles = particles.replace('*10^','e')


            #perform computation
            number = particleToGram(float(particles), float(molarMass))
            answer.Clear()
            answer.write("Answer: " + applySig(number,three) + " Grams")
    elif(rOl == 9):
        liter = parseMe(input,6)
        molarMass = parseMe(third,2)
        one = wholeCheck3(first)
        two = wholeCheck(second)
        four = wholeCheck(fourth)
        if(liter == "Error" or molarMass == "Error" or one == "Error" or two == "Error" or four == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(liter,one)
            three = sFigures(molarMass,two)


            #perform calculation
            number = LiterToGram(float(liter),float(molarMass))
            answer.Clear()
            answer.write("Answer: " + applySig(number,three) + " Grams")
    elif(rOl == 10):
        liter = parseMe(input,6)
        one = wholeCheck3(first)
        two = wholeCheck(second)
        three = wholeCheck5(third)
        four = wholeCheck(fourth)
        if(liter == "Error" or one == "Error" or two == "Error" or three == "Error" or four == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(liter,one)

            #perform calculation
            number = LiterToParticle(float(liter))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Particles")
    elif(rOl == 11):
        liter = parseMe(input,6)
        atom = parseMe(fifth,4)
        one = wholeCheck3(first)
        two = wholeCheck(second)
        three = wholeCheck4(third)
        four = wholeCheck(fourth)
        six = wholeCheck2(sixth)
        if(liter == "Error" or atom == "Error" or one == "Error" or two == "Error" or three == "Error" or four == "Error" or six == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(liter,one)

            #perform calculation
            number = LiterToAtom(float(liter),float(atom))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Atoms")
    elif(rOl == 12):
        mole = parseMe(input,1)
        one = wholeCheck(first)
        two = wholeCheck3(second)
        if(mole == "Error" or one == "Error" or two == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(mole,one)

            #perform calculation
            number = MoleToLiter(float(mole))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Liters")
    elif(rOl == 13):
        liter = parseMe(input,6)
        one = wholeCheck3(first)
        two = wholeCheck(second)
        if(liter == "Error" or one == "Error" or two == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(liter,one)

            #perform calculation
            number = LiterToMole(float(liter))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + "Moles")
    elif(rOl == 14):
        gram = parseMe(input,2)
        molarMass = parseMe(first,2)
        two = wholeCheck(second)
        three = wholeCheck3(third)
        four = wholeCheck(fourth)
        if(gram == "Error" or molarMass == "Error" or two == "Error" or three == "Error" or four == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            one = 3
            two = sFigures(molarMass,one)
            
            #perform calculation
            number = GramToLiter(float(gram),float(molarMass))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Liters")
    elif(rOl == 16):
        particles = parseMe(input,3)
        one = wholeCheck5(first)
        two = wholeCheck(second)
        three = parseMe(third,6)
        four = wholeCheck(fourth)
        if(particles == "Error" or one == "Error" or two == "Error" or three == "Error" or four == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            one = 3
            two = sFigures(particles,one)

            #re-formatting
            particles = particles.replace('*10^','e')

            #perform calculation
            number = ParticleToLiter(float(particles))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Liters")
    elif(rOl == 17):
        gram = parseMe(input,2)
        molarMass = parseMe(first,2)
        placer1 = wholeCheck(second)
        placer2 = wholeCheck(sixth)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        molarMass2 = parseMe(fifth,2)
        if(gram == "Error" or molarMass == "Error" or known == "Error" or unknown == "Error" or molarMass2 == "Error" or placer1 == "Error" or placer2 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            one = sFigures(gram,None)
            two = sFigures(molarMass,one)
            three = sFigures(molarMass2,two)

            #perform calculation
            number = SGramToGram(float(gram),float(molarMass),float(known),float(unknown),float(molarMass2))
            answer.Clear()
            answer.write("Answer: " + applySig(number,three) + " Grams")
    elif(rOl == 18):
        gram = parseMe(input,2)
        molarMass = parseMe(first,2)
        placer1 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        if(gram == "Error" or molarMass == "Error" or known == "Error" or unknown == "Error" or placer1 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = sFigures(gram, None)
            two = sFigures(molarMass,one)

            #perform calculation
            number = SGramToMole(float(gram),float(molarMass),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Moles")
    elif(rOl == 19):
        gram = parseMe(input,2)
        molarMass = parseMe(first,2)
        placer1 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        placer2 = wholeCheck(sixth)
        placer3 = wholeCheck5(fifth)
        if(gram == "Error" or molarMass == "Error" or known == "Error" or unknown == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 4
            two = sFigures(gram,one)
            three = sFigures(molarMass,two)

            #perform calculation
            number = GramToParticle(float(gram),float(molarMass),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,three) + " Particles")
    elif(rOl == 20):
        gram = parseMe(input,2)
        molarMass = parseMe(first,2)
        placer1 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        placer2 = wholeCheck4(fifth)
        placer3 = wholeCheck(sixth)
        atoms = parseMe(seventh,4)
        placer4 = wholeCheck2(eighth)
        if(gram == "Error" or molarMass == "Error" or known == "Error" or unknown == "Error" or atoms == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error" or placer4 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 4
            two = sFigures(gram,one)
            three = sFigures(molarMass,two)

            #perform calculation
            number = SGramToAtom(float(gram),float(molarMass),float(known),float(unknown),float(atoms))
            answer.Clear()
            answer.write("Answer: " + applySig(number,three) + " Atoms")
    elif(rOl == 21):
        gram = parseMe(input,2)
        molarMass = parseMe(first,2)
        placer1 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        placer2 = wholeCheck3(fifth)
        placer3 = wholeCheck(sixth)
        if(gram == "Error" or molarMass == "Error" or known == "Error" or unknown == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            zero = 3
            one = sFigures(gram,3)
            two = sFigures(molarMass,one)
            
            #perform calculation
            number = SGramToLiter(float(gram),float(molarMass),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Liters")
    elif(rOl == 22):
        mole = parseMe(input,1)
        known = wholeCheck6(first)
        unknown = wholeCheck6(second)
        molarMass = parseMe(third,2)
        placer1 = wholeCheck(fourth)
        if(mole == "Error" or known == "Error" or unknown == "Error" or molarMass == "Error" or placer1 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = sFigures(mole,None)
            two = sFigures(molarMass,one)
            
            #perform calculation
            number = SMoleToGram(float(mole),float(known),float(unknown),float(molarMass))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Grams")
    elif(rOl == 23):
        given = parseMe(input,1)
        mole1 = wholeCheck6(first)
        mole2 = wholeCheck6(second)
        if(given == "Error" or mole1 == "Error" or mole2 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig
            one = sFigures(given,None)

            #perform computation
            number = conversionM.MoleToMole(float(given),float(mole1),float(mole2))
            answer.Clear()
            answer.write("\nAnswer: " + applySig(number,one) + " Moles")
    elif(rOl == 24):
        mole = parseMe(input,1)
        known = wholeCheck6(first)
        unknown = wholeCheck6(second)
        placer1 = wholeCheck5(third)
        placer2 = wholeCheck(fourth)
        if(mole == "Error" or known == "Error" or unknown == "Error" or placer1 == "Error" or placer2 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 4
            two = sFigures(mole,one)
            
            #perform calculation
            number = SMoleToParticle(float(mole),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Particles")
    elif(rOl == 25):
        mole = parseMe(input,1)
        known = wholeCheck6(first)
        unknown = wholeCheck6(second)
        placer1 = wholeCheck4(third)
        placer2 = wholeCheck(fourth)
        atoms = parseMe(fifth,4)
        placer3 = wholeCheck2(sixth)
        if(mole == "Error" or known == "Error" or unknown == "Error" or atoms == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 4
            two = sFigures(mole,one)

            #perform calculation
            number = SMoleToAtoms(float(mole),float(known),float(unknown),float(atoms))
            answer.Clear()
            answer.write("\nAnswer: " + applySig(number,two) + " Atoms")
    elif(rOl == 26):
        mole = parseMe(input,1)
        known = wholeCheck6(first)
        unknown = wholeCheck6(second)
        placer1 = wholeCheck3(third)
        placer2 = wholeCheck(fourth)
        if(mole == "Error" or unknown == "Error" or known == "Error" or placer1 == "Error" or placer2 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            # sig fig comparison variables
            one = 3
            two = sFigures(mole,one)

            #perform calculation
            number = SMoleToLiter(float(mole),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Liters")
    elif(rOl == 27):
        particle = parseMe(input,3)
        placer1 = wholeCheck5(first)
        placer2 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        molarMass = parseMe(fifth,2)
        placer3 = wholeCheck(sixth)
        if(particle == "Error" or known == "Error" or unknown == "Error" or molarMass == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            # sig fig comparison variables
            one = 4
            two = sFigures(particle,one)
            three = sFigures(molarMass,two)


            #re-format molecules to be converted to float                                                                                                                                                                                     
            particle = particle.replace('*10^','e')


            #perform calculation
            number = SParticleToGram(float(particle),float(known),float(unknown),float(molarMass))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Grams")
    elif(rOl == 28):
        particle = parseMe(input,3)
        placer1 = wholeCheck5(first)
        placer2 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        if(particle == "Error" or known == "Error" or unknown == "Error" or placer1 == "Error" or placer2 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 4
            two = sFigures(particle,one)

            #re-format molecules to be converted to float                                                                                                                                                                                     
            particle = particle.replace('*10^','e')

            
            #perform calculation
            number = SParticleToMole(float(particle),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Moles")
    elif(rOl ==29):
        particle = parseMe(input,3)
        placer1 = wholeCheck5(first)
        placer2 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        placer3 = wholeCheck5(fifth)
        placer4 = wholeCheck(sixth)
        if(particle == "Error" or known == "Error" or unknown == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error" or placer4 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 4
            two = sFigures(particle,one)
            
            
            #re-format molecules to be converted to float                                                        
            particle = particle.replace('*10^','e')

            #perform calculation
            number = SParticleToParticle(float(particle),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Particles")
    elif(rOl == 30):
        particle = parseMe(input,3)
        placer1 = wholeCheck5(first)
        placer2 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        placer3 = wholeCheck4(fifth)
        placer4 = wholeCheck(sixth)
        placer5 = wholeCheck2(eighth)
        atoms = parseMe(seventh,4)
        if(particle == "Error" or known == "Error" or unknown == "Error" or atoms == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error" or placer4 == "Error" or placer5 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 4
            two = sFigures(particle,one)

            #re-format molecules to be converted to float                                        
            particle = particle.replace('*10^','e')

            #perform calculation
            number = SParticleToAtom(float(particle),float(known),float(unknown),float(atoms))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Atoms")
    elif(rOl == 31):
        particle = parseMe(input,3)
        placer1 = wholeCheck5(first)
        placer2 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        placer3 = wholeCheck3(fifth)
        placer4 = wholeCheck(sixth)
        if(particle == "Error" or known == "Error" or unknown == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error" or placer4 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(particle,one)
            
            #re-format molecules to be converted to float  
            particle = particle.replace('*10^','e')
            
            #perform calculation
            number = SParticleToLiter(float(particle),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Liters")
    elif(rOl == 32):
        liter = parseMe(input,6)
        placer1 = wholeCheck3(first)
        placer2 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        molarMass = parseMe(fifth,2)
        placer3 = wholeCheck(sixth)
        if(liter == "Error" or known == "Error" or unknown == "Error" or molarMass == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(liter,one)
            three = sFigures(molarMass,two)

            #perform calculation
            number = SLiterToGram(float(liter),float(known),float(unknown),float(molarMass))
            answer.Clear()
            answer.write("Answer: " + applySig(number,three) + " Grams")
    elif(rOl == 33):
        liter = parseMe(input,6)
        placer1 = wholeCheck3(first)
        placer2 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        if(liter == "Error" or known == "Error" or unknown == "Error" or placer1 == "Error" or placer2 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(liter,one)
            
            #perform calculation
            number = SLiterToMole(float(liter),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Moles")
    elif(rOl == 34):
        liter = parseMe(input,6)
        placer1 = wholeCheck3(first)
        placer2 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        placer3 = wholeCheck5(fifth)
        placer4 = wholeCheck(sixth)
        if(liter == "Error" or known == "Error" or unknown == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error" or placer4 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(liter,one)

            #perform calculation
            number = SLiterToParticle(float(liter),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Particle")
    elif(rOl == 35):
        liter = parseMe(input,6)
        placer1 = wholeCheck3(first)
        placer2 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        placer3 = wholeCheck4(fifth)
        placer4 = wholeCheck(sixth)
        atoms = parseMe(seventh,4)
        placer5 = wholeCheck2(eighth)
        if(liter == "Error" or known == "Error" or unknown == "Error" or atoms == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error" or placer4 == "Error" or placer5 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(liter,one)
            
            #perform calculation
            number = SLiterToAtom(float(liter),float(known),float(unknown),float(atoms))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Atoms")
    elif(rOl == 36):
        liter = parseMe(input,6)
        placer1 = wholeCheck3(first)
        placer2 = wholeCheck(second)
        known = wholeCheck6(fourth)
        unknown = wholeCheck6(third)
        placer3 = wholeCheck3(fifth)
        placer4 = wholeCheck(sixth)
        if(liter == "Error" or known == "Error" or unknown == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error" or placer4 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = 3
            two = sFigures(liter,one)
            
            #perform calculation
            number = SLiterToLiter(float(liter),float(known),float(unknown))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Liters")
    elif(rOl == 37):
        liter = parseMe(input,6)
        molarityL = parseMe(first,6)
        placer1 = wholeCheck(second)
        if(liter == "Error" or molarityL == "Error" or placer1 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = sFigures(liter, None)
            two = sFigures(molarityL,one)

            #perform calculation
            number = LiquidLiterToMole(float(liter),float(molarityL))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Moles")
    elif(rOl == 38):
        liter = parseMe(input, 6)
        molarityL = parseMe(first, 6)
        placer1 = wholeCheck(second)
        molarMass = parseMe(third, 2)
        placer2 = wholeCheck(fourth)
        if(liter == "Error" or molarityL == "Error" or molarMass == "Error" or placer1 == "Error" or placer2 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = sFigures(liter,None)
            two = sFigures(molarityL, one)
            three = sFigures(molarMass, two)

            #perform calculation
            number = LiquidLiterToGram(float(liter),float(molarityL),float(molarMass))
            answer.Clear()
            answer.write("Answer: " + applySig(number,three) + " Grams")
    elif(rOl == 39):
        liter = parseMe(input, 6)
        molarityL = parseMe(first, 6)
        placer1 = wholeCheck(second)
        placer2 = wholeCheck5(third)
        placer3 = wholeCheck(fourth)
        if(liter == "Error" or molarityL == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error"):
            answer.Clear()
            answer.write("Invalid Input, Try Again!")
        else:
            #sig fig comparison variables
            one = sFigures(liter,None)
            two = sFigures(molarityL,one)

            #perform calculation
            number = LiquidLiterToParticles(float(liter),float(molarityL))
            answer.Clear()
            answer.write("Answer: " + applySig(number,two) + " Particles")
    else:
        grams = parseMe(input, 2)
        molarMass = parseMe(first, 2)
        placer1 = wholeCheck(second)
        placer2 = wholeCheck4(third)
        placer3 = wholeCheck(fourth)
        Atoms = parseMe(fifth, 4)
        placer4 = wholeCheck2(sixth)
        if(grams == "Error" or molarMass == "Error" or Atoms == "Error" or placer1 == "Error" or placer2 == "Error" or placer3 == "Error" or placer4 == "Error"):
            answer.write("Invalid Input, Try Again!")
            answer.Clear()
        else:

            #sig fig comparison variables
            one = 4
            two = sFigures(grams,one)
            three = sFigures(molarMass,two)

            #perform computation
            number = gramToMoleToParticleToAtom(float(grams),float(molarMass),float(Atoms))
            answer.Clear()
            answer.write("Answer: " + applySig(number,three) + " Atoms")

#END OF SECTION SIXTEEN--------------------------------------------------------------------------------




















#SECTION---SEVENTEEN--------------------------------------------------------------------------------------------
#This section is dedicated to parsing all input strings and making sure these strings fulfill all required input
#patterns. -> This is done through the usage of regular expressions.

#parse text box data
def parseMe(textBoxVar,unit):

    value = textBoxVar.GetValue()
    length = len(value)


    #number length error flag
    error = ""

    #x and y are boolean values that
    #tell if the user input matches the
    #pattern required by the regular expression
    #x: corresponds with input that contains numbers in front
    #of the decimal point.
    #y: corresponds with input that contains no numbers in front
    #of the decimal point (no number can correspond with zero).
    y = None
    x = None

    #cancel: serves the purpose of extracting
    #the unit at the end of the number
    cancel = None

    #finish the parsing:
    #use regular expressions to see if user input
    #matches the required input pattern in unit sections (1-4 and 6)
    if(unit == 1):
        x = re.search(r"\A\s*[0-9]+[.]?[0-9]*\s+[Mm][Oo][Ll][Ee][Ss]?\s*\Z",  value)
        y = re.search(r"\A\s*[0-9]*[.][0-9]+\s+[Mm][Oo][Ll][Ee][Ss]?\s*\Z",  value)
        if(x or y):
            value = value.replace(" ","")
            value = value.replace("\n","")
            if(value[len(value) - 1] == 's' or value[len(value) - 1] == 'S'):
                    cancel = value[len(value)-5:]
            else:
                    cancel = value[len(value)-4:]

    elif(unit == 2):
        x = re.search(r"\A\s*[0-9]+[.]?[0-9]*\s+[Gg][Rr][Aa][Mm][Ss]?\s*\Z",  value)
        y = re.search(r"\A\s*[0-9]*[.][0-9]+\s+[Gg][Rr][Aa][Mm][Ss]?\s*\Z",  value)
        if(x or y):
                value = value.replace(" ","")
                value = value.replace("\n","")
                if(value[len(value) - 1] == 's' or value[len(value) - 1] == 'S'):
                    cancel = value[len(value)-5:]
                else:
                    cancel = value[len(value)-4:]

    elif(unit == 3):
        x = re.search(r"\A\s*[0-9]+([.][0-9]+)?\s*[*]\s*10\s*[\^]\s*[0-9]+\s+[Pp][Aa][Rr][Tt][Ii][Cc][Ll][Ee][Ss]?\s*\Z",  value)
        y = re.search(r"\A\s*[0-9]*[.][0-9]+\s*[*]\s*10\s*[\^]\s*[0-9]+\s+[Pp][Aa][Rr][Tt][Ii][Cc][Ll][Ee][Ss]?\s*\Z",  value)
        if(x or y):
                value = value.replace(" ","")
                value =value.replace("\n","")
                if(value[len(value) - 1] == 's' or value[len(value) - 1] == 'S'):
                    cancel = value[len(value)-9:]
                else:
                    cancel = value[len(value)-8:]
            
    elif(unit == 4):
        x = re.search(r"\A\s*[0-9]+\s+[Aa][Tt][Oo][Mm][Ss]?\s*\Z",  value)
        if(x):
            value = value.replace(" ","")
            value =value.replace("\n","")
            if(value[len(value) - 1] == 's' or value[len(value) - 1] == 'S'):
                cancel = value[len(value)-5:]
            else:
                cancel = value[len(value)-4:]
   
    elif(unit == 5):
        x = re.search(r"\A\s*[0-9]+([.][0-9]+)?\s*[*]\s*10\s*[\^]\s*[0-9]+\s+[mM][Oo][lL][eE][cC][uU][Ll][Ee][Ss]?\s*\Z",  value)
        y = re.search(r"\A\s*[0-9]*[.][0-9]+\s*[*]\s*10\s*[\^]\s*[0-9]+\s+[mM][oO][lL][eE][cC][uU][Ll][Ee][Ss]?\s*\Z",  value)
        if(x or y):
                value = value.replace(" ","")
                value =value.replace("\n","")
                if(value[len(value) - 1] == 's' or value[len(value) - 1] == 'S'):
                    cancel = value[len(value)-9:]
                else:
                    cancel = value[len(value)-8:]

    elif(unit == 6):
        x = re.search(r"\A\s*[0-9]+[.]?[0-9]*\s+[Ll][Ii][Tt][Ee][Rr][Ss]?\s*\Z",  value)
        y = re.search(r"\A\s*[0-9]*[.][0-9]+\s+[Ll][Ii][Tt][Ee][Rr][Ss]?\s*\Z",  value)
        if(x or y):
            value = value.replace(" ","")
            value =value.replace("\n","")
            if(value[len(value) - 1] == 's' or value[len(value) - 1] == 'S'):
                    cancel = value[len(value)-6:]
            else:
                    cancel = value[len(value)-5:]



    #modify the error variable if a valid
    #number was passed by the user
    if(cancel != None):
        #The error variable will be assigned
        #a modified version of the value string.
        #The string value is modified by replacing end unit,
        #represented by cancel, and replacing it with an empty
        #substring.
        error = value.replace(cancel,"")
    else:
        error = "Error"


    #return the parsed number string or error string 
    return error


#Make sure that the text boxes
#containing whole numbers contain
#no decimal points (such as 1 in 1 Mole / # Grams)
#wholeCheck() is for Moles
def wholeCheck(textBoxVar):
    
    number = textBoxVar.GetValue()

    #use a regular expression to make
    #sure number is whole
    r = re.search(r"\A\s*1\s+[mM][oO][lL][eE][sS]?\s*\Z",number)

    if(not(r)):
        return "Error"


#Make sure that the text boxes
#containing whole numbers contain
#no decimal points (such as 1 in 1 Mole / # Grams)
#wholeCheck2 is for Molecules
def wholeCheck2(textBoxVar):
    
    number = textBoxVar.GetValue()

    #use a regular expression to make
    #sure number is whole
    s = re.search(r"\A\s*1\s+[mM][oO][lL][eE][cC][uU][lL][eE][sS]?\s*\Z",number)

    if(not(s)):
        return "Error"


#Make sure that the text boxes
#containing parts of conversion factors are correct
#wholeCheck3 is for liters
def wholeCheck3(textBoxVar):
    
    number = textBoxVar.GetValue()

    #use a regular expression to make
    #sure number is whole
    r = re.search(r"\A\s*22.4\s+[lL][iI][tT][eE][rR][sS]?\s*\Z",number)

    if(not(r)):
        return "Error"

#Make sure that the text boxes
#containing parts of conversion factors are correct
#wholeCheck4 is for molecules
def wholeCheck4(textBoxVar):
    
    number = textBoxVar.GetValue()

    #use a regular expression to make
    #sure number is whole
    s = re.search(r"\A\s*6.022\s*[*]\s*10[\^]23\s+[mM][oO][lL][eE][cC][uU][lL][eE][sS]?\s*\Z",number)

    if(not(s)):
        return "Error"

#Make sure that the text boxes
#containing parts of conversion factors are correct
#wholeCheck4 is for particles
def wholeCheck5(textBoxVar):
    
    number = textBoxVar.GetValue()

    #use a regular expression to make
    #sure number is whole
    s = re.search(r"\A\s*6.022\s*[*]\s*10[\^]23\s+[pP][aA][rR][tT][iI][cC][lL][eE][sS]?\s*\Z",number)

    if(not(s)):
        return "Error"


#wholeCheck6 makes sure that
#the unknown/known amounts within
#stoichiometry related problems remain
#as whole numbers; this way results don't
#mistakenly end up being in terms of atoms represented
#as fractional amounts.
def wholeCheck6(textBoxVar):

    number = textBoxVar.GetValue()

    #use regular expression to make sure
    #only whole numbers are used
    s = re.search(r"\A\s*[0-9]+\s+[mM][oO][Ll][Ee][sS]?\s*\Z",number)

    if(not(s)):
        return "Error"
    else:
        number = number.replace(" ","")
        
        if(number[len(number) - 1] == 's'):
            number = number[:len(number) - 5]
        else:
            number = number[:len(number) - 4]

        return number



#END OF SECTION SEVENTEEN--------------------------------------------------------------------------------


























#SECTION---EIGHTEEN--------------------------------------------------------------------------------------------
#This section is dedicated to inserting all molar mass values into their corresponding text boxes.

#auto write element or mole-tree info to textboxes via periodic table buttons
def elementsTObox(event):

    global molarVar
    
    if(molarVar == 10 or molarVar == 12 or molarVar == 13 or molarVar == 15):
        global first
        global third
        global fourth
        global fifth
        global sixth
        global second
        global elementID
        global rOl
        global answer

        #get associated element id
        button = event.GetEventObject()
        num = button.GetId()


        #periodic table molar mass value
        molar1 = None 

        #get element value from periodic table array
        if(elementID == 1):
            molar1 = L1[num].mass
        elif(elementID == 2):
            molar1 = L2[num].mass
        elif(elementID == 3):
            molar1 = L3[num].mass
        elif(elementID == 4):
            molar1 = L4[num].mass
        elif(elementID == 5):
            molar1 = L5[num].mass
        elif(elementID == 6):
            molar1 = L6[num].mass
        elif(elementID == 7):
            molar1 = L7[num].mass
        elif(elementID == 8):
            molar1 = Lanth[num].mass
        else:
            molar1 = Actin[num].mass




        #place numbers in corresponding text boxes
        #based on the number of ratios and problem type
        if(molarVar == 10):
            #for getting current contents
            contents = None
            if(rOl == 0):
                contents = first.GetValue()
                first.Clear()
                if(contents == "" or "# Grams" in contents):
                    first.write(str(molar1) + " Grams")
                else:
                    contents = contents.replace("Grams","")
                    first.write(str(round(molar1 + float(contents),5)) + " Grams")
            elif(rOl == 3):
                contents = second.GetValue()
                second.Clear()
                if(contents == "" or "# Grams" in contents):
                    second.write(str(molar1) + " Grams")
                else:
                    contents = contents.replace("Grams","")
                    second.write(str(round(molar1 + float(contents),5)) + " Grams")
        elif(molarVar == 12):
            contents = None
            if(rOl == 5 or rOl == 18 or rOl == 14):
                contents = first.GetValue()
                first.Clear()
                if(contents == "" or "# Grams" in contents):
                    first.write(str(molar1) + " Grams")
                else:
                    contents = contents.replace("Grams","")
                    first.write(str(round(molar1 + float(contents),5)) + " Grams")
            elif(rOl == 7 or rOl == 9 or rOl == 22 or rOl == 38):
                contents = third.GetValue()
                third.Clear()
                if(contents == "" or "# Grams" in contents):
                    third.write(str(molar1) + " Grams")
                else:
                    contents = contents.replace("Grams","")
                    third.write(str(round(molar1 + float(contents),5)) + " Grams")
        elif(molarVar == 13):
            contents = None
            if(rOl == 8 or rOl == 19 or rOl == 21):
                contents = first.GetValue()
                first.Clear()
                if(contents == "" or "# Grams" in contents):
                    first.write(str(molar1) + " Grams")
                else:
                    contents = contents.replace("Grams","")
                    first.write(str(round(molar1 + float(contents),5)) + " Grams")
            elif(rOl == 27 or rOl == 32):
                contents = fifth.GetValue()
                fifth.Clear()
                if(contents == "" or "# Grams" in contents):
                    fifth.write(str(molar1) + " Grams")
                else:
                    contents = contents.replace("Grams","")
                    fifth.write(str(round(molar1 + float(contents),5)) + " Grams")
            elif(rOl == 17):
                contents = None
                if(left.IsChecked()):
                    contents = first.GetValue()
                    first.Clear()
                    if(contents == "" or "# Grams" in contents):
                        first.write(str(molar1) + " Grams")
                    else:
                        contents = contents.replace("Grams","")
                        first.write(str(round(molar1 + float(contents),5)) + " Grams")
                else:
                    contents = fifth.GetValue()
                    fifth.Clear()
                    if(contents == "" or "# Grams" in contents):
                        fifth.write(str(molar1) + " Grams")
                    else:
                        contents = contents.replace("Grams","")
                        fifth.write(str(round(molar1 + float(contents),5)) + " Grams")
        elif(molarVar == 15):
            contents = None
            if(rOl == 20):
                contents = first.GetValue()
                first.Clear()
                if(contents == "" or "# Grams" in contents):
                    first.write(str(molar1) + " Grams")
                else:
                    contents = contents.replace("Grams","")
                    first.write(str(round(molar1 + float(contents),5)) + " Grams")

#END OF SECTION EIGHTEEN--------------------------------------------------------------------------------












##############################beginning of the application setup process

#directions label
direction = None

#set deletion flag
set1 = 0

#acid/base flag variable...
AB = None

#mole conversion ratio determinant variable
rOl = None

#keep track of most previous problem chosen
problem = 0

#calculate button variable
calculate = None
calculate2 = None
calculate3 = None
calculate4 = None

#Flag variable to determine if problem type has been chosen...
molarVar = 0

#text box id variables
input = None
first = None
second = None
third = None
fourth = None
fifth = None
sixth = None
seventh = None
eighth = None
answer = None
arrow = None
plus = None
Cosmo = None
Wanda = None
Robin = None
Batman = None
equation = None
output = None

#check boxes used for the molarVar == 13
#setup
right = None
left = None

#element array id's
elementID = None

#subscript of chemical equation
subscripts = 0

#chemEquation
chemEquation = ""

#previous symbol
prev = ""

#most previous molarVar number
last = None

#most previous rOl number
last2 = 0

#chemical equation input variable
molar12 = None

#linear algebra counter
columns = 0
rows = 0

#chemical equation counter
up = 0

#chemical equation element memory for balancing
arrName = None

#flag1 makes sure 
flag1 = 0

#chemical equation element memory for equation input
arrName2 = []

#sub -> element variable
sub = None

#stoichiometry flag
sto = 0
stoTwo = 0
double = 0

#boolean flag
ONE = False

#The application, panel, and frame
#variables that will soon act as important
#wxpython related references...
application = None
panel = None
frame = None

#start the graphical program...
def startG():

    #gain access to the global variables
    #that were declared just before this function
    #so they can be modified and hold references to
    #the wx object, panel object, and frame object
    #respectively...
    global application
    global panel
    global frame
    
    #prepare application
    application = wx.App()

    #get dimensions of current screen
    width, height = wx.GetDisplaySize()

    #setup the dimensions of the frame...
    #should the dimensions be larger than that of
    #the base frame used during development, use the
    #base frame dimensions. Should the dimensions
    #be smaller than the base frame's, use the current
    #screen dimensions.
    if(width > 1680):
        width = 1680
    if(height > 1050):
        height = 1050
    
    #setup the frame with the dimensions from above...
    frame = wx.Frame(parent = None, title = 'The Ultimate Chemistry Calculator',size=wx.Size(width,height))

    #create the window where all the controls will appear
    panel = wx.lib.scrolledpanel.ScrolledPanel(frame)
    vbox = wx.BoxSizer(wx.VERTICAL)
    vbox.Add(wx.Size(1680, 1050))
    panel.SetSizer(vbox)
    panel.SetupScrolling()


    #set background color
    panel.SetBackgroundColour(wx.Colour(173,230,230))

    #function to add all periodic table buttons
    periodic_setup(panel)
    
    #function to add all problem buttons
    problemButtons(panel)

    #review video buttons
    review(panel)

    #show the windows
    frame.Show()

    #start application
    application.MainLoop()
    
