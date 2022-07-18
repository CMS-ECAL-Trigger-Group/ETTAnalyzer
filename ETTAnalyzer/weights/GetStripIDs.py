"""
4 February 2022 
Abraham Tishelman-Charny 

The purpose of this module is to get column stripID values from DOF csv files.

Example usage:
python3 GetStripIDs.py 
"""

import pandas as pd

#def AppendEB(f_):
#    EBid_=[]
#    df = pd.read_csv(f_)
#    df.drop_duplicates(subset ="stripid",keep = 'first',inplace = True)
#    AllEB=df['EB']
#    for EBid in AllEB:
    #	print(EBid)
#    	EBid_.append(EBid)
#    return EBid_

def AppendStripIDs(f_):
    stripIDs_ = []
    df = pd.read_csv(f_)
    df.drop_duplicates(subset ="stripid",keep = 'first',inplace = True)
    #df2 = df[~df['EB'].isin(['EB-10','EB+10'])]
    AllstripIDs=df['stripid']
    for stripID in AllstripIDs:
            stripIDs_.append(stripID)

    return stripIDs_


def AppendStripIDs_good(f_):
    stripIDs_ = []
    df = pd.read_csv(f_)
    df.drop_duplicates(subset ="stripid",keep = 'first',inplace = True)
    df2 = df[df['EB'].isin(['EB-10','EB+10'])]
    AllstripIDs=df2['stripid']
    for stripID in AllstripIDs:
            stripIDs_.append(stripID)

    return stripIDs_


def AppendStripIDs_EE(f_):
    stripIDs_ = []
    df = pd.read_csv(f_)
    df.drop_duplicates(subset ="stripid",keep = 'first',inplace = True)
    AllstripIDs=df['stripid']
    for stripID in AllstripIDs:
    	    stripIDs_.append(stripID)

    return stripIDs_



if(__name__ == '__main__'):

    d = '/afs/cern.ch/work/m/mcampana/ecall1algooptimization/PileupMC/parameters/'
    #d = '/afs/cern.ch/work/a/atishelm/private/ecall1algooptimization/PileupMC/parameters/'
    EE_f = '{d}/DOF_EE_2018.csv'.format(d=d)
    EB_f = '{d}/DOF_EB_2018.csv'.format(d=d)

    EB_stripIDs = AppendStripIDs(EB_f)
    #EB_stripIDs_good = AppendStripIDs_good(EB_f)
    EE_stripIDs = AppendStripIDs_EE(EE_f)

    #EB_=AppendEB(EB_f)

    print("len(EB_stripIDs):",len(EB_stripIDs))
    #print("len(EB_stripIDs):",len(EB_stripIDs_good))
    #print("len(EB_stripIDs):",len(EB_stripIDs_good)+len(EB_stripIDs))
    #print("len(EB_):",len(EB_))
    print("len(EE_stripIDs):",len(EE_stripIDs))

    outName = "OneEBOneEEset.txt"

    with open(outName, 'w') as f:
        for EB_stripID in EB_stripIDs:
            print(EB_stripID)
            line = "{EB_stripID}\t0\n".format(EB_stripID=EB_stripID) # assign EB strips weight group 0 
            f.write(line)
    #    for EB_stripID in EB_stripIDs_good:
    #        line = "{EB_stripID}\t3\n".format(EB_stripID=EB_stripID) # assign EB strips weight group 0 
    #        f.write(line)
        for EE_stripID in EE_stripIDs: 
            line = "{EE_stripID}\t1\n".format(EE_stripID=EE_stripID) # assign EE strips weight group 1 
            f.write(line)            
        
#    f.close()
    print("Wrote output file:",outName)
