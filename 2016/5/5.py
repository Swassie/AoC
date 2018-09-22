import hashlib

i = 0
password = [-1, -1, -1, -1, -1, -1, -1, -1]
while True:
    m = hashlib.md5()
    m.update( "ojvtpuvg" + str( i ) )
    md5 = m.hexdigest()
    if md5[0:5] == "00000":
        print( "Found: " + md5 )
        if md5[5] in ['0','1','2','3','4','5','6','7'] and password[ int(md5[5]) ] == -1:
            password[ int(md5[5]) ] = md5[6]
            print( password )
    i += 1
    if -1 not in password:
	print( password )
        break
