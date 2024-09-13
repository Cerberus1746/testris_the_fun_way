from clockwork_reverie_py import Main

from .__version__ import __version__

software: dict[str, str | int] = {
    "name": "FunEngine Editor",
    "version": __version__,
}

main_instance: Main = Main(**software)
main_instance.create_window()
