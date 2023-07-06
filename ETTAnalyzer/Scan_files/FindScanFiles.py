import os 

#Replace by importing a json?
scan_delay = {              #run, first and last (included) LS
    -6 : [369937, 51, 81],   #date: 29/04/23
    -5 : [369937, 84, 105],
    -4 : [369937, 107, 138],
    -3 : [369937, 140, 171],
    -2 : [369938, 1, 31],
    -1 : [369938, 34, 66],
    0 : [369938, 68, 99],
    1 : [369938, 101, 125],
    2 : [369938, 127, 153],
    3 : [369942, 1, 21],
    4 : [369942, 23, 42],
    5 : [369942, 44, 64],
    6 : [369942, 66, 86]
}

for i in range(-6, -5):
    run, first_LS, last_LS = scan_delay[i]
    scan_file = 'Scan_delay_%s.txt'%(i)
    os.system('rm ' + scan_file)
    for ls in range(first_LS, last_LS + 1):
        COMMAND = "dasgoclient --query='file dataset=/SpecialHLTPhysics0/Run2023D-v1/RAW run=%s lumi=%s' >> "%(run, ls) + scan_file
        os.system(COMMAND)
            