import matplotlib.pyplot as plt 
import pandas as pd 

ol = "/eos/user/a/atishelm/www/EcalL1Optimization/Emulator/"
TPinfo = pd.read_csv("TPinfoWithHeader.txt", sep=" ")

recoA = TPinfo["wbf0"] + TPinfo["wbf1"] + TPinfo["wbf2"] + TPinfo["wbf3"] + TPinfo["wbf4"]
TPinfo["recoA"] = recoA

evenRecoAs = TPinfo.loc[TPinfo['Filter'] == "EVEN", "recoA"]
oddRecoAs = TPinfo.loc[TPinfo['Filter'] == "ODD", "recoA"]

plt.hist(oddRecoAs,
         label = "ODD",
        )
plt.legend()
plt.savefig("%s/OddFilterAmplitudes.png"%(ol))

plt.close()

plt.hist(evenRecoAs,
         label = "EVEN" 
        )

plt.legend()
plt.savefig("%s/EvenFilterAmplitudes.png"%(ol))
