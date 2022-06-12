import click
from klear import __version__ as VERSION
from klear.entries import *
import pyfiglet
from klear.Pretty import Pretty
from PyInquirer import style_from_dict, Token, prompt
from klear.klear_client import *

__user__ = ""
session_json = {}


def print_banner():
    os.system("cls" if os.name == "nt" else "clear")
    ascii_banner = pyfiglet.figlet_format("klear", font="slant")
    print(ascii_banner)
    print(" === ======= ======= = ======= === ========= ========")
    print(" Clean , light and effective communication. ")
    print(" === ======= ======= = ======= === ========= ======== \n")


def check_connection_to_server(hostname, port):
    print("Attempting to connect to %s on port %s" % (hostname, port))
    try:
        s = socket.socket()
        s.connect((hostname, int(port)))
        print("Connection succeeded")
        s.close()
        return True
    except socket.error as e:
        print("Socket Error: unable to connect please check the server")
        return False
    finally:
        s.close()


def register_new_user():
    print(Pretty.OKGREEN + "Looks like you are a new user . Let's get you started !! \n " + Pretty.ENDC)
    global __user__
    __user__ = click.prompt(Pretty.OKGREEN + "Please enter a user name  " + Pretty.ENDC)
    global hostname
    hostname = click.prompt(Pretty.OKGREEN + "Please enter the klear server hostname  " + Pretty.ENDC)
    global port
    port = click.prompt(Pretty.OKGREEN + "Please enter the klear server port  " + Pretty.ENDC)
    server_check = check_connection_to_server(hostname, port)
    if server_check:
        print(Pretty.OKGREEN + "Everything looks good !! \n " + Pretty.ENDC)
        create_local_settings(__user__, hostname, port)
    else:
        print_errors("Could not connect to the remote klear server..exiting")
        sys.exit(1)


def print_errors(message):
    print(Pretty.FAIL + message + Pretty.ENDC)


style = style_from_dict(
    {
        Token.QuestionMark: "#E91E63 bold",
        Token.Selected: "#673AB7 bold",
        Token.Instruction: "",  # default
        Token.Answer: "#2196f3 bold",
        Token.Question: "",
    }
)


def enter_room(room_name):
    print(
        Pretty.OKGREEN
        + "Connected to room {} !! \n ".format(room_name)
        + Pretty.ENDC
    )


def connect_room(room, user):
    os.system("cls" if os.name == "nt" else "clear")
    enter_room(room)
    if room == 'General':
        client_start(session_json[room], user)
    else:
        client_start(session_json['hostname'] + '/' + session_json['port'], user)


def update_session():
    session_json = get_klear_session()


def list_room_options():
    room_questions = [
        {
            "type": "list",
            "name": "room",
            "message": "what would you like to do  ?",
            "choices": ["Join a room from my contacts", "Join a room", "Create a new room"],
            "filter": lambda val: val
        }
    ]

    room_choice = prompt(room_questions, style=style)
    if room_choice["room"] == "Join a room from my contacts":
        which_room_questions = [
            {
                "type": "list",
                "name": "which_room",
                "message": "select a room to start a session  ?",
                "choices": session_json['rooms'],
                "filter": lambda val: val
            }
        ]
        room_name = prompt(which_room_questions, style=style)
        os.system("cls" if os.name == "nt" else "clear")
        print(
            Pretty.HEADER + "Joined the room " + room_name["which_room"] + Pretty.ENDC
        )
        roomname = '#' + room_name["which_room"]
        connect_room(room_name["which_room"], session_json["username"] + roomname)
    elif room_choice["room"] == "Join a room":
        join_room = click.prompt(Pretty.OKGREEN + "Please enter the room name  " + Pretty.ENDC)
        add_room_to_contacts(session_json, join_room)
        update_session()
        connect_room(join_room, session_json["username"] + '#' + join_room)
    elif room_choice["room"] == "Create a new room":
        new_room = click.prompt(Pretty.OKGREEN + "Please enter a new room name  " + Pretty.ENDC)
        add_room_to_contacts(session_json, new_room)
        update_session()
        connect_room(new_room, session_json["username"] + '#' + new_room)


@click.command()
@click.option("--version", is_flag=True, help="Gives the installed version of klear")
def main(version):
    print_banner()

    if version:
        print(VERSION)
        sys.exit()

    if check_if_user_exists():
        global session_json
        session_json = get_klear_session()
        print(Pretty.HEADER + "Welcome back " + session_json["username"] + Pretty.ENDC)
        general_room = click.prompt(
            Pretty.OKGREEN
            + "Do you want to connect to the general room [Y/N]"
            + Pretty.ENDC
        )
        if general_room == "Y":
            connect_room("General", session_json["username"] + '#General')
        if general_room == "N":
            list_room_options()
        if general_room != "Y" and general_room != "N":
            print_errors("Not a valid option. Please try again.")
            sys.exit(1)
    else:
        register_new_user()
        session_json = get_klear_session()
        print(Pretty.OKBLUE + (" \n Welcome to KLEAR {} , let's get started !! \n ".format(__user__)) + Pretty.ENDC)

        general_room = click.prompt(Pretty.OKGREEN + "Do you want to connect to the general room [Y/N]" + Pretty.ENDC)
        if general_room == "Y":
            connect_room("General", session_json["username"] + '#General')
        if general_room == "N":
            list_room_options()
        if general_room != "Y" and general_room != "N":
            print_errors("Not a valid option. Please try again.")
            sys.exit(1)


if __name__ == "__main__":
    main()
