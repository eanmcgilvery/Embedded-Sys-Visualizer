from flask import *
import os
from datetime import datetime

app = Flask(__name__)

# Path where file of commands is stored
FNAME = 'commands.txt'
PATH = '/home/pi/server/RC_SERVER/'+ FNAME

@app.route('/', methods=['PUT', 'POST', 'GET'])
def library_to_server():
	#Clean out contents of file
	#open(PATH,'w').close()

	#Save and Decode data to throw into a file
	data = request.data.decode('utf-8')
	if request.method == 'PUT':
		#Get Current Date+Time
		time_stamp = '<LastMod>' + str(int(datetime.now().timestamp())) + '<'
		os.remove(PATH)
		f = open("commands.txt",'a')
		f.write(time_stamp)
		f.write(data)
		f.close()
		return 'FILE TRANSFER SUCCESS'
	elif request.method == 'GET':
#		return 'TEST'
		if  os.path.isfile(PATH):
			return send_file(PATH)
		else:
			return 'ERROR. NO FILE ON SERVER'


if __name__ == '__main__':
	app.secret_key = 'yee'
	app.config['SESSION_TYPE'] = 'filesystem'
#	session =Session()
#	session.init_app(app)
	app.debug = True
	app.run(host='0.0.0.0', port=80)
