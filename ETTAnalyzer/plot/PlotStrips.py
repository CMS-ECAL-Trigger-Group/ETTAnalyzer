import pandas as pd 
import numpy as np 
from matplotlib import pyplot as plt 

ol = "/eos/user/a/atishelm/www/EcalL1Optimization/Emulator/Configuration_1/"

input = "outputs/StripOuts.txt"
df = pd.read_csv(input, sep=' ')
EVEN_mask = df["Filter"] == "EVEN"
ODD_mask = df["Filter"] == "ODD"
EVEN_mask = EVEN_mask.to_numpy()
ODD_mask = ODD_mask.to_numpy()
Energies = df["E"].to_numpy()

ETs_Even = Energies[:][EVEN_mask] 
ETs_Odd = Energies[:][ODD_mask]

fig, ax = plt.subplots()

for ETs in ["Even", "Odd"]:
	# label = "%s%s_%s"%(var, digi, filter)
	label = "ETs_%s"%(ETs)
	#fig, ax = plt.subplots()
	exec("xmin, xmax, xbins = ( min(%s) - abs(min(%s) / 10.) ), ( max(%s) + abs(max(%s) / 10.) ), int( ( max(%s) - min(%s) ) + 1 )"%(label,label,label,label,label,label))
	bins = np.linspace(xmin, xmax, xbins + 1)
	exec("Nentries = np.size(%s)"%(label))
	exec("avg = np.mean(%s)"%(label))           

	exec("plt.hist(%s, histtype = 'step', bins = bins, label = '%s')"%(label, label))
"""
	plt.text(0.5, 0.8, 
					label, 
					fontsize = 15,
					horizontalalignment='center', 
					verticalalignment='center', 
					transform = ax.transAxes)
	plt.text(0.5, 0.7, 
					'Entries = %s'%(Nentries), 
					fontsize = 15,
					horizontalalignment='center', 
					verticalalignment='center', 
					transform = ax.transAxes)
	plt.text(0.5, 0.6,
					'Average = %.5f'%(avg), 
					fontsize = 15,
					horizontalalignment='center', 
					verticalalignment='center', 
					transform = ax.transAxes)  
"""
plt.legend()
plt.yscale('log')
plt.savefig("%s/%s.png"%(ol, label))	
plt.close()	

EminusO = ETs_Even - ETs_Odd

# print"Even:",ETs_Even
# print"Odd:",ETs_Odd
# print"Diff:",EminusO

fig, ax = plt.subplots()
xmin, xmax, xbins = min(EminusO), max(EminusO), int(max(EminusO) - min(EminusO))
bins = np.linspace(xmin, xmax, xbins + 1)
plt.hist(EminusO, histtype = 'step', bins = bins, label = 'EVEN - ODD')
plt.savefig("%s/EvenMinusOdd.png"%(ol))

# fig, ax = plt.subplots()
# xmin, xmax, xbins = 0, 1000000, 1000000
# bins = np.linspace(xmin, xmax, xbins + 1)
# plt.hist(df["StripID"], histtype = 'step', bins = bins, label = 'StripID')
# plt.savefig("%s/StripID.png"%(ol))



# for digi in range(1,6):
#   for filter in ["EVEN","ODD"]:
# 		exec("w%s_%s = df['w%s']"%(digi, filter, digi))
# 		exec("d%s_%s = df['d%s']"%(digi, filter, digi))
# 		exec("w%s_%s = w%s_%s[%s_mask]"%(digi, filter, digi, filter, filter))
# 		exec("d%s_%s = d%s_%s[%s_mask]"%(digi, filter, digi, filter, filter))
# 		label = "dw%s_%s"%(digi, filter)

# 		exec("%s = np.multiply(w%s_%s, d%s_%s)"%(label, digi, filter, digi, filter))

# 		for var in ["w","d","dw"]:
# 			print"Filter:",filter
# 			print"Index:",digi			
# 			print"Variable:",var
# 			label = "%s%s_%s"%(var, digi, filter)
# 			fig, ax = plt.subplots()
# 			exec("xmin, xmax, xbins = ( min(%s) - abs(min(%s) / 10.) ), ( max(%s) + abs(max(%s) / 10.) ), int( ( max(%s) - min(%s) ) + 1 )"%(label,label,label,label,label,label))
# 			bins = np.linspace(xmin, xmax, xbins + 1)
# 			exec("Nentries = np.size(%s)"%(label))
# 			exec("avg = np.mean(%s)"%(label))           

# 			exec("plt.hist(%s, histtype = 'step', bins = bins, label = '%s')"%(label, label))

# 			plt.text(0.5, 0.8, 
# 							label, 
# 							fontsize = 15,
# 							horizontalalignment='center', 
# 							verticalalignment='center', 
# 							transform = ax.transAxes)
# 			plt.text(0.5, 0.7, 
# 							'Entries = %s'%(Nentries), 
# 							fontsize = 15,
# 							horizontalalignment='center', 
# 							verticalalignment='center', 
# 							transform = ax.transAxes)
# 			plt.text(0.5, 0.6,
# 							'Average = %.5f'%(avg), 
# 							fontsize = 15,
# 							horizontalalignment='center', 
# 							verticalalignment='center', 
# 							transform = ax.transAxes)  

# 			plt.legend()
# 			plt.savefig("%s/%s.png"%(ol, label))
# 			plt.close()		

print"DONE"





# ##-- Separate 
# fig, ax = plt.subplots()
# # for f_i, file in enumerate(["log_Run2_ET.txt","test2_ETs.txt"]):
# for f_i, file in enumerate(["FinalCheck_Run2_ETs.txt","FinalCheck_Config1_ETs_final.txt"]):
#     if f_i == 0: label = "Run2"
#     else: label = "Config1"

#     df = pd.read_csv(file)
#     ETs = []
#     for ic,column in enumerate(df):
#         if(ic==0): columnName = column 
#     Energies = [float(ET[6:]) for ET in df[columnName]]
#     ETs = np.array(Energies)
#     Nentries = np.size(ETs)
#     avg = np.mean(ETs)

#     # xmin, xmax, nbins = min(ETs), max(ETs), int(max(ETs) - min(ETs))
#     xmin, xmax, nbins = 0, 15, 15 
#     # xmin, xmax, nbins = 0, 2, 2
#     bins = np.linspace(xmin, xmax, nbins + 1)
#     print("Plotting...")
#     print ETs
#     # fig, ax = plt.subplots()
#     plt.hist(ETs, histtype = 'step', bins = bins, label = label)
#     plt.text(0.5, 0.8, 
#             label, 
#             fontsize = 15,
#             horizontalalignment='center', 
#             verticalalignment='center', 
#             transform = ax.transAxes)
#     plt.text(0.5, 0.7, 
#             'Entries = %s'%(Nentries), 
#             fontsize = 15,
#             horizontalalignment='center', 
#             verticalalignment='center', 
#             transform = ax.transAxes)
#     plt.text(0.5, 0.6,
#             'Average = %.5f'%(avg), 
#             fontsize = 15,
#             horizontalalignment='center', 
#             verticalalignment='center', 
#             transform = ax.transAxes)  
     
#     # plt.text(0.5, 0.8,
#             # 'TP Energy',
#             # fontsize = 20,
#             # horizontalalignment='center', 
#             # verticalalignment='center', 
#             # transform = ax.transAxes)             

#     plt.legend()
#     plt.xlabel("ET")
#     plt.ylabel("Entries")
#     plt.yscale('log')
#     ymin, ymax = 0.1, 10000. 
#     plt.ylim(ymin,ymax)
#     plt.savefig("%s/%s_%s"%(ol,label,"ETs.png"))
#     plt.close()

# ##-- Together
# fig, ax = plt.subplots()
# for f_i, file in enumerate(["FinalCheck_Run2_ETs.txt","FinalCheck_Config1_ETs_final.txt"]):
#     if f_i == 0: label = "Run2"
#     else: label = "Config1"

#     df = pd.read_csv(file)
#     ETs = []
#     for ic,column in enumerate(df):
#         if(ic==0): columnName = column 
#     Energies = [float(ET[6:]) for ET in df[columnName]]
#     ETs = np.array(Energies)
#     Nentries = np.size(ETs)
#     avg = np.mean(ETs)

#     # xmin, xmax, nbins = min(ETs), max(ETs), int(max(ETs) - min(ETs))
#     xmin, xmax, nbins = 0, 15, 15 
#     # xmin, xmax, nbins = 0, 2, 2
#     bins = np.linspace(xmin, xmax, nbins + 1)
#     print("Plotting...")
#     print ETs
#     # fig, ax = plt.subplots()
#     plt.hist(ETs, histtype = 'step', bins = bins, label = label)
#     # plt.text(0.5, 0.8, 
#     #         label, 
#     #         fontsize = 15,
#     #         horizontalalignment='center', 
#     #         verticalalignment='center', 
#     #         transform = ax.transAxes)
#     # plt.text(0.5, 0.7, 
#     #         'Entries = %s'%(Nentries), 
#     #         fontsize = 15,
#     #         horizontalalignment='center', 
#     #         verticalalignment='center', 
#     #         transform = ax.transAxes)
#     # plt.text(0.5, 0.6,
#     #         'Average = %.5f'%(avg), 
#     #         fontsize = 15,
#     #         horizontalalignment='center', 
#     #         verticalalignment='center', 
#     #         transform = ax.transAxes)  
     
# plt.text(0.5, 0.8,
#         'TP Energy',
#         fontsize = 20,
#         horizontalalignment='center', 
#         verticalalignment='center', 
#         transform = ax.transAxes)             

# plt.legend()
# plt.xlabel("ET")
# plt.ylabel("Entries")
# plt.yscale('log')
# ymin, ymax = 0.1, 10000. 
# plt.ylim(ymin,ymax)
# plt.savefig("%s/%s"%(ol,"Compare_ETs.png"))

# print("DONE")
