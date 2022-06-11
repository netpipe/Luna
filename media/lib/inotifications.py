#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (c) 2009, 2010, Thomas Jost <thomas.jost@gmail.com>
# 
# Permission  to use,  copy, modify,  and/or  distribute this  software for  any
# purpose  with  or without  fee  is hereby  granted,  provided  that the  above
# copyright notice and this permission notice appear in all copies.
# 
# THE SOFTWARE IS PROVIDED "AS IS"  AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO  THIS SOFTWARE INCLUDING  ALL IMPLIED WARRANTIES  OF MERCHANTABILITY
# AND FITNESS. IN  NO EVENT SHALL THE AUTHOR BE LIABLE  FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR  CONSEQUENTIAL DAMAGES OR  ANY DAMAGES WHATSOEVER  RESULTING FROM
# LOSS OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER  TORTIOUS ACTION,  ARISING  OUT OF  OR  IN CONNECTION  WITH  THE USE  OR
# PERFORMANCE OF THIS SOFTWARE.

"""Client for the iOS app "Notifications" (aka "Push 4.0").

http://www.appnotifications.com/

This  module helps  scripts to  use  the HTTP  REST API  of the  `Notifications'
application, which is  available for the iPhone and the  iPod Touch. It supports
finding  the  user's credentials  token,  and  then  sending notification  in  a
synchronous or asynchronous way. This modules provides three functions:

get_credentials() -- Get the user's credentials token
send() -- Send a notification, waiting for it to be sent.
send_async() -- Send a  notification, returning immediately, without waiting for
the message to be sent.

"""

__author__ = ("Thomas Jost <thomas.jost@gmail.com>, "
			"Chris Lucas <cjlucas07@gmail.com>")
__version__ = "0.3.2"

import sys
import threading

_py3 = sys.version_info > (3,)

if _py3:
	from urllib.request import urlopen, HTTPError, URLError
	from urllib.parse import urlencode
	from io import StringIO
else:
	from urllib2 import urlopen, HTTPError, URLError #@Reimport @UnresolvedImport
	from urllib import urlencode #@Reimport @UnresolvedImport
	from StringIO import StringIO #@Reimport @UnresolvedImport

try: import simplejson as json
except ImportError: import json

CREDENTIALS_URL = "https://www.appnotifications.com/user_session.json"
SEND_URL = "https://www.appnotifications.com/account/notifications.json"
HTTP_TIMEOUT = 5

def get_credentials(email, password, debug=False):
	"""Get the user's credentials token.
	
	@param email: user's email address
	@type email: str
	
	@param password: user's password
	@type password: str
	
	@param debug: writes the response from the API to sys.stderr
	@type debug: bool
	
	@return: A unique token required to access the API, or -1 if there was 
	an error sending the request.
	@rtype: str
	
	@raise AssertionError: Is raised if:
		- The HTTP response code is not 200
		- API returned error (usually invalid email/password)
	@raise ValueError: Is raised if:
		- JSON couldn't be parsed
		- Invalid username/password given
		- Unrecognizable response is received
	"""
	cred_key = 'single_access_token'

	# Create data to POST
	data = {
		'user_session[email]': email,
		'user_session[password]': password
	}
	data = urlencode(data).encode('utf-8')

	# Send them
	try:
		u = urlopen(CREDENTIALS_URL, data, timeout=HTTP_TIMEOUT)
	except HTTPError as e:
		_handle_httperror(e)
		return(-1)
	except URLError as e:
		_handle_urlerror(e)
		return(-1)

	resp_code = u.getcode()
	assert resp_code == 200, "HTTP Response Code: {0}".format(resp_code)

	# Parse the JSON response
	resp = u.read().decode('utf-8')
	if debug: sys.stderr.write(resp)
	u.close()

	resp_dict = json.load(StringIO(resp))
	#if debug: sys.stderr.write(str(resp_dict))

	assert 'error' not in resp_dict.keys(), resp_dict['error']

	if cred_key in resp_dict.keys(): return(resp_dict[cred_key])
	else: raise ValueError("Unknown response received: {0}".format(resp_dict))

	# old XML code
	#doc = xml.dom.minidom.parseString(response)
	#token = doc.getElementsByTagName("single-access-token")
	#assert len(token) > 0, \
	#	"single-access-token couldn't be found. Email and password correct?"

	#return(token[0].firstChild.data)


def send(credentials, message, title=None, subtitle=None, long_message=None,
		 long_message_preview=None, icon_url=None, message_level=0, silent=False,
		 action_loc_key=None, run_command=None, sound=1, debug=False):
	"""Send a notification, waiting for the message to be sent.

	@param credentials: the API token returned by L{get_credentials}
	@type credentials: bytes or str
	
	@param message: The message used for the alert window when 
	the notification appears.
	@type: message: str
	
	@param title: The title of the notification in the notifications list. (optional)
	@type title: str
	
	@param subtitle: The subtitle of the notification in the 
	notifications list. We suggest you use this to give more informations, 
	for example “RSS: a feed”. (optional)
	@type subtitle: str
	
	@param long_message: The notification when the user select it in the list, 
	this is the long text. (optional)
	@type long_message: str
	
	@param long_message_preview: The preview under the title in the listing, 
	we suggest you don’t put any HTML there. (optional)
	@type long_message_preview: str
	
	@param icon_url: The icon on the left in the listing. (optional)
	@type icon_url: str
	
	@param message_level: the importance of the notification, from -2 to 2. (optional)
	@type message_level: int
	
	@param silent: Should this be silent? (no alert window, just a badge number).
	@type silent: bool
	
	@param action_loc_key: The name of the validation button (optional)
	@type action_loc_key: str
	
	@param run_command: todo
	@type run_command: str
	
	@param sound: Select the sound you want for the notification. The sound
	should be a number that correlates to 
	U{this list<https://gist.github.com/1217045>}. (Valid range: 1-40)
	@type sound: int
	
	@param debug: writes the response from the API to sys.stderr
	@type debug: bool
	
	@return: The ID of the notification, or -1 if there was an error 
	sending the request.	
	@rtype: int
	
	@raise ValueError: Is raised if:
		- Invalid user credentials were given
		- Invalid message was given
		- JSON couldn't be parsed
		- sound param is not within valid range
		- message_level is not within valid range
	
	@note: The first two arguments (credentials  and message) are mandatory, 
	all of the others are optional. They are  the same as the various identifiers 
	described in	the   documentation	of	the   Notifications	HTTP   REST	API
	(http://developer.appnotifications.com/p/user_notifications.html).
	"""
	# Create data to POST
	data = {}

	if credentials is None or credentials == "":
		raise ValueError("Invalid user credentials")
	if message is None or message == "":
		raise ValueError("Invalid message")

	data['user_credentials'] = credentials
	data['notification[message]'] = message

	for key in ("title", "subtitle", "long_message", "long_message_preview",
				"icon_url", "message_level", "action_loc_key", "run_command"):
		value = locals()[key]
		if value is not None:
			data['notification[{0}]'.format(key)] = value

	if not (-2 <= message_level <= 2):
		raise ValueError("message_level must be an integer between -2 and 2")

	if silent:
		data['notification[silent]'] = 1
	else:
		data['notification[silent]'] = 0
		if not (1 <= sound <= 40):
			raise ValueError("sound must be an integer between 1 and 40")
		data['notification[sound]'] = "{0}.caf".format(sound)

	# Encode the data, trying to deal with Unicode
	for k in data:
		if type(data[k]) is str:
			data[k] = data[k].encode('utf-8')

	data = urlencode(data).encode('utf-8')

	# Send the notification
	try:
		u = urlopen(SEND_URL, data, timeout=HTTP_TIMEOUT)
	except HTTPError as e:
		_handle_httperror(e)
		return(-1)
	except URLError as e:
		_handle_urlerror(e)
		return(-1)

	#success = (u.getcode() == 200)
	resp = u.read().decode('utf-8')
	if debug: sys.stderr.write(resp)
	u.close()

	resp_dict = json.load(StringIO(resp))

	if 'id' in resp_dict.keys(): return(resp_dict['id'])
	else: return(-1)


def send_async(*args, **kwargs):
	"""Send  a  notification, returning  immediately,  without  waiting for  the
	message to be sent.
	
	@param args: see L{send}
	
	@param kwargs: see L{send}

	This function does return the ID of the thread that does the HTTP request.
	"""
	thr = threading.Thread(target=send, args=args, kwargs=kwargs)
	thr.daemon = True
	thr.start()
	return(thr)

def _handle_httperror(e):
	sys.stderr.write("*** Caught HTTPError ***\n")
	sys.stderr.write("*** url: {0}\n".format(e.url))
	sys.stderr.write("*** code: {0}\n".format(e.code))
	sys.stderr.write("*** msg: {0}\n".format(e.msg))

def _handle_urlerror(e):
	sys.stderr.write("*** Caught URLError ***\n")
	e = e.__dict__
	for k in e.keys(): sys.stderr.write("*** {0}: {1}\n".format(k, e[k]))

if __name__ == '__main__':
	if len(sys.argv) != 3:
		sys.stderr.write("Syntax: {0} credentials message".format(sys.argv[0]))
	else:
		send(sys.argv[1], sys.argv[2], debug=True)
