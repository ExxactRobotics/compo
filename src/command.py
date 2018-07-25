import model_expand as model
from model_utils import print_me
from model_test import test_model

import Config
import template
import model_expand as model


def test_command_call(args):
    test_model(args.file)
    pass

def find_command_call(args):
    file = args.files
    bdd = args.bdd

    data = model.file_expand(None, file[0])

    if args.TYPE not in data:
        print("TYPE disponible:", data.keys())
        return

    type_section = data[args.TYPE]
    if args.NAME not in type_section:
        print("NAME disponible:", type_section.keys())
        return

    element = type_section[args.NAME]

    print_me(args.NAME, element)


def shell_command_call(args):
    file = args.file
    data = model.file_expand(None, file[0])
    exit = False

    while exit is False:
        start = "- "
        lines = []
        while True:
            try:
                print(start, end="")
                line = input()
                if line:
                    lines.append(start + line)
                    start = "  "
                else:
                    break
            except EOFError:
                return None

        text = '\n'.join(lines)

        print(text)

        model.str_expand(data, text)


def generate_command_call(args):
    file = args.file

    conf = Config.Configuration_manager.get_conf()
    jenv = template.load_jinja_env(conf)
    data = model.file_expand(None, file[0])
    
    template.generate_all(jenv, conf, data)


def TODO_command_call(args):
    print("TODO: this function is not done, do you want to do it ?")


COMMANDS_MAP = {
    "find": find_command_call,
    "test": test_command_call,
    "generate": generate_command_call,
    "expand": TODO_command_call,
    "shell": shell_command_call,
    "graphical": TODO_command_call
}