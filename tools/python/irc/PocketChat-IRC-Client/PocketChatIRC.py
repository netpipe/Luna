#!/usr/bin/python3
from tkinter import *
from tkinter import messagebox, ttk
from tkinter.scrolledtext import ScrolledText
from socket import socket
from select import select
import sys, threading, time, ssl
import configparser

class Window(Frame):
    def __init__(self, master):
        Frame.__init__(self, master)
        self.root = master
        self.sckt = socket()
        self.parser = configparser.ConfigParser()
        self.parser.read('settings.ini')
        self.grid()
        self.tabs = {}
        self.init_window()
        self.getuser_popup()
        
    def getuser_popup(self):# Builds the UI for the username entry window
        self.checkSSL = IntVar()
        self.checkSSL.set(0)
        self.top = Toplevel()
        self.top.transient(root)
        w = 280
        h = 240
        sw = self.top.winfo_screenwidth()
        sh = self.top.winfo_screenheight()
        x = (sw - w)/2
        y = (sh - h)/2
        self.top.geometry('%dx%d+%d+%d' % (w, h, x, y))
        
        self.SERVERIP = Entry(self.top, width=24)
        self.SERVERIP.place(x=75, y=10)
        self.SERVERIP.insert(0, 'weber.​freenode.​net')
        self.SERVERLB = Label(self.top, text = 'Server IP')
        self.SERVERLB.place(x=5, y=10)
        
        self.enterUser = Entry(self.top, width=24)
        self.enterUser.place(x=75, y=32)
        self.enterUser.focus_force()
        self.enterUsername = Label(self.top, text = 'Nickname')
        self.enterUsername.place(x=5, y=32)
        
        self.enterIDENT = Entry(self.top, width=24)
        self.enterIDENT.place(x=75, y=54)
        self.enterIDENTLb = Label(self.top, text = 'Identity')
        self.enterIDENTLb.place(x=5, y=54)
        
        self.enterREALNAME = Entry(self.top, width=24)
        self.enterREALNAME.place(x=75, y=76)
        self.enterREALNAMELb = Label(self.top, text = 'Realname')
        self.enterREALNAMELb.place(x=5, y=76)
        
        self.enterPASSWORD = Entry(self.top, show="*", width=24)
        self.enterPASSWORD.place(x=75, y=98)
        self.enterPASSWORDLb = Label(self.top, text = '*Password')
        self.enterPASSWORDLb.place(x=5, y=98)
        
        self.autoJoin = Entry(self.top, width=32)
        self.autoJoin.place(x=10, y=142)
        self.autoJoinLb = Label(self.top, text = '*Auto join channels seperated by a ","')
        self.autoJoinLb.place(x=5, y=120)

        self.sslCHECKBOX = Checkbutton(self.top, variable=self.checkSSL, onvalue=1, offvalue=0, text="Use SSL")
        self.sslCHECKBOX.place(x=5, y=160)         
        self.sslCHECKBOX.select()
        
        self.OPTIONALLb = Label(self.top, text = '"*"optional sections')
        self.OPTIONALLb.place(x=140, y=160)
        
        self.usernameButton = Button(self.top, text='Connect', command = self.get_username, height=2, width=8)
        self.usernameButton.bind('<Return>', self.get_username)
        self.usernameButton.place(x=90, y=185)
        
        if self.parser.has_section("UserSettings"):
            self.enterUser.insert(0, self.parser.get('UserSettings', 'nickname'))
            self.enterIDENT.insert(0, self.parser.get('UserSettings', 'identity'))
            self.enterREALNAME.insert(0, self.parser.get('UserSettings', 'realname'))
        if self.parser.has_section("AutoJoin"):
            self.autoJoin.insert(0, self.parser.get('AutoJoin', 'channels'))
        
    def init_window(self):# Builds the UI for the main window
        self.n = ttk.Notebook(root)
        self.n.enable_traversal()
        root.title('Python Chat')
        w = 480
        h = 272
        sw = root.winfo_screenwidth()
        sh = root.winfo_screenheight()
        x = (sw - w)/2
        y = (sh - h)/2
        root.geometry('%dx%d+%d+%d' % (w, h, x, y))
        
        self.textboxframe = ttk.Frame(self.n)
        self.textboxframe.grid(row=0, column=0, sticky=N+S+E+W) 
 
        self.textReceive = ScrolledText(self.textboxframe,  height=24, width=47, wrap = WORD)
        self.textReceive.grid(row = 0, column= 0, padx=(10,0), pady=(10,5), sticky=N+S+E+W)
        self.textReceive.config(state=DISABLED)
        
        self.textEntry = ScrolledText(self.textboxframe, height=2, width=47, wrap = WORD)
        self.textEntry.grid(row = 2, column= 0, padx=(10,0), pady=(0,10), sticky=N+S+E+W)
        self.textEntry.bind('<Return>', self.check_pm_commands)
        
        Grid.rowconfigure(root, 0, weight=1)
        Grid.columnconfigure(root, 0, weight=1) 
        Grid.rowconfigure(self.textboxframe, 0, weight=1)
        Grid.columnconfigure(self.textboxframe, 0, weight=1)
        
        self.tabs['Server Info'] = {}
        self.tabs['Server Info']['tab'] = self.textboxframe
        self.tabs['Server Info']['textbox'] = self.textReceive
        self.tabs['Server Info']['entrybox'] = self.textEntry
        self.tabs['Server Info']['onlineusers'] = ''
        
        self.n.add(self.textboxframe, text='Server Info')
        self.n.grid(row=0, column=0, sticky=N+S+E+W)
        
    def get_username(self, event=None):# Gets the initial username after hitting the enter chat button
        self.aliasName = self.enterUser.get()
        self.IDENT = self.enterIDENT.get()
        self.REALNAME = self.enterREALNAME.get()
        self.SERVER = self.SERVERIP.get()
        password = self.enterPASSWORD.get()
        self.Channels = self.autoJoin.get()
        if self.aliasName == '':
            messagebox.showinfo(message='You must enter a username', icon='warning')
        elif ' ' in self.aliasName:
            messagebox.showinfo(message='Username cannot contain spaces', icon='warning')
        elif not password and self.checkSSL.get() == 1:
            self.sckt = ssl.wrap_socket(self.sckt)
            self.PORT = 6697
            self.start_recv_loop()     
        elif password and self.checkSSL.get() == 1:
            self.sckt = ssl.wrap_socket(self.sckt)
            self.PORT = 6697
            self.start_recv_loop()
            self.sckt.send(bytes('PRIVMSG NickServ : IDENTIFY %s\r\n' % password, "UTF-8"))             
        else:
            self.PORT = 6667
            self.start_recv_loop()
        self.user_settings()
        
    def start_recv_loop(self):
        self.top.destroy()
        self.master.title('Python Chat - %s' % self.aliasName)
        self.sckt.connect((self.SERVER, self.PORT))
        thread = threading.Thread(target=self.recv_loop, args=[self.sckt])
        thread.daemon = True
        thread.start()
        self.root.after(500, lambda:self.sckt.send(bytes("NICK %s\r\n" % self.aliasName, "UTF-8")))
        self.root.after(500, lambda:self.sckt.send(bytes("USER %s %s bla :%s\r\n" % (self.IDENT, self.SERVER, self.REALNAME), "UTF-8")))
        self.textEntry.focus_force()
        self.root.after(8000, self.auto_join_chan)

    def check_pm_commands(self, event=None):
        tab = self.n.tab(self.n.select(), "text")
        textboxinc = self.tabs[tab]['textbox']
        message = self.tabs[tab]['entrybox'].get('1.0','end-1c')
        self.tabs[tab]['entrybox'].delete('1.0', END)
        self.tabs[tab]['entrybox'].focus_force()
        if len(message)>=1 and message[0] == '/':
            self.process_commands(message)
        else:
            self.post_pm_controls(self.aliasName + ':>' + message + '\n', textboxinc)# Post the received text to the window
            self.sckt.send(bytes("PRIVMSG %s %s \r\n" % (tab, ':' + message), "UTF-8"))
        return 'break'

    def process_commands(self, message):
        format = message.split(' ')
        if '/msg' in format:
            type = 'pm'
            message = " ".join(format[2:])
            tab_name = format[1].lower()
            if len(message) < 1:
                messagebox.showinfo(message='You must enter some text after /msg username', icon='warning')
            else:
                self.add_tab(tab_name, type)
                self.tabs[tab_name]['entrybox'].delete('1.0', END)
                self.find_window(tab_name, self.aliasName + ':>' + message + '\n')
                self.sckt.send(bytes("PRIVMSG %s %s \r\n" % (tab_name, ':' + message), "UTF-8")) 
        elif '/join' in message:
            tab_name = format[1].lower()
            type = 'channel'
            self.add_tab(tab_name, type)
        elif '/leave' in message:
            self.leave_channel()
        elif '/nick' in message:
            self.name_change(self.aliasName, message)
        elif '/quit' in message:
            self.shutdownClient()
        else:
            messagebox.showinfo(message='Command not found.', icon='warning')

    def recv_loop(self, connection): # Main receiving loop for all incoming messages
        while True:
            (readable, writable, errored) = select([connection], [], [connection], 0.1)
            if readable:
                readbuffer=""
                readbuffer=readbuffer+self.sckt.recv(1024).decode("UTF-8")
                temp=str.split(readbuffer, "\n")
                readbuffer=temp.pop( )
                for line in temp:
                    line=str.rstrip(line)
                    line=str.split(line)
                    self.root.after_idle(self.iterate_through_incoming, line)

    def iterate_through_incoming(self, line): # Look through the incoming messages for info from the server
        try:
            if line[0] == "PING":# Looks for PING from the server and replies with a PONG
                self.sckt.send(bytes("PONG %s\r\n" % line[1], "UTF-8"))
            elif self.aliasName + '!' in line[0]:
                pass
            elif line[0] == '353' or line[1] == '353': # Looks for NAMES list
                self.build_online_list(line)
            elif line[1] == '401': # Returns warning if user/channel doesn't exist
                messagebox.showinfo(message='No such user/channel %s'% line[3], icon='warning')
            elif line[1] == 'QUIT':
                self.remove_on_quit(line)
            elif line[1] == "PRIVMSG" and line[3] == ':\x01ACTION':
                message = line[3].lstrip(':')
                x = " ".join(line[4:]) # Grabbing everything after the 3rd index and joining the message.
                format_user1 = line[0].strip(':')
                finish_format = format_user1.split('!')
                user = finish_format[0]
                self.find_window(line[2].lower(), '*' + user + ' ' + x + '\n') # Post the received text to the window    
            elif line[1] == "PRIVMSG": # If PRIVMSG is in line[1] position, its a message from a channel or a private message
                self.get_incoming_channel(line)
            elif line[1] == 'JOIN' and self.aliasName not in line[0]:# If JOIN is line[1], a new user joined the channel
                self.get_join_leave_name(line)
            elif line[1] == 'PART' and self.aliasName not in line[0]: # If PART is line[1] a user has left update the online user list
                self.get_join_leave_name(line)
            elif line[1] == 'NICK' and self.aliasName not in line[2]: # If NICK is line[1] a user has changed their name, update the online user list
                self.get_join_leave_name(line)
            elif line[1] == 'NOTICE' and line[2] == self.aliasName: # If line[1] is NOTICE and line[2] is the users name grab that message
                get_tab = line[3].split('[')
                get_tab_finish = get_tab[1].split(']')
                x = " ".join(line[4:]) # Grabbing everything after the 3rd index and join the message.
                self.find_window(get_tab_finish[0].lower(), x + '\n')
            elif line[1] == '328' or line[1] == '332' or line[1] == '333' or line[1] == '366': # Grabs server messages on joining. If the tab name is in line[3], grab the message
                x = " ".join(line[3:]) # Grabbing everything after the 3rd index and join the message.
                self.find_window(line[3].lower(), x + '\n')
            elif ':' in line[0]: # Grabs all message from the server and posts them to the main tab
                x = " ".join(line[3:]) # Grabbing everything after the 1st index and join the message.
                self.post_pm_controls(x + '\n', self.tabs['Server Info']['textbox'])
            else: # Grabs names that come through as a seperate list and rebuilds it and runs it back through this method to be reiterated
                tab = self.n.tab(self.n.select(), "text")
                strayusers = [':placeholder', '353', self.aliasName, '=', tab]
                for item in line:
                    strayusers.append(item)
                self.iterate_through_incoming(strayusers)
        except IndexError: # Some times there is no data in the indexes of the incoming messages
            pass

    def get_incoming_channel(self, line):
        if "#" in line[2]: # Message from channel
            channel = "" # Get the incoming sender
            incomg_msg = line[0].split('!') # Split the message at the !
            channel += incomg_msg[0].lstrip(':') # Strip the : out
            x = " ".join(line[3:]) # Grabbing everything after the 3rd index and join the message.
            self.find_window(line[2].lower(), channel+':>'+ x.lstrip(':') + '\n') # Post the received text to the window  
        else: # Private message from user
            type = 'pm'
            message = line[3].lstrip(':')
            x = " ".join(line[4:]) # Grabbing everything after the 3rd index and joining the message.
            format_sender1 = line[0].strip(':')
            finish_format = format_sender1.split('!')
            user = finish_format[0]
            self.add_tab(user.lower(), type)
            self.find_window(user.lower(), user + ':>' + message + ' ' + x + '\n')

    def add_tab(self, tab_name, type):
        if tab_name not in self.tabs:
            self.tab_generator(tab_name, type)
        else:
            if tab_name == self.n.tab(self.tabs[tab_name]['tab'], "text") and self.n.tab(self.tabs[tab_name]['tab'], "state") == 'hidden' and type == 'channel':
                self.n.tab(self.tabs[tab_name]['tab'], state='normal')
                self.n.select(self.tabs[tab_name]['tab'])
                self.tabs[tab_name]['onlineusers'].delete(1, 'end')
                self.tabs[tab_name]['textbox'].delete(0,'end-1c')
                self.tabs[tab_name]['entrybox'].focus_force()
                self.sckt.send(bytes("JOIN %s\r\n" % tab_name, "UTF-8"))
            elif tab_name == self.n.tab(self.tabs[tab_name]['tab'], "text") and self.n.tab(self.tabs[tab_name]['tab'], "state") == 'normal' and type == 'channel':
                self.n.select(self.tabs[tab_name]['tab'])
                self.tabs[tab_name]['entrybox'].focus_force()

    def tab_generator(self, tab_name, type): # Tab generator for creating channels/pms
        # Create channel tab
        self.tab_name = ttk.Frame(self.n)
        self.tab_name.grid(row=0, column=0, rowspan=2, sticky=N+S+E+W)

        self.receive_user = ScrolledText(self.tab_name,  height=24, width=47, wrap = WORD)
        self.receive_user.grid(row=0, column=0, padx=(10,0), pady=(10,5), sticky=N+S+E+W)
        self.receive_user.config(state=DISABLED)

        self.pm_Entry = ScrolledText(self.tab_name, height=2, width=47, wrap = WORD)
        self.pm_Entry.grid(row=2, column=0, padx=(10,0), pady=(0,10), sticky=N+S+E+W)
        self.pm_Entry.bind('<Return>', self.check_pm_commands)

        if type == 'channel':
            self.pm_users_box = Listbox(self.tab_name, width=12)
            self.pm_users_box.grid(row = 0, column= 1, rowspan=3, padx=(0,10), pady=(10,10), sticky=N+S+E+W)
            self.pm_users_box.insert(0, 'Online [0]')

            self.tabs[tab_name] = {}
            self.tabs[tab_name]['tab'] = self.tab_name
            self.tabs[tab_name]['textbox'] = self.receive_user
            self.tabs[tab_name]['entrybox'] = self.pm_Entry
            self.tabs[tab_name]['onlineusers'] = self.pm_users_box
            self.sckt.send(bytes("JOIN %s\r\n" % tab_name, "UTF-8"))
        else:
            self.pm_Close = Button(self.tab_name, width=7, text='Close tab', command=lambda:self.remove_on_close())
            self.pm_Close.grid(row=0, column=1, padx=(5,5), pady=(5,150), sticky=N+S+E+W)

            self.tabs[tab_name] = {}
            self.tabs[tab_name]['tab'] = self.tab_name
            self.tabs[tab_name]['textbox'] = self.receive_user
            self.tabs[tab_name]['entrybox'] = self.pm_Entry
            self.tabs[tab_name]['onlineusers'] = ''

        Grid.rowconfigure(self.tab_name, 0, weight=1)
        Grid.columnconfigure(self.tab_name, 0, weight=1)

        self.n.add(self.tab_name, text = tab_name)
        self.n.select(self.tab_name)
        self.pm_Entry.focus_force()

    def remove_on_close(self): # Get the current active tab and close it on click
        current_tab = self.n.tab(self.n.select(), "text")
        if current_tab in self.tabs and current_tab != self.SERVER:
            if self.tabs[current_tab]['onlineusers'] == '':
                self.n.hide(self.n.select())
                current_tab = self.n.tab(self.n.select(), "text")
                self.tabs[current_tab]['entrybox'].focus_force()
            else:
                self.n.hide(self.n.select())
                current_tab = self.n.tab(self.n.select(), "text")
                self.tabs[current_tab]['entrybox'].focus_force()
                
    def find_window(self, tab_name, message): # Get the name of the tab so the message gets to the correct tab
        if tab_name == self.n.tab(self.tabs[tab_name]['tab'], "text"):
            if "No such channel" in self.tabs[tab_name]['textbox'].get("1.0",'end-1c'):
                pass
            else:
                self.n.tab(self.tabs[tab_name]['tab'], state='normal') # If the incoming user in the the current tabs change the state of the tab to normal if hidden
                self.post_pm_controls(message, self.tabs[tab_name]['textbox'])# Post the received text to the window

    def name_change(self, user, line): # Handles a name change if a user in the channel changes their name.
        tab_storage = []
        for tabs in self.tabs:
            if self.tabs[tabs]['onlineusers'] == '':
                pass
            else:
                tab_storage.append(tabs)
        for tabs in tab_storage:        
            for item in self.tabs[tabs]['onlineusers'].get(0, 'end'):
                if user == item:
                    incbox = self.tabs[tabs]['textbox']
                    new_user = line[2].split(':')
                    index = self.tabs[tabs]['onlineusers'].get(0, END).index(user) 
                    self.tabs[tabs]['onlineusers'].delete(index)
                    if user in item and user == self.aliasName:
                        new_user = line.split(' ')
                        self.tabs[tabs]['onlineusers'].insert(END, new_user[1])
                        self.post_pm_controls(('*You are now known as %s' % new_user[1]) + '\n', incbox)
                        self.aliasName = new_user[1]
                        self.sckt.send(bytes("NICK %s\r\n" % self.aliasName, "UTF-8"))
                    else:
                        self.tabs[tabs]['onlineusers'].insert(END, new_user[1])
                        self.post_pm_controls('*User %s is now known as %s' % (user, new_user[1]) + '\n', incbox)

    def get_join_leave_name(self, line): # Gets the name of the user if they join, leave, or change their name
        tab = line[2].split(':') # Format the incoming name and remove the ":" and get the channel
        user = "" # Temp storage for incoming sender name    
        incomg_msg = line[0].split('!') # Split is at the '!'
        user += incomg_msg[0].lstrip(":")# Remove the ':' from the string
        if(line[1] == 'JOIN'): # Check if the message is someone joining
            self.add_online_user(user, tab[1])
        elif(line[1] == 'PART'): # Check if the message is someone leaving
            self.remove_online_user(user, tab[0])
        elif(line[1] == 'NICK'): # Check is the message is someone changing their name
            self.name_change(user, line)
            
    def add_online_user(self, user, tab): # Adds users as they join
        inctab = self.tabs[tab]['textbox'] # Tells which tab to update
        self.tabs[tab]['onlineusers'].insert(END, user)  # Add the new user to the online user Listbox
        self.post_pm_controls('*User %s has joined the channel' % user + '\n', inctab) # Post a message to the window that a user had joined       

    def remove_online_user(self, user, tab): # Remove users as they leave an active channel
        inctab = self.tabs[tab.lower()]# Tells which tab to update
        try:
            index = inctab['onlineusers'].get(0,'end').index(user)
            inctab['onlineusers'].delete(index) # Try to remove the user from the onlinelist and post who left
            self.post_pm_controls('User %s has left the channel' % user + '\n', inctab['textbox'])
        except ValueError: # If the user's not in the dictionary list, post who left anyway
            self.post_pm_controls('*User %s has left the channel' % user + '\n', inctab['textbox'])
        try:
            index1 = inctab['onlineusers'].get(0,'end').index('@' + user) # For getting the index if the user is admin
            inctab['onlineusers'].delete(index1)
            self.post_pm_controls('*User %s has left the channel' % user + '\n', inctab['textbox'])
        except ValueError: # If the user's not in the dictionary list, post who left anyway
            pass
            
    def remove_on_quit(self, line): # Remove users as they quit an active channel
        tab_storage = []
        format = line[0].split('!')
        user = format[0].strip(':')
        for tabs in self.tabs:
            if self.tabs[tabs]['onlineusers'] == '':
                pass
            else:
                tab_storage.append(tabs)
        for tabs in tab_storage:        
            for item in self.tabs[tabs]['onlineusers'].get(0, 'end'):
                if user == item:
                    incbox = self.tabs[tabs]['textbox']
                    index = self.tabs[tabs]['onlineusers'].get(0, END).index(user) 
                    self.tabs[tabs]['onlineusers'].delete(index)
                    x = " ".join(line[2:]) 
                    self.post_pm_controls('*User %s has quit. Reason: %s' % (user, x) + '\n', incbox)
                    
    def leave_channel(self): # Called on /leave from user. Leaves the current tab that is focused    
        tab = self.n.tab(self.n.select(), "text")
        if tab == self.SERVER:
            pass
        elif "No such channel" in self.tabs[tab]['textbox'].get("1.0",'end-1c'):
            self.remove_on_close()
        elif self.tabs[tab]['onlineusers'] == '':
            self.remove_on_close()
        else:
            self.sckt.send(bytes("PART %s\r\n" % tab, "UTF-8"))
            self.remove_on_close()

    def build_online_list(self, line):# Builds the online users list
        try:
            if self.tabs[line[4].lower()]['onlineusers'] == '': # If there are no users in that channel/users dictionary, pass
                pass
            else:
                users = [] # Temp storage for incoming names
                first_user = line[5].replace(':', '') # Formats the first username in the list
                users.append(first_user) # add user to temp list
                for items in line[6:]: # Get the rest of the incoming name and add them to the dictionaries users list
                    users.append(items)
                for items in sorted(users):
                    self.tabs[line[4].lower()]['onlineusers'].insert(END, items)
                self.count_online(line[4].lower())
        except KeyError:
            pass

    def count_online(self, tab_name): # counts the online users.
        user_count = self.tabs[tab_name]['onlineusers'].size()
        self.tabs[tab_name]['onlineusers'].delete(0)
        self.tabs[tab_name]['onlineusers'].insert(0, 'Online [%d]' % (user_count - 1))       
        
    def post_pm_controls(self, pm, window):# Handles the state of the tabed text boxes as well as inserting text into the box
        window.config(state=NORMAL)
        window.insert(END, time.strftime("[%I:%M %p]") + pm)
        window.config(state=DISABLED)
        window.see(END)
        
    def shutdownClient(self): # Called on /quit from the user.
        for i in self.n.tabs():
            self.sckt.send(bytes("PART %s\r\n" % self.n.tab(i, "text"), "UTF-8"))
        self.root.destroy()
        
    def auto_join_chan(self):
        if self.Channels:
            get_channels = self.Channels.split(',')
            for item in get_channels:
                self.add_tab(item, 'channel')

    def user_settings(self):
        if not self.parser.has_section("UserSettings"):
            self.parser.add_section('UserSettings')
        self.parser.set('UserSettings', 'NickName', self.aliasName)
        self.parser.set('UserSettings', 'Identity', self.IDENT)
        self.parser.set('UserSettings', 'RealName', self.REALNAME)
        if not self.parser.has_section('AutoJoin'):
            self.parser.add_section('AutoJoin')
        self.parser.set('AutoJoin', 'Channels', self.Channels)
        with open("settings.ini", "w") as config:
            self.parser.write(config)

if __name__ == '__main__': 
    root = Tk()
    app = Window(root)
    root.mainloop()                                 
