#all nine mole conversion functions

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
