import os 

#Replace by importing a json?
scan_delay = {              #run, first and last (included) LS
    -6 : [366794, 0, 33],   #date: 29/04/23
    -5 : [366794, 35, 63],
    -4 : [366794, 66, 94],
    -3 : [366794, 96, 125],
    -2 : [366795, 0, 32],
    -1 : [366795, 35, 62],
    0 : [366795, 64, 97],
    1 : [366797, 4, 32],
    2 : [366797, 34, 68],
    3 : [366798, 0, 25],
    4 : [366798, 27, 52],
    5 : [366798, 54, 75],
    6 : [366798, 77, 111]
}

for i in range(-6, 7):
    run, first_LS, last_LS = scan_delay[i]
    scan_file = 'Scan_delay_%s.txt'%(i)
    os.system('rm ' + scan_file)
    for ls in range(first_LS, last_LS + 1):
        COMMAND = "dasgoclient --query='file dataset=/SpecialHLTPhysics0/Run2023B-v1/RAW run=%s lumi=%s' >> "%(run, ls) + scan_file
        os.system(COMMAND)
            