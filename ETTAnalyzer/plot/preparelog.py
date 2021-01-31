import os 

vetos=["Initiating","Successfully"]

log_in = open('TPinfo.txt')


log_out = open('TPinfoWithHeader.txt', 'w')
header_ = open('HeaderNoRLE.txt').readline()
log_out.write(header_)
def myjoin(to_join, deli=" "):
    output=""
    for i in to_join: 
        output = output + i + " "
    return output

pre_str=""

for iline in log_in:
    vetoline=False
    for iveto in vetos: 
        if iveto in iline:
            vetoline=True
    if vetoline: continue 
    if "Closed file file" in iline: break 
    # if "Begin processing" in iline:
        # run_ =   str(iline.rsplit(" ")[6].split(",")[0] )
        # lumi_ =  str(iline.rsplit(" ")[10].split(",")[0] )
        # event_ = str(iline.rsplit(" ")[8].split(",")[0])
        # pre_str = myjoin([run_, lumi_, event_], " ")
    
    else: 
        iline = pre_str + iline
        log_out.write(iline)


    

log_out.close()
