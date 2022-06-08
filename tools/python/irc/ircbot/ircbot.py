#! /usr/bin/env python

import os
import ssl
import sys
import bs4
import time
import json
import socket
import urllib2
import requests
import threading
import subprocess

from rottentomatoes import RT

# Setup the IRC connection
irc = socket.socket()
irc = ssl.wrap_socket(irc)

# List of currently active threads
threadlist = []

# Edit these values for your server
ircServer = "irc.servercentral.net"
ircSSLPort = 9999
ircNick = "univac"
# What the bot uses as a command character
ircCKey = "!"
# List of channels to connect to
channelList = ['#vbender',
              ]

def rawSend(data):
        irc.send(data + "\r\n")

def ircConnect():
        irc.connect((ircServer, ircSSLPort))

def ircMessage(msg, channel):
        rawSend("PRIVMSG " + channel + " :" + msg + "\r\n")

def ircRegister():
        rawSend("USER " + ircNick + " 0 * " + ":" + ircNick + "\r\n")

def ircSendNick():
        rawSend("NICK " + ircNick + "\r\n")

def ircJoin(channel):
        rawSend("JOIN " + channel + "\r\n")
 
def ircPassword():
       rawSend("PASS " + ircPass + "\r\n")

def Initialize():
        ircConnect()
        ircRegister()
        ircSendNick()
        for channel in channelList:
                ircJoin(channel)

def xkcdSummary(search_string, channel):
        '''Takes a number and outputs details about the xkcd comic'''

        search_string = search_string.rstrip()
        curl_request = "curl -s https://xkcd.com/" + search_string + "/info.0.json"
        output = subprocess.check_output(curl_request, shell=True)

        #This is a nasty workaround due to limitations of the json library
        comic = json.loads(output.decode('utf8'))

        message = 'Title: "{0}", Year: {1}, Alt Text: {2}'.format(comic["safe_title"], comic["year"], comic["alt"])
        ircMessage(message, channel)

def rottenTomatoes(search_string, channel):
        '''Takes a string and outputs details from rotten tomatoes'''

        # Look up the json data from rotten tomatoes
        movie = RT().search(search_string, page_limit=1)

        # Respond if you don't find a match
        if not movie:
                ircMessage("no u", channel)
                return

        movie = movie[0]
        ratings = movie['ratings']

        # Not all movies have a synopsis
        summary = ""
        if movie['synopsis'] != "":
                summary = "Summary: " + movie['synopsis'][:200] + "..."

        # Movies without critics scores are replaced with N/A
        critics = "N/A"
        if ratings['critics_score'] > 0:
                critics = ratings['critics_score']

        message = "{0} ({1}): Critics: {2} Audience: {3} URL: http://rottentomatoes.com/m/{4} {5}".format(movie['title'], movie['year'], critics, ratings['audience_score'], movie['id'], summary)
        ircMessage(message, channel)


def channelRequests(channel, data):
        '''Process all of the commands into the channel'''

        # !ping to see if the bot is alive
        if ircCKey + "ping" in data:
                ircMessage("pong", channel)

        # !rt to search movie details
        if ircCKey + "rt" in data:
                search_string = data[data.find("!rt ") + 4:]
                rottenTomatoes(search_string, channel)

        # !testurl to see if a website is responding
        if ircCKey + "testurl" in data:
                hostname = data[data.find("!testurl ") + 9:]
                try:
                        hostname = hostname.strip("\r\n")
                        request = urllib2.urlopen("http://isup.me/" + hostname)
                        source = request.read()
                        if "s just you." in source:
                                ircMessage(hostname + " is up from here.", channel)
                        else:
                                ircMessage(hostname + " is down from here.", channel)
                except ValueError:
                        ircMessage("Failed to check if: " + hostname + " is up.", channel)

        # !xkcd to do a basic search of xkcd comics
        if ircCKey + "xkcd" in data:
                search_string = data[data.find("!xkcd ") + 6:]

                response = requests.get("http://derp.co.uk/xkcd/page?q=" + search_string + "&search=Search")

                soup = bs4.BeautifulSoup(response.text)
                links = soup.select('a[target="_blank"]')

                for href in links:
                        ircMessage(href.get('href'), channel)

        # print the comic details of any xkcd comic put into the chat
        if "xkcd.com/" in data:
                search_string = data[data.find("xkcd.com/") + 9:]
                xkcdSummary(search_string, channel)

        # Per RFC 1149.5
        if ircCKey + "random" in data:
                ircMessage("4", channel)

Initialize()

while True:
        data = irc.recv(4096)

        # Some servers have a non-standard implementation of IRC, so we're looking for 'ING' rather than 'PING'
        if "ING" in data:
                rawSend("PONG")
                continue

        # Take anything sent from the server and process it for expected commands
        for channel in channelList:
                if "PRIVMSG " + channel in data:
                        t = threading.Thread(target=channelRequests, args=(channel, data))
                        t.daemon = True
                        t.start()
                        continue
