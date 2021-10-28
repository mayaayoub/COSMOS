#Created by Maya Ayoub July, 2021

import numpy as np
import matplotlib.pyplot as plt

# Proccesing input
I,steps=np.loadtxt("RawSpectrumData2.txt",unpack=True) #Load data file
angles=(((steps)/2048)*360) # Turn steps to angles
phi=(42/180)*np.pi #Find detector angle
d=1e-6 # d of grating
I=I/np.max(I) # normalize intensity

#Convert Input to lambda
rad_angles=(angles/180)*np.pi # get angle in radians
wavelength=d*(np.sin(rad_angles+phi)-np.sin(rad_angles))*1e9 
#compute wavelenth, multiply to get in units of nm

#plot
plt.figure(figsize=(16,10))
plt.plot(wavelength,I)
plt.ylabel("Intensity [norm. arb units]",fontsize=20)
plt.xlabel("Wavelength [nm]",fontsize=20)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.title("Laser spectra",fontsize=20)
plt.savefig("SpectrumProject.pdf")
plt.show()
