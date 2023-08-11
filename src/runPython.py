import sys
try:
    print('Using python ' + sys.version + ' at ' + sys.executable + '\n')
    sys.path.append(sys.argv[1])
    exec(open(sys.argv[2]).read())
    input('Press any key to continue')
except Exception as e:
    print('Something gone wrong: ' + e)
    input('Press any key to continue')