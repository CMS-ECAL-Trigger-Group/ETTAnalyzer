import matplotlib.pyplot as plt 
import pandas as pd 
import argparse 

argparser = argparse.ArgumentParser()
argparser.add_argument("--outLoc", type=str, default="", required=True)
args = argparser.parse_args()

outLoc = args.outLoc
TPinfo = pd.read_csv("TPinfoWithHeader.txt", sep=" ")

recoA = TPinfo["wbf0"] + TPinfo["wbf1"] + TPinfo["wbf2"] + TPinfo["wbf3"] + TPinfo["wbf4"]
TPinfo["recoA"] = recoA

evenRecoAs = TPinfo.loc[TPinfo['Filter'] == "EVEN", "recoA"]
oddRecoAs = TPinfo.loc[TPinfo['Filter'] == "ODD", "recoA"]

plt.hist(oddRecoAs,
         label = "ODD",
        )
plt.legend()
plt.savefig("%s/OddFilterAmplitudes.png"%(outLoc))

plt.close()

plt.hist(evenRecoAs,
         label = "EVEN" 
        )

plt.legend()
plt.savefig("%s/EvenFilterAmplitudes.png"%(outLoc))
