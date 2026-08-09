
if host_machine.system() == 'windows'
  executable('unscrambler', 'unscrambler.c')
else
  executable('unscrambler', ['unscrambler.c', '../others/linenoise.c'])
endif