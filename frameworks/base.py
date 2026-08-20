from os.path import join

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
env.SConscript(join(env.subst("$PLATFORM_DIR"), "..", "builder", "frameworks", "base.py"), exports="env")
