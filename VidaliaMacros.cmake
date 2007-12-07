#####################################################################
#  $Id$
# 
#  Vidalia is distributed under the following license:
#
#  Copyright (C) 2006-2007,  Matt Edman, Justin Hipple
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  
#  02110-1301, USA.
#####################################################################


## Search for lrelease
find_program(lrelease_CMD  NAMES lrelease lrelease-qt4 ${QT_BINARY_DIR})
if (NOT lrelease_CMD)
  message(FATAL_ERROR
    "Vidalia could not find lrelease. Please make sure Qt >= 4.1 is installed."
  )
endif(NOT lrelease_CMD)


## Wraps the supplied .ts files in lrelease commands
macro(QT4_ADD_TRANSLATIONS outfiles)
  foreach (it ${ARGN})
    get_filename_component(it ${it} ABSOLUTE)
    get_filename_component(outfile ${it} NAME_WE)

    set(outfile ${CMAKE_CURRENT_BINARY_DIR}/${outfile}.qm)
    add_custom_command(OUTPUT ${outfile}
      COMMAND ${lrelease_CMD}
      ARGS -compress -silent -nounfinished ${it} -qm ${outfile}
      MAIN_DEPENDENCY ${it}
    )
    set(${outfiles} ${${outfiles}} ${outfile})
  endforeach(it)
endmacro(QT4_ADD_TRANSLATIONS)

