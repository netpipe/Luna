import os
import json

from klear.Pretty import Pretty

bufferSize = 64 * 1024


def path_to_klear():
    home = os.path.expanduser("~")
    if not os.path.exists(home + "/klear"):
        os.mkdir(home + "/klear")
    return home + "/klear/"


def print_errors(message):
    print(Pretty.FAIL + message + Pretty.ENDC)


def check_if_user_exists():
    if os.path.isfile(path_to_klear() + "klear.json"):
        return True
    else:
        return False


def get_klear_session():
    klear_session = None
    if os.path.isfile(path_to_klear() + "klear.json"):
        with open(path_to_klear() + "klear.json") as json_file:
            klear_session = json.load(json_file)
    return klear_session


def delete_json(file_name):
    if os.path.isfile(path_to_klear() + file_name):
        os.remove(path_to_klear() + file_name)


def dump_json(file_name, json_data):
    try:
        if not os.path.exists(path_to_klear() + file_name):
            with open(path_to_klear() + file_name, "w+") as outfile:
                json.dump(json_data, outfile)
        if os.path.exists(path_to_klear() + file_name):
            with open(path_to_klear() + file_name, "w+") as outfile:
                json.dump(json_data, outfile)
    except IOError as io_exception:
        print_errors(
            "Could not create room")
        raise IOError(str(io_exception))


def add_room_to_contacts(session_json,room_name):
    listroom = session_json['rooms']
    print('creating room')
    listroom.append(room_name)
    session_json['rooms'] = listroom
    dump_json('klear.json',session_json)


def create_local_settings(user, hostname, port):
    klear = {}
    rooms = []
    rooms.append("General")
    klear["username"] = user
    klear["hostname"] = hostname
    klear["port"] = port
    klear["General"] = hostname + "/" + port
    klear["rooms"] = rooms

    dump_json("klear.json", klear)
