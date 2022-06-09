import socket
from threading import Thread
from json import dumps as dictToJson
from json import loads as jsonToDict

class NodeSocket(Thread):
	def __init__(self, path='/tmp/node-python-sock', openSocket=True):
		super(NodeSocket, self).__init__()
		self.path = path
		self.data = ''
		self.channels = {}
		self.go = True
		if openSocket:
			self.open()
		self.start()

	def open(self):
		while True:
			try:
				self.client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
				self.client.connect(self.path)
				self.socketOpen = True
				return
			except: continue

	def run(self, size=256):
		if self.socketOpen:
			tmp = ''
			while self.go:
				tmp += self.client.recv(size).decode().encode('utf-8')
				try:
					msg = jsonToDict(tmp)
					if msg['type'] not in self.channels.keys():
						self.registerChannel(msg['type'])
					self.channels[msg['type']] = msg['data']
					tmp = ''
				except: continue
		return

	def registerChannel(self, channel):
		self.channels[channel] = None

	def get(self, channel):
		if channel in self.channels.keys():
			return self.channels[channel]
		return None

	def write(self, channel, data):
		msg = {'type': channel, 'data': data}
		self.client.send(dictToJson(msg).encode())

	def close(self):
		self.client.close()
		self.socketOpen = False

	def isOpen(self):
		return self.socketOpen

	def exit(self):
		self.go = False
		msg = {'stop': True}
		self.client.send(dictToJson(msg).encode())
